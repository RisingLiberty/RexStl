// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: has_virtual_destructor.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct has_virtual_destructor : public Boolconstant<__has_virtual_destructor(T)>
    {};

    template <typename T>
    constexpr bool has_virtual_destructor_v = has_virtual_destructor<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using HasVirtualDestructorStruct = has_virtual_destructor<T>;

    template <typename T>
    constexpr bool HasVirtualDestructor = HasVirtualDestructorStruct<T>::value;
#endif
}