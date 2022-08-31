// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: add_lvalue_reference.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/add_reference.h"

namespace rsl
{
    template <typename T>
    struct add_lvalue_reference 
    {
        using type = typename bonus::add_reference<T>::LValue;
    };

    template <typename T>
    using add_lvalue_reference_t = typename bonus::add_reference<T>::LValue;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using AddLValueReferenceStruct = add_lvalue_reference<T>;

    template <typename T>
    using AddLValueReference = typename AddLValueReferenceStruct<T>::type;
#endif
}
