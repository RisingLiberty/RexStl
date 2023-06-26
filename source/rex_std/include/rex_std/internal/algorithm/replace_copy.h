// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: replace_copy.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
		template <typename InputIterator, typename OutputIterator, typename T>
		OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_value, const T& new_value)
		{
			for (; first != last; ++first, ++result)
			{
				*result = (*first == old_value) 
					? new_value 
					: *first;
			}
			return result;
		}
  } // namespace v1
} // namespace rsl

