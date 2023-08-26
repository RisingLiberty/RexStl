// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: uninitialized_copy_copy.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/memory/uninitialized_copy.h"

namespace rsl
{
  inline namespace v1
  {
		template <typename InputIterator1, typename InputIterator2, typename ForwardIterator>
		constexpr ForwardIterator uninitialized_copy_copy(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, ForwardIterator result)
		{
			const ForwardIterator mid(rsl::uninitialized_copy(first1, last1, result));

			return rsl::uninitialized_copy(first2, last2, mid);
		}
  }
}
