// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_nan.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    constexpr bool is_nan(const T x)
    {
      return x != x; // NOLINT(misc-redundant-expression)
    }
  } // namespace v1
} // namespace rsl
