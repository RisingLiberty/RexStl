// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: declval.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/add_rvalue_reference.h"
#include "rex_std/bonus/utility/always_false.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    typename add_rvalue_reference_t<T> declval()
    {
        static_assert(internal::always_false<T>, "declval cannot be called in an evaluated expression");
    }

REX_RSL_END_NAMESPACE
