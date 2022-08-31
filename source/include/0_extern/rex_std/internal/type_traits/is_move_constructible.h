// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_move_constructible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct is_move_constructible : bool_constant<__is_constructible(T, T)>
    {};

    template <typename T>
    constexpr bool is_move_constructible_v = is_move_constructible<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsMoveConstructibleStruct = is_move_constructible<T>;

    template <typename T>
    constexpr bool IsMoveConstructible = IsMoveConstructibleStruct<T>::value;
#endif
}