// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_extent.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct remove_extent 
    {
        using type = T;
    };

    template <typename T, size_t I>
    struct remove_extent<T[I]> 
    {
        using type = T;
    };

    template <typename T>
    struct remove_extent<T[]> 
    {
        using type = T;
    };

    template <typename T>
    using remove_extent_t = typename remove_extent<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using RemoveExtentStruct = remove_extent<T>;

    template <typename T>
    using RemoveExtent = typename RemoveExtentStruct<T>::type;
#endif
}
