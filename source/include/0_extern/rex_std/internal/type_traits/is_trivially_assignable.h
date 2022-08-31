// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_trivially_assignable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T, typename U>
    struct is_trivially_assignable : bool_constant<__is_trivially_assignable(T, U)>
    {};

    template <typename T, typename U>
    constexpr bool is_trivially_assignable_v = is_trivially_assignable<T, U>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T, typename U>
    using IsTriviallyAssignableStruct = is_trivially_assignable<T, U>;

    template <typename T, typename U>
    constexpr bool IsTriviallyAssignable = is_trivially_assignable<T, U>::value;
#endif
}