// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: pop_heap.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/utility/forward.h"
#include "rex_std/internal/algorithm/adjust_heap.h"

namespace rsl
{
  namespace v1
  {
    template <typename RandomAccessIterator>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;
      using value_type = typename rsl::iterator_traits<RandomAccessIterator>::value_type;

      value_type temp_bottom(rsl::forward<value_type>(*(last - 1)));
      *(last - 1) = rsl::forward<value_type>(*first);
      rsl::adjust_heap<RandomAccessIterator, difference_type, value_type>
        (first, (difference_type)0, (difference_type)(last - first - 1), 0, rsl::forward<value_type>(temp_bottom));
    }

    template <typename RandomAccessIterator, typename Compare>
    void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
    {
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;
      using value_type = typename rsl::iterator_traits<RandomAccessIterator>::value_type;

      value_type temp_bottom(rsl::forward<value_type>(*(last - 1)));
      *(last - 1) = rsl::forward<value_type>(*first);
      rsl::adjust_heap<RandomAccessIterator, difference_type, value_type, Compare>
        (first, (difference_type)0, (difference_type)(last - first - 1), 0, rsl::forward<value_type>(temp_bottom), compare);
    }
  } // namespace v1
} // namespace rsl

