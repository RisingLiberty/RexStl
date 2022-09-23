// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: exp.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std_extra/math/pow.h"

REX_RSL_BEGIN_NAMESPACE

constexpr float32 exp(const card32 exp)
{
  return pow(Euler, exp);
}

REX_RSL_END_NAMESPACE
