// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_trivially_constructible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T, typename ... Args>
    struct is_trivially_constructible : bool_constant<__is_trivially_constructible(T, Args...)>
    {};

    template <typename T>
    constexpr bool is_trivially_constructible_v = is_trivially_constructible<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T, typename ... Args>
    using IsTriviallyConstructibleStruct = is_trivially_constructible<T, Args...>;

    template <typename T, typename ... Args>
    constexpr bool IsTriviallyConstructible = is_trivially_constructible<T, Args...>::value;
#endif
}