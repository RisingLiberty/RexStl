// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: string_utils.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/bonus/attributes.h"

#include "rex_std/bonus/type_traits/is_character.h"

#include "rex_std/limits.h"

#include "rex_std/internal/algorithm/memcmp.h"
#include "rex_std/internal/algorithm/max.h"
#include "rex_std/internal/algorithm/min.h"

#include "rex_std/internal/math/pow.h"

#include "rex_std/internal/string/char_traits.h"

#include "rex_std/bonus/string/character_lookup.h"

#include "rex_std/internal/memory/memcpy.h"

#include "rex_std/internal/utility/size.h"

namespace rsl
{
  REX_NO_DISCARD constexpr tchar to_wide_char(char8 chr)
  {
    return static_cast<tchar>(chr);
  }
  REX_NO_DISCARD constexpr char8 to_ascii(tchar chr)
  {
    return static_cast<char8>(chr);
  }
  
  REX_NO_DISCARD constexpr bool is_upper(char8 letter)
  {
    return letter >= 'A' && letter <= 'Z';
  }
  REX_NO_DISCARD constexpr bool is_lower(char8 letter)
  {
    return letter >= 'a' && letter <= 'z';
  }
  
  REX_NO_DISCARD constexpr bool is_letter(char8 letter)
  {
    return is_upper(letter) || is_lower(letter);
  }
  REX_NO_DISCARD constexpr bool is_digit(char8 digit)
  {
    return digit >= '0' && digit <= '9';
  }
  REX_NO_DISCARD constexpr bool is_digitf(char8 digit)
  {
    return is_digit(digit) || digit == '.';
  }
  REX_NO_DISCARD constexpr bool is_sign(char8 sign)
  {
    return sign == '-' || sign == '+';
  }
  
  REX_NO_DISCARD constexpr bool is_multibye(char8 c)
  {
    return (c & 0x80) != 0;
  }

  REX_NO_DISCARD constexpr char8 to_upper(char8 letter)
  {
    return is_lower(letter) ? letter - ('z' - 'Z') : letter;
  }
  REX_NO_DISCARD constexpr char8 to_lower(char8 letter)
  {
    return is_upper(letter) ? letter - ('Z' - 'z') : letter;
  }

  REX_NO_DISCARD constexpr card32 ctoi(char8 digit)
  {
    return digit - '0';
  }

  template <typename Char>
  REX_NO_DISCARD constexpr card32 string_length(const Char* str)
  {
    static_assert(is_character_v<Char>, "argument is not of character type");
    
    card32 length = 0;
    while (*str)
    {
      str++;
      ++length;
    }
    return length;
  }

  REX_NO_DISCARD constexpr bool string_compare(const char8* str, card32 length, bool(*string_compare_func)(char8))
  {
    for (card32 i = 0; i < length; ++i)
    {
      if (!string_compare_func(str[i]))
        return false;
    }

    return true;
  }

  REX_NO_DISCARD constexpr bool string_equals(const char8* lhs, card32 lhs_length, const char8* rhs, card32 rhs_length)
  {
    if (lhs_length != rhs_length)
      return false;

    for (card32 i = 0; i < lhs_length; ++i)
    {
      if (lhs[i] != rhs[i])
        return false;
    }

    return true;
  }

  REX_NO_DISCARD constexpr bool string_equals_case_insensitive(const char* lhs, card32 lhs_length, const char8* rhs, card32 rhs_length)
  {
    if (lhs_length != rhs_length)
      return false;

    for (card32 i = 0; i < lhs_length; ++i)
    {
      char8 lhs_c = to_lower(lhs[i]);
      char8 rhs_c = to_lower(rhs[i]);

      if (lhs_c != rhs_c)
      {
        return false;
      }
    }

    return true;
  }
  REX_NO_DISCARD constexpr int32 string_lex_compare(const char* lhs, const char* rhs, card32 count)
  {
    return rsl::memcmp(lhs, rhs, count);
  }

  REX_NO_DISCARD constexpr bool ends_with(const char8* str, card32 str_length, const char8* suffix, card32 suffix_length)
  {
    if (str_length < suffix_length)
    {
      return false;
    }

    const char* start = str + (str_length - suffix_length);

    return string_equals(start, suffix_length, suffix, suffix_length);
  }
  REX_NO_DISCARD constexpr bool ends_with(const char8* str, const char8* suffix)
  {
    card32 str_length = string_length(str);
    card32 suffix_length = string_length(suffix);

    return ends_with(str, str_length, suffix, suffix_length);
  }

