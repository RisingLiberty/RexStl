// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: log2.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    template <typename Size>
    inline Size log2(Size n)
    {
      int i;
      for(i = 0; n; ++i)
      {
        n >>= 1;
      }

      return i - 1;
    }
  } // namespace v1
} // namespace rsl
