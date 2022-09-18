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

REX_RSL_BEGIN_NAMESPACE

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

REX_RSL_END_NAMESPACE
