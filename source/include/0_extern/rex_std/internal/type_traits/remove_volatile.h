// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_volatile.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct remove_volatile
    {
        using type = T;
    };

    template <typename T>
    struct remove_volatile<volatile T>
    {
        using type = T;
    };

    template <typename T>
    using remove_volatile_t = typename remove_volatile<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using RemoveVolatileStruct = remove_volatile_t<T>;

    template <typename T>
    using RemoveVolatile = typename remove_volatile<T>::type;
#endif
}
