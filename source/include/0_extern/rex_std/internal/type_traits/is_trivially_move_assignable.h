// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_trivially_move_assignable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct is_trivially_move_assignable : bool_constant<__is_trivially_assignable(add_lvalue_reference_t<T>, T)>
    {};

    template <typename T>
    constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsTriviallyMoveAssignableStruct = is_trivially_move_assignable<T>;

    template <typename T>
    constexpr bool IsTriviallyMoveAssignable = is_trivially_move_assignable<T>::value;
#endif
}