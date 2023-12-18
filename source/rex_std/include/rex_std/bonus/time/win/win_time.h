// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_time.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std_extra/time/time.h"

namespace rsl
{
  inline namespace v1
  {
    class time; // IWYU pragma: keep

    time current_time();

  } // namespace v1
} // namespace rsl