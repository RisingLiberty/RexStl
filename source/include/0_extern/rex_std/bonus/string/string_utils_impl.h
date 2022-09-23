// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_utils_impl.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/type_traits/is_integral.h"
#include "rex_std/internal/type_traits/is_unsigned.h"
#include "rex_std/internal/type_traits/make_unsigned.h"

// #include "rex_std/internal/iterator/distance.h"
// #include "rex_std/internal/iterator/begin.h"
// #include "rex_std/internal/iterator/rbegin.h"
// #include "rex_std/internal/iterator/end.h"
// #include "rex_std/internal/iterator/rend.h"
#include "rex_std/bonus/string/character_lookup.h"
#include "rex_std/internal/algorithm/reverse.h"
#include "rex_std/internal/iterator/random_access_iterator.h"
#include "rex_std/internal/iterator/reverse_iterator.h"
#include "rex_std/iterator.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  constexpr card32 MaxIntBuffer = 21;

  template <typename CharType, typename T>
  constexpr CharType* unsigned_integral_to_buff(CharType* rnext, T value)
  {
    static_assert(rsl::is_unsigned_v<T>, "T must be unsigned");

    auto value_trunc = value;

    do
    {
      *--rnext = static_cast<T>(CharType('0') + value_trunc % 10);
      value_trunc /= 10;
    } while(value_trunc != 0);
    return rnext;
  }

  template <typename StringType, typename T>
  constexpr StringType signed_to_string(T value)
  {
    static_assert(rsl::is_integral_v<T>, "T must be integral");

    using char_type = typename StringType::value_type;

    char_type buff[MaxIntBuffer]; // can hold -2^63 and 2^64 - 1, plus NULL
    char_type* buff_end       = rsl::end(buff);
    char_type* rnext          = buff_end;
    const auto unsigned_value = static_cast<rsl::make_unsigned_t<T>>(value);

    if(value < 0)
    {
      rnext = unsigned_integral_to_buff(rnext, 0 - unsigned_value);
    }
    else
    {
      rnext = unsigned_integral_to_buff(rnext, unsigned_value);
    }

    size_t size = buff_end - rnext;
    return StringType(rnext, static_cast<count_t>(size));
  }

  template <typename StringType, typename T>
  constexpr StringType unsigned_to_string(T value)
  {
    static_assert(rsl::is_integral_v<T>, "T must be integral");
    static_assert(rsl::is_unsigned_v<T>, "T must be unsigned");

    using char_type = typename StringType::value_type;

    char_type buff[MaxIntBuffer];
    char_type* buff_end = rsl::end(buff);
    char_type* rnext    = unsigned_integral_to_buff(buff_end, value);

    size_t size = buff_end - rnext;
    return StringType(rnext, static_cast<count_t>(size));
  }
} // namespace internal

