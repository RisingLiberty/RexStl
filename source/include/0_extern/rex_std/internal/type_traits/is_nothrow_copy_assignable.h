// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_nothrow_copy_assignable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct is_nothrow_copy_assignable : bool_constant<__is_nothrow_assignable(add_lvalue_reference_t<T>, add_lvalue_reference_t<const T>)>
    {};

    template <typename T>
    constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsNoThrowCopyAssignableStruct = is_nothrow_copy_assignable<T>;

    template <typename T>
    constexpr bool IsNoThrowCopyAssignable = is_nothrow_copy_assignable<T>::value;    
#endif
}