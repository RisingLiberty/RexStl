// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: normalise.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    constexpr float32 unorm_to_snorm(float32 val)
    {
      return (val * 2) - 1;
    }
    constexpr float32 snorm_to_unorm(float32 val)
    {
      return (val + 1) * 0.5f;
    }

  } // namespace v1
} // namespace rsl