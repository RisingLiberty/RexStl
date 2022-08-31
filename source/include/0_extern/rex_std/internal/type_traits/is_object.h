// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_object.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_scalar.h"
#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/type_traits/is_union.h"
#include "rex_std/internal/type_traits/is_class.h"

namespace rsl
{
    template <typename T>
    struct is_object : public bool_constant<is_scalar_v<T> || is_array_v<T> || is_union_v<T> || is_class_v<T>>
    {};

    template <typename T>
    constexpr bool is_object_v = is_object<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsObjectStruct = is_object<T>;

    template <typename T>
    constexpr bool IsObject = is_object<T>::value;
#endif
}