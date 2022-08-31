// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: abs.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl::internal
{
  template <typename T>
  constexpr T abs(T value)
  {
    return (value > 0) ? value : -value;
  }
}