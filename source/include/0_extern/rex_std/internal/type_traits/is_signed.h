// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_signed.h
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
  struct IsSignedHelper : bool_constant<T(-1) < T(0)>
  {
  };

  template <typename T>
  struct IsSignedHelper<T, false> : false_type
  {
  };
} // namespace internal

template <typename T>
struct is_signed : public internal::IsSignedHelper<T>
{
};

template <typename T>
constexpr bool is_signed_v = is_signed<T>::value;

REX_RSL_END_NAMESPACE