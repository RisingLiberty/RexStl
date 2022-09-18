// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: add_rvalue_reference.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/add_reference.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    struct add_rvalue_reference 
    {
        using type = typename bonus::add_reference<T>::RValue;
    };

    template <typename T>
    using add_rvalue_reference_t = typename bonus::add_reference<T>::RValue;

REX_RSL_END_NAMESPACE

