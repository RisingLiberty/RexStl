// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_reference.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
	template <typename T> struct is_reference : public false_type {};
	template <typename T> struct is_reference<T&> : public true_type {};
	template <typename T> struct is_reference<T&&> : public true_type {};

	template<typename T>
	constexpr bool is_reference_v = is_reference<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
	template <typename T>
	using IsReferenceStruct = is_reference<T>;

	template <typename T>
	constexpr bool IsReference = is_reference<T>::value;
#endif
}
