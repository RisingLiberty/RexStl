// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: quick_sort.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/algorithm/get_partition.h"
#include "rex_std/bonus/algorithm/median.h"
#include "rex_std/internal/algorithm/insertion_sort.h"
#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/math/log2.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
#ifdef REX_PLATFORM_X64
      inline constexpr card32 g_quicksort_limit = 28; // For sorts of random arrays over 100 items, 28 - 32 have been found to be good numbers on x86.
#else
      inline constexpr card32 g_quicksort_limit = 16; // It seems that on other processors lower limits are more beneficial, as they result in fewer compares.
#endif

#pragma warning(push)
#pragma warning(disable : 4702) // unreachable code

      template <typename RandomAccessIterator, typename Size, typename PivotValueType>
      void quick_sort_impl_helper(RandomAccessIterator first, RandomAccessIterator last, Size kRecursionCount)
      {
        using value_type = typename iterator_traits<RandomAccessIterator>::value_type;

        while(((last - first) > g_quicksort_limit) && (kRecursionCount > 0))
        {
          const auto& a           = (*first);
          const auto& b           = (*(first + (last - first) / 2));
          const auto& c           = (*(last - 1));
          const auto& pivot_value = rsl::median<value_type>(a, b, c);

          const RandomAccessIterator position = rsl::get_partition<RandomAccessIterator, value_type>(first, last, pivot_value);

          quick_sort_impl_helper<RandomAccessIterator, Size, PivotValueType>(position, last, --kRecursionCount);
          last = position;
        }

        if(kRecursionCount == 0)
        {
          rsl::partial_sort<RandomAccessIterator>(first, last, last);
        }
      }

      template <typename RandomAccessIterator, typename Size, typename Compare, typename PivotValueType>
      void quick_sort_impl_helper(RandomAccessIterator first, RandomAccessIterator last, Size kRecursionCount, Compare compare)
      {
        using value_type = typename iterator_traits<RandomAccessIterator>::value_type;

        while(((last - first) > g_quicksort_limit) && (kRecursionCount > 0))
        {
          const auto& a           = (*first);
          const auto& b           = (*(first + (last - first) / 2));
          const auto& c           = (*(last - 1));
          const auto& pivot_value = rsl::median<value_type, Compare>(a, b, c, compare);

          const RandomAccessIterator position = rsl::get_partition<RandomAccessIterator, value_type, Compare>(first, last, pivot_value, compare);

          quick_sort_impl_helper<RandomAccessIterator, Size, Compare, PivotValueType>(position, last, --kRecursionCount, compare);
          last = position;
        }

        if(kRecursionCount == 0)
        {
          rsl::partial_sort<RandomAccessIterator, Compare>(first, last, last, compare);
        }
      }
#pragma warning(pop)

      template <typename RandomAccessIterator, typename Size>
      void quick_sort_impl(RandomAccessIterator first, RandomAccessIterator last, Size kRecursionCount, typename rsl::enable_if<rsl::is_copy_constructible<typename iterator_traits<RandomAccessIterator>::value_type>::value>::type* = 0)
      {
        using value_type = typename iterator_traits<RandomAccessIterator>::value_type;

        // copy constructors require const value_type
        quick_sort_impl_helper<RandomAccessIterator, Size, const value_type>(first, last, kRecursionCount);
      }

      template <typename RandomAccessIterator, typename Size>
      void quick_sort_impl(
          RandomAccessIterator first, RandomAccessIterator last, Size kRecursionCount,
          typename rsl::enable_if<rsl::is_move_constructible<typename iterator_traits<RandomAccessIterator>::value_type>::value && !rsl::is_copy_constructible<typename iterator_traits<RandomAccessIterator>::value_type>::value>::type* = 0)
      {
        using value_type = typename iterator_traits<RandomAccessIterator>::value_type;

        // move constructors require non-const value_type
        quick_sort_impl_helper<RandomAccessIterator, Size, value_type>(first, last, kRecursionCount);
      }

      template <typename RandomAccessIterator, typename Size, typename Compare>
      void quick_sort_impl(RandomAccessIterator first, RandomAccessIterator last, Size kRecursionCount, Compare compare,
                           typename rsl::enable_if<rsl::is_copy_constructible<typename iterator_traits<RandomAccessIterator>::value_type>::value>::type* = 0)
      {
        using value_type = typename iterator_traits<RandomAccessIterator>::value_type;

        // copy constructors require const value_type
        quick_sort_impl_helper<RandomAccessIterator, Size, Compare, const value_type>(first, last, kRecursionCount, compare);
      }

      template <typename RandomAccessIterator, typename Size, typename Compare>
      void quick_sort_impl(
          RandomAccessIterator first, RandomAccessIterator last, Size kRecursionCount, Compare compare,
          typename rsl::enable_if<rsl::is_move_constructible<typename iterator_traits<RandomAccessIterator>::value_type>::value && !rsl::is_copy_constructible<typename iterator_traits<RandomAccessIterator>::value_type>::value>::type* = 0)
      {
        using value_type = typename iterator_traits<RandomAccessIterator>::value_type;

        // move constructors require non-const value_type
        quick_sort_impl_helper<RandomAccessIterator, Size, Compare, value_type>(first, last, kRecursionCount, compare);
      }
    } // namespace internal

    template <typename RandomAccessIterator>
    void quick_sort(RandomAccessIterator first, RandomAccessIterator last)
    {
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;

      if(first != last)
      {
        internal::quick_sort_impl<RandomAccessIterator, difference_type>(first, last, 2 * log2(last - first));

        if((last - first) > (difference_type)internal::g_quicksort_limit)
        {
          rsl::insertion_sort<RandomAccessIterator>(first, first + internal::g_quicksort_limit);
          internal::insertion_sort_simple<RandomAccessIterator>(first + internal::g_quicksort_limit, last);
        }
        else
          rsl::insertion_sort<RandomAccessIterator>(first, last);
      }
    }

    template <typename RandomAccessIterator, typename Compare>
    void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
    {
      using difference_type = typename rsl::iterator_traits<RandomAccessIterator>::difference_type;

      if(first != last)
      {
        internal::quick_sort_impl<RandomAccessIterator, difference_type, Compare>(first, last, 2 * log2(last - first), compare);

        if((last - first) > (difference_type)internal::g_quicksort_limit)
        {
          rsl::insertion_sort<RandomAccessIterator, Compare>(first, first + internal::g_quicksort_limit, compare);
          internal::insertion_sort_simple<RandomAccessIterator, Compare>(first + internal::g_quicksort_limit, last, compare);
        }
        else
          rsl::insertion_sort<RandomAccessIterator, Compare>(first, last, compare);
      }
    }
  } // namespace v1
} // namespace rsl