  REX_NO_DISCARD constexpr bool starts_with(const char8* str, card32 str_length, const char8* prefix, card32 prefix_length)
  {
    if (str_length < prefix_length)
    {
      return false;
    }

    return string_equals(str, prefix_length, prefix, prefix_length);
  }
  REX_NO_DISCARD constexpr bool starts_with(const char8* str, const char8* prefix)
  {
    card32 str_length = string_length(str);
    card32 prefix_length = string_length(prefix);

    return starts_with(str, str_length, prefix, prefix_length);
  }

  REX_NO_DISCARD constexpr bool is_letters(const char8* letters, card32 length)
  {
    return string_compare(letters, length, is_letter);
  }
  REX_NO_DISCARD constexpr bool is_letters(const char8* letters)
  {
    card32 length = string_length(letters);
    return is_letters(letters, length);
  }
  REX_NO_DISCARD constexpr bool is_digits(const char8* digits, card32 length)
  {
    return (is_sign(*digits) && string_compare(digits + 1, length - 1, is_digit))
      || string_compare(digits, length, is_digit);
  }
  REX_NO_DISCARD constexpr bool is_digits(const char8* digits)
  {
    card32 length = string_length(digits);
    return (is_sign(*digits) && string_compare(digits + 1, length - 1, is_digit))
      || string_compare(digits, length, is_digit);
  }
  REX_NO_DISCARD constexpr bool is_digitsf(const char8* digits, card32 length)
  {
    return (is_sign(*digits) && string_compare(digits + 1, length - 1, is_digitf))
      || string_compare(digits, length, is_digitf);
  }
  REX_NO_DISCARD constexpr bool is_digitsf(const char8* digits)
  {
    card32 length = string_length(digits);
    return (is_sign(*digits) && string_compare(digits + 1, length - 1, is_digitf))
      || string_compare(digits, length, is_digitf);
  }
  REX_NO_DISCARD constexpr bool is_nan(const char8* digits, card32 length)
  {
    return !is_digits(digits, length);
  }
  REX_NO_DISCARD constexpr bool is_nan(const char8* digits)
  {
    card32 length = string_length(digits);
    return is_nan(digits, length);
  }
  REX_NO_DISCARD constexpr bool is_nanf(const char8* digits, card32 length)
  {
    return !is_digitsf(digits, length);
  }
  REX_NO_DISCARD constexpr bool is_nanf(const char8* digits)
  {
    card32 length = string_length(digits);
    return !is_digitsf(digits, length);
  }

  REX_NO_DISCARD constexpr bool is_lower(const char8* letters, card32 length)
  {
    return string_compare(letters, length, is_lower);
  }
  REX_NO_DISCARD constexpr bool is_lower(const char8* letters)
  {
    card32 length = string_length(letters);
    return string_compare(letters, length, is_lower);
  }
  REX_NO_DISCARD constexpr bool is_upper(const char8* letters, card32 length)
  {
    return string_compare(letters, length, is_upper);
  }
  REX_NO_DISCARD constexpr bool is_upper(const char8* letters)
  {
    card32 length = string_length(letters);
    return string_compare(letters, length, is_upper);
  }

  constexpr void to_lower(const char8* str, char8* buf, card32 length)
  {
    for (card32 i = 0; i < length; ++i)
    {
      buf[i] = to_lower(str[i]);
    }
  }

  template <card32 Size>
  constexpr void to_lower(const char8* str, char8(&buf)[Size])
  {
    to_lower(str, buf, Size - 1);
  }
  constexpr void to_upper(const char8* str, char8* buf, card32 length)
  {
    for (card32 i = 0; i < length; ++i)
    {
      buf[i] = to_upper(str[i]);
    }
  }

  template <card32 Size>
  constexpr void to_upper(const char8* str, char8(&buf)[Size])
  {
    to_upper(str, buf, Size - 1);
  }

