// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_date.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std_extra/time/date.h"

namespace rsl
{
  inline namespace v1
  {
    class date; // IWYU pragma: keep

    date current_date();

  } // namespace v1
} // namespace rsl