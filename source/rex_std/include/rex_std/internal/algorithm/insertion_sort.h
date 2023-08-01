// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: insertion_sort.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/functional/less.h"
#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/utility/forward.h"
#include "rex_std/internal/utility/move.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename RandomAccessIterator>
      inline void insertion_sort_simple(RandomAccessIterator first, RandomAccessIterator last)
      {
        for(RandomAccessIterator current = first; current != last; ++current)
        {
          using value_type = typename rsl::iterator_traits<RandomAccessIterator>::value_type;

          RandomAccessIterator end(current), prev(current);
          value_type value(rsl::forward<value_type>(*current));

          for(--prev; rsl::less<value_type>()(value, *prev); --end, --prev)
          {
            RSL_ASSERT_X(!rsl::less<value_type>()(*prev, value), "invalid comparison func");
            *end = rsl::forward<value_type>(*prev);
          }

          *end = rsl::forward<value_type>(value);
        }
      }

      template <typename RandomAccessIterator, typename Compare>
      inline void insertion_sort_simple(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
      {
        for(RandomAccessIterator current = first; current != last; ++current)
        {
          using value_type = typename rsl::iterator_traits<RandomAccessIterator>::value_type;

          RandomAccessIterator end(current), prev(current);
          value_type value(rsl::forward<value_type>(*current));

          for(--prev; compare(value, *prev); --end, --prev)
          {
            RSL_ASSERT_X(!compare(*prev, value), "invalid comparison func");
            *end = rsl::forward<value_type>(*prev);
          }

          *end = rsl::forward<value_type>(value);
        }
      }
    } // namespace internal

    template <typename BidirectionalIterator, typename StrictWeakOrdering>
    void insertion_sort(BidirectionalIterator first, BidirectionalIterator last, StrictWeakOrdering compare)
    {
      using value_type = typename rsl::iterator_traits<BidirectionalIterator>::value_type;

      if(first != last)
      {
        BidirectionalIterator i = first;

        for(++i; i != last; ++i)
        {
          value_type insertValue(rsl::move(*i));
          BidirectionalIterator insertPosition = i;

          for(BidirectionalIterator movePosition = i; movePosition != first && compare(insertValue, *(--movePosition)); --insertPosition)
          {
            RSL_ASSERT_X(!compare(*movePosition, insertValue), "invalid comparison function");
            *insertPosition = rsl::move(*movePosition);
          }

          *insertPosition = rsl::move(insertValue);
        }
      }
    }

    template <typename BidirectionalIterator>
    void insertion_sort(BidirectionalIterator first, BidirectionalIterator last)
    {
      using Less = rsl::less<typename rsl::iterator_traits<BidirectionalIterator>::value_type>;

      insertion_sort<BidirectionalIterator>(first, last, Less());
    }
  } // namespace v1
} // namespace rsl
