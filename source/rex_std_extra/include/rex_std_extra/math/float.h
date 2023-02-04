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

namespace rsl
{
  inline namespace v1
  {

    constexpr bool equals(float32 lhs, float32 rhs, float32 comparisonThreshold = 0.0001f)
    {
      float32 val = lhs - rhs;
      return rsl::internal::abs(val) < comparisonThreshold;
    }

  } // namespace v1
} // namespace rsl