// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: make_heap.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/utility/forward.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename RandomAccessIterator>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
      // We do bottom-up heap construction as per Sedgewick. Such construction is O(n).
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;
      using value_type = typename rsl::iterator_traits<RandomAccessIterator>::value_type      ;

      const difference_type heapSize = last - first;

      if (heapSize >= 2) // If there is anything to do... (we need this check because otherwise the math fails below).
      {
        difference_type parentPosition = ((heapSize - 2) >> 1) + 1; // We use '>> 1' instead of '/ 2' because we have seen VC++ generate better code with >>.

        do {
          --parentPosition;
          value_type temp(rsl::forward<value_type>(*(first + parentPosition)));
          rsl::adjust_heap<RandomAccessIterator, difference_type, value_type>
            (first, parentPosition, heapSize, parentPosition, rsl::forward<value_type>(temp));
        } while (parentPosition != 0);
      }
    }


    template <typename RandomAccessIterator, typename Compare>
    void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
    {
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;
      using value_type = typename rsl::iterator_traits<RandomAccessIterator>::value_type;

      const difference_type heapSize = last - first;

      if (heapSize >= 2) // If there is anything to do... (we need this check because otherwise the math fails below).
      {
        difference_type parentPosition = ((heapSize - 2) >> 1) + 1; // We use '>> 1' instead of '/ 2' because we have seen VC++ generate better code with >>.

        do {
          --parentPosition;
          value_type temp(rsl::forward<value_type>(*(first + parentPosition)));
          rsl::adjust_heap<RandomAccessIterator, difference_type, value_type, Compare>
            (first, parentPosition, heapSize, parentPosition, rsl::forward<value_type>(temp), compare);
        } while (parentPosition != 0);
      }
    }
  } // namespace v1
} // namespace rsl
