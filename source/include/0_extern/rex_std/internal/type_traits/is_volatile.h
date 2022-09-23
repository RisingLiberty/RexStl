// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_volatile.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

template <typename>
constexpr bool is_volatile_v = false;

template <typename T>
constexpr bool is_volatile_v<volatile T> = true;

template <typename T>
struct is_volatile : public bool_constant<is_volatile_v<T>>
{
};

REX_RSL_END_NAMESPACE
