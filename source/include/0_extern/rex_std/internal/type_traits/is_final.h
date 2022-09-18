// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_final.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T> 
	struct is_final : public bool_constant<__is_final(T)>
    {};

    template <typename T>
    constexpr bool is_final_v = is_final<T>::value;

REX_RSL_END_NAMESPACE
