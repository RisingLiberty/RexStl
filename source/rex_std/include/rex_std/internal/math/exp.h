// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: exp.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/math/pow.h"
#include "rex_std/numbers.h"

namespace rsl
{
  inline namespace v1
  {

    constexpr float32 exp(const card32 exp)
    {
      return pow(E, exp);
    }

  } // namespace v1
} // namespace rsl
