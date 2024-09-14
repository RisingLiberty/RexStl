// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: div_result.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    struct div_result
    {
      T quot;
      T rem;
    };

    template <typename T>
    constexpr div_result<T> div(T x, T y)
    {
      div_result<T> res {};
      res.quot = x / y;
      res.rem  = x % y;
      return res;
    }

  } // namespace v1
} // namespace rsl
