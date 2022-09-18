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

#include "rex_std/internal/type_traits/is_same.h"
#include "rex_std/internal/type_traits/remove_cv.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    struct is_null_pointer : public is_same<typename remove_cv_t<T>::type, decltype(nullptr)> {};

    template <typename T>
    constexpr bool is_null_pointer_v = is_null_pointer_v<T>::value;

REX_RSL_END_NAMESPACE
