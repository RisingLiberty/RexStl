// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_pointer_interconvertible_base_of.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename Base, typename Derived>
    struct is_pointer_inter_convertible_base_of : public bool_constant<__is_pointer_interconvertible_base_of(Base, Derived)>
    {};

    template <typename Base, typename Derived>
    constexpr bool is_pointer_inter_convertible_base_of_v = is_pointer_inter_convertible_base_of<Base, Derived>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename Base, typename Derived>
    using IsPointerInterConvertibleBaseOfStruct = is_pointer_inter_convertible_base_of<Base, Derived>;

    template <typename Base, typename Derived>
    constexpr bool IsPointerInterConvertibleBaseOf = IsPointerInterConvertibleBaseOfStruct<Base, Derived>::value;
#endif
}