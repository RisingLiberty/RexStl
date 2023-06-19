// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: clamp.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/assert.h"
#include "rex_std/internal/functional/less.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T, typename Compare>
    constexpr T clamp(const T& x, const T& min, const T& max, Compare comp)
    {
      return comp(x, min) ? min : comp(max, x) ? max : x;
    }

    template <typename T>
    constexpr T clamp(const T& x, const T& min, const T& max)
    {
      return clamp(x, min, max, rsl::less<>());
    }

  } // namespace v1
} // namespace rsl
