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
  struct is_unsigned_helper : bool_constant<static_cast<T>((0) < static_cast<T>(-1))>
  {
  };

  template <typename T>
  struct is_unsigned_helper<T, false> : false_type
  {
  };
} // namespace internal

template <typename T>
struct is_unsigned : public internal::is_unsigned_helper<T>
{
};

template <typename T>
constexpr bool is_unsigned_v = is_unsigned<T>::value;

REX_RSL_END_NAMESPACE
