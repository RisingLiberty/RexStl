// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_empty.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename T>
    struct is_empty : public bool_constant<__is_empty(T)> {};

    template <typename T>
    constexpr bool is_empty_v = is_empty<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsEmptyStruct = is_empty<T>;

    template <typename T>
    constexpr bool IsEmpty = IsEmptyStruct<T>::value;
#endif
}
