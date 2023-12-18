// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: clock.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std_extra/time/timepoint.h"

namespace rsl
{
  inline namespace v1
  {

    class clock
    {
    public:
      clock();

      void update();
      void pause();
      void resume();

      float32 delta_time() const;

    private:
      rsl::time_point m_start_time;
      rsl::time_point m_current_time;

      bool m_is_paused;

      // delta time is expressed in seconds
      float32 m_delta_time;
    };

  } // namespace v1
} // namespace rsl