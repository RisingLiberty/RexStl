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
      // see https://github.com/fmtlib/fmt/issues/3948
      return !(x >= x); // NOLINT(misc-redundant-expression)
    }
  } // namespace v1
} // namespace rsl
