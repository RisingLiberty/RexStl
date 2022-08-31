// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_void.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/remove_cv.h"
#include "rex_std/internal/type_traits/is_same.h"

namespace rsl
{
    template <typename T>
    struct is_void : public bool_constant<is_same_v<remove_cv_t<T>, void>>
    {};

    template <typename T>
    constexpr bool is_void_v = is_void<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsVoidStruct = is_void<T>;

    template <typename T>
    constexpr bool IsVoid = IsVoidStruct<T>::value;
#endif
}