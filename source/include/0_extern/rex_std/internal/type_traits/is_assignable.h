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

REX_RSL_BEGIN_NAMESPACE

    template <typename T, typename U>
    struct is_assignable : bool_constant<__is_assignable(T, U)>
    {};

    template <typename T, typename U>
    constexpr bool is_assignable_v = is_assignable<T, U>::value;

REX_RSL_END_NAMESPACE
