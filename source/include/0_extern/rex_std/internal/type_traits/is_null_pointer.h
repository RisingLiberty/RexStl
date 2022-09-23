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

#include "rex_std/internal/cstddef/nullptr.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/remove_cv.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_null_pointer : public bool_constant<rsl::is_same_v<remove_cv_t<T>, nullptr_t>>
{
};

template <typename T>
constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

REX_RSL_END_NAMESPACE
