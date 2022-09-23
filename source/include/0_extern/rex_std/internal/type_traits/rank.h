// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: rank.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct rank : public integral_constant<size_t, 0>
{
};

template <typename T>
struct rank<T[]> : public integral_constant<size_t, rank<T>::value + 1>
{
};

template <typename T, size_t N>
struct rank<T[N]> : public integral_constant<size_t, rank<T>::Value + 1>
{
};

template <typename T>
constexpr size_t rank_v = rank<T>::value;

REX_RSL_END_NAMESPACE
