// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stopwatch.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std_extra/time/timepoint.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {

    class stopwatch
    {
    public:
      stopwatch();

      void stop();
      void pause();
      void resume();

      float32 time_in_seconds() const;
      float32 time_in_ms() const;

    private:
      rsl::time_point m_start;
      rsl::time_point m_end;

      rsl::time_point m_pause_start;
      float32 m_paused_time_in_ms;
    };

  } // namespace v1
} // namespace rsl