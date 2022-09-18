// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: count_if.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

	// Note: The non-predicate version of count_if is count and not another variation of count_if.
	// This is because both versions would have three parameters and there could be ambiguity.
	template <typename InputIterator, typename Predicate>
	typename InputIterator::difference_type count_if(InputIterator first, InputIterator last, Predicate predicate)
	{
		typename InputIterator::difference_type result = 0;

		for (; first != last; ++first)
		{
			if (predicate(*first))
				++result;
		}
		return result;
	}

REX_RSL_END_NAMESPACE
