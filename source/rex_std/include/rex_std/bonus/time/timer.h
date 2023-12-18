// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: timer.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/time/timepoint.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {

    class timer
    {
    public:
      explicit timer(float32 maxTimeInSeconds);

      void update();
      void reset();

      void set_max_time(float32 maxTimeInSeconds);

      bool is_done() const;

    private:
      float32 m_max_time;
      float32 m_current_time;

      rsl::time_point m_prev_time_point;
    };

  } // namespace v1
} // namespace rsl