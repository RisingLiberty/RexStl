// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_same.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename, typename>
    constexpr bool is_same_v = false;
    template <typename T>
    constexpr bool is_same_v<T, T> = true;

    template <typename T1, typename T2>
    struct is_same : public bool_constant<is_same_v<T1, T2>> {};

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T1, typename T2>
    using IsSameStruct = is_same<T1, T2>;

    template <typename T1, typename T2>
    constexpr bool IsSame = is_same<T1, T2>::value;
#endif
}
