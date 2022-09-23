// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_nothrow_constructible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T, typename... Args>
struct is_nothrow_constructible : bool_constant<__is_nothrow_constructible(T, Args...)>
{
};

template <typename T, typename... Args>
constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<T, Args>::value;

REX_RSL_END_NAMESPACE
