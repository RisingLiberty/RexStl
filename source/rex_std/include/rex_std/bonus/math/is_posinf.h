// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_posinf.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/limits.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T>
    constexpr bool is_posinf(T val)
    {
      return val == numeric_limits<T>::infinity();
    }
  }
}
