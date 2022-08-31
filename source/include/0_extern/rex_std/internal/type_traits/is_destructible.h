// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_destructible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct is_destructible : bool_constant<__is_destructible(T)>
    {};

    template <typename T>
    constexpr bool is_destructible_v = is_destructible<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsDestructibleStruct = is_destructible<T>;

    template <typename T>
    constexpr bool IsDestructible = IsDestructibleStruct<T>::value;
#endif
}