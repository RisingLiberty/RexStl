// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: lerp.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl { inline namespace v1 {

template <typename T>
constexpr T lerp(const T& from, const T& to, float32 amount)
{
  return from + ((to - from) * amount);
}

}}