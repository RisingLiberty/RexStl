// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: find_last_of.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/algorithm/find.h"
#include "rex_std/internal/algorithm/find_if.h"

namespace rsl
{
  inline namespace v1
  {
		template <typename BidirectionalIterator1, typename ForwardIterator2>
		constexpr BidirectionalIterator1 find_last_of(BidirectionalIterator1 first1, BidirectionalIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
		{
			if ((first1 != last1) && (first2 != last2))
			{
				BidirectionalIterator1 it1(last1);

				while ((--it1 != first1) && (rsl::find(first2, last2, *it1) == last2))
					; // Do nothing

				if ((it1 != first1) || (rsl::find(first2, last2, *it1) != last2))
				{
					return it1;
				}
			}

			return last1;
		}


		template <typename BidirectionalIterator1, typename ForwardIterator2, typename BinaryPredicate>
		BidirectionalIterator1 find_last_of(BidirectionalIterator1 first1, BidirectionalIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate)
		{
			using value_type = typename rsl::iterator_traits<BidirectionalIterator1>::value_type;

			if ((first1 != last1) && (first2 != last2))
			{
				BidirectionalIterator1 it1(last1);
				
				while ((--it1 != first1) && (rsl::find_if(first2, last2, [&](const value_type& val) { return predicate(*it1, val); }) == last2))
					; // Do nothing

				if ((it1 != first1) || (rsl::find_if(first2, last2, [&](const value_type& val) { return predicate(*it1, val); }) != last2))
				{
					return it1;
				}
			}

			return last1;
		}
  }
}
