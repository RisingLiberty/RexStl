// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: float.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/math/abs.h"

REX_RSL_BEGIN_NAMESPACE

constexpr bool equals(float32 lhs, float32 rhs, float32 comparison_threshold = 0.0001f)
{
  float32 val = lhs - rhs;
  return abs(val) < comparison_threshold;
}

REX_RSL_END_NAMESPACE