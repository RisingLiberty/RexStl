// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_permutation.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/distance.h"
#include "rex_std/internal/iterator/advance.h"
#include "rex_std/internal/algorithm/count.h"
#include "rex_std/internal/algorithm/find.h"

namespace rsl
{
  inline namespace v1
  {

		template<typename ForwardIterator1, typename ForwardIterator2>
		bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
		{
			using difference_type = typename rsl::iterator_traits<ForwardIterator1>::difference_type;

			// Skip past any equivalent initial elements.
			while ((first1 != last1) && (*first1 == *first2))
			{
				++first1;
				++first2;
			}

			if (first1 != last1)
			{
				const difference_type first1Size = rsl::distance(first1, last1);
				ForwardIterator2 last2 = first2;
				rsl::advance(last2, first1Size);

				for (ForwardIterator1 i = first1; i != last1; ++i)
				{
					if (i == rsl::find(first1, i, *i))
					{
						const difference_type c = rsl::count(first2, last2, *i);

						if ((c == 0) || (c != rsl::count(i, last1, *i)))
						{
							return false;
						}
					}
				}
			}

			return true;
		}

		/// is_permutation
		///
		template<typename ForwardIterator1, typename ForwardIterator2, class BinaryPredicate>
		bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate predicate)
		{
			using difference_type = typename rsl::iterator_traits<ForwardIterator1>::difference_type;

			// Skip past any equivalent initial elements.
			while ((first1 != last1) && predicate(*first1, *first2))
			{
				++first1;
				++first2;
			}

			if (first1 != last1)
			{
				const difference_type first1Size = rsl::distance(first1, last1);
				ForwardIterator2 last2 = first2;
				rsl::advance(last2, first1Size);

				for (ForwardIterator1 i = first1; i != last1; ++i)
				{
					if (i == rsl::find(first1, i, *i, predicate))
					{
						const difference_type c = rsl::count(first2, last2, *i, predicate);

						if ((c == 0) || (c != rsl::count(i, last1, *i, predicate)))
						{
							return false;
						}
					}
				}
			}

			return true;
		}
  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"