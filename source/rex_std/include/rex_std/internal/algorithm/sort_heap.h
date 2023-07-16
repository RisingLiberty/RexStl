// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: sort_heap.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
		template <typename RandomAccessIterator>
		void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
		{
			for (; (last - first) > 1; --last) // We simply use the heap to sort itself.
			{
				rsl::pop_heap<RandomAccessIterator>(first, last);
			}
		}

		template <typename RandomAccessIterator, typename Compare>
		void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
		{
			for (; (last - first) > 1; --last) // We simply use the heap to sort itself.
			{
				rsl::pop_heap<RandomAccessIterator, Compare>(first, last, compare);
			}
		}
	} // namespace v1
} // namespace rsl

