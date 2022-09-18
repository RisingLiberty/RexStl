// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: copy_if.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

	template <typename InputIterator, typename OutputIterator, typename Predicate>
	OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator dst, Predicate predicate)
	{
		// This implementation's performance could be improved by taking a more complicated approach like with the copy algorithm.
		for (; first != last; ++first)
		{
			if (predicate(*first))
			{
				*dst++ = *first;
			}
		}

		return dst;
	}

REX_RSL_END_NAMESPACE
