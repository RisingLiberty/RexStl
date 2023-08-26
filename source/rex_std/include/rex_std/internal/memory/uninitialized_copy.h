// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: uninitialized_copy.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_trivial.h"
#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/memory/addressof.h"
#include "rex_std/internal/algorithm/copy.h"

namespace rsl
{
  inline namespace v1
  {
		namespace internal
		{
			template <typename InputIterator, typename ForwardIt>
			inline ForwardIt uninitialized_copy_impl(InputIterator first, InputIterator last, ForwardIt dest, true_type)
			{
				return rsl::copy(first, last, dest); // The copy() in turn will use memcpy for POD types.
			}

			template <typename InputIterator, typename ForwardIt>
			inline ForwardIt uninitialized_copy_impl(InputIterator first, InputIterator last, ForwardIt dest, false_type)
			{
				using value_type = typename rsl::iterator_traits<ForwardIt>::value_type;
				ForwardIt current_dst(dest);

				// ForwardIt = int32
				// InputIterator = rsl::v1::move_iterator<rsl::v1::deque_iterator<rsl::v1::int32, 8>>
				// value_type = int32

				for (; first != last; ++first, ++current_dst)
				{
					::new(static_cast<void*>(rsl::addressof(*current_dst))) value_type(*first);
				}

				return current_dst;
			}
		}

		template <typename InputIterator, typename ForwardIt>
		constexpr ForwardIt uninitialized_copy(InputIterator first, InputIterator last, ForwardIt result)
		{
			using value_type = typename rsl::iterator_traits<ForwardIt>::value_type;

			return internal::uninitialized_copy_impl(first, last, result, rsl::is_trivial<value_type>());
		}
  } // namespace v1
} // namespace rsl
