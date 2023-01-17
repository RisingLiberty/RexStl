// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: type_not_equal.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {

    template <int b1, int b2>
    struct type_not_equal
    {
      static const bool value = (b1 != b2);
    };

  } // namespace v1
} // namespace rsl
