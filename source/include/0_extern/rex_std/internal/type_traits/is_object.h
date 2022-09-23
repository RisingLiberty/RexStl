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
#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/type_traits/is_class.h"
#include "rex_std/internal/type_traits/is_scalar.h"
#include "rex_std/internal/type_traits/is_union.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_object : public bool_constant<is_scalar_v<T> || is_array_v<T> || is_union_v<T> || is_class_v<T>>
{
};

template <typename T>
constexpr bool is_object_v = is_object<T>::value;

REX_RSL_END_NAMESPACE
