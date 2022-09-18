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

REX_RSL_BEGIN_NAMESPACE

    template <typename Base, typename Derived>
    struct is_pointer_inter_convertible_base_of : public bool_constant<__is_pointer_interconvertible_base_of(Base, Derived)>
    {};

    template <typename Base, typename Derived>
    constexpr bool is_pointer_inter_convertible_base_of_v = is_pointer_inter_convertible_base_of<Base, Derived>::value;

REX_RSL_END_NAMESPACE
