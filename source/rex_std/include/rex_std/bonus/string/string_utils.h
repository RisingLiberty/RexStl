// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_utils.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/string/character_lookup.h"
#include "rex_std/bonus/type_traits/is_character.h"
#include "rex_std/bonus/types.h"
#include "rex_std/ctype.h"
#include "rex_std/internal/algorithm/max.h"
#include "rex_std/internal/algorithm/memcmp.h"
#include "rex_std/internal/algorithm/min.h"
#include "rex_std/internal/math/pow.h"
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/optional/optional.h"
#include "rex_std/internal/string/char_traits.h"
#include "rex_std/internal/type_traits/is_unsigned.h"
#include "rex_std/internal/utility/size.h"
#include "rex_std/limits.h"

namespace rsl
{
  inline namespace v1
  {

    //
    // Character Classification (cctype.h)
    //

    //
    // Character Manipulation
    //

    //// converts a character to lowercase
    // REX_NO_DISCARD constexpr char8 to_lower(char8 ch);
    //// converts a character to uppercase
    // REX_NO_DISCARD constexpr char8 to_upper(char8 ch);

    //
    // Conversion To Numeric Formats (cstdlib.h)
    //

    REX_NO_DISCARD constexpr tchar to_wide_char(char8 chr);
    REX_NO_DISCARD constexpr char8 to_ascii(tchar chr);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_letter(Iterator letter);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_sign(Iterator sign);

    REX_NO_DISCARD constexpr bool is_multibyte(char8 c);

    template <typename Iterator>
    REX_NO_DISCARD constexpr card32 ctoi(Iterator digit);

    template <typename Iterator>
    REX_NO_DISCARD constexpr card32 string_length(const Iterator* str);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool string_compare(const Iterator* str, card32 length, bool (*stringCompareFunc)(Iterator));

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool string_equals(const Iterator* lhs, card32 lhsLength, const Iterator* rhs, card32 rhsLength);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool string_equals(const Iterator* lhs, const Iterator* rhs, card32 rhsLength);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool string_equals_case_insensitive(const char* lhs, card32 lhsLength, const Iterator* rhs, card32 rhsLength);
    template <typename Iterator>
    REX_NO_DISCARD constexpr int32 string_lex_compare(const char* lhs, const char* rhs, card32 count);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool ends_with(const Iterator* str, card32 strLength, const Iterator* suffix, card32 suffixLength);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool ends_with(const Iterator* str, const Iterator* suffix);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool starts_with(const Iterator* str, card32 strLength, const Iterator* prefix, card32 prefixLength);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool starts_with(const Iterator* str, const Iterator* prefix);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_letters(const Iterator* letters, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_letters(const Iterator* letters);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_digits(const Iterator* digits, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_digits(const Iterator* digits);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_digitsf(const Iterator* digits, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_digitsf(const Iterator* digits);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_nan(const Iterator* digits, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_nan(const Iterator* digits);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_nanf(const Iterator* digits, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_nanf(const Iterator* digits);

    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_lower(const Iterator* letters, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_lower(const Iterator* letters);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_upper(const Iterator* letters, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr bool is_upper(const Iterator* letters);

    template <typename Iterator>
    constexpr void to_lower(const Iterator* str, Iterator* buf, card32 length);

    template <typename Iterator, card32 Size>
    constexpr void to_lower(const Iterator* str, Iterator (&buf)[Size]);
    template <typename Iterator>
    constexpr void to_upper(const Iterator* str, Iterator* buf, card32 length);

    template <typename Iterator, card32 Size>
    constexpr void to_upper(const Iterator* str, Iterator (&buf)[Size]);

    template <typename T>
    class optional;

    template <typename Iterator>
    REX_NO_DISCARD constexpr optional<float32> stof(const Iterator* str, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr optional<int32> stoi(const Iterator* str, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr optional<uint32> stoui(const Iterator* str, card32 length);
    template <typename Iterator>
    REX_NO_DISCARD constexpr optional<bool> stob(const Iterator* str, card32 length);

    template <typename SizeType, typename Iterator>
    constexpr SizeType find(Iterator srcBegin, Iterator srcEnd, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find(Iterator srcBegin, Iterator srcEnd, Iterator toFindBegin, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType rfind(Iterator srcBegin, Iterator srcEnd, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType rfind(Iterator srcBegin, Iterator srcEnd, Iterator toFindBegin, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find_first_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find_first_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find_first_not_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find_first_not_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find_last_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find_last_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find_last_not_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType toFindLength, SizeType defaultValue);
    template <typename SizeType, typename Iterator>
    constexpr SizeType find_last_not_of(Iterator srcBegin, SizeType numCharsToCheck, Iterator toFindBegin, SizeType defaultValue);

    namespace internal
    {
      template <typename CharType, typename T>
      constexpr CharType* unsigned_integral_to_buff(CharType* rnext, T value);
      template <typename StringType, typename T>
      constexpr StringType signed_to_string(T value);
      template <typename StringType, typename T>
      constexpr StringType unsigned_to_string(T value);

      template <typename StringType>
      constexpr StringType to_string(int32 value);
      template <typename StringType>
      constexpr StringType to_string(uint32 value);
      template <typename StringType>
      constexpr StringType to_string(int64 value);
      template <typename StringType>
      constexpr StringType to_string(uint64 value);
      template <typename StringType>
      constexpr StringType to_string(float32 value, card32 precision = 4);
      template <typename StringType>
      constexpr StringType to_string(float64 value, card32 precision = 4);
      template <typename StringType>
      constexpr StringType to_string(lfloat64 value, card32 precision = 4);
      template <typename StringType>
      constexpr StringType to_string(void* ptr);

      // iterator can be of type:
      // - char8*
      // - tchar*
      // - istreambuf_iterator
      // - random_access_iterator
      template <typename T, typename Iterator, typename IteratorPointer>
      constexpr optional<T> str_to_signed(Iterator str, IteratorPointer strEnd, int32 base);

      template <typename T, typename Iterator>
      constexpr optional<T> str_to_signed(const Iterator str, int32 base);

      // iterator can be of type:
      // - char8*
      // - tchar*
      // - istreambuf_iterator
      // - random_access_iterator
      template <typename T, typename Iterator, typename IteratorPointer>
      constexpr optional<T> str_to_unsigned(Iterator str, IteratorPointer /*str_end*/, int32 base);

      template <typename T, typename Iterator>
      constexpr optional<T> str_to_unsigned(Iterator str, int32 base);
      // iterator can be of type:
      // - char8*
      // - tchar*
      // - istreambuf_iterator
      // - random_access_iterator
      template <typename T, typename Iterator, typename IteratorPointer>
      constexpr optional<T> str_to_floating_point(Iterator str, IteratorPointer /*str_end*/);

      template <typename T, typename Iterator>
      constexpr optional<T> str_to_floating_point(Iterator str);

      template <typename Iterator, typename IteratorPointer>
      constexpr optional<bool> str_to_bool(Iterator str, IteratorPointer strEnd);

      template <typename T, typename Iterator>
      constexpr optional<T> str_to_bool(const Iterator str);

      // iterator can be of type:
      // - char8*
      // - tchar*
      // - istreambuf_iterator
      // - random_access_iterator
      template <typename Iterator, typename IteratorPointer>
      constexpr optional<void*> str_to_pointer(Iterator str, IteratorPointer strEnd);

      template <typename Iterator>
      constexpr optional<void*> str_to_pointer(const Iterator str);

    } // namespace internal

    namespace string_utils
    {
      // compares 2 strings lexicographically
      template <typename Traits, typename Pointer, typename SizeType>
      int32 compare(Pointer lhs, Pointer rhs, SizeType lhsLength, SizeType rhsLength);
      // finds the first substring [str, str + toFindLength) within [lhsStr, lhsStr + lhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      constexpr SizeType find(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer toFindStr, SizeType toFindLength, SizeType defaultValue);
      // finds the last substring [str, str + toFindLength) within [lhsStr, lhsStr + lhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType rfind(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer toFindStr, SizeType toFindLength, SizeType defaultValue);
      // finds the first occurrence of a char in the substring [lhsStr, lhsStr + lhsLength) within [rhsStr, rhsStr + rhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType find_first_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue);
      // finds the last occurrence of a char in the substring [lhsStr, lhsStr + lhsLength) within [rhsStr, rhsStr + rhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType find_last_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue);
      // finds the first occurrence of a char not in the substring [lhsStr, lhsStr + lhsLength) within [rhsStr, rhsStr + rhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType find_first_not_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue);
      // finds the last occurrence of a char not in the substring [lhsStr, lhsStr + lhsLength) within [rhsStr, rhsStr + rhsLength), starting from pos
      template <typename Traits, typename Pointer, typename SizeType>
      SizeType find_last_not_of(Pointer lhsStr, SizeType lhsLength, SizeType pos, Pointer rhsStr, SizeType rhsLength, SizeType defaultValue);
    } // namespace string_utils

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // returns an optional instead of a basic type
    // converts a byte string to a floating point value
    REX_NO_DISCARD constexpr optional<float64> atof(const char8* str);

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<int32> atoi(const char8* str);
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<long> atol(const char8* str);
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<int64> atoll(const char8* str);

    /// RSL Comment: Not in ISO C++ Standard at time of writing (10/Jul/2022)
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<int32> strtoi(const char8* str, char8** strEnd, int32 base);
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<long> strtol(const char8* str, char8** strEnd, int32 base);
    // converts a byte string to an integer value
    // this returns an optional instead of a basic type
    REX_NO_DISCARD constexpr optional<int64> strtoll(const char8* str, char8** strEnd, int32 base);

    /// RSL Comment: Not in ISO C++ Standard at time of writing (10/Jul/2022)
    // converts a byte string to an unsigned integer value
    REX_NO_DISCARD constexpr optional<uint32> strtoui(const char8* str, char8** strEnd, int32 base);
    // converts a byte string to an unsigned integer value
    REX_NO_DISCARD constexpr optional<ulong> strtoul(const char8* str, char8** strEnd, int32 base);
    // converts a byte string to an unsigned integer value
    REX_NO_DISCARD constexpr optional<uint64> strtoull(const char8* str, char8** strEnd, int32 base);

    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    REX_NO_DISCARD constexpr optional<float32> strtof(const char8* str, char8** strEnd);
    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    REX_NO_DISCARD constexpr optional<float64> strtod(const char8* str, char8** strEnd);
    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    REX_NO_DISCARD constexpr optional<lfloat64> strtold(const char8* str, char8** strEnd);

    //
    // string Manipulation (cstring.h)
    //

    //
    // string Examination (cstring.h)
    //

    //
    // Miscellaneous (cstring.h)
    //

    // returns a text version of a given error code
    // REX_NO_DISCARD const char8* strerror(int32 errnum);

  } // namespace v1
} // namespace rsl

#include "rex_std/bonus/string/string_utils_impl.h"