// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: make_unsigned.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/type_traits/add_const.h"
#include "rex_std/internal/type_traits/add_cv.h"
#include "rex_std/internal/type_traits/add_volatile.h"
#include "rex_std/internal/type_traits/is_enum.h"
#include "rex_std/internal/type_traits/is_integral.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T, bool = is_enum_v<T> || is_integral_v<T>>
  struct MakeUnsignedHelper0
  {
    struct CharHelper
    {
      using type = uint8;
    };

    struct ShortHelper
    {
      using type = uint16;
    };

    struct IntHelper
    {
      using type = uint32;
    };

    struct LongHelper
    {
      using type = ulong;
    };

    struct LongLongHelper
    {
      using type = uint64;
    };

    struct NoTypeHelper
    {
    };

    using type = conditional_t<sizeof(T) <= sizeof(uint8), CharHelper,
                               conditional_t<sizeof(T) <= sizeof(uint16), ShortHelper,
                                             conditional_t<sizeof(T) <= sizeof(uint32), IntHelper, conditional_t<sizeof(T) <= sizeof(uint64), LongLongHelper, conditional_t<sizeof(T) <= sizeof(ulong), LongHelper, NoTypeHelper>>>>>::type;
  };

  template <typename T>
  struct MakeUnsignedHelper0<T, false>
  {
    struct NoTypeHelper
    {
    };

    using type = NoTypeHelper;
  };

  template <typename T>
  struct MakeUnsignedHelper1
  {
    using type = typename T::type;
  };

  template <typename T>
  struct MakeUnsignedHelper
  {
    using type = typename MakeUnsignedHelper1<typename MakeUnsignedHelper0<T>::type>::type;
  };
} // namespace internal

template <typename T>
struct make_unsigned
{
  using type = internal::MakeUnsignedHelper<T>::type;
};

template <>
struct make_unsigned<bool>
{
};
template <>
struct make_unsigned<int8>
{
  using type = uint8;
};
template <>
struct make_unsigned<uint8>
{
  using type = uint8;
};
template <>
struct make_unsigned<int16>
{
  using type = uint16;
};
template <>
struct make_unsigned<uint16>
{
  using type = uint16;
};
template <>
struct make_unsigned<int32>
{
  using type = uint32;
};
template <>
struct make_unsigned<uint32>
{
  using type = uint32;
};
template <>
struct make_unsigned<int64>
{
  using type = uint64;
};
template <>
struct make_unsigned<uint64>
{
  using type = uint64;
};
template <>
struct make_unsigned<long>
{
  using type = ulong;
};
template <>
struct make_unsigned<ulong>
{
  using type = ulong;
};

template <>
struct make_unsigned<char>
{
  using type = uint8;
};
template <>
struct make_unsigned<char8_t>
{
  using type = uint8;
};

template <typename T>
struct make_unsigned<const T>
{
  using type = add_const_t<typename make_unsigned<T>::type>;
};
template <typename T>
struct make_unsigned<volatile T>
{
  using type = add_volatile_t<typename make_unsigned<T>::type>;
};
template <typename T>
struct make_unsigned<const volatile T>
{
  using type = add_cv<typename make_unsigned<T>::type>;
};

template <typename T>
using make_unsigned_t = make_unsigned<T>::type;

REX_RSL_END_NAMESPACE
