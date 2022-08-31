// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: add_volatile.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct add_volatile
    {
        using type = volatile T;
    };

    template <typename T>
    using add_volatile_t = add_volatile<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using AddVolatileStruct = add_volatile<T>;

    template <typename T>
    using AddVolatile = typename AddVolatileStruct<T>::type;
#endif
}