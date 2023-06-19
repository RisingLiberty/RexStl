// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: ticks.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      int64 get_time_in_ticks();
    } // namespace internal
  }   // namespace v1
} // namespace rsl
