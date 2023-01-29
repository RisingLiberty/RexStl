// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: xtime.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/time/xtime.h"
#include "rex_std/bonus/time/ticks.h"

#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      xtime xtime::get()
      {
        constexpr long nsec100_per_sec = rsl::nano::den / 100;

        int64 now_in_ticks = get_time_in_ticks();

        xtime time{};
        time.sec = static_cast<uint64>(now_in_ticks / nsec100_per_sec);
        time.nsec = static_cast<uint32>(now_in_ticks % nsec100_per_sec) * 100;

        return time;
      }

      void xtime::normalise() { // adjust so that 0 <= nsec < 1 000 000 000
        // normalize target time
        while (nsec < 0)
        {
          sec -= 1;
          nsec += rsl::nano::den;
        }

        // normalize target time
        while (rsl::nano::den <= nsec)
        {
          sec += 1;
          nsec -= rsl::nano::den;
        }
      }

      // return xtime object holding difference between xt and now, treating negative difference as 0
      xtime xtime::diff(const xtime& now) const
      {
        xtime diff = *this;
        diff.normalise();

        // avoid underflow
        if (diff.nsec < now.nsec)
        {
          diff.sec -= now.sec + 1;
          diff.nsec += rsl::nano::den - now.nsec;
        }
        // no underflow
        else
        {
          diff.sec -= now.sec;
          diff.nsec -= now.nsec;
        }
        // time is zero
        if (diff.sec < 0 || (diff.sec == 0 && diff.nsec <= 0))
        {
          diff.sec = 0;
          diff.nsec = 0;
        }
        return diff;
      }

      int32 xtime::diff_in_ms(const xtime& xt2) const
      {
        xtime diff = this->diff(xt2);
        return static_cast<long>(diff.sec * rsl::milli::den + (diff.nsec + rsl::micro::den - 1) / rsl::micro::den);
      }
    }
  }
}