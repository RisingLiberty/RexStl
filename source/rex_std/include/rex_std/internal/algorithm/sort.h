// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: sort.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/algorithm/quick_sort.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename RandomAccessIterator>
    inline void sort(RandomAccessIterator first, RandomAccessIterator last)
    {
      rsl::quick_sort<RandomAccessIterator>(first, last);
    }

    template <typename RandomAccessIterator, typename Compare>
    inline void sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
    {
      rsl::quick_sort<RandomAccessIterator, Compare>(first, last, compare);
    }
  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"