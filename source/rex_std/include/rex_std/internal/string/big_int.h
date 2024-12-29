#pragma once

#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/memory/memset.h"
#include "rex_std/internal/limits/numeric_limits.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
	inline namespace v1
	{
		namespace internal
		{
      struct big_int
      {
        big_int();
        big_int(const big_int& other);
        big_int& operator=(const big_int& other);

        // 1074 bits are required to represent 2^1074. the smallest representable double value is 2^-1074
        // 2552 bits are required for parsing. this number comes from 10^768, 
        // which is needed for the decimal representation of the smallest denormalized value
        // 2^-1074 uses 752 decimal digits after trimming zeroes, so we have a bit of slack space
        constexpr static uint32 s_element_count = 1074 + 2552 + 54;
        constexpr static uint32 s_element_bits = sizeof(uint32) * rsl::limits_byte::num_bits_per_byte;

        uint32 used;
        uint32 data[s_element_count];
      };

      bool operator==(const big_int& lhs, const big_int& rhs);

      bool operator!=(const big_int& lhs, const big_int& rhs);

      bool operator<(const big_int& lhs, const big_int& rhs);

      bool operator>=(const big_int& lhs, const big_int& rhs);

      big_int make_big_int(uint64 value);

      big_int make_big_int_power_of_two(uint32 power);

      bool is_zero(const big_int& value);

      uint32 bit_scan_reverse(uint32 value);

      uint32 bit_scan_reverse(uint64 value);

      uint32 bit_scan_reverse(const big_int& x);

      // Shifts the high precision integer x by n bits to the left.  Returns true if
      // the left shift was successful; false if it overflowed.  When overflow occurs,
      // the high precision integer is reset to zero.
      bool shift_left(big_int& x, uint32 n);

      // Adds a 32-bit value to the high-precision integer x.  Returns true if the
      // addition was successful; false if it overflowed.  When overflow occurs, the
      // high precision integer is reset to zero.
      bool add(big_int& x, const uint32 value);

      uint32 add_carry(
        uint32& u1,
        const uint32 u2,
        const uint32 u_carry
      );

      uint32 add_multiply_carry(
        uint32& u_add,
        const uint32 u_mul_1,
        const uint32 u_mul_2,
        const uint32 u_carry
      );

      uint32 multiply_core(
        _Inout_updates_all_(multiplicand_count) uint32* const multiplicand,
        uint32    const multiplicand_count,
        uint32    const multiplier
      );


      // Multiplies the high precision multiplicand by a 32-bit multiplier.  Returns
      // true if the multiplication was successful; false if it overflowed.  When
      // overflow occurs, the multiplicand is reset to zero.
      bool multiply(big_int& multiplicand, const uint32 multiplier);

      // This high precision integer division implementation was translated from the
      // implementation of System.Numerics.BigIntegerBuilder.Mul in the .NET Framework
      // sources.  It multiplies the multiplicand by the multiplier and returns true
      // if the multiplication was successful; false if it overflowed.  When overflow
      // occurs, the multiplicand is reset to zero.
      bool multiply(big_int& multiplicand, const big_int& multiplier);

      bool multiply_by_power_of_ten(big_int& x, const uint32 power);

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
      uint32 count_sequential_high_zeroes(const uint32 u);

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
      uint64 multiply_64_32(uint64 const multiplicand, const uint32 multiplier
      );
#endif

      // This high precision integer division implementation was translated from the
      // implementation of System.Numerics.BigIntegerBuilder.ModDivCore in the .NET
      // Framework sources.  It computes both quotient and remainder:  the remainder
      // is stored in the numerator argument, and the least significant 32 bits of the
      // quotient are returned from the function.
      uint64 divide(big_int& numerator, const big_int& denominator
      );

		}
	}
}