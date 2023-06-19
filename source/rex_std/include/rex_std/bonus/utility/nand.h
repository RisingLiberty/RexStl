// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: nand.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    constexpr bool nand(T lhs, T rhs)
    {
      return !(lhs && rhs);
    }
  } // namespace v1
} // namespace rsl
