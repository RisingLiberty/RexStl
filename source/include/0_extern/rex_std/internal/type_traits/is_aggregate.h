// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_aggregate.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T> 
	struct is_aggregate : public bool_constant<__is_aggregate(T)>
    {};

    template <typename T>
    constexpr bool is_aggregate_v = is_aggregate<T>::value;

REX_RSL_END_NAMESPACE
