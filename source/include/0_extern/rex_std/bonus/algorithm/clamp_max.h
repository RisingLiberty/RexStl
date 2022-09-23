// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: clamp_max.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/min.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
constexpr T clamp_max(const T& x, const T& max)
{
  return (rsl::min)(x, max);
}

REX_RSL_END_NAMESPACE
