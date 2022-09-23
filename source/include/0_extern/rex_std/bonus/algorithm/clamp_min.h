// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: clamp_min.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/algorithm/max.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
constexpr T clamp_min(const T& x, const T& min)
{
  return rsl::max(x, min);
}

REX_RSL_END_NAMESPACE
