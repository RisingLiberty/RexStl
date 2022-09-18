// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: add_const.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    struct add_const
    {
        using type = const T;
    };

    template <typename T>
    using add_const_t = typename add_const<T>::type;

REX_RSL_END_NAMESPACE
