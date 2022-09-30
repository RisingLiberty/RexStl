// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: negation.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct negation : bool_constant<!bool(T::value)>
{
};

template <typename T>
inline constexpr bool negation_v = negation<T>::value;

REX_RSL_END_NAMESPACE
