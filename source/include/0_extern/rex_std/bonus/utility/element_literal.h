// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: element_literal
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

constexpr int32 operator"" _elem(unsigned long long int count)
{
  return static_cast<int32>(count);
}

REX_RSL_END_NAMESPACE
