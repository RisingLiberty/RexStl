// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_array.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    template <typename>
    constexpr bool is_array_v = false; // determine whether type argument is an array

    template <typename T, size_t N>
    constexpr bool is_array_v<T[N]> = true;

    template <typename T>
    constexpr bool is_array_v<T[]> = true;

    template <class T>
    struct is_array : public bool_constant<is_array_v<T>> {};

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsArrayStruct = is_array<T>;

    template <typename T>
    constexpr bool IsArray = is_array<T>::value;
#endif
}
