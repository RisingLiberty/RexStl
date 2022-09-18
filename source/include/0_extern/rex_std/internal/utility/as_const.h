// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: as_const.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/add_const.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    constexpr add_const_t<T>& as_const(T& t)
    {
        return t;
    }

    template <typename T>
    void as_const(const T&&) = delete;

REX_RSL_END_NAMESPACE
