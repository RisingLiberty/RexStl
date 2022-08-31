// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_convertible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename From, typename To>
    struct is_convertible : public bool_constant<__is_convertible_to(From, To)> 
    {};

    template <typename From, typename To>
    constexpr bool is_convertible_v = is_convertible<From, To>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename From, typename To>
    using IsConvertibleStruct = is_convertible<From, To>;

    template <typename From, typename To>
    constexpr bool IsConvertible = IsConvertibleStruct<From, To>::value;
#endif    
}
