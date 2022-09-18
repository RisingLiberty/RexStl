// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: add_reference.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/void.h"

REX_RSL_BEGIN_NAMESPACE

    namespace bonus
    {
        // add reference (non-referenceable type)
        template <typename T, typename = void>
        struct add_reference
        {
            using LValue = T;
            using RValue = T;
        };

        // (referenceable type)
        template <typename T>
        struct add_reference<T, void_t<T&>>
        {
            using LValue = T&;
            using RValue = T&&;
        };
    }

REX_RSL_END_NAMESPACE
