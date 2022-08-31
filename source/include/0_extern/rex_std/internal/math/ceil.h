// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: ceil.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
  template <typename T>
  constexpr T ceil(T num)
  {
    return (static_cast<T>(static_cast<int32>(num)) == num)
      ? num
      : static_cast<T>(static_cast<int32>(num) + int32(num > 0));
  }
}