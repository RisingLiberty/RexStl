// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: uninitialized_move.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/memory/uninitialized_copy.h"
#include "rex_std/internal/iterator/move_iterator.h"

namespace rsl
{
  inline namespace v1
  {
		template <typename InputIterator, typename ForwardIterator>
		inline ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator dest)
		{
			return rsl::uninitialized_copy(rsl::make_move_iterator(first), rsl::make_move_iterator(last), dest);
		}
  } // namespace v1
} // namespace rsl

