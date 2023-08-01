// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: partial_sort.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/adjust_heap.h"
#include "rex_std/internal/algorithm/sort_heap.h"
#include "rex_std/internal/functional/less.h"
#include "rex_std/internal/utility/forward.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename RandomAccessIterator>
    void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last)
    {
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;
      using value_type      = typename rsl::iterator_traits<RandomAccessIterator>::value_type;

      rsl::make_heap<RandomAccessIterator>(first, middle);

      for(RandomAccessIterator i = middle; i < last; ++i)
      {
        if(rsl::less<value_type>()(*i, *first))
        {
          RSL_ASSERT_X(!rsl::less<value_type>()(*first, *i), "invalid comparison function"); // Validate that the compare function is sane.
          value_type temp(rsl::forward<value_type>(*i));
          *i = rsl::forward<value_type>(*first);
          rsl::adjust_heap<RandomAccessIterator, difference_type, value_type>(first, difference_type(0), difference_type(middle - first), difference_type(0), rsl::forward<value_type>(temp));
        }
      }

      rsl::sort_heap<RandomAccessIterator>(first, middle);
    }

    template <typename RandomAccessIterator, typename Compare>
    void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Compare compare)
    {
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;
      using value_type      = typename rsl::iterator_traits<RandomAccessIterator>::value_type;

      rsl::make_heap<RandomAccessIterator, Compare>(first, middle, compare);

      for(RandomAccessIterator i = middle; i < last; ++i)
      {
        if(compare(*i, *first))
        {
          RSL_ASSERT_X(!compare(*first, *i), "invalid comparison function"); // Validate that the compare function is sane.
          value_type temp(rsl::forward<value_type>(*i));
          *i = rsl::forward<value_type>(*first);
          rsl::adjust_heap<RandomAccessIterator, difference_type, value_type, Compare>(first, difference_type(0), difference_type(middle - first), difference_type(0), rsl::forward<value_type>(temp), compare);
        }
      }

      rsl::sort_heap<RandomAccessIterator, Compare>(first, middle, compare);
    }
  } // namespace v1
} // namespace rsl
