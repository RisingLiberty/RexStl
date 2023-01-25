// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: trunc.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <typename T, typename T2>
    constexpr T trunc(T2 value)
    {
      return static_cast<T>(value);
    }

  } // namespace v1
} // namespace rsl