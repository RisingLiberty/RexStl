// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: this_thread.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/header/thread
//
// The class thread represents a single thread of execution.
//-----------------------------------------------------------------------------

#include "rex_std/bonus/time/xtime.h"
#include "rex_std/internal/chrono/clock.h"
#include "rex_std/internal/chrono/duration.h"
#include "rex_std/internal/chrono/time_point.h"
#include "rex_std/internal/thread/thread.h"

namespace rsl
{
  inline namespace v1
  {
    namespace this_thread
    {
      namespace internal
      {
        void sleep_this_thread_until(rsl::internal::xtime sleeptime);
      } // namespace internal

      // returns the id of the current thread
      thread::id get_id();

      // suggest that the implementation reschedule exeuction of the threads
      void yield();
      // stops execution of the current thread until a specified time point
      template <typename Clock, typename Duration>
      void sleep_until(const chrono::time_point<Clock, Duration>& absTime)
      {
        for(;;)
        {
          const auto now = Clock::now();
          if(absTime <= now)
          {
            return;
          }

          rsl::internal::xtime xtime = rsl::internal::to_xtime_clamped(absTime - now);
          internal::sleep_this_thread_until(xtime);
        }
      }
      // stops exeuction of the current thread for a specified time duration
      template <typename Rep, typename Period>
      void sleep_for(const chrono::duration<Rep, Period>& relTime)
      {
        return sleep_until(chrono::internal::to_abs_time(relTime));
      }
    } // namespace this_thread
  }   // namespace v1
} // namespace rsl