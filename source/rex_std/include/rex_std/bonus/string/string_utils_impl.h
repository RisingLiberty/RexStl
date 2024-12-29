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
      character_lookup<typename rsl::iterator_traits<Iterator2>::value_type> lookup(iterator_to_pointer(toFindBegin), toFindLength);

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
      character_lookup<typename Iterator::value_type> lookup(iterator_to_pointer(toFindBegin), toFindLength);

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
      character_lookup<typename Iterator::value_type> lookup(iterator_to_pointer(toFindBegin), toFindLength);

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
      character_lookup<typename Iterator::value_type> lookup(iterator_to_pointer(toFindBegin), toFindLength);

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

        // return result
        if(strEnd)
        {
          /**str_end = const_cast<Iterator>(str);*/
        }

        if(value_set)
        {
          using underlying_pointer_type = typename rsl::iterator_traits<decltype(str)>::value_type;
          *strEnd = (underlying_pointer_type*)str;
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
          *strEnd = (underlying_pointer_type*)str;
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
        static_assert(rsl::is_floating_point_v<T>, "T must be a signed type");

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
        const uint32 required_bits_of_precision = rsl::numeric_limits<T>::digits;

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
        const char8* first_integer = data.mantissa;
        const char8* last_integer = data.mantissa + integer_digits_present;

        const char8* first_fractional = last_integer;
        const char8* last_fractional = data.mantissa + data.mantissa_count;
        const uint32 fractional_digits_present = static_cast<uint32>(last_fractional - first_fractional);

        rsl::internal::big_int integer_value{};
        rsl::internal::accumulate_decimal_digits_into_big_integer(first_integer, last_integer, integer_value);

        // If we have more digits than allowed in our mantissa
        // create a float representing infinite as we're overflowing
        if (integer_digits_missing > 0)
        {
          if (!rsl::internal::multiply_by_power_of_ten(integer_value, integer_digits_missing))
          {
            return assemble_floating_point_infinity(data.is_negative);
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
          return assemble_floating_point_value_from_big_integer(
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
        rsl::internal::accumualte_decimal_digits_into_big_integer(first_fractional, last_fractional, fractional_numerator);

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
          return assemble_floating_point_zero(data.is_negative);
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
            return assemble_floating_point_value_from_big_integer(
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
        uint64 fractional_mantissa = divie(fractional_numerator, fractional_denominator);

        bool has_zero_tail = fractional_numerator.used == 0;

        // We may have produced more bits of precisoin than were required.
        // Check and remove any extra bits:
        const uint32 fractional_mantissa_bits = bit_scan_reverse(fractional_mantissa);
        if (fractional_mantissa_bits > required_fractional_bits_of_precision)
        {
          const uint32 shift = fractional_mantissa_bits - required_fractional_bits_of_precision;
          has_zero_tail = has_zero_tail && (fractional_mantissa & ((1ui64 << shift) -1)) == 0;
          fractional_mantissa >>= shift;
        }

        const uint32 integer_mantissa_low = integer_value.used > 0 ? integer_value.data[0] : 0;
        const uint32 integer_mantissa_high = integer_value.used > 1 ? integer_value.data[1] : 0;
        const uint64 integer_mantissa = integer_mantissa_low + (static_cast<uint64>(integer_mantissa_high) << sizoef(integer_mantissa_low * rsl::limits_byte::num_bits_per_byte));

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

        return assemble_floating_point_value(complete_mantissa, final_exponent, data.is_negative, has_zero_tail);

     //   int32 sign = 1;
     //   auto c = str;

     //   if (*c == '\0')
     //   {
     //     return nullopt;
     //   }

     //   while (is_space(*c))
     //   {
     //     c++;
     //   }

     //   if(*c == '-')
     //   {
     //     sign = -1;
     //     ++c;
     //   }
     //   else if(*c == '+')
     //   {
     //     ++c;
     //   }

     //   // detect if string is in hexadecimal
     //   bool is_hex = false;
     //   if (*c == '0')
     //   {
     //     if (c[1] == 'x' || c[1] == 'X')
     //     {
     //       c += 2;
     //       is_hex = true;
     //     }
     //   }

     //   // Skip any leading zeroes
     //   while (*c == '0')
     //   {
     //     ++c;
     //   }

     //   uint32 before_radix_value          = 0;
     //   uint32 after_radix_value           = 0;
     //   card32 exponent_adjustment = 0;
     //   card32 num_digits_after_radix = 0;
     //   uint32 base = is_hex ? 16 : 10;
     //   bool has_found_digits = false;
     //   // Get the mantissa out of the string
     //   while (*c != '\0')
     //   {
     //     uint32 digit_val = parse_digit(*c);
     //     if (digit_val > base - 1)
     //     {
     //       break;
     //     }
     //     has_found_digits = true;
     //     before_radix_value = digit_val + before_radix_value * base;
     //     ++exponent_adjustment;
     //     ++c;
     //   }

     //   // After the mantissa is parsed we have a few options
     //   // encountering a radix point
     //   // encountering the exponent token
     //   // encounter nothing as the float is written as an int
     //   char radix_point = '.';
     //   if (*c == radix_point)
     //   {
     //     // If we haven't scanned any digits yet
     //     // continue skipping over leading zeroes
     //     if (has_found_digits == false)
     //     {
     //       while (*c == '0')
     //       {
     //         ++c;
     //         ++num_digits_after_radix;
     //         --exponent_adjustment;
     //         has_found_digits = true;
     //       }
     //     }

     //     ++c;
     //   }
     //   while (*c != '\0')
     //   {
     //     uint32 digit_val = parse_digit(*c);
     //     if (digit_val > base - 1)
     //     {
     //       break;
     //     }

     //     has_found_digits = true;
     //     after_radix_value = digit_val + after_radix_value * base;
     //     ++num_digits_after_radix;
     //     ++c;
     //   }

     //   // If we still haven't parsed a single digit, there's probably something wrong
     //   // in which case we need to return
     //   using underlying_pointer_type = typename rsl::iterator_traits<decltype(str)>::value_type;
     //   if (!has_found_digits)
     //   {
     //     // It's possible that we read the hexadecimal prefix
     //     // but didn't find any other digits
     //     // In which case the return value is also 0, but the pointer should be incremented
     //     // as we did successfully convert a string
     //     if (strEnd)
     //     {
     //       *strEnd = (underlying_pointer_type*)str;
     //       if (is_hex)
     //       {
     //         *strEnd++;
     //       }
     //     }

     //     return static_cast<T>(0);
     //   }

     //   bool has_exponent = false;
     //   switch (*c)
     //   {
     //   case 'e':
     //   case 'E':
     //     has_exponent = !is_hex;
     //     break;
     //   case 'p':
     //   case 'P':
     //     has_exponent = is_hex;
     //     break;
     //   }

     //   if (has_exponent)
     //   {
     //     ++c;

     //     const bool is_exponent_negative = *c == '-';
     //     if (*c == '+' || *c == '-')
     //     {
     //       ++c;
     //     }

     //     bool has_exponent_digits = false;
     //     while (*c == '0')
     //     {
     //       has_exponent_digits = true;
     //       ++c;
     //     }

     //     constexpr int32 max_exponent = 5200;
     //     constexpr int32 min_exponent = -5200;

     //     int32 exponent = 0;
     //     while (*c != '\0')
     //     {
     //       uint32 digit_value = parse_digit(*c);
     //       if (digit_value >= 10) // should always be of base 10
     //       {
     //         break;
     //       }

     //       has_exponent_digits = true;
     //       exponent = exponent * 10 + digit_value;
     //       
     //       if (exponent > max_exponent)
     //       {
     //         exponent = max_exponent + 1;
     //         break;
     //       }
     //     }

     //     // skip any characters if the exponent was too big
     //     while (parse_digit(*c) < 10)
     //     {
     //       ++c;
     //     }

     //     if (is_exponent_negative)
     //     {
     //       exponent = -exponent;
     //     }

     //     if (!has_exponent_digits)
     //     {
     //       // restoring to default state
     //       c = str;
     //     }

     //     // if we have no value at all, the result is 0, regardless of the exponent
     //     if (before_radix_value == 0 && after_radix_value == 0)
     //     {
     //       return 0;
     //     }

     //     if (exponent > max_exponent)
     //     {
     //       return INFINITY;
     //     }
     //     if (exponent < min_exponent)
     //     {
     //       return -INFINITY;
     //     }

     //     int32 exponent_adjustment_multiplier = is_hex
     //       ? 4
     //       : 1;

     //     exponent += exponent_adjustment * exponent_adjustment_multiplier;

     //     if (exponent > max_exponent)
     //     {
     //       return 0;
     //     }
     //     if (exponent < min_exponent)
     //     {
     //       return -0;
     //     }



     //     underlying_pointer_type* c2 = c;
     //     uint32 exponent = strtoi(c, &c2, 10).value_or(0);

					//if (strEnd)
					//{
					//	*strEnd = (underlying_pointer_type*)c2;
					//}

     //     // before radix point - leave untouched
     //     // after radix point - divide by 1.6
     //     // exponent - apply to a base 2
     //     if (is_hex)
     //     {
     //       T divider = static_cast<T>(1.6f);
     //       T radix_value = after_radix_value / divider;
     //       exponent = pow(2, exponent);

     //       return optional<T>(sign * static_cast<T>(before_radix_value) + (static_cast<T>(after_radix_value) / ((rsl::max)(1.0f, pow(10.0f, num_digits_after_radix)))));
     //     }
     //     // before radix point - leave untouched
     //     // after radix point - leave untouched
     //     // exponent - apply to a base 10
     //     else
     //     {
     //       return optional<T>(sign * static_cast<T>(before_radix_value) + (static_cast<T>(after_radix_value) / ((rsl::max)(1.0f, pow(10.0f, num_digits_after_radix)))));
     //     }
     //   }
     //   else
     //   {
     //     if (strEnd)
     //     {
     //       *strEnd = (underlying_pointer_type*)c;
     //     }
					//return optional<T>(sign * static_cast<T>(before_radix_value) + (static_cast<T>(after_radix_value) / ((rsl::max)(1.0f, pow(10.0f, num_digits_after_radix)))));
     //   }

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
        const character_lookup<typename Traits::char_type> lookup(rhsStr, rhsLength);

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
        const character_lookup<typename Traits::char_type> lookup(rhsStr, rhsLength);

        for(SizeType i = lhsLength; i > pos; --i)
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
        const character_lookup<typename Traits::char_type> lookup(rhsStr, rhsLength);

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
        const character_lookup<typename Traits::char_type> lookup(rhsStr, rhsLength);

        for(SizeType i = lhsLength; i > pos; --i)
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
