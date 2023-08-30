// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: uninitialized_move_fill.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/memory/uninitialized_move.h"
#include "rex_std/internal/memory/uninitialized_fill.h"

namespace rsl
{
  inline namespace v1
  {
		template <typename InputIterator, typename ForwardIterator, typename T>
		inline void uninitialized_move_fill(InputIterator first1, InputIterator last1,
			ForwardIterator first2, ForwardIterator last2, const T& value)
		{
			const ForwardIterator mid(rsl::uninitialized_move(first1, last1, first2));

			rsl::uninitialized_fill(mid, last2, value);
		}
  }
}
