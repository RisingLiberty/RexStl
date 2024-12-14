// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: abs.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename T>
      constexpr T abs(T value)
      {
        return (value > 0) ? value : -value; // this has a bug when used with INT_MIN
      }
    } // namespace internal

  } // namespace v1
} // namespace rsl
