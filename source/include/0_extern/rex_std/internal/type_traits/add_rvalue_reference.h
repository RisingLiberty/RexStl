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

namespace rsl
{
    template <typename T>
    struct add_rvalue_reference 
    {
        using type = typename bonus::add_reference<T>::RValue;
    };

    template <typename T>
    using add_rvalue_reference_t = typename bonus::add_reference<T>::RValue;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using AddRValueReferenceStruct = add_rvalue_reference<T>;

    template <typename T>
    using AddRValueReference = typename AddRValueReferenceStruct<T>::type;
#endif
}
