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

namespace rsl
{
    template <typename T> 
	struct is_aggregate : public bool_constant<__is_aggregate(T)>
    {};

    template <typename T>
    constexpr bool is_aggregate_v = is_aggregate<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsAggregateStruct = is_aggregate<T>;

    template <typename T>
    constexpr bool IsAggregate = IsAggregateStruct<T>::value;
#endif
}