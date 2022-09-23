// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: pow.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_arithmetic.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
constexpr T pow(const T base, const card32 exp)
{
  static_assert(rsl::is_arithmetic_v<T>, "T must be of an arithmetic type");

  return exp == 0 ? T(1) : base * pow(base, exp - 1);
}

REX_RSL_END_NAMESPACE
