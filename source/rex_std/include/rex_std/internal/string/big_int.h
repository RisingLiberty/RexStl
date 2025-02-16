#pragma once

#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/memory/memset.h"
#include "rex_std/internal/limits/numeric_limits.h"
#include "rex_std/bonus/types.h"
#include "rex_std/bit.h"

namespace rsl
{
	inline namespace v1
	{
		namespace internal
		{
      struct big_int
      {
        constexpr big_int()
          : used(0)
          , data()
        {}
        constexpr big_int(const big_int& other)
          : used(other.used)
          , data()
        {
          rsl::memcpy(data, other.data, used * sizeof(uint32));
        }
        constexpr big_int& operator=(const big_int& other)
        {
          used = other.used;
          rsl::memcpy(data, other.data, used * sizeof(uint32));
          return *this;
        }

        // 1074 bits are required to represent 2^1074. the smallest representable double value is 2^-1074
        // 2552 bits are required for parsing. this number comes from 10^768, 
        // which is needed for the decimal representation of the smallest denormalized value
        // 2^-1074 uses 752 decimal digits after trimming zeroes, so we have a bit of slack space
        constexpr static uint32 s_element_count = 1074 + 2552 + 54;
        constexpr static uint32 s_element_bits = sizeof(uint32) * rsl::limits_byte::num_bits_per_byte;

        uint32 used;
        uint32 data[s_element_count];
      };

            constexpr bool operator==(const big_int& lhs, const big_int& rhs)
      {
        if (lhs.used != rhs.used)
          return false;

        for (uint32 i = 0; i != lhs.used; ++i)
        {
          if (lhs.data[i] != rhs.data[i])
            return false;
        }

        return true;
      }

      constexpr bool operator!=(const big_int& lhs, const big_int& rhs)
      {
        return !(rhs == lhs);
      }

      constexpr bool operator<(const big_int& lhs, const big_int& rhs)
      {
        if (lhs.used > rhs.used)
          return false;

        if (lhs.used < rhs.used)
          return true;

        uint32 i = lhs.used - 1;
        for (; i != static_cast<uint32>(-1) && lhs.data[i] == rhs.data[i]; --i)
        {
          // No-op
        }

        if (i == static_cast<uint32>(-1))
          return false;

        if (lhs.data[i] <= rhs.data[i])
          return true;

        return false;
      }

      constexpr bool operator>=(const big_int& lhs, const big_int& rhs)
      {
        return !(lhs < rhs);
      }

      constexpr big_int make_big_int(uint64 value)
      {
        big_int x{};
        x.data[0] = value & 0xffffffff;
        x.data[1] = value >> 32;
        x.used = x.data[1] == 0 ? 1 : 2;
        return x;
      }

      constexpr big_int make_big_int_power_of_two(uint32 power)
      {
        const uint32 one = 1;

        big_int x{};

        const uint32 element_index = power / big_int::s_element_bits;
        const uint32 bit_index = power % big_int::s_element_bits;

        rsl::memset(x.data, 0, element_index * sizeof(uint32));
        x.data[element_index] = (one << bit_index);
        x.used = element_index + 1;

        return x;
      }

      constexpr bool is_zero(const big_int& value)
      {
        return value.used == 0;
      }

      constexpr uint32 bit_scan_reverse(uint64 value)
      {
        uint32 ui32_buff[2] = {};
        rsl::memcpy(ui32_buff, &value, sizeof(value));

        if (value > UINT32_MAX)
        {
          return rsl::bit_width(ui32_buff[1]);
        }
        else
        {
          return rsl::bit_width(ui32_buff[0]);
        }
      }

      constexpr uint32 bit_scan_reverse(const big_int& x)
      {
        if (x.used == 0)
        {
          return 0;
        }

        return (x.used - 1) * big_int::s_element_bits + bit_scan_reverse(x.data[x.used - 1]);
      }

      // Shifts the high precision integer x by n bits to the left.  Returns true if
      // the left shift was successful; false if it overflowed.  When overflow occurs,
      // the high precision integer is reset to zero.
      constexpr bool shift_left(big_int& x, uint32 n)
      {
        const uint32 unit_shift = n / big_int::s_element_bits;
        const uint32 bit_shift = n % big_int::s_element_bits;

        uint64 const one = 1;

        const uint32 msb_bits = bit_shift;
        const uint32 lsb_bits = big_int::s_element_bits - msb_bits;

        const uint32 lsb_mask = static_cast<uint32>((one << lsb_bits) - one);
        const uint32 msb_mask = ~lsb_mask;

        bool const bit_shifts_into_next_unit = bit_shift > (big_int::s_element_bits - bit_scan_reverse(x.data[x.used - 1]));

        bool const unit_shift_will_overflow = x.used + unit_shift > big_int::s_element_count;

        if (unit_shift_will_overflow)
        {
          x = big_int{};
          return false;
        }

        const uint32 newused =
          x.used + unit_shift + static_cast<uint32>(bit_shifts_into_next_unit);

        if (newused > big_int::s_element_count)
        {
          x = big_int{};
          return false;
        }

        for (uint32 destination_index = newused - 1; destination_index != unit_shift - 1; --destination_index)
        {
          const uint32 upper_source_index = destination_index - unit_shift;
          const uint32 lower_source_index = destination_index - unit_shift - 1;

          const uint32 upper_source = upper_source_index < x.used ? x.data[upper_source_index] : 0;
          const uint32 lower_source = lower_source_index < x.used ? x.data[lower_source_index] : 0;

          const uint32 shifted_upper_source = (upper_source & lsb_mask) << msb_bits;
          const uint32 shifted_lower_source = (lower_source & msb_mask) >> lsb_bits;

          const uint32 combined_shifted_source = shifted_upper_source | shifted_lower_source;

          x.data[destination_index] = combined_shifted_source;
        }

        for (uint32 destination_index = 0; destination_index != unit_shift; ++destination_index)
        {
          x.data[destination_index] = 0;
        }

        x.used = newused;

        return true;
      }

      // Adds a 32-bit value to the high-precision integer x.  Returns true if the
      // addition was successful; false if it overflowed.  When overflow occurs, the
      // high precision integer is reset to zero.
      constexpr bool add(big_int& x, const uint32 value)
      {
        if (value == 0)
        {
          return true;
        }

        uint32 carry = value;
        for (uint32 i = 0; i != x.used; ++i)
        {
          uint64 const result = static_cast<uint64>(x.data[i]) + carry;
          x.data[i] = static_cast<uint32>(result);
          carry = static_cast<uint32>(result >> 32);
        }

        if (carry != 0)
        {
          if (x.used < big_int::s_element_count)
          {
            x.data[x.used] = carry;
            ++x.used;
          }
          else
          {
            x = big_int{};
            return false;
          }
        }

        return true;
      }

      constexpr uint32 add_carry(
        uint32& u1,
        const uint32 u2,
        const uint32 u_carry
      )
      {
        uint64 const uu = static_cast<uint64>(u1) + u2 + u_carry;
        u1 = static_cast<uint32>(uu);
        return static_cast<uint32>(uu >> 32);
      }

      constexpr uint32 add_multiply_carry(
        uint32& u_add,
        const uint32 u_mul_1,
        const uint32 u_mul_2,
        const uint32 u_carry
      )
      {
        uint64 const uu_res = static_cast<uint64>(u_mul_1) * u_mul_2 + u_add + u_carry;
        uint32 ui32_buffer[2] = {};
        rsl::memcpy(ui32_buffer, &uu_res, sizeof(uu_res));
        u_add = ui32_buffer[0];

        return ui32_buffer[1];
      }

      constexpr uint32 multiply_core(
        _Inout_updates_all_(multiplicand_count) uint32* const multiplicand,
        uint32    const multiplicand_count,
        uint32    const multiplier
      )
      {
        uint32 carry = 0;
        for (uint32 i = 0; i != multiplicand_count; ++i)
        {
          uint64 const result = static_cast<uint64>(multiplicand[i]) * multiplier + carry;
          multiplicand[i] = static_cast<uint32>(result);
          carry = static_cast<uint32>(result >> 32);
        }

        return carry;
      }


      // Multiplies the high precision multiplicand by a 32-bit multiplier.  Returns
      // true if the multiplication was successful; false if it overflowed.  When
      // overflow occurs, the multiplicand is reset to zero.
      constexpr bool multiply(big_int& multiplicand, const uint32 multiplier)
      {
        if (multiplier == 0)
        {
          multiplicand = big_int{};
          return true;
        }

        if (multiplier == 1)
        {
          return true;
        }

        if (multiplicand.used == 0)
        {
          return true;
        }

        const uint32 carry = multiply_core(multiplicand.data, multiplicand.used, multiplier);
        if (carry != 0)
        {
          if (multiplicand.used < big_int::s_element_count)
          {
            multiplicand.data[multiplicand.used] = carry;
            ++multiplicand.used;
          }
          else
          {
            multiplicand = big_int{};
            return false;
          }
        }

        return true;
      }

      // This high precision integer division implementation was translated from the
      // implementation of System.Numerics.BigIntegerBuilder.Mul in the .NET Framework
      // sources.  It multiplies the multiplicand by the multiplier and returns true
      // if the multiplication was successful; false if it overflowed.  When overflow
      // occurs, the multiplicand is reset to zero.
      constexpr bool multiply(big_int& multiplicand, const big_int& multiplier)
      {
        if (multiplier.used <= 1)
        {
          return multiply(multiplicand, multiplier.data[0]);
        }

        if (multiplicand.used <= 1)
        {
          const uint32 small_multiplier = multiplicand.data[0];
          multiplicand = multiplier;
          return multiply(multiplicand, small_multiplier);
        }

        // We prefer more iterations on the inner loop and fewer on the outer:
        bool const multiplier_is_shorter = multiplier.used < multiplicand.used;
        const uint32* const rgu1 = multiplier_is_shorter ? multiplier.data : multiplicand.data;
        const uint32* const rgu2 = multiplier_is_shorter ? multiplicand.data : multiplier.data;

        const uint32 cu1 = multiplier_is_shorter ? multiplier.used : multiplicand.used;
        const uint32 cu2 = multiplier_is_shorter ? multiplicand.used : multiplier.used;

        big_int result{};
        for (uint32 iu1 = 0; iu1 != cu1; ++iu1)
        {
          const uint32 u_cur = rgu1[iu1];
          if (u_cur == 0)
          {
            if (iu1 == result.used)
            {
              result.data[iu1] = 0;
              result.used = iu1 + 1;
            }

            continue;
          }

          uint32 u_carry = 0;
          uint32 iu_res = iu1;
          for (uint32 iu2 = 0; iu2 != cu2 && iu_res != big_int::s_element_count; ++iu2, ++iu_res)
          {
            if (iu_res == result.used)
            {
              result.data[iu_res] = 0;
              result.used = iu_res + 1;
            }

            u_carry = add_multiply_carry(result.data[iu_res], u_cur, rgu2[iu2], u_carry);
          }

          while (u_carry != 0 && iu_res != big_int::s_element_count)
          {
            if (iu_res == result.used)
            {
              result.data[iu_res] = 0;
              result.used = iu_res + 1;
            }

            u_carry = add_carry(result.data[iu_res++], 0, u_carry);
          }

          if (iu_res == big_int::s_element_count)
          {
            multiplicand = big_int{};
            return false;
          }
        }

        // Store the result in the multiplicand and compute the actual number of
        // elements used:
        multiplicand = result;
        return true;
      }

      // Multiplies the high precision integer x by 10^power.  Returns true if the
      // multiplication was successful; false if it overflowed.  When overflow occurs,
      // the high precision integer is reset to zero.
      constexpr bool multiply_by_power_of_ten(big_int& x, const uint32 power)
      {
        // To improve performance, we use a table of precomputed powers of ten, from
        // 10^10 through 10^380, in increments of ten.  In its unpacked form, as an
        // array of big_int objects, this table consists mostly of zero elements.
        // Thus, we store the table in a packed form, trimming leading and trailing
        // zero elements.  We provide an index that is used to unpack powers from the
        // table, using the function that appears after this function in this file.
        //
        // The minimum value representable with double precision is 5E-324.  With
        // this table we can thus compute most multiplications with a single multiply.
        const uint32 large_power_data[] =
        {
            0x540be400, 0x00000002, 0x63100000, 0x6bc75e2d, 0x00000005, 0x40000000, 0x4674edea, 0x9f2c9cd0,
            0x0000000c, 0xb9f56100, 0x5ca4bfab, 0x6329f1c3, 0x0000001d, 0xb5640000, 0xc40534fd, 0x926687d2,
            0x6c3b15f9, 0x00000044, 0x10000000, 0x946590d9, 0xd762422c, 0x9a224501, 0x4f272617, 0x0000009f,
            0x07950240, 0x245689c1, 0xc5faa71c, 0x73c86d67, 0xebad6ddc, 0x00000172, 0xcec10000, 0x63a22764,
            0xefa418ca, 0xcdd17b25, 0x6bdfef70, 0x9dea3e1f, 0x0000035f, 0xe4000000, 0xcdc3fe6e, 0x66bc0c6a,
            0x2e391f32, 0x5a450203, 0x71d2f825, 0xc3c24a56, 0x000007da, 0xa82e8f10, 0xaab24308, 0x8e211a7c,
            0xf38ace40, 0x84c4ce0b, 0x7ceb0b27, 0xad2594c3, 0x00001249, 0xdd1a4000, 0xcc9f54da, 0xdc5961bf,
            0xc75cabab, 0xf505440c, 0xd1bc1667, 0xfbb7af52, 0x608f8d29, 0x00002a94, 0x21000000, 0x17bb8a0c,
            0x56af8ea4, 0x06479fa9, 0x5d4bb236, 0x80dc5fe0, 0xf0feaa0a, 0xa88ed940, 0x6b1a80d0, 0x00006323,
            0x324c3864, 0x8357c796, 0xe44a42d5, 0xd9a92261, 0xbd3c103d, 0x91e5f372, 0xc0591574, 0xec1da60d,
            0x102ad96c, 0x0000e6d3, 0x1e851000, 0x6e4f615b, 0x187b2a69, 0x0450e21c, 0x2fdd342b, 0x635027ee,
            0xa6c97199, 0x8e4ae916, 0x17082e28, 0x1a496e6f, 0x0002196e, 0x32400000, 0x04ad4026, 0xf91e7250,
            0x2994d1d5, 0x665bcdbb, 0xa23b2e96, 0x65fa7ddb, 0x77de53ac, 0xb020a29b, 0xc6bff953, 0x4b9425ab,
            0x0004e34d, 0xfbc32d81, 0x5222d0f4, 0xb70f2850, 0x5713f2f3, 0xdc421413, 0xd6395d7d, 0xf8591999,
            0x0092381c, 0x86b314d6, 0x7aa577b9, 0x12b7fe61, 0x000b616a, 0x1d11e400, 0x56c3678d, 0x3a941f20,
            0x9b09368b, 0xbd706908, 0x207665be, 0x9b26c4eb, 0x1567e89d, 0x9d15096e, 0x7132f22b, 0xbe485113,
            0x45e5a2ce, 0x001a7f52, 0xbb100000, 0x02f79478, 0x8c1b74c0, 0xb0f05d00, 0xa9dbc675, 0xe2d9b914,
            0x650f72df, 0x77284b4c, 0x6df6e016, 0x514391c2, 0x2795c9cf, 0xd6e2ab55, 0x9ca8e627, 0x003db1a6,
            0x40000000, 0xf4ecd04a, 0x7f2388f0, 0x580a6dc5, 0x43bf046f, 0xf82d5dc3, 0xee110848, 0xfaa0591c,
            0xcdf4f028, 0x192ea53f, 0xbcd671a0, 0x7d694487, 0x10f96e01, 0x791a569d, 0x008fa475, 0xb9b2e100,
            0x8288753c, 0xcd3f1693, 0x89b43a6b, 0x089e87de, 0x684d4546, 0xfddba60c, 0xdf249391, 0x3068ec13,
            0x99b44427, 0xb68141ee, 0x5802cac3, 0xd96851f1, 0x7d7625a2, 0x014e718d, 0xfb640000, 0xf25a83e6,
            0x9457ad0f, 0x0080b511, 0x2029b566, 0xd7c5d2cf, 0xa53f6d7d, 0xcdb74d1c, 0xda9d70de, 0xb716413d,
            0x71d0ca4e, 0xd7e41398, 0x4f403a90, 0xf9ab3fe2, 0x264d776f, 0x030aafe6, 0x10000000, 0x09ab5531,
            0xa60c58d2, 0x566126cb, 0x6a1c8387, 0x7587f4c1, 0x2c44e876, 0x41a047cf, 0xc908059e, 0xa0ba063e,
            0xe7cfc8e8, 0xe1fac055, 0xef0144b2, 0x24207eb0, 0xd1722573, 0xe4b8f981, 0x071505ae, 0x7a3b6240,
            0xcea45d4f, 0x4fe24133, 0x210f6d6d, 0xe55633f2, 0x25c11356, 0x28ebd797, 0xd396eb84, 0x1e493b77,
            0x471f2dae, 0x96ad3820, 0x8afaced1, 0x4edecddb, 0x5568c086, 0xb2695da1, 0x24123c89, 0x107d4571,
            0x1c410000, 0x6e174a27, 0xec62ae57, 0xef2289aa, 0xb6a2fbdd, 0x17e1efe4, 0x3366bdf2, 0x37b48880,
            0xbfb82c3e, 0x19acde91, 0xd4f46408, 0x35ff6a4e, 0x67566a0e, 0x40dbb914, 0x782a3bca, 0x6b329b68,
            0xf5afc5d9, 0x266469bc, 0xe4000000, 0xfb805ff4, 0xed55d1af, 0x9b4a20a8, 0xab9757f8, 0x01aefe0a,
            0x4a2ca67b, 0x1ebf9569, 0xc7c41c29, 0xd8d5d2aa, 0xd136c776, 0x93da550c, 0x9ac79d90, 0x254bcba8,
            0x0df07618, 0xf7a88809, 0x3a1f1074, 0xe54811fc, 0x59638ead, 0x97cbe710, 0x26d769e8, 0xb4e4723e,
            0x5b90aa86, 0x9c333922, 0x4b7a0775, 0x2d47e991, 0x9a6ef977, 0x160b40e7, 0x0c92f8c4, 0xf25ff010,
            0x25c36c11, 0xc9f98b42, 0x730b919d, 0x05ff7caf, 0xb0432d85, 0x2d2b7569, 0xa657842c, 0xd01fef10,
            0xc77a4000, 0xe8b862e5, 0x10d8886a, 0xc8cd98e5, 0x108955c5, 0xd059b655, 0x58fbbed4, 0x03b88231,
            0x034c4519, 0x194dc939, 0x1fc500ac, 0x794cc0e2, 0x3bc980a1, 0xe9b12dd1, 0x5e6d22f8, 0x7b38899a,
            0xce7919d8, 0x78c67672, 0x79e5b99f, 0xe494034e, 0x00000001, 0xa1000000, 0x6c5cd4e9, 0x9be47d6f,
            0xf93bd9e7, 0x77626fa1, 0xc68b3451, 0xde2b59e8, 0xcf3cde58, 0x2246ff58, 0xa8577c15, 0x26e77559,
            0x17776753, 0xebe6b763, 0xe3fd0a5f, 0x33e83969, 0xa805a035, 0xf631b987, 0x211f0f43, 0xd85a43db,
            0xab1bf596, 0x683f19a2, 0x00000004, 0xbe7dfe64, 0x4bc9042f, 0xe1f5edb0, 0x8fa14eda, 0xe409db73,
            0x674fee9c, 0xa9159f0d, 0xf6b5b5d6, 0x7338960e, 0xeb49c291, 0x5f2b97cc, 0x0f383f95, 0x2091b3f6,
            0xd1783714, 0xc1d142df, 0x153e22de, 0x8aafdf57, 0x77f5e55f, 0xa3e7ca8b, 0x032f525b, 0x42e74f3d,
            0x0000000a, 0xf4dd1000, 0x5d450952, 0xaeb442e1, 0xa3b3342e, 0x3fcda36f, 0xb4287a6e, 0x4bc177f7,
            0x67d2c8d0, 0xaea8f8e0, 0xadc93b67, 0x6cc856b3, 0x959d9d0b, 0x5b48c100, 0x4abe8a3d, 0x52d936f4,
            0x71dbe84d, 0xf91c21c5, 0x4a458109, 0xd7aad86a, 0x08e14c7c, 0x759ba59c, 0xe43c8800, 0x00000017,
            0x92400000, 0x04f110d4, 0x186472be, 0x8736c10c, 0x1478abfb, 0xfc51af29, 0x25eb9739, 0x4c2b3015,
            0xa1030e0b, 0x28fe3c3b, 0x7788fcba, 0xb89e4358, 0x733de4a4, 0x7c46f2c2, 0x8f746298, 0xdb19210f,
            0x2ea3b6ae, 0xaa5014b2, 0xea39ab8d, 0x97963442, 0x01dfdfa9, 0xd2f3d3fe, 0xa0790280, 0x00000037,
            0x509c9b01, 0xc7dcadf1, 0x383dad2c, 0x73c64d37, 0xea6d67d0, 0x519ba806, 0xc403f2f8, 0xa052e1a2,
            0xd710233a, 0x448573a9, 0xcf12d9ba, 0x70871803, 0x52dc3a9b, 0xe5b252e8, 0x0717fb4e, 0xbe4da62f,
            0x0aabd7e1, 0x8c62ed4f, 0xceb9ec7b, 0xd4664021, 0xa1158300, 0xcce375e6, 0x842f29f2, 0x00000081,
            0x7717e400, 0xd3f5fb64, 0xa0763d71, 0x7d142fe9, 0x33f44c66, 0xf3b8f12e, 0x130f0d8e, 0x734c9469,
            0x60260fa8, 0x3c011340, 0xcc71880a, 0x37a52d21, 0x8adac9ef, 0x42bb31b4, 0xd6f94c41, 0xc88b056c,
            0xe20501b8, 0x5297ed7c, 0x62c361c4, 0x87dad8aa, 0xb833eade, 0x94f06861, 0x13cc9abd, 0x8dc1d56a,
            0x0000012d, 0x13100000, 0xc67a36e8, 0xf416299e, 0xf3493f0a, 0x77a5a6cf, 0xa4be23a3, 0xcca25b82,
            0x3510722f, 0xbe9d447f, 0xa8c213b8, 0xc94c324e, 0xbc9e33ad, 0x76acfeba, 0x2e4c2132, 0x3e13cd32,
            0x70fe91b4, 0xbb5cd936, 0x42149785, 0x46cc1afd, 0xe638ddf8, 0x690787d2, 0x1a02d117, 0x3eb5f1fe,
            0xc3b9abae, 0x1c08ee6f, 0x000002be, 0x40000000, 0x8140c2aa, 0x2cf877d9, 0x71e1d73d, 0xd5e72f98,
            0x72516309, 0xafa819dd, 0xd62a5a46, 0x2a02dcce, 0xce46ddfe, 0x2713248d, 0xb723d2ad, 0xc404bb19,
            0xb706cc2b, 0x47b1ebca, 0x9d094bdc, 0xc5dc02ca, 0x31e6518e, 0x8ec35680, 0x342f58a8, 0x8b041e42,
            0xfebfe514, 0x05fffc13, 0x6763790f, 0x66d536fd, 0xb9e15076, 0x00000662, 0x67b06100, 0xd2010a1a,
            0xd005e1c0, 0xdb12733b, 0xa39f2e3f, 0x61b29de2, 0x2a63dce2, 0x942604bc, 0x6170d59b, 0xc2e32596,
            0x140b75b9, 0x1f1d2c21, 0xb8136a60, 0x89d23ba2, 0x60f17d73, 0xc6cad7df, 0x0669df2b, 0x24b88737,
            0x669306ed, 0x19496eeb, 0x938ddb6f, 0x5e748275, 0xc56e9a36, 0x3690b731, 0xc82842c5, 0x24ae798e,
            0x00000ede, 0x41640000, 0xd5889ac1, 0xd9432c99, 0xa280e71a, 0x6bf63d2e, 0x8249793d, 0x79e7a943,
            0x22fde64a, 0xe0d6709a, 0x05cacfef, 0xbd8da4d7, 0xe364006c, 0xa54edcb3, 0xa1a8086e, 0x748f459e,
            0xfc8e54c8, 0xcc74c657, 0x42b8c3d4, 0x57d9636e, 0x35b55bcc, 0x6c13fee9, 0x1ac45161, 0xb595badb,
            0xa1f14e9d, 0xdcf9e750, 0x07637f71, 0xde2f9f2b, 0x0000229d, 0x10000000, 0x3c5ebd89, 0xe3773756,
            0x3dcba338, 0x81d29e4f, 0xa4f79e2c, 0xc3f9c774, 0x6a1ce797, 0xac5fe438, 0x07f38b9c, 0xd588ecfa,
            0x3e5ac1ac, 0x85afccce, 0x9d1f3f70, 0xe82d6dd3, 0x177d180c, 0x5e69946f, 0x648e2ce1, 0x95a13948,
            0x340fe011, 0xb4173c58, 0x2748f694, 0x7c2657bd, 0x758bda2e, 0x3b8090a0, 0x2ddbb613, 0x6dcf4890,
            0x24e4047e, 0x00005099,
        };

        struct unpack_index
        {
          uint16_t _offset; // The offset of this power's initial byte in the array
          uint8_t  _zeroes; // The number of omitted leading zero elements
          uint8_t  _size;   // The number of elements present for this power
        };

        unpack_index const large_power_indices[] =
        {
            {    0,  0,  2 }, {    2,  0,  3 }, {    5,  0,  4 }, {    9,  1,  4 },
            {   13,  1,  5 }, {   18,  1,  6 }, {   24,  2,  6 }, {   30,  2,  7 },
            {   37,  2,  8 }, {   45,  3,  8 }, {   53,  3,  9 }, {   62,  3, 10 },
            {   72,  4, 10 }, {   82,  4, 11 }, {   93,  4, 12 }, {  105,  5, 12 },
            {  117,  5, 13 }, {  130,  5, 14 }, {  144,  5, 15 }, {  159,  6, 15 },
            {  174,  6, 16 }, {  190,  6, 17 }, {  207,  7, 17 }, {  224,  7, 18 },
            {  242,  7, 19 }, {  261,  8, 19 }, {  280,  8, 21 }, {  301,  8, 22 },
            {  323,  9, 22 }, {  345,  9, 23 }, {  368,  9, 24 }, {  392, 10, 24 },
            {  416, 10, 25 }, {  441, 10, 26 }, {  467, 10, 27 }, {  494, 11, 27 },
            {  521, 11, 28 }, {  549, 11, 29 },
        };

        uint32 large_power = power / 10;
        while (large_power != 0)
        {
          const uint32 current_power = large_power > _countof(large_power_indices)
            ? _countof(large_power_indices)
            : large_power;

          unpack_index const& index = large_power_indices[current_power - 1];
          big_int multiplier{};
          multiplier.used = index._size + index._zeroes;

          const uint32* const source = large_power_data + index._offset;

          memset(multiplier.data, 0, index._zeroes * sizeof(uint32));
          memcpy(multiplier.data + index._zeroes, source, index._size * sizeof(uint32));

          if (!multiply(x, multiplier))
          {
            x = big_int{};
            return false;
          }

          large_power -= current_power;
        }

        const uint32 small_powers_of_ten[9] =
        {
              10,
             100,
            1000,
            1000 * 10,
            1000 * 100,
            1000 * 1000,
            1000 * 1000 * 10,
            1000 * 1000 * 100,
            1000 * 1000 * 1000
        };

        const uint32 small_power = power % 10;
        if (small_power != 0)
        {
          if (!multiply(x, small_powers_of_ten[small_power - 1]))
          {
            return false;
          }
        }

        return true;
      }

      // The following non-compiled functions are the generators for the big powers of
      // ten table found in multiply_by_power_of_ten().  This code is provided for
      // future use if the table needs to be amended.  Do not remove this code.
      /*
      uint32 count_leading_zeroes(const big_int& x)
      {
          for (uint32 i = 0; i != x.used; ++i)
          {
              if (x.data[i] != 0)
                  return i;
          }

          return 0;
      }

      void generate_table()
      {
          std::vector<uint32>     elements;
          std::vector<unpack_index> indices;

          for (uint32 i = 10; i != 390; i += 10)
          {
              big_int x = make_big_int(1);
              for (uint32 j = 0; j != i; ++j)
              {
                  multiply(x, 10);
              }

              unpack_index index{};
              index._offset = elements.size();
              index._zeroes = count_leading_zeroes(x);
              index._size   = x.used - index._zeroes;

              for (uint32 j = index._zeroes; j != x.used; ++j)
              {
                  elements.push_back(x.data[j]);
              }
              indices.push_back(index);
          }

          printf("static const uint32 large_power_data[] = \n{");
          for (uint32 i = 0; i != elements.size(); ++i)
          {
              printf("%s0x%08x, ", i % 8 == 0 ? "\n    " : "", elements[i]);
          }
          printf("\n};\n");

          printf("static unpack_index const large_power_indices[] = \n{\n");
          for (uint32 i = 0; i != indices.size(); ++i)
          {
              printf("%s{ %4u, %2u, %2u }, ",
                  i % 4 == 0 ? "\n    " : "",
                  indices[i]._offset,
                  indices[i]._zeroes,
                  indices[i]._size);
          }
          printf("};\n");
      }
      */

      // Computes the number of zeroes higher than the most significant set bit in 'u'
      constexpr uint32 count_sequential_high_zeroes(const uint32 u)
      {
        unsigned long result = 0;
        return _BitScanReverse(&result, u) ? 31 - result : 32;
      }

      // PERFORMANCE NOTE:  On x86, for multiplication of a 64-bit unsigned integer by
      // a 32-bit unsigned integer, the compiler will generate a call to _allmul.  For
      // division-heavy conversions, the inline assembly version presented here gives a
      // 10% overall performance improvement (not 10% faster division--10% faster total).
      // This function [1] uses only two 32-bit multiplies instead of the three required
      // for general 64-bit x 64-bit multiplication, and [2] is inlineable, allowing the
      // compile to elide the extreme overhead of calling the _allmul function.
#if defined(_M_IX86) && !defined(_M_HYBRID_X86_ARM64)
      uint64 multiply_64_32(
        uint64 const multiplicand,
        const uint32 multiplier
      )
      {
        __asm
        {
          mov eax, dword ptr[multiplicand + 4]
          mul multiplier

          mov ecx, eax

          mov eax, dword ptr[multiplicand]
          mul multiplier

          add edx, ecx
        }
      }
#else
      constexpr uint64 multiply_64_32(
        uint64 const multiplicand,
        const uint32 multiplier
      )
      {
        return multiplicand * multiplier;
      }
#endif

      // This high precision integer division implementation was translated from the
      // implementation of System.Numerics.BigIntegerBuilder.ModDivCore in the .NET
      // Framework sources.  It computes both quotient and remainder:  the remainder
      // is stored in the numerator argument, and the least significant 32 bits of the
      // quotient are returned from the function.
      constexpr uint64 divide(big_int& numerator, const big_int& denominator
      )
      {
        // If the numerator is zero, then both the quotient and remainder are zero:
        if (numerator.used == 0)
        {
          return 0;
        }

        // If the denominator is zero, then uh oh. We can't divide by zero:
        if (denominator.used == 0)
        {
          _ASSERTE(("Division by zero", false));
          return 0;
        }

        uint32 max_numerator_element_index = numerator.used - 1;
        uint32 max_denominator_element_index = denominator.used - 1;

        // The numerator and denominator are both nonzero.  If the denominator is
        // only one element wide, we can take the fast route:
        if (max_denominator_element_index == 0)
        {
          const uint32 small_denominator = denominator.data[0];

          if (small_denominator == 1)
          {
            const uint32 quotient = numerator.data[0];
            numerator = big_int{};
            return quotient;
          }

          if (max_numerator_element_index == 0)
          {
            const uint32 small_numerator = numerator.data[0];

            numerator = big_int{};
            numerator.data[0] = small_numerator % small_denominator;
            numerator.used = numerator.data[0] > 0 ? 1 : 0;
            return small_numerator / small_denominator;
          }

          // We count down in the next loop, so the last assignment to quotient
          // will be the correct one.
          uint64 quotient = 0;

          uint64 uu = 0;
          for (uint32 iv = max_numerator_element_index; iv != static_cast<uint32>(-1); --iv)
          {
            uu = (uu << 32) | numerator.data[iv];
            quotient = (quotient << 32) + static_cast<uint32>(uu / small_denominator);
            uu %= small_denominator;
          }

          numerator = big_int{};
          numerator.data[1] = static_cast<uint32>(uu >> 32);
          numerator.data[0] = static_cast<uint32>(uu);
          numerator.used = numerator.data[1] > 0 ? 2 : 1;
          return quotient;
        }

        if (max_denominator_element_index > max_numerator_element_index)
        {
          return 0;
        }

        uint32 cu_den = max_denominator_element_index + 1;
        int32_t  cu_diff = max_numerator_element_index - max_denominator_element_index;

        // Determine whether the result will have cu_diff or cu_diff + 1 digits:
        int32_t cu_quo = cu_diff;
        for (int32_t iu = max_numerator_element_index; ; --iu)
        {
          if (iu < cu_diff)
          {
            ++cu_quo;
            break;
          }

          if (denominator.data[iu - cu_diff] != numerator.data[iu])
          {
            if (denominator.data[iu - cu_diff] < numerator.data[iu])
            {
              ++cu_quo;
            }

            break;
          }
        }

        if (cu_quo == 0)
        {
          return 0;
        }

        // Get the uint to use for the trial divisions.  We normalize so the
        // high bit is set:
        uint32 u_den = denominator.data[cu_den - 1];
        uint32 u_den_next = denominator.data[cu_den - 2];

        uint32 cbit_shift_left = count_sequential_high_zeroes(u_den);
        uint32 cbit_shift_right = 32 - cbit_shift_left;
        if (cbit_shift_left > 0)
        {
          u_den = (u_den << cbit_shift_left) | (u_den_next >> cbit_shift_right);
          u_den_next <<= cbit_shift_left;

          if (cu_den > 2)
          {
            u_den_next |= denominator.data[cu_den - 3] >> cbit_shift_right;
          }
        }

        uint64 quotient{};
        for (int32_t iu = cu_quo; --iu >= 0; )
        {
          // Get the high (normalized) bits of the numerator:
          uint32 u_num_hi = (iu + cu_den <= max_numerator_element_index)
            ? numerator.data[iu + cu_den]
            : 0;

          uint64 uu_num = numerator.data[iu + cu_den - 1];
          reinterpret_cast<uint32*>(&uu_num)[1] = u_num_hi;

          uint32 u_num_next = numerator.data[iu + cu_den - 2];
          if (cbit_shift_left > 0)
          {
            uu_num = (uu_num << cbit_shift_left) | (u_num_next >> cbit_shift_right);
            u_num_next <<= cbit_shift_left;

            if (iu + cu_den >= 3)
            {
              u_num_next |= numerator.data[iu + cu_den - 3] >> cbit_shift_right;
            }
          }

          // Divide to get the quotient digit:
          uint64 uu_quo = uu_num / u_den;
          uint64 uu_rem = static_cast<uint32>(uu_num % u_den);

          if (uu_quo > UINT32_MAX)
          {
            uu_rem += u_den * (uu_quo - UINT32_MAX);
            uu_quo = UINT32_MAX;
          }

          while (uu_rem <= UINT32_MAX && uu_quo * u_den_next > ((uu_rem << 32) | u_num_next))
          {
            --uu_quo;
            uu_rem += u_den;
          }

          // Multiply and subtract.  Note that uu_quo may be one too large.  If
          // we have a borrow at the end, we'll add the denominator back on and 
          // decrement uu_quo.
          if (uu_quo > 0)
          {
            uint64 uu_borrow = 0;

            for (uint32 iu2 = 0; iu2 < cu_den; ++iu2)
            {
              uu_borrow += multiply_64_32(uu_quo, denominator.data[iu2]);

              const uint32 u_sub = static_cast<uint32>(uu_borrow);
              uu_borrow >>= 32;
              if (numerator.data[iu + iu2] < u_sub)
              {
                ++uu_borrow;
              }

              numerator.data[iu + iu2] -= u_sub;
            }

            if (u_num_hi < uu_borrow)
            {
              // Add, tracking carry:
              uint32 u_carry = 0;
              for (uint32 iu2 = 0; iu2 < cu_den; ++iu2)
              {
                uint64 const sum =
                  static_cast<uint64>(numerator.data[iu + iu2]) +
                  static_cast<uint64>(denominator.data[iu2]) +
                  u_carry;

                numerator.data[iu + iu2] = static_cast<uint32>(sum);
                u_carry = sum >> 32;
              }

              --uu_quo;
            }

            max_numerator_element_index = iu + cu_den - 1;
          }

          quotient = (quotient << 32) + static_cast<uint32>(uu_quo);
        }

        // Trim the remainder:
        for (uint32 i = max_numerator_element_index + 1; i < numerator.used; ++i)
        {
          numerator.data[i] = 0;
        }

        numerator.used = max_numerator_element_index + 1;
        while (numerator.used != 0 && numerator.data[numerator.used - 1] == 0)
        {
          --numerator.used;
        }

        return quotient;
      }

		}
	}
}