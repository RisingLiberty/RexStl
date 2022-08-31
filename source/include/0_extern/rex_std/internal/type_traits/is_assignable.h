// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_assignable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T, typename U>
    struct is_assignable : bool_constant<__is_assignable(T, U)>
    {};

    template <typename T, typename U>
    constexpr bool is_assignable_v = is_assignable<T, U>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T, typename U>
    using IsAssignableStruct = is_assignable<T, U>;

    template <typename T, typename U>
    constexpr bool IsAssignable = IsAssignableStruct<T, U>::value;
#endif
}