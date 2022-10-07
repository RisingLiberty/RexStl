// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: trunc.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T, typename T2>
constexpr T trunc(T2 value)
{
  return static_cast<T>(value);
}

REX_RSL_END_NAMESPACE