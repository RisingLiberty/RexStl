// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: next_permutation.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/iter_swap.h"
#include "rex_std/internal/algorithm/reverse.h"
#include "rex_std/internal/functional/less.h"
#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/utility/swap.h"

namespace rsl
{
  inline namespace v1
  {
		template<typename BidirectionalIterator, typename Compare>
		bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare compare)
		{
			if (first != last) // If there is anything in the range...
			{
				BidirectionalIterator i = last;

				if (first != --i) // If the range has more than one item...
				{
					for (;;)
					{
						BidirectionalIterator ii(i), j;

						if (compare(*--i, *ii)) // Find two consecutive values where the first is less than the second.
						{
							j = last;
							while (!compare(*i, *--j)) // Find the final value that's greater than the first (it may be equal to the second).
							{
							}
							rsl::iter_swap(i, j);     // Swap the first and the final.
							rsl::reverse(ii, last);   // Reverse the ranget from second to last.
							return true;
						}

						if (i == first) // There are no two consecutive values where the first is less than the second, meaning the range is in reverse order. The reverse ordered range is always the last permutation.
						{
							rsl::reverse(first, last);
							break; // We are done.
						}
					}
				}
			}

			return false;
		}

		template<typename BidirectionalIterator>
		bool next_permutation(BidirectionalIterator first, BidirectionalIterator last)
		{
			using value_type = typename rsl::iterator_traits<BidirectionalIterator>::value_type;

			return rsl::next_permutation(first, last, rsl::less<value_type>());
		}
  } // namespace v1
} // namespace rsl