template <typename SizeType, typename Iterator>
constexpr SizeType find(Iterator src_begin, Iterator src_end, Iterator to_find_begin, SizeType to_find_length, SizeType default_value)
{
  Iterator to_find_str_end = to_find_begin + to_find_length;
  auto it                  = search(src_begin, src_end, to_find_begin, to_find_str_end);
  return it != src_end ? rsl::distance(src_begin, it) : default_value;
}
template <typename SizeType, typename Iterator>
constexpr SizeType find(Iterator src_begin, Iterator src_end, Iterator to_find_begin, SizeType default_value)
{
  SizeType to_find_length = string_length(to_find_begin);
  return find<SizeType>(src_begin, src_end, to_find_begin, to_find_length, default_value);
}
template <typename SizeType, typename Iterator>
constexpr SizeType rfind(Iterator src_begin, Iterator src_end, Iterator to_find_begin, SizeType to_find_length, SizeType default_value)
{
  Iterator to_find_str_end = to_find_begin + to_find_length;
  auto it                  = search(src_begin, src_end, to_find_begin, to_find_str_end);
  return it != src_end ? rsl::distance(src_begin, it) : default_value;
}
template <typename SizeType, typename Iterator>
constexpr SizeType rfind(Iterator src_begin, Iterator src_end, Iterator to_find_begin, SizeType default_value)
{
  SizeType to_find_length = string_length(to_find_begin);
  return rfind<SizeType>(src_begin, src_end, to_find_begin, to_find_length, default_value);
}
template <typename SizeType, typename Iterator>
constexpr SizeType find_first_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType to_find_length, SizeType default_value)
{
  character_lookup<typename Iterator::value_type> lookup(iterator_to_pointer(to_find_begin), to_find_length);

  for(SizeType i = 0; i < num_chars_to_check; ++i)
  {
    auto c = src_begin[i];
    if(lookup.exists(c))
    {
      return i;
    }
  }

  return default_value;
}
template <typename SizeType, typename Iterator>
constexpr SizeType find_first_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType default_value)
{
  SizeType to_find_length = string_length(to_find_begin);
  return find_first_of<SizeType>(src_begin, num_chars_to_check, to_find_begin, to_find_length, default_value);
}
template <typename SizeType, typename Iterator>
constexpr SizeType find_first_not_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType to_find_length, SizeType default_value)
{
  character_lookup<typename Iterator::value_type> lookup(iterator_to_pointer(to_find_begin), to_find_length);

  for(SizeType i = 0; i < num_chars_to_check; ++i)
  {
    auto c = src_begin[i];
    if(!lookup.exists(c))
    {
      return i;
    }
  }

  return default_value;
}
template <typename SizeType, typename Iterator>
constexpr SizeType find_first_not_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType default_value)
{
  SizeType to_find_length = string_length(to_find_begin);
  return find_first_not_of<SizeType>(src_begin, num_chars_to_check, to_find_begin, to_find_length, default_value);
}
template <typename SizeType, typename Iterator>
constexpr SizeType find_last_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType to_find_length, SizeType default_value)
{
  character_lookup<typename Iterator::value_type> lookup(iterator_to_pointer(to_find_begin), to_find_length);

  for(SizeType i = num_chars_to_check; i >= 0; --i)
  {
    auto c = src_begin[i];
    if(lookup.exists(c))
    {
      return i;
    }
  }

  return default_value;
}
template <typename SizeType, typename Iterator>
constexpr SizeType find_last_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType default_value)
{
  SizeType to_find_length = string_length(to_find_begin);
  return find_last_of<SizeType>(src_begin, num_chars_to_check, to_find_begin, to_find_length, default_value);
}
template <typename SizeType, typename Iterator>
constexpr SizeType find_last_not_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType to_find_length, SizeType default_value)
{
  character_lookup<typename Iterator::value_type> lookup(iterator_to_pointer(to_find_begin), to_find_length);

  for(SizeType i = num_chars_to_check; i >= 0; --i)
  {
    auto c = src_begin[i];
    if(!lookup.exists(c))
    {
      return i;
    }
  }

  return default_value;
}
template <typename SizeType, typename Iterator>
constexpr SizeType find_last_not_of(Iterator src_begin, SizeType num_chars_to_check, Iterator to_find_begin, SizeType default_value)
{
  SizeType to_find_length = string_length(to_find_begin);
  return find_last_not_of<SizeType>(src_begin, num_chars_to_check, to_find_begin, to_find_length, default_value);
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
    card32 int_value = static_cast<card32>(value);

    float32 radix_value        = value - int_value;
    float32 radix_value_to_int = radix_value * rsl::pow(10, precision);
    card32 radix_value_as_int  = static_cast<card32>(radix_value_to_int);

    return to_string<StringType>(int_value) + typename StringType::value_type('.') + to_string<StringType>(radix_value_as_int);
  }
  template <typename StringType>
  constexpr StringType to_string(const float64 value, card32 precision)
  {
    card64 int_value = static_cast<card64>(value);

    float64 radix_value        = value - int_value;
    float64 radix_value_to_int = radix_value * rsl::pow(10, precision);
    card64 radix_value_as_int  = static_cast<card64>(radix_value_to_int);

    return to_string<StringType>(int_value) + typename StringType::value_type('.') + to_string<StringType>(radix_value_as_int);
  }
  template <typename StringType>
  constexpr StringType to_string(const lfloat64 value, card32 precision)
  {
    return to_string<StringType>(static_cast<const float64>(value), precision);
  }
  template <typename StringType>
  constexpr StringType to_string(const void* ptr)
  {
    uintptr ptr_as_int = reinterpret_cast<uintptr>(ptr);

    StringType str;
    str.resize(MaxIntBuffer + 2);
    auto it = str.rbegin();
    *it     = '0';
    ++it;
    *it = 'x';
    ++it;

    constexpr char8 digits[] = "0123456789abcdef";

    do
    {
      *it = digits[ptr_as_int & 15];
      ptr_as_int >>= 4; // divide by 16
      ++it;
    } while(ptr_as_int);

    rsl::reverse(str.begin(), str.end());
    return str;
  }
} // namespace internal

REX_RSL_END_NAMESPACE
