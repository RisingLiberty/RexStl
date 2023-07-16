// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: promote_heap.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/utility/forward.h"
#include "rex_std/internal/functional/less.h"
#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  namespace v1
  {
    namespace internal
    {
      template <typename RandomAccessIterator, typename Distance, typename T, typename Compare, typename ValueType>
      void promote_heap_impl(RandomAccessIterator first, Distance topPosition, Distance position, T value, Compare compare)
      {
        for (Distance parentPosition = (position - 1) >> 1; // This formula assumes that (position > 0). // We use '>> 1' instead of '/ 2' because we have seen VC++ generate better code with >>.
          (position > topPosition) && compare(*(first + parentPosition), value);
          parentPosition = (position - 1) >> 1)
        {
          *(first + position) = rsl::forward<ValueType>(*(first + parentPosition)); // Swap the node with its parent.
          position = parentPosition;
        }

        *(first + position) = rsl::forward<ValueType>(value);
      }

      template <typename RandomAccessIterator, typename Distance, typename T, typename ValueType>
      void promote_heap_impl(RandomAccessIterator first, Distance topPosition, Distance position, T value)
      {
        for (Distance parentPosition = (position - 1) >> 1; // This formula assumes that (position > 0). // We use '>> 1' instead of '/ 2' because we have seen VC++ generate better code with >>.
          (position > topPosition) && rsl::less<ValueType>()(*(first + parentPosition), value);
          parentPosition = (position - 1) >> 1)
        {
          *(first + position) = rsl::forward<ValueType>(*(first + parentPosition)); // Swap the node with its parent.
          position = parentPosition;
        }

        *(first + position) = rsl::forward<ValueType>(value);
      }
    }

    template <typename RandomAccessIterator, typename Distance, typename T>
    void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, const T& value)
    {
      using value_type = typename iterator_traits<RandomAccessIterator>::value_type;
      internal::promote_heap_impl<RandomAccessIterator, Distance, const T&, const value_type>(first, topPosition, position, value);
    }

    template <typename RandomAccessIterator, typename Distance, typename T>
    void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, T&& value)
    {
      using value_type = typename iterator_traits<RandomAccessIterator>::value_type;
      internal::promote_heap_impl<RandomAccessIterator, Distance, T&&, value_type>(first, topPosition, position, rsl::forward<T>(value));
    }

    template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, const T& value, Compare compare)
    {
      using value_type = typename iterator_traits<RandomAccessIterator>::value_type;
      internal::promote_heap_impl<RandomAccessIterator, Distance, const T&, Compare, const value_type>(first, topPosition, position, value, compare);
    }

    template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
    void promote_heap(RandomAccessIterator first, Distance topPosition, Distance position, T&& value, Compare compare)
    {
      using value_type = typename iterator_traits<RandomAccessIterator>::value_type;
      internal::promote_heap_impl<RandomAccessIterator, Distance, T&&, Compare, value_type>(first, topPosition, position, rsl::forward<T>(value), compare);
    }
  }
}
