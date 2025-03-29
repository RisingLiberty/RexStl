// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_utils_impl.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/string/character_lookup.h"
#include "rex_std/bonus/string/string_utils.h"
#include "rex_std/bonus/types.h"
#include "rex_std/internal/algorithm/reverse.h"
#include "rex_std/internal/string/big_int.h"
#include "rex_std/internal/iterator/distance.h"
#include "rex_std/internal/iterator/end.h"
#include "rex_std/internal/iterator/random_access_iterator.h"
#include "rex_std/internal/iterator/reverse_iterator.h"
#include "rex_std/internal/optional/optional.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/is_integral.h"
#include "rex_std/internal/type_traits/is_unsigned.h"
#include "rex_std/internal/type_traits/make_unsigned.h"
#include "rex_std/iterator.h"
#include "rex_std/limits.h"

#include <fenv.h>

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      constexpr uint32 parse_digit(char const c)
      {
        if (c >= '0' && c <= '9')
        {
          return static_cast<uint32>(c - '0');
        }

        if (c >= 'a' && c <= 'z')
        {
          return static_cast<uint32>(c - 'a' + 10);
        }

        if (c >= 'A' && c <= 'Z')
        {
          return static_cast<uint32>(c - 'A' + 10);
        }

        return static_cast<uint32>(-1);
      }

      struct floating_point_string
      {
        int32 exponent;
        uint32 mantissa_count;
        uint8 mantissa[768];
        bool is_negative;
      };

      template <typename FloatingType>
      struct floating_type_traits;

      template <>
      struct floating_type_traits<float>
      {
				static constexpr int32 mantissa_bits = limits_32bit::num_mantissa_bits;
				static constexpr int32 exponent_bits = sizeof(float) * limits_byte::num_bits_per_byte - limits_32bit::num_mantissa_bits;

				static constexpr int32 maximum_binary_exponent = limits_32bit::max_binary_exponent - 1;
        static constexpr int32 minimum_binary_exponent = limits_32bit::min_binary_exponent -1;

				static constexpr int32 exponent_bias = 127;

				static constexpr uint32 exponent_mask = (1u << (exponent_bits)) - 1;
				static constexpr uint32 normal_mantissa_mask = (1u << (mantissa_bits)) - 1;
				static constexpr uint32 denormal_mantissa_mask = (1u << (mantissa_bits - 1)) - 1;

				static constexpr uint32 special_nan_mantissa_mask = (1u << (mantissa_bits - 2));

        struct components_type
        {
          uint32 mantissa : mantissa_bits - 1;
          uint32 exponent : exponent_bits;
          uint32 sign : 1;
        };

        static_assert(sizeof(components_type) == sizeof(float), "unexpected components size");
      };

      template <>
      struct floating_type_traits<double>
      {
        static constexpr int32 mantissa_bits = limits_64bit::num_mantissa_bits;
        static constexpr int32 exponent_bits = sizeof(double) * limits_byte::num_bits_per_byte - limits_64bit::num_mantissa_bits;

        static constexpr int32 maximum_binary_exponent = limits_64bit::max_binary_exponent - 1;
        static constexpr int32 minimum_binary_exponent = limits_64bit::min_binary_exponent - 1;

        static constexpr int32 exponent_bias = 1023;

        static constexpr uint64 exponent_mask = (1ui64 << (exponent_bits)) - 1;
        static constexpr uint64 normal_mantissa_mask = (1ui64 << (mantissa_bits)) - 1;
        static constexpr uint64 denormal_mantissa_mask = (1ui64 << (mantissa_bits - 1)) - 1;

        static constexpr uint64 special_nan_mantissa_mask = (1ui64 << (mantissa_bits - 2));

        struct components_type
        {
          uint64 mantissa : mantissa_bits - 1;
          uint64 exponent : exponent_bits;
          uint64 sign : 1;
        };

        static_assert(sizeof(components_type) == sizeof(double), "unexpected components size");
      };

      template <>
      struct floating_type_traits<long double>
      {
        static constexpr int32 mantissa_bits = limits_64bit::num_mantissa_bits;
        static constexpr int32 exponent_bits = sizeof(double) * limits_byte::num_bits_per_byte - limits_64bit::num_mantissa_bits;

        static constexpr int32 maximum_binary_exponent = limits_64bit::max_binary_exponent - 1;
        static constexpr int32 minimum_binary_exponent = limits_64bit::min_binary_exponent - 1;

        static constexpr int32 exponent_bias = 1023;

        static constexpr uint64 exponent_mask = (1ui64 << (exponent_bits)) - 1;
        static constexpr uint64 normal_mantissa_mask = (1ui64 << (mantissa_bits)) - 1;
        static constexpr uint64 denormal_mantissa_mask = (1ui64 << (mantissa_bits - 1)) - 1;

        static constexpr uint64 special_nan_mantissa_mask = (1ui64 << (mantissa_bits - 2));

        struct components_type
        {
          uint64 mantissa : mantissa_bits - 1;
          uint64 exponent : exponent_bits;
          uint64 sign : 1;
        };

        static_assert(sizeof(components_type) == sizeof(double), "unexpected components size");
      };

      template <typename T>
      constexpr T assemble_floating_point_zero(bool isNegative);
      template <typename T>
      constexpr T assemble_floating_point_infinity(bool isNegative);
      template <typename T>
      constexpr T assemble_floating_point_qnan(bool isNegative);
      template <typename T>
      constexpr T assemble_floating_point_snan(bool isNegative);
      template <typename T>
      constexpr T assemble_floating_point_ind();

      // Determines whether a mantissa should be rounded up in the current rounding
      // mode given [1] the value of the least significant bit of the mantissa, [2]
      // the value of the next bit after the least significant bit (the "round" bit)
      // and [3] whether any trailing bits after the round bit are set.
      //
      // The mantissa is treated as an unsigned integer magnitude; the sign is used
      // only to compute the correct rounding direction for directional rounding modes.
      //
      // For this function, "round up" is defined as "increase the magnitude" of the
      // mantissa.  (Note that this means that if we need to round a negative value to
      // the next largest representable value, we return false, because the next
      // largest representable value has a smaller magnitude.)
      constexpr bool should_round_up(
        bool is_negative,
        bool lsb_bit,
        bool round_bit,
        bool has_tail_bits
      )
      {
        // If there are no insignificant set bits, the value is exactly representable
        // and should not be rounded in any rounding mode:
        bool const is_exactly_representable = !round_bit && !has_tail_bits;
        if (is_exactly_representable)
        {
          return false;
        }

        // If there are insignificant set bits, we need to round according to the
        // current rounding mode.  For FE_TONEAREST, we need to handle two cases:
        // we round up if either [1] the value is slightly greater than the midpoint
        // between two exactly representable values or [2] the value is exactly the
        // midpoint between two exactly representable values and the greater of the
        // two is even (this is "round-to-even").
        switch (fegetround())
        {
        case FE_TONEAREST:  return round_bit && (has_tail_bits || lsb_bit);
        case FE_UPWARD:     return !is_negative;
        case FE_DOWNWARD:   return is_negative;
        case FE_TOWARDZERO: return false;
        }

        _ASSERTE(("unexpected rounding mode", false));
        return false;
      }

      // Computes value / 2^shift, then rounds the result according to the current
      // rounding mode.  By the time we call this function, we will already have
      // discarded most digits.  The caller must pass true for has_zero_tail if
      // all discarded bits were zeroes.
      constexpr uint64 right_shift_with_rounding(
        bool     is_negative,
        uint64 value,
        uint32 shift,
        bool     has_zero_tail
      ) throw()
      {
        // If we'd need to shift further than it is possible to shift, the answer
        // is always zero:
        if (shift >= sizeof(uint64) * CHAR_BIT)
        {
          return 0;
        }

        const uint64 extra_bits_mask = (1ui64 << (shift - 1)) - 1;
        const uint64 round_bit_mask = (1ui64 << (shift - 1));
        const uint64 lsb_bit_mask = 1ui64 << shift;

        const bool lsb_bit = (value & lsb_bit_mask) != 0;
        const bool round_bit = (value & round_bit_mask) != 0;
        const bool tail_bits = !has_zero_tail || (value & extra_bits_mask) != 0;

        return (value >> shift) + should_round_up(is_negative, lsb_bit, round_bit, tail_bits);
      }

      // Converts the floating point value [sign] 0.mantissa * 2^exponent into the
      // correct form for FloatingType and stores the result into the result object.
      // The caller must ensure that the mantissa and exponent are correctly computed
      // such that either [1] the most significant bit of the mantissa is in the
      // correct position for the FloatingType, or [2] the exponent has been correctly
      // adjusted to account for the shift of the mantissa that will be required.
      //
      // This function correctly handles range errors and stores a zero or infinity in
      // the result object on underflow and overflow errors, respectively.  This
      // function correctly forms denormal numbers when required.
      //
      // If the provided mantissa has more bits of precision than can be stored in the
      // result object, the mantissa is rounded to the available precision.  Thus, if
      // possible, the caller should provide a mantissa with at least one more bit of
      // precision than is required, to ensure that the mantissa is correctly rounded.
      // (The caller should not round the mantissa before calling this function.)
      template <typename T>
      constexpr T assemble_floating_point_value_t(
        bool   is_negative,
        int32  exponent,
        uint64 mantissa
      )
      {
        using components_type = typename floating_type_traits<T>::components_type;

        components_type result_components{};
        result_components.sign = is_negative;
        result_components.exponent = exponent + floating_type_traits<T>::exponent_bias;
        result_components.mantissa = mantissa;

        // This is a safe cast, without doing UB
        T result{};
        memcpy(&result, &result_components, sizeof(result));

        return result;
      }

      template <typename T>
      constexpr T assemble_floating_point_value(
        uint64 initial_mantissa,
        int32  initial_exponent,
        bool   is_negative,
        bool   has_zero_tail
      )
      {
        // Assume that the number is representable as a normal value.  Compute the
        // number of bits by which we must adjust the mantissa to shift it into the
        // correct position, and compute the resulting base two exponent for the
        // normalized mantissa:
        const uint32 initial_mantissa_bits = bit_scan_reverse(initial_mantissa);
        const int32 normal_mantissa_shift = static_cast<int32>(floating_type_traits<T>::mantissa_bits - initial_mantissa_bits);
        const int32 normal_exponent = initial_exponent - normal_mantissa_shift;

        uint64 mantissa = initial_mantissa;
        int32  exponent = normal_exponent;

        if (normal_exponent > floating_type_traits<T>::maximum_binary_exponent)
        {
          // The exponent is too large to be represented by the floating point
          // type; report the overflow condition:
          return assemble_floating_point_infinity<T>(is_negative);
        }
        else if (normal_exponent < floating_type_traits<T>::minimum_binary_exponent)
        {
          // The exponent is too small to be represented by the floating point
          // type as a normal value, but it may be representable as a denormal
          // value.  Compute the number of bits by which we need to shift the
          // mantissa in order to form a denormal number.  (The subtraction of
          // an extra 1 is to account for the hidden bit of the mantissa that
          // is not available for use when representing a denormal.)
          const int32 denormal_mantissa_shift =
            normal_mantissa_shift +
            normal_exponent +
            floating_type_traits<T>::exponent_bias -
            1;

          // Denormal values have an exponent of zero, so the debiased exponent is
          // the negation of the exponent bias:
          exponent = -floating_type_traits<T>::exponent_bias;

          if (denormal_mantissa_shift < 0)
          {
            // Use two steps for right shifts:  for a shift of N bits, we first
            // shift by N-1 bits, then shift the last bit and use its value to
            // round the mantissa.
            mantissa = right_shift_with_rounding(is_negative, mantissa, -denormal_mantissa_shift, has_zero_tail);

            // If the mantissa is now zero, we have underflowed:
            if (mantissa == 0)
            {
              return assemble_floating_point_zero<T>(is_negative);
            }

            // When we round the mantissa, the result may be so large that the
            // number becomes a normal value.  For example, consider the single
            // precision case where the mantissa is 0x01ffffff and a right shift
            // of 2 is required to shift the value into position. We perform the
            // shift in two steps:  we shift by one bit, then we shift again and
            // round using the dropped bit.  The initial shift yields 0x00ffffff.
            // The rounding shift then yields 0x007fffff and because the least
            // significant bit was 1, we add 1 to this number to round it.  The
            // final result is 0x00800000.
            //
            // 0x00800000 is 24 bits, which is more than the 23 bits available
            // in the mantissa.  Thus, we have rounded our denormal number into
            // a normal number.
            //
            // We detect this case here and re-adjust the mantissa and exponent
            // appropriately, to form a normal number:
            if (mantissa > floating_type_traits<T>::denormal_mantissa_mask)
            {
              // We add one to the denormal_mantissa_shift to account for the
              // hidden mantissa bit (we subtracted one to account for this bit
              // when we computed the denormal_mantissa_shift above).
              exponent =
                initial_exponent -
                (denormal_mantissa_shift + 1) -
                normal_mantissa_shift;
            }
          }
          else
          {
            mantissa <<= denormal_mantissa_shift;
          }
        }
        else
        {
          if (normal_mantissa_shift < 0)
          {
            // Use two steps for right shifts:  for a shift of N bits, we first
            // shift by N-1 bits, then shift the last bit and use its value to
            // round the mantissa.
            mantissa = right_shift_with_rounding(is_negative, mantissa, -normal_mantissa_shift, has_zero_tail);

            // When we round the mantissa, it may produce a result that is too
            // large.  In this case, we divide the mantissa by two and increment
            // the exponent (this does not change the value).
            if (mantissa > floating_type_traits<T>::normal_mantissa_mask)
            {
              mantissa >>= 1;
              ++exponent;

              // The increment of the exponent may have generated a value too
              // large to be represented.  In this case, report the overflow:
              if (exponent > floating_type_traits<T>::maximum_binary_exponent)
              {
                return assemble_floating_point_infinity<T>(is_negative);
              }
            }
          }
          else if (normal_mantissa_shift > 0)
          {
            mantissa <<= normal_mantissa_shift;
          }
        }

        // Unset the hidden bit in the mantissa and assemble the floating point value
        // from the computed components:
        mantissa &= floating_type_traits<T>::denormal_mantissa_mask;

        return assemble_floating_point_value_t<T>(is_negative, exponent, mantissa);
      }

      // This function is part of the fast track for integer floating point strings.
      // It takes an integer and a sign and converts the value into its FloatingType
      // representation, storing the result in the result object.  If the value is not
      // representable, +/-infinity is stored and overflow is reported (since this
      // function only deals with integers, underflow is impossible).
      template <typename T>
      constexpr T assemble_floating_point_value_from_big_integer(const big_int& integer_value, uint32 integer_bits_of_precision, bool is_negative, bool has_nonzero_fractional_part)
      {
        const int32 base_exponent = floating_type_traits<T>::mantissa_bits - 1;

        // Very fast case:  If we have fewer than 64 bits of precision, we can just
        // take the two low order elements from the big_integer:
        if (integer_bits_of_precision <= 64)
        {
          const int32 exponent = base_exponent;

          const uint32 mantissa_low = integer_value.used > 0 ? integer_value.data[0] : 0;
          const uint32 mantissa_high = integer_value.used > 1 ? integer_value.data[1] : 0;
          uint64 const mantissa =
            mantissa_low +
            (static_cast<uint64>(mantissa_high) << 32);

          return assemble_floating_point_value<T>(mantissa, exponent, is_negative, !has_nonzero_fractional_part);
        }

        const uint32 top_element_bits = integer_bits_of_precision % 32;
        const uint32 top_element_index = integer_bits_of_precision / 32;

        const uint32 middle_element_index = top_element_index - 1;
        const uint32 bottom_element_index = top_element_index - 2;

        // Pretty fast case:  If the top 64 bits occupy only two elements, we can
        // just combine those two elements:
        if (top_element_bits == 0)
        {
          const int32 exponent = base_exponent + bottom_element_index * 32;

          uint64 const mantissa =
            integer_value.data[bottom_element_index] +
            (static_cast<uint64>(integer_value.data[middle_element_index]) << 32);

          bool has_zero_tail = !has_nonzero_fractional_part;
          for (uint32 i = 0; i != bottom_element_index; ++i)
          {
            has_zero_tail &= integer_value.data[i] == 0;
          }

          return assemble_floating_point_value<T>(mantissa, exponent, is_negative, has_zero_tail);
        }

        // Not quite so fast case:  The top 64 bits span three elements in the big
        // integer.  Assemble the three pieces:
        const uint32 top_element_mask = (1u << top_element_bits) - 1;
        const uint32 top_element_shift = 64 - top_element_bits; // Left

        const uint32 middle_element_shift = top_element_shift - 32; // Left

        const uint32 bottom_element_bits = 32 - top_element_bits;
        const uint32 bottom_element_mask = ~top_element_mask;
        const uint32 bottom_element_shift = 32 - bottom_element_bits; // Right

        const int32 exponent = base_exponent + bottom_element_index * 32 + top_element_bits;

        uint64 const mantissa =
          (static_cast<uint64>(integer_value.data[top_element_index] & top_element_mask) << top_element_shift) +
          (static_cast<uint64>(integer_value.data[middle_element_index]) << middle_element_shift) +
          (static_cast<uint64>(integer_value.data[bottom_element_index] & bottom_element_mask) >> bottom_element_shift);

        bool has_zero_tail =
          !has_nonzero_fractional_part &&
          (integer_value.data[bottom_element_index] & top_element_mask) == 0;

        for (uint32 i = 0; i != bottom_element_index; ++i)
        {
          has_zero_tail &= integer_value.data[i] == 0;
        }

        return assemble_floating_point_value<T>(mantissa, exponent, is_negative, has_zero_tail);
      }

      // Accumulates the decimal digits in [first_digit, last_digit) into the result
      // high precision integer.  This function assumes that no overflow will occur.
      constexpr void accumulate_decimal_digits_into_big_integer(const uint8* first_digit, const uint8* last_digit, big_int& result)
      {
        // We accumulate nine digit chunks, transforming the base ten string into
        // base one billion on the fly, allowing us to reduce the number of high
        // precision multiplication and addition operations by 8/9.
        uint32 accumulator{};
        uint32 accumulator_count{};
        for (const uint8* it = first_digit; it != last_digit; ++it)
        {
          if (accumulator_count == 9)
          {
            multiply(result, 1000 * 1000 * 1000);
            add(result, accumulator);

            accumulator = 0;
            accumulator_count = 0;
          }

          accumulator *= 10;
          accumulator += *it;
          ++accumulator_count;
        }

        if (accumulator_count != 0)
        {
          multiply_by_power_of_ten(result, accumulator_count);
          add(result, accumulator);
        }
      }

      template <typename T>
      constexpr T convert_decimal_to_float(const floating_point_string& data)
      {
        static_assert(rsl::is_floating_point_v<T>, "T must be a floating point type");

        // A lot of this code is inspired by MSVC's implementation
        // See the following files for more details
        // - <windows sdk>/ucrt/inc/corecrt_internal_big_integer.h
        // - <windows sdk>/ucrt/inc/corecrt_internal_fltintrn.h
        // - <windows sdk>/ucrt/inc/corecrt_internal_strtox.h

        // a 32 bit floating point is stored in memory as followed
        // 1 bit for the sign
        // 8 bits for the exponent, the actual exponent is this value - 127
        // 23 bits for the mantissa
        // to calculate the fractional part that the mantissa represents
        // each N'th bit stands for 1/2^N, starting from N = 1
        // meaning, the first bit represents 1/2^1 == 1/2
        // the second bit represents 1/2^2 == 1/4
        // and so on


        // To generate a mantissa with N bits precission, we need N + 1 bits.
        // The extra bit is used to correctly round the mantissa. If there are fewer bits
        // than this available, then that's okay as in that case we use what we have and
        // we don't need to round
        const uint32 required_bits_of_precision = floating_type_traits<T>::mantissa_bits + 1;

        // The input is of the form 0.mantissa x 10^exponent, where 'mantissa' are
        // the decimal digits of the mantissa and 'exponent' is the decimal exponent.
        // We decompose the mantissa into 2 parts, an integer part and a fractional part.
        // If the exponent is positive, then the integer part consists of the first 'exponent' digits
        // or all the present digits if there are fewer digits.
        // If the exponent is 0 or negative, then the integer part is empty.
        // In either case, the remaining digits form the fractional part of the mantissa.
        const uint32 positive_exponent = (rsl::max)(0, data.exponent);
        const uint32 integer_digits_present = (rsl::min)(positive_exponent, data.mantissa_count);
        const uint32 integer_digits_missing = positive_exponent - integer_digits_present;
        const uint8* first_integer = data.mantissa;
        const uint8* last_integer = data.mantissa + integer_digits_present;

        const uint8* first_fractional = last_integer;
        const uint8* last_fractional = data.mantissa + data.mantissa_count;
        const uint32 fractional_digits_present = static_cast<uint32>(last_fractional - first_fractional);

        rsl::internal::big_int integer_value{};
        rsl::internal::accumulate_decimal_digits_into_big_integer(first_integer, last_integer, integer_value);

        // If we have more digits than allowed in our mantissa
        // create a float representing infinite as we're overflowing
        if (integer_digits_missing > 0)
        {
          if (!rsl::internal::multiply_by_power_of_ten(integer_value, integer_digits_missing))
          {
            return assemble_floating_point_infinity<T>(data.is_negative);
          }
        }

        // At this point, the integer value is stored in the big int.
        // If either (1) the number has more than the required of bits of precision
        // or (2) the mantissa has no fractional part,
        // then we can assemble the result immediately
        // eg 1: 1235678901234567912345.6789
        // eg 2: 123
        const uint32 integer_bits_of_precision = bit_scan_reverse(integer_value);
        if (integer_bits_of_precision >= required_bits_of_precision || fractional_digits_present == 0)
        {
          return assemble_floating_point_value_from_big_integer<T>(
            integer_value,
            integer_bits_of_precision,
            data.is_negative,
            fractional_digits_present != 0);
        }

        // Otherwise, we did nogt get enough bits of precision from the integer part.
        // and the mantissa has a fractional part.
        // We parse the fractional part of the mantisssa to obtain more bits of precision
        // To do this, we convert the fractional part into an actual fraction N/M, 
        // where the numerator N is computed from the digits of the fractional part,
        // and the denominator M is computed as the power of 10 such that N/M is equal to
        // the value of the fractional part of the mantissa
        rsl::internal::big_int fractional_numerator{};
        rsl::internal::accumulate_decimal_digits_into_big_integer(first_fractional, last_fractional, fractional_numerator);

        // Make sure that if we have leading zeroes in the fraction
        // that these are included in the denominator exponent
        const uint32 fractional_denominator_exponent = data.exponent < 0
          ? fractional_digits_present + static_cast<uint32>(-data.exponent)
          : fractional_digits_present;

        rsl::internal::big_int fractional_denominator = rsl::internal::make_big_int(1);
        if (!multiply_by_power_of_ten(fractional_denominator, fractional_denominator_exponent))
        {
          // IF there were any digits in the integer part, it is impossible to underflow.
          // This is because the exponent cannot possible be small enough.
          // So if we underflow here, it is a true underflow and we return 0
          return assemble_floating_point_zero<T>(data.is_negative);
        }

        // Because we are using only the fractional part of the mantissa here,
        // the numerator is guaranteed to be smaller than the denominator
        // We normalize the fraction such that the most significant bit of the numerator
        // is in the same position as the most significant bit in the denominiator.
        // This ensures that when we later shift the numerator N bits to the left,
        // we will produce N bits of precission
        // 
        // The goal here is to reduce the leading zeroes as much as posisble
        // Let's say you have the following fraction: 0.0625
        // A fraction is converted to binary by multiplying it by 2 over and over again
        // if the result is bigger than 1, you store a 1, otherwise you store a 0
        // for the example fractoin this would be the result
        // 0.0625 * 2 = 0.125 = 0b0
        // 0.125 * 2 = 0.25 = 0b0
        // 0.25 * 2 = 0.5 = 0b0
        // 0.5 * 2 = 1.0 = 0b1
        // Result: 0b0001
        // By shifting the most significant bit, those leading zeroes go away
        // Leaving more room for precision, as long as we update our exponent
        const uint32 fractional_numerator_bits = bit_scan_reverse(fractional_numerator);
        const uint32 fractional_denominator_bits = bit_scan_reverse(fractional_denominator);

        const uint32 fractional_shift = fractional_denominator_bits > fractional_numerator_bits
          ? fractional_denominator_bits - fractional_numerator_bits
          : 0;

        if (fractional_shift > 0)
        {
          shift_left(fractional_numerator, fractional_shift);
        }
        const uint32 required_fractional_bits_of_precision = required_bits_of_precision - integer_bits_of_precision;

        uint32 remaining_bits_of_precision_required = required_fractional_bits_of_precision;
        if (integer_bits_of_precision > 0)
        {
          // If the fractional part of the mantissa provides no bits of precision
          // and cannot affect rounding, we can just take whatever bits we got from
          // the integer part of the mantissa. This is the case for numbers with a lot
          // of leading zeroes like 5.0000000000000000000001, where the significant
          // digits of the fractional part start so far to the right that they do not affect 
          // the floating point representation
          // 
          // IF the fractional shift is exactly equal to the number of bits of precision that
          // we require, then no fractional bits will be part of the result, but the result may affect rounding
          // This is e.g. the case for large, odd integers with a fractional part greater than or wqual to 0.5.
          // Thus we need to do the division to correctly round the result.
          if (fractional_shift > remaining_bits_of_precision_required)
          {
            return assemble_floating_point_value_from_big_integer<T>(
              integer_value,
              integer_bits_of_precision,
              data.is_negative,
              fractional_digits_present != 0);
          }

          remaining_bits_of_precision_required -= fractional_shift;
        }

        // If there was no integer part of the mantissa, we will need to compute
        // the exponent from the fractional part. The fractonal exponent is the power
        // of two by which we must multiply the fractional part to move it into the 
        // range [1.0, 2.0). This will either be the same as the shift we computed
        // earlier, or one greater than that shift
        const uint32 fractional_exponent = fractional_numerator < fractional_denominator
          ? fractional_shift + 1
          : fractional_shift;

        shift_left(fractional_numerator, remaining_bits_of_precision_required);
        uint64 fractional_mantissa = divide(fractional_numerator, fractional_denominator);

        bool has_zero_tail = fractional_numerator.used == 0;

        // We may have produced more bits of precisoin than were required.
        // Check and remove any extra bits:
        const uint32 fractional_mantissa_bits = bit_scan_reverse(fractional_mantissa);
        if (fractional_mantissa_bits > required_fractional_bits_of_precision)
        {
          const uint32 shift = fractional_mantissa_bits - required_fractional_bits_of_precision;
          has_zero_tail = has_zero_tail && (fractional_mantissa & ((1ui64 << shift) - 1)) == 0;
          fractional_mantissa >>= shift;
        }

        const uint32 integer_mantissa_low = integer_value.used > 0 ? integer_value.data[0] : 0;
        const uint32 integer_mantissa_high = integer_value.used > 1 ? integer_value.data[1] : 0;
        const uint64 integer_mantissa = integer_mantissa_low + (static_cast<uint64>(integer_mantissa_high) << sizeof(integer_mantissa_low) * rsl::limits_byte::num_bits_per_byte);

        const uint64 complete_mantissa = (integer_mantissa << required_fractional_bits_of_precision) + fractional_mantissa;

        // Compute the final exponent:
        // * If the mantissa had an integer part, then the exponent is one less than the number
        // of bits we obtained from the integer part. IT's one less because we are converting
        // to the form 1.11111 with one 1 to the left of the decimal point.
        // * If the mantissa had no integer part, then the exponent is the fractional exponent that we computed
        // Then, in both cases, we subtract an additional one from the exponent,
        // to account for the fact that we've generated an extra bit of precision, for use in rounding
        const int32 final_exponent = integer_bits_of_precision > 0
          ? integer_bits_of_precision - 2
          : -static_cast<int32>(fractional_exponent) - 1;

        return assemble_floating_point_value<T>(complete_mantissa, final_exponent, data.is_negative, has_zero_tail);
      }

      template <typename T>
      constexpr T convert_hexadecimal_to_float(const floating_point_string& data)
      {
        static_assert(rsl::is_floating_point_v<T>, "T must be a floating point type");

        uint64 mantissa = 0;
        int32 exponent = data.exponent + floating_type_traits<T>::mantissa_bits - 1;

        const uint8* mantissa_last = data.mantissa + data.mantissa_count;
        const uint8* mantissa_it = data.mantissa;

        while (mantissa_it != mantissa_last && mantissa <= floating_type_traits<T>::normal_mantissa_mask)
        {
          mantissa *= 16;
          mantissa += *mantissa_it++;
          exponent -= 4; // The exponent is in binary; log2(16) == 4
        }

        bool has_zero_tail = true;
        while (mantissa_it != mantissa_last && has_zero_tail)
        {
          has_zero_tail = has_zero_tail && *mantissa_it++ == 0;
        }

        return assemble_floating_point_value<T>(mantissa, exponent, data.is_negative, has_zero_tail);
      }

      template <typename T>
      constexpr T assemble_floating_point_zero(bool isNegative)
      {
        static_assert(rsl::is_floating_point_v<T>, "T must be a floating point type");

        using components_type = typename floating_type_traits<T>::components_type;

        components_type result_components{};
        result_components.sign = isNegative ? 1 : 0;
        result_components.exponent = 0;
        result_components.mantissa = 0;

        // This is a safe cast, without doing UB
        T result{};
        memcpy(&result, &result_components, sizeof(result));

        return result;
      }
      template <typename T>
      constexpr T assemble_floating_point_infinity(bool isNegative)
      {
        static_assert(rsl::is_floating_point_v<T>, "T must be a floating point type");

        using components_type = typename floating_type_traits<T>::components_type;

        components_type result_components{};
        result_components.sign = isNegative ? 1 : 0;
        result_components.exponent = floating_type_traits<T>::exponent_mask;
        result_components.mantissa = 0;

        // This is a safe cast, without doing UB
        T result{};
        memcpy(&result, &result_components, sizeof(result));

        return result;
      }
      template <typename T>
      constexpr T assemble_floating_point_qnan(bool isNegative)
      {
        static_assert(rsl::is_floating_point_v<T>, "T must be a floating point type");

        using components_type = typename floating_type_traits<T>::components_type;

        components_type result_components{};
        result_components.sign = isNegative ? 1 : 0;
        result_components.exponent = floating_type_traits<T>::exponent_mask;
        result_components.mantissa = floating_type_traits<T>::denormal_mantissa_mask;

        // This is a safe cast, without doing UB
        T result{};
        memcpy(&result, &result_components, sizeof(result));

        return result;
      }
      template <typename T>
      constexpr T assemble_floating_point_snan(bool isNegative)
      {
        static_assert(rsl::is_floating_point_v<T>, "T must be a floating point type");

        using components_type = typename floating_type_traits<T>::components_type;

        components_type result_components{};
        result_components.sign = isNegative ? 1 : 0;
        result_components.exponent = floating_type_traits<T>::exponent_mask;
        result_components.mantissa = 1;

        // This is a safe cast, without doing UB
        T result{};
        memcpy(&result, &result_components, sizeof(result));

        return result;
      }
      template <typename T>
      constexpr T assemble_floating_point_ind()
      {
        static_assert(rsl::is_floating_point_v<T>, "T must be a floating point type");

        using components_type = typename floating_type_traits<T>::components_type;

        components_type result_components{};
        result_components.sign = 1;
        result_components.exponent = floating_type_traits<T>::exponent_mask;
        result_components.mantissa = floating_type_traits<T>::special_nan_mantissa_mask;

        // This is a safe cast, without doing UB
        T result{};
        memcpy(&result, &result_components, sizeof(result));

        return result;
      }

      enum class floating_point_parse_result_metadata
      {
        decimal_digits,
        hexadecimal_digits,

        zero,
        infinity,
        qnan,
        snan,
        indeterminate,

        no_digits,
        underflow,
        overflow
      };
      struct floating_point_parse_result
      {
        floating_point_parse_result_metadata metadata;
        floating_point_string fp_string;
      };
      template <typename Character>
      bool __cdecl parse_next_characters_from_source(const Character* uppercase, const Character* lowercase, size_t count, const Character* str)
      {
        for (size_t i = 0; i != count; ++i)
        {
          Character c = *str;
          if (c != uppercase[i] && c != lowercase[i])
          {
            return false;
          }

          ++str;
        }

        return true;
      }
      template <typename T, typename Iterator, typename IteratorPointer>
      floating_point_parse_result parse_floating_point_possible_infinity(bool isNegative, Iterator str, IteratorPointer strEnd)
      {
        using underlying_pointer_type = typename rsl::iterator_traits<decltype(str)>::value_type;

        floating_point_parse_result res{};

        static const underlying_pointer_type inf_uppercase[] = { 'I', 'N', 'F' };
        static const underlying_pointer_type inf_lowercase[] = { 'i', 'n', 'f' };
        static const underlying_pointer_type infinity_uppercase[] = { 'I', 'N', 'I', 'T', 'Y' };
        static const underlying_pointer_type infinity_lowercase[] = { 'i', 'n', 'i', 't', 'y' };
        if (parse_next_characters_from_source(inf_uppercase, inf_lowercase, sizeof(inf_uppercase), str))
        {
          if (strEnd)
          {
            *strEnd = (underlying_pointer_type*)str + sizeof(inf_uppercase);
          }
          res.fp_string.is_negative = isNegative;
          res.metadata = floating_point_parse_result_metadata::infinity;
          return res;
        }
        else if (parse_next_characters_from_source(infinity_uppercase, infinity_lowercase, sizeof(infinity_uppercase), str))
        {
          if (strEnd)
          {
            *strEnd = (underlying_pointer_type*)str + sizeof(infinity_uppercase);
          }
          res.metadata = floating_point_parse_result_metadata::infinity;
          return res;
        }

        res.metadata = floating_point_parse_result_metadata::no_digits;
        return res;
      }
      template <typename Character>
      bool __cdecl parse_floating_point_possible_nan_is_snan(const Character* str)
      {
        static Character const uppercase[] = { 'S', 'N', 'A', 'N', ')' };
        static Character const lowercase[] = { 's', 'n', 'a', 'n', ')' };
        return parse_next_characters_from_source(uppercase, lowercase, sizeof(uppercase), str);
      }

      template <typename Character>
      bool __cdecl parse_floating_point_possible_nan_is_ind(const Character* str)
      {
        static Character const uppercase[] = { 'I', 'N', 'D', ')' };
        static Character const lowercase[] = { 'i', 'n', 'd', ')' };
        return parse_next_characters_from_source(uppercase, lowercase, sizeof(uppercase), str);
      }
      template <typename T, typename Iterator, typename IteratorPointer>
      floating_point_parse_result parse_floating_point_possible_nan(bool isNegative, Iterator str, IteratorPointer strEnd)
      {
        using underlying_pointer_type = typename rsl::iterator_traits<decltype(str)>::value_type;
        floating_point_parse_result res{};
        res.fp_string.is_negative = isNegative;

        static const underlying_pointer_type uppercase[] = { 'N', 'A', 'N' };
        static const underlying_pointer_type lowercase[] = { 'n', 'a', 'n' };
        if (!parse_next_characters_from_source(uppercase, lowercase, sizeof(uppercase), str))
        {
          res.metadata = floating_point_parse_result_metadata::no_digits;
          return res;
        }

        if (*str != '(')
        {
          if (strEnd)
          {
            *strEnd = (underlying_pointer_type*)str + sizeof(uppercase);
          }
          res.metadata = floating_point_parse_result_metadata::qnan;
          return res;
        }

        // advance past the left parenthesis
        ++str;

        // After we've parsed a left parenthesis, test to see whether the parenthesized
        // string represents a signaling NaN "(SNAN)" or an indeterminate "(IND)".  If
        // so, we return the corresponding kind of NaN:
        if (parse_floating_point_possible_nan_is_snan(str))
        {
          if (strEnd)
          {
            *strEnd = (underlying_pointer_type*)str + 5; // 5 = "SNAN)"
          }
          res.metadata = floating_point_parse_result_metadata::snan;
          return res;
        }

        if (parse_floating_point_possible_nan_is_ind(str))
        {
          if (strEnd)
          {
            *strEnd = (underlying_pointer_type*)str + 4; // 4 = "IND)"
          }
          res.metadata = floating_point_parse_result_metadata::indeterminate;
          return res;
        }

        // Otherwise, we didn't match one of the two special parenthesized strings.
        // Keep eating chracters until we come across the right parenthesis or the
        // end of the character sequence:
        while (*str != ')' && *str != '\0')
        {
          if (!is_xdigit(*str) && *str != '_')
          {
            if (strEnd)
            {
              *strEnd = (underlying_pointer_type*)str;
            }
            res.metadata = floating_point_parse_result_metadata::qnan;
            return res;
          }

          ++str;
        }

        if (*str == ')')
        {
          ++str;
        }

        if (strEnd)
        {
          *strEnd = (underlying_pointer_type*)str;
        }
        res.metadata = floating_point_parse_result_metadata::qnan;
        return res;
      }
      template <typename T, typename Iterator, typename IteratorPointer>
      floating_point_parse_result parse_floating_point(Iterator str, IteratorPointer strEnd)
      {
        floating_point_parse_result res{};
        using underlying_pointer_type = typename rsl::iterator_traits<decltype(str)>::value_type;
        if (strEnd)
        {
          *strEnd = (underlying_pointer_type*)str;
        }

        // If a nullptr is passed in, we return early, indicating we didn't parse any digits
        if (str == nullptr)
        {
          res.metadata = floating_point_parse_result_metadata::no_digits;
          return res;
        }

        auto c = str;

        // Skip over all leading white spaces
        while (is_space(*c))
        {
          ++c;
        }

        res.fp_string.is_negative = *c == '-';
        if (*c == '-' || *c == '+')
        {
          ++c;
        }

        // Handle the special cases first
        // * INF or INFINITY
        // * NAN and NAN(...)
        if (*c == 'i' || *c == 'I')
        {
          return internal::parse_floating_point_possible_infinity<T>(res.fp_string.is_negative, c, strEnd);
        }
        if (*c == 'n' || *c == 'N')
        {
          return internal::parse_floating_point_possible_nan<T>(res.fp_string.is_negative, c, strEnd);
        }

        // Detect if the string starts with "0x"
        // in which case, it's hexadecimal
        bool is_hex = false;
        auto one_after_first_digit = c + 1;
        if (*c == '0')
        {
          if (c[1] == 'x' || c[1] == 'X')
          {
            is_hex = true;
            c += 2;
          }
        }

        uint8* mantissa_first = res.fp_string.mantissa;
        const uint8* mantissa_last = res.fp_string.mantissa + sizeof(res.fp_string.mantissa);
        uint8* mantissa_it = mantissa_first;

        // The exponent adjustment holds the number of digits in the mantissa buffer
        // that appeared before the radix point. It's positive for number strings
        // with a ninteger component and negative for number strings without it
        int32 exponent_adjustment = 0;

        // Track whether we've seen any digits or not, so we know we successfully parsed something
        bool found_digits = false;

        // skip past any leading zeroes in the mantissa
        while (*c == '0')
        {
          found_digits = true;
          ++c;
        }

        // scan the integer part of the mantissa
        while (*c)
        {
          const uint32 max_digit_value = is_hex
            ? 0xf
            : 9;

          const uint32 digit_value = parse_digit(*c);
          if (digit_value > max_digit_value)
          {
            break;
          }

          found_digits = true;
          if (mantissa_it != mantissa_last)
          {
            *mantissa_it++ = static_cast<uint8>(digit_value);
          }

          ++exponent_adjustment;
          ++c;
        }

        const char8 radix_point = '.';
        if (*c == radix_point)
        {
          ++c;

          // If we haven't yet scanned any non zero digits,
          // continue skipping over zeroes
          // updating the exponent adjustment to account for zeroes we are skipping
          if (mantissa_it == mantissa_first)
          {
            while (*c == '0')
            {
              found_digits = true;
              --exponent_adjustment;
              ++c;
            }
          }

          while (*c)
          {
            const uint32 max_digit_value = is_hex
              ? 0xf
              : 9;

            const uint32 digit_value = parse_digit(*c);
            if (digit_value > max_digit_value)
            {
              break;
            }

            found_digits = true;
            if (mantissa_it != mantissa_last)
            {
              *mantissa_it++ = static_cast<uint8>(digit_value);
            }

            ++c;
          }
        }

        // Early our if not digits were found at this point
        if (!found_digits)
        {
          // If we did deect a "0x" or "0X", the prefix for a hex number
          // but we didn't encounter any digits after
          // What we actually parsed was a '0', part of a decimal number
          // and an 'x', which is part of whatever comes after our number
          // This means, if we detected our string is in hex at this point
          // but no other character can be parsed, we should return 0 instead
          if (is_hex)
          {
            if (strEnd)
            {
              *strEnd = (underlying_pointer_type*)one_after_first_digit;
            }
            res.metadata = floating_point_parse_result_metadata::zero;
          }
          // In all other cases, we failed to parse any digit in the string
          else
          {
            res.metadata = floating_point_parse_result_metadata::no_digits;
          }

          return res;
        }

        // Detect if we're using the notation with an exponent or not
        bool has_exponent = false;
        switch (*c)
        {
        case 'e':
        case 'E':
          has_exponent = !is_hex;
          break;

        case 'p':
        case 'P':
          has_exponent = is_hex;
          break;
        }

        const int32 max_exponent = 5200;
        const int32 min_exponent = -5200;
        int32 exponent = 0;
        if (has_exponent)
        {
          ++c;
          const bool is_exponent_negative = *c == '-';
          if (*c == '+' || *c == '-')
          {
            ++c;
          }

          bool has_exponent_digits = false;
          // Skip any leading zeroes of the exponent
          while (*c == '0')
          {
            has_exponent_digits = true;
            ++c;
          }

          const uint32 exponent_base = 10;
          while (*c)
          {
            const uint32 digit_value(parse_digit(*c));
						// The exponent must always be in decimal format
						// meaning that it's max value is always 9
						if (digit_value >= exponent_base)
						{
							break;
						}

						has_exponent_digits = true;
						exponent = exponent * exponent_base + digit_value;
            if (exponent > max_exponent)
            {
              exponent = max_exponent + 1;
              break;
            }

            ++c;
					}

          // If the exponent is too large, skip over the remaining exponent digits
          // so we can correctly update the end pointer
          while (parse_digit(*c) < exponent_base)
          {
            ++c;
          }

          if (is_exponent_negative)
          {
            exponent = -exponent;
          }

          // If the exponent has no digits, the float is invalid and we should return
          if (!has_exponent_digits)
          {
            res.metadata = floating_point_parse_result_metadata::no_digits;
            return res;
          }
        }

        // After this point, we've scanned the entire string for everything we need to look for
        // We just need to prepare the output result now
        if (strEnd)
        {
          *strEnd = (underlying_pointer_type*)c;
        }

        // Remove trailing zeroes from the mantissa
        while (mantissa_it != mantissa_first && *(mantissa_it - 1) == 0)
        {
          --mantissa_it;
        }

        // If the mantissa buffer is empty, the mantissa was compossed of all zeroes
        // meaning the mantissa is 0. All strings with a mantissa of 0 are of a floating
        // point value of 0, regardless of what their exponent is.
        // Keep in mind that the mantissa parsed here is of the form of
        // 0.mantissa, unlike how a floating point's mantissa is used, which is stored as 1.mantissa
        if (mantissa_it == mantissa_first)
        {
          res.metadata = floating_point_parse_result_metadata::zero;
          return res;
        }

        // Before we adjust the exponent, handle the case where we detected a wildly
        // out of range exponent during parsing, and clamping the value
        if (exponent > max_exponent)
        {
          res.metadata = floating_point_parse_result_metadata::overflow;
          return res;
        }
        if (exponent < min_exponent)
        {
          res.metadata = floating_point_parse_result_metadata::underflow;
          return res;
        }

        // In a hexadecimal constant, the exponent is a base of 2 exponent.
        // The exponent adjustment computed during parsing has the same base as the mantissa
        // so 16 for hexadecimal floating point constants. We therefore need to scale
        // the base 16 multiplier to base 2 by multiplying by log2(16)
        const int32 exponent_adjustment_multiplier = is_hex
          ? 4
          : 1;

        exponent += exponent_adjustment * exponent_adjustment_multiplier;

        // Verify that after the adjustment the exponent isn't wildly out of range.
        // If it is, it isn't representable in any supported floating point format.
        if (exponent > max_exponent)
        {
          res.metadata = floating_point_parse_result_metadata::overflow;
          return res;
        }
        if (exponent < min_exponent)
        {
          res.metadata = floating_point_parse_result_metadata::underflow;
          return res;
        }

        res.fp_string.exponent = exponent;
        res.fp_string.mantissa_count = static_cast<uint32>(mantissa_it - mantissa_first);
        res.metadata = is_hex
          ? floating_point_parse_result_metadata::hexadecimal_digits
          : floating_point_parse_result_metadata::decimal_digits;

        return res;
      }
    }

    RSL_NO_DISCARD constexpr tchar to_wide_char(char8 chr)
    {
      return static_cast<tchar>(chr);
    }
    RSL_NO_DISCARD constexpr char8 to_ascii(tchar chr)
    {
      return static_cast<char8>(chr);
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_letter(Iterator letter)
    {
      return is_upper(letter) || is_lower(letter);
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_sign(Iterator sign)
    {
      return sign == '-' || sign == '+';
    }

    RSL_NO_DISCARD constexpr bool is_multibyte(char8 c)
    {
      return (c & 0x80) != 0; // NOLINT(readability-magic-numbers, hicpp-signed-bitwise)
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr card32 ctoi(Iterator digit)
    {
      return digit - '0';
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr card32 string_length(const Iterator* str)
    {
      static_assert(is_character_v<Iterator>, "argument is not of character type");

      card32 length = 0;
      while(*str)
      {
        str++;
        ++length;
      }
      return length;
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool string_compare(const Iterator* str, card32 length, bool (*stringCompareFunc)(Iterator))
    {
      for(card32 i = 0; i < length; ++i)
      {
        if(!stringCompareFunc(str[i]))
          return false;
      }

      return true;
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool string_equals(const Iterator* lhs, card32 lhsLength, const Iterator* rhs, card32 rhsLength)
    {
      if(lhsLength != rhsLength)
        return false;

      for(card32 i = 0; i < lhsLength; ++i)
      {
        if(lhs[i] != rhs[i])
          return false;
      }

      return true;
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool string_equals(const Iterator* lhs, const Iterator* rhs, card32 rhsLength)
    {
      for(card32 i = 0; i < rhsLength; ++i)
      {
        if(lhs[i] != rhs[i])
          return false;
      }

      return true;
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool string_equals_case_insensitive(const char* lhs, card32 lhsLength, const Iterator* rhs, card32 rhsLength)
    {
      if(lhsLength != rhsLength)
        return false;

      for(card32 i = 0; i < lhsLength; ++i)
      {
        Iterator lhs_c = to_lower(lhs[i]);
        Iterator rhs_c = to_lower(rhs[i]);

        if(lhs_c != rhs_c)
        {
          return false;
        }
      }

      return true;
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr int32 string_lex_compare(const char* lhs, const char* rhs, card32 count)
    {
      return rsl::memcmp(lhs, rhs, count);
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool ends_with(const Iterator* str, card32 strLength, const Iterator* suffix, card32 suffixLength)
    {
      if(strLength < suffixLength)
      {
        return false;
      }

      const char* start = str + (strLength - suffixLength);

      return string_equals(start, suffixLength, suffix, suffixLength);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool ends_with(const Iterator* str, const Iterator* suffix)
    {
      card32 str_length    = string_length(str);
      card32 suffix_length = string_length(suffix);

      return ends_with(str, str_length, suffix, suffix_length);
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool starts_with(const Iterator* str, card32 strLength, const Iterator* prefix, card32 prefixLength)
    {
      if(strLength < prefixLength)
      {
        return false;
      }

      return string_equals(str, prefixLength, prefix, prefixLength);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool starts_with(const Iterator* str, const Iterator* prefix)
    {
      card32 str_length    = string_length(str);
      card32 prefix_length = string_length(prefix);

      return starts_with(str, str_length, prefix, prefix_length);
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_letters(const Iterator* letters, card32 length)
    {
      return string_compare(letters, length, is_letter);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_letters(const Iterator* letters)
    {
      card32 length = string_length(letters);
      return is_letters(letters, length);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_digits(const Iterator* digits, card32 length)
    {
      return (is_sign(*digits) && string_compare(digits + 1, length - 1, is_digit)) || string_compare(digits, length, is_digit);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_digits(const Iterator* digits)
    {
      card32 length = string_length(digits);
      return (is_sign(*digits) && string_compare(digits + 1, length - 1, is_digit)) || string_compare(digits, length, is_digit);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_digitsf(const Iterator* digits, card32 length)
    {
      return (is_sign(*digits) && string_compare(digits + 1, length - 1, is_digitf)) || string_compare(digits, length, is_digitf);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_digitsf(const Iterator* digits)
    {
      card32 length = string_length(digits);
      return (is_sign(*digits) && string_compare(digits + 1, length - 1, is_digitf)) || string_compare(digits, length, is_digitf);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_nan(const Iterator* digits, card32 length)
    {
      return !is_digits(digits, length);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_nan(const Iterator* digits)
    {
      card32 length = string_length(digits);
      return is_nan(digits, length);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_nanf(const Iterator* digits, card32 length)
    {
      return !is_digitsf(digits, length);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_nanf(const Iterator* digits)
    {
      card32 length = string_length(digits);
      return !is_digitsf(digits, length);
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_lower(const Iterator* letters, card32 length)
    {
      return string_compare(letters, length, is_lower);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_lower(const Iterator* letters)
    {
      card32 length = string_length(letters);
      return string_compare(letters, length, is_lower);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_upper(const Iterator* letters, card32 length)
    {
      return string_compare(letters, length, is_upper);
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr bool is_upper(const Iterator* letters)
    {
      card32 length = string_length(letters);
      return string_compare(letters, length, is_upper);
    }

    template <typename ConstIterator, typename Iterator>
    constexpr void to_lower(const ConstIterator str, Iterator buf, card32 length)
    {
      for(card32 i = 0; i < length; ++i)
      {
        buf[i] = to_lower(str[i]);
      }
    }

    template <typename Iterator, card32 Size>
    constexpr void to_lower(const Iterator str, Iterator (&buf)[Size]) // NOLINT(modernize-avoid-c-arrays)
    {
      to_lower(str, buf, Size - 1);
    }
    template <typename ConstIterator, typename Iterator>
    constexpr void to_upper(const ConstIterator str, Iterator buf, card32 length)
    {
      for(card32 i = 0; i < length; ++i)
      {
        buf[i] = to_upper(str[i]);
      }
    }

    template <typename Iterator, card32 Size>
    constexpr void to_upper(const Iterator* str, Iterator (&buf)[Size]) // NOLINT(modernize-avoid-c-arrays)
    {
      to_upper(str, buf, Size - 1);
    }

    template <typename Iterator>
    RSL_NO_DISCARD constexpr optional<float32> stof(const Iterator* str, card32 length)
    {
      float32 before_radix_value = 0.0f;
      float32 after_radix_value  = 0.0f;

      int32 sign                  = 1;
      card32 i                    = 0;
      card32 digits_after_radix   = 0;
      bool assigning_before_radix = true;

      if(str[0] == '-')
      {
        sign = -1;
        ++i;
      }
      else if(str[0] == '+')
      {
        ++i;
      }

      for(; i < length; ++i)
      {
        if(!is_digitf(str[i]))
          return nullopt;

        if(str[i] == '.')
        {
          assigning_before_radix = false;
          continue;
        }

        if(assigning_before_radix)
        {
          before_radix_value = ctoi(str[i]) + before_radix_value * 10.0f; // NOLINT(readability-magic-numbers)
        }
        else
        {
          after_radix_value = ctoi(str[i]) + after_radix_value * 10.0f; // NOLINT(readability-magic-numbers)
          ++digits_after_radix;
        }
      }

      return sign * before_radix_value + (after_radix_value / (max(1.0f, pow(10.0f, digits_after_radix)))); // NOLINT(readability-magic-numbers, bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr optional<int32> stoi(const Iterator* str, card32 length)
    {
      int32 value = 0;
      int32 sign  = 1;
      int32 i     = 0;

      if(str[0] == '-')
      {
        sign = -1;
        ++i;
      }
      else if(str[0] == '+')
      {
        ++i;
      }

      for(; i < length; ++i)
      {
        if(!is_digit(str[i]))
          return nullopt;

        value = ctoi(str[i]) + value * 10; // NOLINT(readability-magic-numbers)
      }

      return sign * value;
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr optional<uint32> stoui(const Iterator* str, card32 length)
    {
      uint32 value = 0;

      for(card32 i = 0; i < length; ++i)
      {
        if(!is_digit(str[i]))
          return nullopt;

        value = ctoi(str[i]) + value * 10; // NOLINT(readability-magic-numbers)
      }

      return value;
    }
    template <typename Iterator>
    RSL_NO_DISCARD constexpr optional<bool> stob(const Iterator* str, card32 length)
    {
      constexpr Iterator true_str[]  = "true";  // NOLINT(modernize-avoid-c-arrays)
      constexpr Iterator false_str[] = "false"; // NOLINT(modernize-avoid-c-arrays)

      if(string_equals(str, length, true_str, size(true_str) - 1))
      {
        return true;
      }
      else if(string_equals(str, length, false_str, size(false_str) - 1))
      {
        return false;
      }

      return stoi(str, length);
    }

    namespace internal
    {
      constexpr card32 max_int_buffer = 21;

      template <typename CharType, typename T>
      constexpr CharType* unsigned_integral_to_buff(CharType* rnext, T value)
      {
        static_assert(rsl::is_unsigned_v<T>, "T must be unsigned");

        auto value_trunc = value;

        do
        {
          *--rnext = static_cast<T>(static_cast<CharType>('0') + value_trunc % 10);
          value_trunc /= 10;
        } while(value_trunc != 0);
        return rnext;
      }

      template <typename StringType, typename T>
      constexpr StringType signed_to_string(T value)
      {
        static_assert(rsl::is_integral_v<T>, "T must be integral");

        using char_type = typename StringType::value_type;

        char_type buff[max_int_buffer]; // NOLINT(modernize-avoid-c-arrays) // can hold -2^63 and 2^64 - 1, plus NULL
        char_type* buff_end       = rsl::end(buff);
        char_type* rnext          = buff_end;
        const auto unsigned_value = static_cast<rsl::make_unsigned_t<T>>(value);

        if(value < 0)
        {
          rnext    = unsigned_integral_to_buff(rnext, 0 - unsigned_value);
          *--rnext = '-';
        }
        else
        {
          rnext = unsigned_integral_to_buff(rnext, unsigned_value);
        }

        const size_t size = buff_end - rnext;
        return StringType(rnext, static_cast<count_t>(size));
      }

      template <typename StringType, typename T>
      constexpr StringType unsigned_to_string(T value)
      {
        static_assert(rsl::is_integral_v<T>, "T must be integral");
        static_assert(rsl::is_unsigned_v<T>, "T must be unsigned");

        using char_type = typename StringType::value_type;

        char_type buff[max_int_buffer]; // NOLINT(modernize-avoid-c-arrays) // can hold -2^63 and 2^64 - 1, plus NULL
        char_type* buff_end = rsl::end(buff);
        char_type* rnext    = unsigned_integral_to_buff(buff_end, value);

        const size_t size = buff_end - rnext;
        return StringType(rnext, static_cast<count_t>(size));
      }
    } // namespace internal

    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find(Iterator srcBegin, Iterator srcEnd, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue)
    {
      Iterator to_find_str_end = toFindBegin + toFindLength;
      auto it                  = search(srcBegin, srcEnd, toFindBegin, to_find_str_end);
      return it != srcEnd ? rsl::distance(srcBegin, it) : defaultValue;
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find(Iterator srcBegin, Iterator srcEnd, Iterator toFindBegin, SizeType defaultValue)
    {
      SizeType to_find_length = string_length(toFindBegin);
      return find<SizeType>(srcBegin, srcEnd, toFindBegin, to_find_length, defaultValue);
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType rfind(Iterator srcBegin, Iterator srcEnd, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue)
    {
      Iterator to_find_str_end = toFindBegin + toFindLength;
      auto it                  = search(srcBegin, srcEnd, toFindBegin, to_find_str_end);
      return it != srcEnd ? rsl::distance(srcBegin, it) : defaultValue;
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType rfind(Iterator srcBegin, Iterator srcEnd, Iterator toFindBegin, SizeType defaultValue)
    {
      SizeType to_find_length = string_length(toFindBegin);
      return rfind<SizeType>(srcBegin, srcEnd, toFindBegin, to_find_length, defaultValue);
    }
    template <typename SizeType, typename Iterator1, typename Iterator2, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find_first_of(Iterator1 srcBegin, SizeType numCharsToCheck, Iterator2 toFindBegin, SizeType toFindLength, SizeType defaultValue)
    {
      character_lookup<char_traits<typename rsl::iterator_traits<Iterator2>::value_type>> lookup(iterator_to_pointer(toFindBegin), toFindLength);

      for(SizeType i = 0; i < numCharsToCheck; ++i)
      {
        auto c = srcBegin[i];
        if(lookup.exists(c))
        {
          return i;
        }
      }

      return defaultValue;
    }
    template <typename SizeType, typename Iterator1, typename Iterator2, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find_first_of(Iterator1 srcBegin, SizeType numCharsToCheck, Iterator2 toFindBegin, SizeType defaultValue)
    {
      SizeType to_find_length = string_length(toFindBegin);
      return find_first_of<SizeType>(srcBegin, numCharsToCheck, toFindBegin, to_find_length, defaultValue);
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find_first_not_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue)
    {
      character_lookup<char_traits<typename rsl::iterator_traits<Iterator2>::value_type>> lookup(iterator_to_pointer(toFindBegin), toFindLength);

      for(SizeType i = 0; i < numCharsToCheck; ++i)
      {
        auto c = srcBegin[i];
        if(!lookup.exists(c))
        {
          return i;
        }
      }

      return defaultValue;
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find_first_not_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType defaultValue)
    {
      SizeType to_find_length = string_length(toFindBegin);
      return find_first_not_of<SizeType>(srcBegin, numCharsToCheck, toFindBegin, to_find_length, defaultValue);
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find_last_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue)
    {
      character_lookup<char_traits<typename rsl::iterator_traits<Iterator2>::value_type>> lookup(iterator_to_pointer(toFindBegin), toFindLength);

      for(SizeType i = numCharsToCheck; i >= 0; --i)
      {
        auto c = srcBegin[i];
        if(lookup.exists(c))
        {
          return i;
        }
      }

      return defaultValue;
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find_last_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType defaultValue)
    {
      SizeType to_find_length = string_length(toFindBegin);
      return find_last_of<SizeType>(srcBegin, numCharsToCheck, toFindBegin, to_find_length, defaultValue);
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find_last_not_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue)
    {
      character_lookup<char_traits<typename rsl::iterator_traits<Iterator2>::value_type>> lookup(iterator_to_pointer(toFindBegin), toFindLength);

      for(SizeType i = numCharsToCheck; i >= 0; --i)
      {
        auto c = srcBegin[i];
        if(!lookup.exists(c))
        {
          return i;
        }
      }

      return defaultValue;
    }
    template <typename SizeType, typename Iterator, rsl::enable_if_t<rsl::is_integral_v<SizeType>, bool>>
    constexpr SizeType find_last_not_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType defaultValue)
    {
      SizeType to_find_length = string_length(toFindBegin);
      return find_last_not_of<SizeType>(srcBegin, numCharsToCheck, toFindBegin, to_find_length, defaultValue);
    }

    namespace internal
    {
      template <typename StringType>
      constexpr StringType to_string(const int32 value)
      {
        return internal::signed_to_string<StringType>(value);
      }
      template <typename StringType>
      constexpr StringType to_string(const long value)
      {
        return internal::signed_to_string<StringType>(static_cast<int32>(value));
      }
      template <typename StringType>
      constexpr StringType to_string(const uint32 value)
      {
        return internal::unsigned_to_string<StringType>(value);
      }
      template <typename StringType>
      constexpr StringType to_string(const ulong value)
      {
        return internal::unsigned_to_string<StringType>(static_cast<uint32>(value));
      }
      template <typename StringType>
      constexpr StringType to_string(const int64 value)
      {
        return internal::signed_to_string<StringType>(value);
      }
      template <typename StringType>
      constexpr StringType to_string(const uint64 value)
      {
        return internal::unsigned_to_string<StringType>(value);
      }
      template <typename StringType>
      constexpr StringType to_string(const float32 value, card32 precision)
      {
        const card32 int_value = static_cast<card32>(value);

        const float32 radix_value        = value - int_value;                     // NOLINT(cppcoreguidelines-narrowing-conversions)
        const float32 radix_value_to_int = radix_value * rsl::pow(10, precision); // NOLINT(cppcoreguidelines-narrowing-conversions)
        const card32 radix_value_as_int  = static_cast<card32>(radix_value_to_int);

        return to_string<StringType>(int_value) + static_cast<typename StringType::value_type>('.') + to_string<StringType>(radix_value_as_int);
      }
      template <typename StringType>
      constexpr StringType to_string(const float64 value, card32 precision)
      {
        const card64 int_value = static_cast<card64>(value);

        const float64 radix_value        = value - int_value; // NOLINT(cppcoreguidelines-narrowing-conversions)
        const float64 radix_value_to_int = radix_value * rsl::pow(10, precision);
        const card64 radix_value_as_int  = static_cast<card64>(radix_value_to_int);

        return to_string<StringType>(int_value) + static_cast<typename StringType::value_type>('.') + to_string<StringType>(radix_value_as_int);
      }
      template <typename StringType>
      constexpr StringType to_string(const lfloat64 value, card32 precision)
      {
        return to_string<StringType>(static_cast<const float64>(value), precision);
      }
      template <typename StringType>
      constexpr StringType to_string(const void* ptr)
      {
        uintptr ptr_as_int = reinterpret_cast<uintptr>(ptr); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)

        StringType str;
        str.resize(max_int_buffer + 2);
        auto it = str.rbegin();
        *it     = '0';
        ++it;
        *it = 'x';
        ++it;

        constexpr char8 digits[] = "0123456789abcdef"; // NOLINT(modernize-avoid-c-arrays)

        do
        {
          *it = digits[ptr_as_int & 15u];
          ptr_as_int >>= 4; // divide by 16
          ++it;
        } while(ptr_as_int);

        rsl::reverse(str.begin(), str.end());
        return str;
      }

      // iterator can be of type:
      // - char8*
      // - tchar*
      // - istreambuf_iterator
      // - random_access_iterator
      template <typename T, typename Iterator, typename IteratorPointer>
      constexpr optional<T> str_to_signed(Iterator str, IteratorPointer strEnd, int32 base)
      {
        static_assert(rsl::is_signed_v<T>, "T must be a signed type");

        // skip white space
        while(is_space(*str))
        {
          ++str;
        }

        // determine base
        if((base == 0 || base == 16) && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) // NOLINT(readability-magic-numbers)
        {
          str += 2;
          return 16; // NOLINT(readability-magic-numbers)
        }
        if(base == 0)
        {
          base = *str == '0' ? 8 : 10; // NOLINT(readability-magic-numbers)
        }

        // determine sign
        int32 sign = 1;
        if(*str == '-')
        {
          sign = -1;
          ++str;
        }
        else if(*str == '+')
        {
          ++str;
        }

        // process string
        T value        = 0;
        bool value_set = false;

        while(*str != '\0')
        {
          auto c = *str;

          if(is_digit(c))
          {
            c -= '0';
          }
          else if(is_alpha(c))
          { /* is_alpha(c))*/
            c -= is_upper(c) ? 'A' - 10 : 'a' - 10;
          }
          else
          {
            break;
          }

          if(c >= base)
          {
            break;
          }
          else
          {
            value_set = true;
            value *= base;
            value += c;
          }

          ++str;
        }

        if(value_set)
        {
          using underlying_pointer_type = typename rsl::iterator_traits<decltype(str)>::value_type;
          if (strEnd)
          {
            *strEnd = (underlying_pointer_type*)str;
          }
          return optional<T>(value * sign);
        }
        else
        {
          return nullopt;
        }
      }

      template <typename T, typename Iterator>
      constexpr optional<T> str_to_signed(const Iterator str, int32 base)
      {
        return str_to_signed<T>(str, static_cast<Iterator*>(nullptr), base);
      }

      // iterator can be of type:
      // - char8*
      // - tchar*
      // - istreambuf_iterator
      // - random_access_iterator
      template <typename T, typename Iterator, typename IteratorPointer>
      constexpr optional<T> str_to_unsigned(Iterator str, IteratorPointer strEnd, int32 base)
      {
        static_assert(rsl::is_unsigned_v<T>, "T must be a unsigned type");

        // skip white space
        while(is_space(*str))
        {
          ++str;
        }

        // determine base
        if((base == 0 || base == 16) && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
        {
          str += 2;
          return 16;
        }
        if(base == 0)
        {
          base = *str == '0' ? 8 : 10;
        }

        // process string
        T value        = 0;
        bool value_set = false;
        while(*str != '\0')
        {
          auto c = *str;

          if(is_digit(c))
          {
            c -= '0';
          }
          else if(is_alpha(c))
          {
            c -= is_upper(c) ? 'A' - 10 : 'a' - 10;
          }
          else
          {
            break;
          }

          if(c >= base)
          {
            break;
          }
          else
          {
            value_set = true;
            value *= base;
            value += c;
          }

          ++str;
        }

        if(value_set)
        {
          using underlying_pointer_type = typename rsl::iterator_traits<decltype(str)>::value_type;
          if (strEnd)
          {
            *strEnd = (underlying_pointer_type*)str;
          }
          return optional<T>(value);
        }
        else
        {
          return nullopt;
        }
      }

      template <typename T, typename Iterator>
      constexpr optional<T> str_to_unsigned(Iterator str, int32 base)
      {
        return str_to_unsigned<T>(str, static_cast<Iterator*>(nullptr), base);
      }
      // iterator can be of type:
      // - char8*
      // - tchar*
      // - istreambuf_iterator
      // - random_access_iterator
      template <typename T, typename Iterator, typename IteratorPointer>
      constexpr optional<T> str_to_floating_point(Iterator str, IteratorPointer strEnd)
      {
        static_assert(rsl::is_floating_point_v<T>, "T must be a floating point type");

        floating_point_parse_result res = internal::parse_floating_point<T>(str, strEnd);

        switch (res.metadata)
        {
        case internal::floating_point_parse_result_metadata::decimal_digits: return internal::convert_decimal_to_float<T>(res.fp_string); 
        case internal::floating_point_parse_result_metadata::hexadecimal_digits: return internal::convert_hexadecimal_to_float<T>(res.fp_string);

        case internal::floating_point_parse_result_metadata::zero:          return internal::assemble_floating_point_zero<T>(res.fp_string.is_negative);
        case internal::floating_point_parse_result_metadata::infinity:      return internal::assemble_floating_point_infinity<T>(res.fp_string.is_negative);
        case internal::floating_point_parse_result_metadata::qnan:          return internal::assemble_floating_point_qnan<T>(res.fp_string.is_negative);
        case internal::floating_point_parse_result_metadata::snan:          return internal::assemble_floating_point_snan<T>(res.fp_string.is_negative);
        case internal::floating_point_parse_result_metadata::indeterminate: return internal::assemble_floating_point_ind<T>();

        case internal::floating_point_parse_result_metadata::no_digits:     return rsl::nullopt;
        case internal::floating_point_parse_result_metadata::underflow:     return internal::assemble_floating_point_zero<T>(res.fp_string.is_negative); 
        case internal::floating_point_parse_result_metadata::overflow:      return internal::assemble_floating_point_infinity<T>(res.fp_string.is_negative);
        }

        return rsl::nullopt;
      }

      template <typename T, typename Iterator>
      constexpr optional<T> str_to_floating_point(Iterator str)
      {
        return str_to_floating_point<T>(str, static_cast<Iterator*>(nullptr));
      }

      template <typename Iterator, typename IteratorPointer>
      constexpr optional<bool> str_to_bool(Iterator str, IteratorPointer strEnd)
      {
        constexpr Iterator true_str[]  = "true";  // NOLINT(modernize-avoid-c-arrays)
        constexpr Iterator false_str[] = "false"; // NOLINT(modernize-avoid-c-arrays)

        if(string_equals(str, true_str, size(true_str)))
        {
          // if (str_end)
          //{
          //   *str_end = str + size(true_str);
          // }
          return true;
        }
        else if(string_equals(str, false_str, size(false_str)))
        {
          // if (str_end)
          //{
          //   *str_end = str + size(false_str);
          // }
          return false;
        }

        return str_to_unsigned(str, strEnd, 10);
      }

      template <typename T, typename Iterator>
      constexpr optional<T> str_to_bool(const Iterator str)
      {
        return str_to_bool<T>(str, static_cast<Iterator*>(nullptr));
      }

      // iterator can be of type:
      // - char8*
      // - tchar*
      // - istreambuf_iterator
      // - random_access_iterator
      template <typename Iterator, typename IteratorPointer>
      constexpr optional<void*> str_to_pointer(Iterator str, IteratorPointer strEnd)
      {
        optional<uint64> opt_value(str_to_unsigned(str, strEnd));
        void* val = opt_value.has_value() ? reinterpret_cast<void*>(*opt_value) : nullptr; // NOLINT(performance-no-int-to-ptr, cppcoreguidelines-pro-type-reinterpret-cast)
        return optional<void*>(val);
      }

      template <typename Iterator>
      constexpr optional<void*> str_to_pointer(const Iterator str)
      {
        return str_to_pointer(str, static_cast<Iterator*>(nullptr));
      }
    } // namespace internal

    namespace string_utils
    {
      // compares 2 strings lexicographically
      template <typename Traits, typename Pointer, typename SizeType>
      int32 compare(Pointer lhs, Pointer rhs, SizeType lhsLength, SizeType rhsLength)
      {
        const int32 result = Traits::compare(lhs, rhs, (rsl::min)(lhsLength, rhsLength));

        if(result != 0)
        {
          return result;
        }
        if(lhsLength < rhsLength)
        {
          return -1;
        }
        if(lhsLength > rhsLength)
        {
          return 1;
        }
        return 0;
      }
      // finds the first substring [str, str + toFindLength) within [lhsStr, lhsStr + lhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      constexpr SizeType find(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer toFindStr, SizeType toFindLength, SizeType defaultValue)
      {
        if(lhsLength == 0)
        {
          return defaultValue;
        }

        RSL_ASSERT_X(pos < lhsLength, "pos out of bounds");

        // substring must be found between [pos, size() - toFindLength)
        // we subtract the length of the string to find for optimization
        Pointer start         = lhsStr + pos;
        const Pointer lhs_end = lhsStr + lhsLength;

        const Pointer end = lhs_end - toFindLength + 1;
        start             = Traits::find(start, static_cast<count_t>(end - start), *toFindStr);

        while(start != nullptr && start != end)
        {
          if(Traits::compare(start + 1, toFindStr + 1, toFindLength - 1) == 0)
          {
            return static_cast<SizeType>(start - lhsStr);
          }
          ++start;
          start = Traits::find(start, static_cast<count_t>(lhs_end - start), *toFindStr);
        }
        return defaultValue;
      }
      // finds the last substring [str, str + toFindLength) within [lhsStr, lhsStr + lhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType rfind(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer toFindStr, SizeType toFindLength, SizeType defaultValue)
      {
        pos = (rsl::min)(pos, lhsLength - 1);
        RSL_ASSERT_X(pos < lhsLength, "pos out of bounds");

        // the string must be found between [begin, pos]

        // we'll first check where the last char in the substring is found in the string
        Pointer start              = lhsStr + pos;
        const Pointer end          = (lhsStr - 1) + toFindLength - 1;
        const Pointer to_find_last = toFindStr + toFindLength - 1;
        start                      = Traits::rfind(start, static_cast<count_t>(start - end), *to_find_last);

        while(start != nullptr && start != end)
        {
          const Pointer new_start = start - (toFindLength - 1);
          if(Traits::compare(new_start, toFindStr, toFindLength - 1) == 0)
          {
            return static_cast<SizeType>(new_start - lhsStr);
          }
          --start;
          start = Traits::rfind(start, static_cast<count_t>(start - end), *to_find_last);
        }
        return defaultValue;
      }
      // finds the first occurrence of a char in the substring [lhsStr, lhsStr + lhsLength) within [rhsStr, rhsStr + rhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType find_first_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue)
      {
        const character_lookup<Traits> lookup(rhsStr, rhsLength);

        for(SizeType i = pos; i < lhsLength; ++i)
        {
          auto c = lhsStr[i];
          if(lookup.exists(c))
          {
            return i;
          }
        }

        return defaultValue;
      }
      // finds the last occurrence of a char in the substring [lhsStr, lhsStr + lhsLength) within [rhsStr, rhsStr + rhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType find_last_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue)
      {
        const character_lookup<Traits> lookup(rhsStr, rhsLength);

        for(SizeType i = lhsLength - 1; i > pos; --i)
        {
          auto c = lhsStr[i];
          if(lookup.exists(c))
          {
            return i;
          }
        }

        return defaultValue;
      }
      // finds the first occurrence of a char not in the substring [lhsStr, lhsStr + lhsLength) within [rhsStr, rhsStr + rhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType find_first_not_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue)
      {
        const character_lookup<Traits> lookup(rhsStr, rhsLength);

        for(SizeType i = pos; i < lhsLength; ++i)
        {
          auto c = lhsStr[i];
          if(!lookup.exists(c))
          {
            return i;
          }
        }

        return defaultValue;
      }
      // finds the last occurrence of a char not in the substring [lhsStr, lhsStr + lhsLength) within [rhsStr, rhsStr + rhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType find_last_not_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue)
      {
        const character_lookup<Traits> lookup(rhsStr, rhsLength);

        for(SizeType i = lhsLength - 1; i > pos; --i)
        {
          auto c = lhsStr[i];
          if(!lookup.exists(c))
          {
            return i;
          }
        }

        return defaultValue;
      }
    } // namespace string_utils

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // returns an optional instead of a basic type
    // converts a byte string to a floating point value
    RSL_NO_DISCARD constexpr optional<float64> atof(const char8* str)
    {
      return internal::str_to_floating_point<float64>(str);
    }

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    RSL_NO_DISCARD constexpr optional<int32> atoi(const char8* str)
    {
      // this is the same function as strtoi, but is less flexible
      return internal::str_to_signed<int32>(str, 10);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    RSL_NO_DISCARD constexpr optional<long> atol(const char8* str)
    {
      // this is the same function as strtol, but is less flexible
      return internal::str_to_signed<long>(str, 10);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    RSL_NO_DISCARD constexpr optional<int64> atoll(const char8* str)
    {
      // this is the same function as strtoll, but is less flexible
      return internal::str_to_signed<int64>(str, 10);
    }

    /// RSL Comment: Not in ISO C++ Standard at time of writing (10/Jul/2022)
    // converts a byte string to an integer value
    RSL_NO_DISCARD constexpr optional<int32> strtoi(const char8* str, char8** strEnd, int32 base)
    {
      return internal::str_to_signed<int32>(str, strEnd, base);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    RSL_NO_DISCARD constexpr optional<long> strtol(const char8* str, char8** strEnd, int32 base)
    {
      return internal::str_to_signed<long>(str, strEnd, base);
    }
    // converts a byte string to an integer value
    // this returns an optional instead of a basic type
    RSL_NO_DISCARD constexpr optional<int64> strtoll(const char8* str, char8** strEnd, int32 base)
    {
      return internal::str_to_signed<int64>(str, strEnd, base);
    }

    /// RSL Comment: Not in ISO C++ Standard at time of writing (10/Jul/2022)
    // converts a byte string to an unsigned integer value
    RSL_NO_DISCARD constexpr optional<uint32> strtoui(const char8* str, char8** strEnd, int32 base)
    {
      return internal::str_to_unsigned<uint32>(str, strEnd, base);
    }
    // converts a byte string to an unsigned integer value
    RSL_NO_DISCARD constexpr optional<ulong> strtoul(const char8* str, char8** strEnd, int32 base)
    {
      return internal::str_to_unsigned<ulong>(str, strEnd, base);
    }
    // converts a byte string to an unsigned integer value
    RSL_NO_DISCARD constexpr optional<uint64> strtoull(const char8* str, char8** strEnd, int32 base)
    {
      return internal::str_to_unsigned<uint64>(str, strEnd, base);
    }

    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    RSL_NO_DISCARD constexpr optional<float32> strtof(const char8* str, char8** strEnd)
    {
      return internal::str_to_floating_point<float32>(str, strEnd);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    RSL_NO_DISCARD constexpr optional<float64> strtod(const char8* str, char8** strEnd)
    {
      return internal::str_to_floating_point<float64>(str, strEnd);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    RSL_NO_DISCARD constexpr optional<lfloat64> strtold(const char8* str, char8** strEnd)
    {
      return internal::str_to_floating_point<lfloat64>(str, strEnd);
    }

  } // namespace v1
} // namespace rsl
