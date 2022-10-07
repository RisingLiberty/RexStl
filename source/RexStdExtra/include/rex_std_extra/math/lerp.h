// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: lerp.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
constexpr T lerp(const T& from, const T& to, float32 amount)
{
  return from + ((to - from) * amount);
}

REX_RSL_END_NAMESPACE