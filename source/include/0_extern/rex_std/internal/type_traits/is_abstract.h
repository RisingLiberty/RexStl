// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_abstract.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T> 
	struct is_abstract : public bool_constant<__is_abstract(T)>
    {};

    template <typename T>
    constexpr bool is_abstract_v = is_abstract<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsAbstractStruct = is_abstract<T>;

    template <typename T>
    constexpr bool IsAbstract = IsAbstractStruct<T>::value;
#endif
}