// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: uninitialized_fill.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/memory/addressof.h"

namespace rsl
{
  inline namespace v1
  {
		namespace internal
		{
			template <typename ForwardIterator, typename T>
			inline void uninitialized_fill_impl(ForwardIterator first, ForwardIterator last, const T& value, true_type)
			{
				rsl::fill(first, last, value);
			}

			template <typename ForwardIterator, typename T>
			void uninitialized_fill_impl(ForwardIterator first, ForwardIterator last, const T& value, false_type)
			{
				using value_type = typename rsl::iterator_traits<ForwardIterator>::value_type;
				ForwardIterator currentDest(first);

				for (; currentDest != last; ++currentDest)
				{
					::new((void*)rsl::addressof(*currentDest)) value_type(value);
				}
			}
		}

		template <typename ForwardIterator, typename T>
		inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
		{
			using value_type = typename rsl::iterator_traits<ForwardIterator>::value_type;
			internal::uninitialized_fill_impl(first, last, value, rsl::is_trivially_copy_assignable<value_type>());
		}

  } // namespace v1
} // namespace rsl

