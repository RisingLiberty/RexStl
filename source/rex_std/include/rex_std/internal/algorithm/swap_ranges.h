// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: swap_ranges.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/iter_swap.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename ForwardIterator1, typename ForwardIterator2>
    constexpr ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
    {
      for(; first1 != last1; ++first1, ++first2)
      {
        iter_swap(first1, first2);
      }
      return first2;
    }
  } // namespace v1
} // namespace rsl
