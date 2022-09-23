// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: add_cv.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/add_const.h"
#include "rex_std/internal/type_traits/add_volatile.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct add_cv
{
  using type = add_const_t<add_volatile_t<T>>;
};

template <typename T>
using add_cv_t = add_cv<T>::type;

REX_RSL_END_NAMESPACE
