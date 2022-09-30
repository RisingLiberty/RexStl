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

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_function : public bool_constant<!is_const_v<const T> && !is_reference_v<T>>
{
};

template <typename T>
struct is_function<T&> : public false_type
{
};

template <typename T>
struct is_function<T&&> : public false_type
{
};

template <typename T>
inline constexpr bool is_function_v = is_function<T>::value;

REX_RSL_END_NAMESPACE
