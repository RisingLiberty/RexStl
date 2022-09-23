// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_unsigned.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_arithmetic.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T, bool = is_arithmetic_v<T>>
  struct IsUnsignedHelper : bool_constant<T((0) < T(-1))>
  {
  };

  template <typename T>
  struct IsUnsignedHelper<T, false> : false_type
  {
  };
} // namespace internal

template <typename T>
struct is_unsigned : public internal::IsUnsignedHelper<T>
{
};

template <typename T>
constexpr bool is_unsigned_v = is_unsigned<T>::value;

REX_RSL_END_NAMESPACE
