// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_polymorphic.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T> 
	struct is_polymorphic : public bool_constant<__is_polymorphic(T)>
    {};

    template <typename T>
    constexpr bool is_polymorphic_v = is_polymorphic<T>::value;

REX_RSL_END_NAMESPACE
