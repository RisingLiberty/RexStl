// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_function.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_const.h"
#include "rex_std/internal/type_traits/is_reference.h"

namespace rsl
{
    template <typename T>
    struct is_function : public bool_constant<!is_const_v<const T> && !is_reference_v<T>> { };

    template <typename T>
    struct is_function<T&> : public false_type { };

    template <typename T>
    struct is_function<T&&> : public false_type { };

    template <typename T>
    constexpr bool is_function_v = is_function<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsFunctionStruct = is_function<T>;

    template <typename T>
    constexpr bool IsFunction = IsFunctionStruct<T>::value;
#endif

}
