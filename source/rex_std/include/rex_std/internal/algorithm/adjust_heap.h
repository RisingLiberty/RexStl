// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: adjust_heap.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/promote_heap.h"
#include "rex_std/internal/functional/less.h"
#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/utility/forward.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename RandomAccessIterator, typename Distance, typename T, typename ValueType>
      void adjust_heap_impl(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T value)
      {
        // We do the conventional approach of moving the position down to the
        // bottom then inserting the value at the back and moving it up.
        Distance child_pos = (2 * position) + 2;

        for(; child_pos < heapSize; child_pos = (2 * child_pos) + 2)
        {
          if(rsl::less<ValueType>()(*(first + child_pos), *(first + (child_pos - 1)))) // Choose the larger of the two children.
          {
            --child_pos;
          }
          *(first + position) = rsl::forward<ValueType>(*(first + child_pos)); // Swap positions with this child.
          position            = child_pos;
        }

        if(child_pos == heapSize) // If we are at the very last index of the bottom...
        {
          *(first + position) = rsl::forward<ValueType>(*(first + (child_pos - 1)));
          position            = child_pos - 1;
        }

        rsl::promote_heap<RandomAccessIterator, Distance, T>(first, topPosition, position, rsl::forward<ValueType>(value));
      }

      template <typename RandomAccessIterator, typename Distance, typename T, typename Compare, typename ValueType>
      void adjust_heap_impl(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T value, Compare compare)
      {
        // We do the conventional approach of moving the position down to the
        // bottom then inserting the value at the back and moving it up.
        Distance child_pos = (2 * position) + 2;

        for(; child_pos < heapSize; child_pos = (2 * child_pos) + 2)
        {
          if(compare(*(first + child_pos), *(first + (child_pos - 1)))) // Choose the larger of the two children.
          {
            --child_pos;
          }
          *(first + position) = rsl::forward<ValueType>(*(first + child_pos)); // Swap positions with this child.
          position            = child_pos;
        }

        if(child_pos == heapSize) // If we are at the bottom...
        {
          *(first + position) = rsl::forward<ValueType>(*(first + (child_pos - 1)));
          position            = child_pos - 1;
        }

        rsl::promote_heap<RandomAccessIterator, Distance, T, Compare>(first, topPosition, position, rsl::forward<ValueType>(value), compare);
      }
    } // namespace internal

    template <typename RandomAccessIterator, typename Distance, typename T>
    void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, const T& value)
    {
      using value_type = typename iterator_traits<RandomAccessIterator>::value_type;
      internal::adjust_heap_impl<RandomAccessIterator, Distance, const T&, const value_type>(first, topPosition, heapSize, position, rsl::forward<const T&>(value));
    }

    template <typename RandomAccessIterator, typename Distance, typename T>
    void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T&& value)
    {
      using value_type = typename iterator_traits<RandomAccessIterator>::value_type;
      internal::adjust_heap_impl<RandomAccessIterator, Distance, T&&, value_type>(first, topPosition, heapSize, position, rsl::forward<T>(value));
    }

    template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, const T& value, Compare compare)
    {
      using value_type = typename iterator_traits<RandomAccessIterator>::value_type;
      internal::adjust_heap_impl<RandomAccessIterator, Distance, const T&, Compare, const value_type>(first, topPosition, heapSize, position, rsl::forward<const T&>(value), compare);
    }

    template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    void adjust_heap(RandomAccessIterator first, Distance topPosition, Distance heapSize, Distance position, T&& value, Compare compare)
    {
      using value_type = typename iterator_traits<RandomAccessIterator>::value_type;
      internal::adjust_heap_impl<RandomAccessIterator, Distance, T&&, Compare, value_type>(first, topPosition, heapSize, position, rsl::forward<T>(value), compare);
    }
  } // namespace v1
} // namespace rsl
