// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: this_thread.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/thread/this_thread.h"
#include "rex_std/ratio.h"

#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {
    namespace this_thread
    {
      namespace internal
      {
        void sleep_this_thread_until(rsl::internal::xtime xtime)
        {
          rsl::internal::xtime now = rsl::internal::xtime::get();
          do
          {
            Sleep(xtime.diff_in_ms(now));
            now = rsl::internal::xtime::get();
          } while (now.sec < xtime.sec || now.sec == xtime.sec && now.nsec < xtime.nsec);
        }
      }

      thread::id get_id()
      {
        return GetCurrentThreadId();
      }

      void yield()
      {
        SwitchToThread();
      }
    }
  }
}