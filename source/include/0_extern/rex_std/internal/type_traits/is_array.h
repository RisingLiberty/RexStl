// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_array.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

template <typename>
constexpr bool is_array_v = false; // determine whether type argument is an array

template <typename T, size_t N>
constexpr bool is_array_v<T[N]> = true;

template <typename T>
constexpr bool is_array_v<T[]> = true;

template <class T>
struct is_array : public bool_constant<is_array_v<T>>
{
};

REX_RSL_END_NAMESPACE
