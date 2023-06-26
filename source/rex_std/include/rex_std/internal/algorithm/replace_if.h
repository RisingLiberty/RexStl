// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: replace_if.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
		template <typename ForwardIterator, typename Predicate, typename T>
		void replace_if(ForwardIterator first, ForwardIterator last, Predicate predicate, const T& new_value)
		{
			for (; first != last; ++first)
			{
				if (predicate(*first))
				{
					*first = new_value;
				}
			}
		}
  } // namespace v1
} // namespace rsl

