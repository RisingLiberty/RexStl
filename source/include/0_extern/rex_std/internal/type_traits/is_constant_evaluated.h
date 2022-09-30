// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_constant_evaluated.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

inline constexpr bool is_constant_evaluated()
{
  return __builtin_is_constant_evaluated();
}

REX_RSL_END_NAMESPACE
