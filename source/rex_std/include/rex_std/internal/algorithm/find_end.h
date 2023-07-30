// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: find_end.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/algorithm/search.h"
#include "rex_std/internal/functional/equal_to.h"

namespace rsl
{
  inline namespace v1
  {

		template <typename ForwardIterator1, typename ForwardIterator2, typename Predicate>
		ForwardIterator1 find_end_impl(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, Predicate predicate, forward_iterator_tag, forward_iterator_tag)
		{
			if (first2 != last2) // We have to do this check because the search algorithm below will return first1 (and not last1) if the first2/last2 range is empty.
			{
				for (ForwardIterator1 result = last1; ; )
				{
					const ForwardIterator1 resultNext(rsl::search<ForwardIterator1, ForwardIterator2, Predicate>(first1, last1, first2, last2, predicate));

					if (resultNext != last1) // If another sequence was found...
					{
						first1 = result = resultNext;
						++first1;
					}
					else
					{
						return result;
					}
				}
			}
			return last1;
		}

		template <typename BidirectionalIterator1, typename BidirectionalIterator2, typename Predicate>
		BidirectionalIterator1 find_end_impl(BidirectionalIterator1 first1, BidirectionalIterator1 last1, BidirectionalIterator2 first2, BidirectionalIterator2 last2, Predicate predicate, bidirectional_iterator_tag, bidirectional_iterator_tag)
		{
			using reverse_iterator1 = rsl::reverse_iterator<BidirectionalIterator1>;
			using reverse_iterator2 = rsl::reverse_iterator<BidirectionalIterator2>;

			reverse_iterator1 rresult(rsl::search(reverse_iterator1(last1), reverse_iterator1(first1), reverse_iterator2(last2), reverse_iterator2(first2), predicate));
			if (rresult.base() != first1) // If we found something...
			{
				BidirectionalIterator1 result(rresult.base());
				rsl::advance(result, -rsl::distance(first2, last2));
				return result;
			}
			return last1;
		}

		template <typename ForwardIterator1, typename ForwardIterator2>
		ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
		{
			using IC1 = typename rsl::iterator_traits<ForwardIterator1>::iterator_category;
			using IC2 = typename rsl::iterator_traits<ForwardIterator2>::iterator_category;

			return rsl::find_end_impl(first1, last1, first2, last2, rsl::equal_to<typename iterator_traits<ForwardIterator1>::value_type>(), IC1(), IC2());
		}

		template <typename ForwardIterator1, typename ForwardIterator2, typename Predicate>
		ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, Predicate predicate)
		{
			using IC1 = typename rsl::iterator_traits<ForwardIterator1>::iterator_category;
			using IC2 = typename rsl::iterator_traits<ForwardIterator2>::iterator_category;

			return rsl::find_end_impl<ForwardIterator1, ForwardIterator2, Predicate>
				(first1, last1, first2, last2, predicate, IC1(), IC2());
		}
  } // namespace v1
} // namespace rsl