  STATIC_WARNING("Use optional for these");
  constexpr float32 StofInvalidValue = rsl::numeric_limits<float32>::quiet_NaN();
  constexpr int32 StoiInvalidValue = ((rsl::numeric_limits<uint32>::max)());
  constexpr uint32 StouiInvalidValue = ((rsl::numeric_limits<uint32>::max)());

  REX_NO_DISCARD constexpr float32 stof(const char8* str, card32 length)
  {
    float32 before_radix_value = 0.0f;
    float32 after_radix_value = 0.0f;

    int32 sign = 1;
    card32 i = 0;
    card32 digits_after_radix = 0;
    bool assigning_before_radix = true;

    if (str[0] == '-')
    {
      sign = -1;
      ++i;
    }
    else if (str[0] == '+')
    {
      ++i;
    }

    for (; i < length; ++i)
    {
      if (!is_digitf(str[i]))
        return StofInvalidValue;

      if (str[i] == '.')
      {
        assigning_before_radix = false;
        continue;
      }

      if (assigning_before_radix)
      {
        before_radix_value = ctoi(str[i]) + before_radix_value * 10.0f;
      }
      else
      {
        after_radix_value = ctoi(str[i]) + after_radix_value * 10.0f;
        ++digits_after_radix;
      }
    }

    return sign * before_radix_value + (after_radix_value / (max(1.0f, pow(10.0f, digits_after_radix))));
  }
  constexpr int32 stoi(const char8* str, card32 length)
  {
    int32 value = 0;
    int32 sign = 1;
    int32 i = 0;

    if (str[0] == '-')
    {
      sign = -1;
      ++i;
    }
    else if (str[0] == '+')
    {
      ++i;
    }

    for (; i < length; ++i)
    {
      if (!is_digit(str[i]))
        return StoiInvalidValue;

      value = ctoi(str[i]) + value * 10;
    }

    return sign * value;
  }
  constexpr uint32 stoui(const char8* str, card32 length)
  {
    uint32 value = 0;

    for (card32 i = 0; i < length; ++i)
    {
      if (!is_digit(str[i]))
        return StouiInvalidValue;

      value = ctoi(str[i]) + value * 10;
    }

    return value;
  }
  constexpr bool stob(const char8* str, card32 length)
  {
    constexpr char8 true_str[] = "true";
    constexpr char8 false_str[] = "false";

    if (string_equals(str, length, true_str, size(true_str)))
    {
      return true;
    }
    else if (string_equals(str, length, false_str, size(false_str)))
    {
      return false;
    }

    return stoi(str, length);
  }

