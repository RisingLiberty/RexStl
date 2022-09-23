// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: size.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T, count_t N>
constexpr count_t size(const T (&/*arr*/)[N])
{
  return N;
}

REX_RSL_END_NAMESPACE
