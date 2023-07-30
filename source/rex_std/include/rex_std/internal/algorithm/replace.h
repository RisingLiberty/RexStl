// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: replace.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/iterator.h"

namespace rsl
{
  inline namespace v1
  {
    template <class It, class T>
    constexpr void replace(It first, const It last, const T& oldVal, const T& newVal)
    {
      for(; first != last; ++first)
      {
        if(*first == oldVal)
        {
          *first = newVal;
        }
      }
    }
  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
