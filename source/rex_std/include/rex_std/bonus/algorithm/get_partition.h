// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: get_partition.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/assert.h"
#include "rex_std/internal/algorithm/iter_swap.h"
#include "rex_std/internal/utility/forward.h"
#include "rex_std/internal/utility/move.h"
#include "rex_std/internal/type_traits/decay.h"

namespace rsl
{
  inline namespace v1
  {
		namespace internal
		{
			template <typename RandomAccessIterator, typename T>
			RandomAccessIterator get_partition_impl(RandomAccessIterator first, RandomAccessIterator last, T&& pivotValue)
			{
				using PureT = decay_t<T>;

				for (; ; ++first)
				{
					while (rsl::less<PureT>()(*first, pivotValue))
					{
						RSL_ASSERT_X(!rsl::less<PureT>()(pivotValue, *first), "invalid comparison function"); // Validate that the compare function is sane.
						++first;
					}
					--last;

					while (rsl::less<PureT>()(pivotValue, *last))
					{
						RSL_ASSERT_X(!rsl::less<PureT>()(*last, pivotValue), "invalid comparison function"); // Validate that the compare function is sane.
						--last;
					}

					if (first >= last) // Random access iterators allow operator >=
						return first;

					rsl::iter_swap(first, last);
				}
			}

			template <typename RandomAccessIterator, typename T, typename Compare>
			RandomAccessIterator get_partition_impl(RandomAccessIterator first, RandomAccessIterator last, T&& pivotValue, Compare compare)
			{
				for (; ; ++first)
				{
					while (compare(*first, pivotValue))
					{
						RSL_ASSERT_X(!compare(pivotValue, *first), "invalid comparison function");
						++first;
					}
					--last;

					while (compare(pivotValue, *last))
					{
						RSL_ASSERT_X(!compare(*last, pivotValue), "invalid comparison function");
						--last;
					}

					if (first >= last) // Random access iterators allow operator >=
					{
						return first;
					}

					rsl::iter_swap(first, last);
				}
			}
		}

		template <typename RandomAccessIterator, typename T>
		RandomAccessIterator get_partition(RandomAccessIterator first, RandomAccessIterator last, const T& pivotValue)
		{
			return internal::get_partition_impl<RandomAccessIterator, const T&>(first, last, pivotValue);
		}

		template <typename RandomAccessIterator, typename T>
		RandomAccessIterator get_partition(RandomAccessIterator first, RandomAccessIterator last, T&& pivotValue)
		{
			// Note: unlike the copy-constructible variant of get_partition... we can't create a temporary const move-constructible object
			return internal::get_partition_impl<RandomAccessIterator, T&&>(first, last, rsl::move(pivotValue));
		}

		template <typename RandomAccessIterator, typename T, typename Compare>
		RandomAccessIterator get_partition(RandomAccessIterator first, RandomAccessIterator last, const T& pivotValue, Compare compare)
		{
			return internal::get_partition_impl<RandomAccessIterator, const T&, Compare>(first, last, pivotValue, compare);
		}

		template <typename RandomAccessIterator, typename T, typename Compare>
		RandomAccessIterator get_partition(RandomAccessIterator first, RandomAccessIterator last, T&& pivotValue, Compare compare)
		{
			// Note: unlike the copy-constructible variant of get_partition... we can't create a temporary const move-constructible object
			return internal::get_partition_impl<RandomAccessIterator, T&&, Compare>(first, last, rsl::forward<T>(pivotValue), compare);
		}
  }
}
