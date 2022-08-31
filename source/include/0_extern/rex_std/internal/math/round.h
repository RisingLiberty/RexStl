// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: round.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
  template <typename T>
  constexpr T round(const T x)
  {
    return abs(x) - 0.5f < static_cast<int32>(abs(x))
      ? sign(x) * static_cast<T>(static_cast<int32>(abs(x)))
      : static_cast<T>(static_cast<int32>(x) + sign(x) * 1);
  }
}