// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_move_assignable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    struct is_move_assignable : bool_constant<__is_assignable(add_lvalue_reference_t<T>, T)>
    {};

    template <typename T>
    constexpr bool is_move_assignable_v = is_move_assignable<T>::value;

REX_RSL_END_NAMESPACE
