// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_null_pointer.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/remove_cv.h"
#include "rex_std/internal/cstddef/nullptr.h"

namespace rsl
{
    template <typename T>
    struct is_null_pointer : public bool_constant<rsl::is_same_v<remove_cv_t<T>, nullptr_t>>
    {};

    template <typename T>
    constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsNullPointerStruct = is_null_pointer<T>;

    template <typename T>
    constexpr bool IsNullPointer = is_null_pointer<T>::value;
#endif
}