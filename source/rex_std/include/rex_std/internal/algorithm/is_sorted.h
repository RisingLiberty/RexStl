// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_sorted.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/assert.h"
#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  inline namespace v1
  {
		template <typename ForwardIterator, typename StrictWeakOrdering>
		bool is_sorted(ForwardIterator first, ForwardIterator last, StrictWeakOrdering compare)
		{
			if (first != last)
			{
				ForwardIterator current = first;

				for (++current; current != last; first = current, ++current)
				{
					if (compare(*current, *first))
					{
						RSL_ASSERT_X(!compare(*first, *current), "invalid comparison function"); // Validate that the compare function is sane.
						return false;
					}
				}
			}
			return true;
		}

		template <typename ForwardIterator>
		bool is_sorted(ForwardIterator first, ForwardIterator last)
		{
			using Less = rsl::less<typename rsl::iterator_traits<ForwardIterator>::value_type>;

			return rsl::is_sorted<ForwardIterator, Less>(first, last, Less());
		}
  } // namespace v1
} // namespace rsl
