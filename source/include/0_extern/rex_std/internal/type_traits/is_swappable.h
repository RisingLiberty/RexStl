// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_swappable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/bonus/type_traits/unused.h"
#include "rex_std/bonus/type_traits/is_swappable_utils.h"

namespace rsl
{
    template <typename T>
	struct is_swappable : public bool_constant<!is_same_v<decltype(swap(declval<T&>(), declval<T&>())), Unused>>
    {};

    template <typename T>
    constexpr bool is_swappable_v = is_swappable<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsSwappableStruct = is_swappable<T>;

    template <typename T>
    constexpr bool IsSwappable = is_swappable<T>::value;
#endif
}