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

namespace rsl
{
    template <typename T> 
	struct is_final : public bool_constant<__is_final(T)>
    {};

    template <typename T>
    constexpr bool is_final_v = is_final<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    struct IsFinalStruct = is_final<T>;

    template <typename T>
    constexpr bool IsFinal = IsFinalStruct<T>;
#endif
}