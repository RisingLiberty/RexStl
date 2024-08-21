// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: accumulate.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/iterator.h"
#include "rex_std/functional.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename It, typename T, typename Func>
    constexpr T accumulate(const It first, const It last, T val, Func op) 
    {
      for (; first != last; ++first)
      {
        val = op(val, *first);
      }
      return val;
    }

    template <typename It, typename T>
    constexpr T accumulate(const It first, const It last, T val) 
    {
      return accumulate(first, last, val, rsl::plus<T>{});
    }
  }
} // namespace rsl

