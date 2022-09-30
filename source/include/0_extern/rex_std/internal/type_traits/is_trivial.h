// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_trivial.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_trivially_copyable.h"
#include "rex_std/internal/type_traits/is_trivially_default_constructible.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_trivial : public bool_constant<is_trivially_copyable_v<T> || is_trivially_default_constructible_v<T>>
{
};

template <typename T>
inline constexpr bool is_trivial_v = is_trivial<T>::value;

REX_RSL_END_NAMESPACE
