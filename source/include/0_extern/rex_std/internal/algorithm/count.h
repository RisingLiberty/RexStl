// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: count.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

	template <typename InputIterator, typename T>
	typename InputIterator::difference_type count(InputIterator first, InputIterator last, const T& value)
	{
		typename InputIterator::difference_type result = 0;

		for (; first != last; ++first)
		{
			if (*first == value)
				++result;
		}
		return result;
	}

REX_RSL_END_NAMESPACE
