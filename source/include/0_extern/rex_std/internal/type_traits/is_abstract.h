// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_abstract.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_abstract : public bool_constant<__is_abstract(T)>
{
};

template <typename T>
constexpr bool is_abstract_v = is_abstract<T>::value;

REX_RSL_END_NAMESPACE
