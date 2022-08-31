// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_volatile.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename>
    constexpr bool is_volatile_v = false;

    template <typename T>
    constexpr bool is_volatile_v<volatile T> = true;

    template <typename T>
    struct is_volatile : public bool_constant<is_volatile_v<T>>
    {};

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsVolatileStruct = is_volatile<T>;

    template <typename T>
    constexpr bool IsVolatile = is_volatile<T>::value;
#endif
}