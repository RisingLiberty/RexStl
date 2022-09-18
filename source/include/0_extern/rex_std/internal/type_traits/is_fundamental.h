// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_fundamental.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

#include "rex_std/internal/type_traits/is_arithmetic.h"
#include "rex_std/internal/type_traits/is_null_pointer.h"
#include "rex_std/internal/type_traits/is_void.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    struct is_fundamental : public bool_constant<is_arithmetic_v<T> || is_null_pointer_v<T> || is_void_v<T>>
    {};

    template <typename T>
    constexpr bool is_fundamental_v = is_fundamental<T>;

REX_RSL_END_NAMESPACE
