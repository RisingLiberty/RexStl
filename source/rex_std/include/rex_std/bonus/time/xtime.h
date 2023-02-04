// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: xtime.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/chrono/clock.h"
#include "rex_std/internal/chrono/duration.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      struct xtime
      {
      public:
        static xtime get();
        void normalise();
        xtime diff(const xtime& other) const;
        int32 diff_in_ms(const xtime& other) const;

      public:
        uint64 sec;
        uint32 nsec;
      };

      // converts the abs time to xtime clamped to a maximum (10 days by default)
      template <typename Rep, typename Period>
      xtime to_xtime_clamped(const chrono::duration<Rep, Period>& relTime, const chrono::nanoseconds max = chrono::hours(24) * 10)
      {
        const chrono::duration<float32> max_duration = max;
        chrono::nanoseconds time                     = chrono::system_clock::now().time_since_epoch();
        const bool should_clamp                      = relTime > max_duration;
        if(should_clamp)
        {
          time += max;
        }
        else
        {
          time += chrono::duration_cast<chrono::nanoseconds>(relTime);
        }

        const auto whole_seconds = chrono::duration_cast<chrono::seconds>(time);
        xtime xtime {};
        xtime.sec = whole_seconds.count();
        time -= whole_seconds;
        xtime.nsec = static_cast<uint32>(time.count());

        return xtime;
      }
    } // namespace internal
  }   // namespace v1
} // namespace rsl
