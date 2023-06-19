// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: this_thread.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/internal/thread/this_thread.h"

#include <Windows.h>
// IWYU pragma: no_include <built-in>

namespace rsl
{
  inline namespace v1
  {
    namespace this_thread
    {
      namespace internal
      {
        void sleep_this_thread_until(rsl::internal::xtime sleeptime)
        {
          rsl::internal::xtime now = rsl::internal::xtime::get();
          do
          {
            Sleep(sleeptime.diff_in_ms(now));
            now = rsl::internal::xtime::get();
          } while((now.sec < sleeptime.sec || now.sec == sleeptime.sec) && now.nsec < sleeptime.nsec);
        }
      } // namespace internal

      thread::id get_id()
      {
        return thread::id(GetCurrentThreadId());
      }

      void yield()
      {
        SwitchToThread();
      }
    } // namespace this_thread
  }   // namespace v1
} // namespace rsl