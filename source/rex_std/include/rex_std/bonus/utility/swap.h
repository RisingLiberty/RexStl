// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: swap.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <typename T>
    constexpr void swap_adl(T& lhs, T& rhs)
    {
      T tmp = std::move(lhs);
      lhs   = std::move(rhs);
      rhs   = std::move(tmp);
    }

  } // namespace v1
} // namespace rsl