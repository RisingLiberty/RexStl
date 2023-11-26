// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: uninitialized_copy_n.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/copy_n.h"

namespace rsl
{
	inline namespace v1
	{
		namespace internal
		{
			template <typename InputIterator, typename ForwardIt>
			inline ForwardIt uninitialized_copy_n_impl(InputIterator first, card32 count, ForwardIt dest, true_type /*unused*/)
			{
				return rsl::copy_n(first, count, dest);
			}

			template <typename InputIterator, typename ForwardIt>
			inline ForwardIt uninitialized_copy_n_impl(InputIterator first, card32 count, ForwardIt dest, false_type /*unused*/)
			{
				using value_type = typename rsl::iterator_traits<ForwardIt>::value_type;
				ForwardIt current_dst(dest);

				while (count--)
				{
					::new(static_cast<void*>(rsl::addressof(*current_dst))) value_type(*first);
					++first;
					++dest;
				}

				return current_dst;
			}
		} // namespace internal

		template <typename InputIterator, typename ForwardIt>
		constexpr ForwardIt uninitialized_copy_n(InputIterator first, card32 count, ForwardIt result)
		{
			using value_type = typename rsl::iterator_traits<ForwardIt>::value_type;

			return internal::uninitialized_copy_n_impl(first, count, result, rsl::is_trivial<value_type>());
		}
	} // namespace v1
} // namespace rsl