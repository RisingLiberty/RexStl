// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: random_shuffle.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/iter_swap.h"
#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename RandomAccessIterator, typename RandomNumberGenerator>
    inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator&& rng)
    {
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;

      for(RandomAccessIterator i = first + 1; i < last; ++i)
      {
        iter_swap(i, first + (difference_type)rng((size_t)((i - first) + 1)));
      }
    }
  } // namespace v1
} // namespace rsl
