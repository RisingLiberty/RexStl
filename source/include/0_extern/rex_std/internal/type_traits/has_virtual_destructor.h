// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: has_virtual_destructor.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct has_virtual_destructor : public Boolconstant<__has_virtual_destructor(T)>
{
};

template <typename T>
constexpr bool has_virtual_destructor_v = has_virtual_destructor<T>::value;

REX_RSL_END_NAMESPACE