  template <typename SizeType, typename Iterator>
  constexpr SizeType find(Iterator src_begin, Iterator src_end, Iterator to_find_begin, SizeType to_find_length, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find(Iterator src_begin, Iterator src_end, Iterator to_find_begin, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType rfind(Iterator src_begin, Iterator src_end, Iterator to_find_begin, SizeType to_find_length, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType rfind(Iterator src_begin, Iterator src_end, Iterator to_find_begin, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find_first_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType to_find_length, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find_first_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find_first_not_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType to_find_length, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find_first_not_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find_last_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType to_find_length, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find_last_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find_last_not_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType to_find_length, SizeType default_value);
  template <typename SizeType, typename Iterator>
  constexpr SizeType find_last_not_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType default_value);

  namespace internal
  {
    template <typename StringType>
    constexpr StringType to_string(const int32 value);
    template <typename StringType>
    constexpr StringType to_string(const uint32 value);
    template <typename StringType>
    constexpr StringType to_string(const int64 value);
    template <typename StringType>
    constexpr StringType to_string(const uint64 value);
    template <typename StringType>
    constexpr StringType to_string(const float32 value, card32 precision = 4);
    template <typename StringType>
    constexpr StringType to_string(const float64 value, card32 precision = 4);
    template <typename StringType>
    constexpr StringType to_string(const lfloat64 value, card32 precision = 4);
    template <typename StringType>
    constexpr StringType to_string(const void* ptr);

    namespace string_utils
    {
        // compares 2 strings lexicographically
        template <typename Traits, typename Pointer, typename SizeType>
        int32 compare(Pointer lhs, Pointer rhs, SizeType lhsLength, SizeType rhsLength)
        {
            return Traits::compare(lhs, rhs, (rsl::min)(lhsLength, rhsLength));
        }
        // finds the first substring [str, str + toFindLength) within [lhsStr, lhsStr + lhsLength), starting from pos
        template <typename Traits, typename Pointer, typename SizeType>
        SizeType find(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer toFindStr, SizeType toFindLength, SizeType defaultValue)
        {
            REX_ASSERT_X(pos < lhsLength, "pos out of bounds");

            // substring must be found between [pos, size() - toFindLength)
            // we subtract the length of the string to find for optimization
            Pointer start = lhsStr + pos;
            const Pointer lhs_end = lhsStr + lhsLength;

            const Pointer end = lhs_end - toFindLength + 1;
            start = Traits::find(start, end - start, *toFindStr);

            if (start != nullptr)
            {
                while (start != end)
                {
                    if (Traits::compare(start + 1, toFindStr + 1, toFindLength - 1) == 0)
                    {
                        return start - lhsStr;
                    }
                    ++start;
                    start = Traits::find(start, lhs_end - start, *toFindStr);
                }
            }
            return defaultValue;
        }
        // finds the last substring [str, str + toFindLength) within [lhsStr, lhsStr + lhsLength), starting from pos
        template <typename Traits, typename Pointer, typename SizeType>
        SizeType rfind(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer toFindStr, SizeType toFindLength, SizeType defaultValue)
        {
            pos = min(pos, lhsLength - 1);

            // the string must be found between [begin, pos]

            // we'll first check where the last char in the substring is found in the string
            Pointer start = lhsStr + pos;
            const Pointer end = (lhsStr - 1) + toFindLength - 1;
            const Pointer to_find_last = toFindStr + toFindLength - 1;
            start = Traits::rfind(start, start - end, *to_find_last);

            if (start != nullptr)
            {
                while (start != end)
                {
                    const Pointer start = start - (toFindLength + 1);
                    if (Traits::compare(start, toFindStr, toFindLength - 1) == 0)
                    {
                        return start - lhsStr;
                    }
                    --start;
                    start = Traits::rfind(start, start - end, *to_find_last);
                }
            }
            return defaultValue;
        }
        // finds the first occurrence of a char in the substring [str, str + length) within [lhsStr, lhsStr + lhsLength), starting from pos
        template <typename Traits, typename Pointer, typename SizeType>
        SizeType find_first_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue)
        {
            character_lookup<typename Traits::char_type> lookup(rhsStr, rhsLength);

            for (SizeType i = pos; i < lhsLength; ++i)
            {
                auto c = lhsStr[i];
                if (lookup.exists(c))
                {
                    return i;
                }
            }

            return defaultValue;
        }
        // finds the last occurrence of a char in the substring [rhsStr, rhsStr + rhsLength) within [lhsStr, lhsStr + lhsLength), starting from pos
        template <typename Traits, typename Pointer, typename SizeType>
        SizeType find_last_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue)
        {
            character_lookup<typename Traits::char_type> lookup(rhsStr, rhsLength);

            for (SizeType i = lhsLength; i >= 0; --i)
            {
                auto c = lhsStr[i];
                if (lookup.exists(c))
                {
                    return i;
                }
            }

            return defaultValue;
        }
        // finds the first occurrence of a char not in the substring [str, str + length) within [lhsStr, lhsStr + lhsLength), starting from pos
        template <typename Traits, typename Pointer, typename SizeType>
        SizeType find_first_not_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue)
        {
            character_lookup<typename Traits::char_type> lookup(rhsStr, rhsLength);

            for (SizeType i = 0; i < lhsLength; ++i)
            {
                auto c = lhsStr[i];
                if (!lookup.exists(c))
                {
                    return i;
                }
            }

            return defaultValue;
        }
        // finds the last occurrence of a char not in the substring [str, str + length) within [lhsStr, lhsStr + lhsLength), starting from pos
        template <typename Traits, typename Pointer, typename SizeType>
        SizeType find_last_not_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue)
        {
            character_lookup<typename Traits::char_type> lookup(rhsStr, rhsLength);

            for (SizeType i = lhsLength; i >= 0; --i)
            {
                auto c = lhsStr[i];
                if (!lookup.exists(c))
                {
                    return i;
                }
            }

            return defaultValue;
        }
    }
  }
}

#include "rex_std/bonus/string/string_utils_impl.h"