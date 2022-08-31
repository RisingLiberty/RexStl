// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_layout_compatible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T, typename U>
    struct is_layout_compatible : public bool_constant<__is_layout_compatible(T, U)>
    {};

    template <typename T, typename U>
    constexpr bool is_layout_compatible_v = is_layout_compatible<T, U>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T, typename U>
    using IsLayoutCompatibleStruct = is_layout_compatible_v<T, U>;

    template <typename T, typename U>
    constexpr bool IsLayoutCompatible = IsLayoutCompatibleStruct<T, U>::value;
#endif

}