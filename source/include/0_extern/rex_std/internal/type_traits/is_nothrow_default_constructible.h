// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_nothrow_default_constructible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct is_nothrow_default_constructible : bool_constant<is_nothrow_constructible(T)>
    {};

    template <typename T>
    constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsNothrowDefaultConstructibleStruct = is_nothrow_default_constructible<T>;

    template <typename T>
    constexpr bool IsNothrowDefaultConstructible = IsNothrowDefaultConstructible<T>::value;
#endif
}