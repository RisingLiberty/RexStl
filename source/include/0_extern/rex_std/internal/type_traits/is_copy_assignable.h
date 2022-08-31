// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_copy_assignable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct is_copy_assignable : bool_constant<__is_assignable(add_lvalue_reference_t<T>, add_lvalue_reference_t<const T>)>
    {};

    template <typename T>
    constexpr bool is_copy_assignable = is_copy_assignable<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    struct IsCopyAssignableStruct = is_copy_assignable<T>;

    template <typename T>
    constexpr bool IsCopyAssignable = IsCopyAssignableStruct<T>::value;
#endif
}