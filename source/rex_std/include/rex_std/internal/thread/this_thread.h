// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: this_thread.h
// Copyright (c) Nick De Breuck 2022
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
#include "rex_std/internal/thread/thread.h"

namespace rsl
{
  inline namespace v1
  {
    namespace this_thread
    {
      namespace internal
      {
        template <typename Rep, typename Period>
        auto to_abs_time(const chrono::duration<Rep, Period>& rel_time)
        {
          const auto zero                   = chrono::duration<Rep, Period>::zero();
          const auto now                    = chrono::steady_clock::now();
          decltype(now + rel_time) abs_time = now;
          if(rel_time > zero)
          {
            const auto forever = (chrono::steady_clock::time_point::max)();
            if(abs_time < forever - rel_time)
            {
              abs_time += rel_time;
            }
            else
            {
              abs_time = forever;
            }
          }

          return abs_time;
        }

        void sleep_this_thread_until(rsl::internal::xtime sleeptime);
      } // namespace internal

      // returns the id of the current thread
      thread::id get_id();

      // suggest that the implementation reschedule exeuction of the threads
      void yield();
      // stops execution of the current thread until a specified time point
      template <typename Clock, typename Duration>
      void sleep_until(const chrono::time_point<Clock, Duration>& abs_time)
      {
        for(;;)
        {
          const auto now = Clock::now();
          if(abs_time <= now)
          {
            return;
          }

          rsl::internal::xtime xtime = rsl::internal::to_xtime_clamped(abs_time - now);
          internal::sleep_this_thread_until(xtime);
        }
      }
      // stops exeuction of the current thread for a specified time duration
      template <typename Rep, typename Period>
      void sleep_for(const chrono::duration<Rep, Period>& rel_time)
      {
        return sleep_until(internal::to_abs_time(rel_time));
      }
    } // namespace this_thread
  }   // namespace v1
} // namespace rsl