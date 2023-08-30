// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: uninitialized_default_construct.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/memory/addressof.h"

namespace rsl
{
  inline namespace v1
  {
		template <typename ForwardIterator, typename Count>
		constexpr ForwardIterator uninitialized_default_construct(ForwardIterator first, Count n)
		{
			using value_type = typename rsl::iterator_traits<ForwardIterator>::value_type;
			ForwardIterator current_dst(first);

			for (; n > 0; --n, ++current_dst)
			{
				::new (rsl::addressof(*current_dst)) value_type;
			}
				return current_dst;
		}
  } // namespace v1
} // namespace rsl

