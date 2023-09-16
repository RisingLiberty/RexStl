// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: uninitialized_fill_move.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/memory/uninitialized_fill.h"
#include "rex_std/internal/memory/uninitialized_move.h"

namespace rsl
{
  inline namespace v1
  {
		template <typename ForwardIterator, typename T, typename InputIterator>
		inline ForwardIterator
			uninitialized_fill_move(ForwardIterator result, ForwardIterator mid, const T& value, InputIterator first, InputIterator last)
		{
			rsl::uninitialized_fill(result, mid, value);

			return rsl::uninitialized_move(first, last, mid);
		}
  }
}
