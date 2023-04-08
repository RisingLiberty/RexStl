// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: condition_variable.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/time/xtime.h"
#include "rex_std/chrono.h"
#include "rex_std/internal/mutex/mutex.h"
#include "rex_std/internal/mutex/unique_lock.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
#if defined(REX_PLATFORM_X64)
      inline constexpr card32 g_condition_variable_size      = 72;
      inline constexpr card32 g_condition_variable_alignment = 8;
#endif
    } // namespace internal

    enum class cv_status
    {
      no_timeout,
      timeout
    };

    class condition_variable
    {
    public:
      class impl;
      using native_handle_type = impl*;

      condition_variable();
      condition_variable(const condition_variable&) = delete;
      ~condition_variable()                         = default;

      condition_variable& operator=(const condition_variable&) = delete;

      void notify_one();
      void notify_all();

      void wait(unique_lock<mutex>& lock);

      template <typename Predicate>
      void wait(unique_lock<mutex>& lock, Predicate pred)
      {
        while(!pred())
        {
          wait(lock);
        }
      }

      template <typename Rep, typename Period>
      cv_status wait_for(unique_lock<mutex>& lock, const chrono::duration<Rep, Period>& relTime)
      {
        if(relTime <= chrono::duration<Rep, Period>::zero())
        {
          return cv_status::timeout;
        }

        rsl::internal::xtime xtime = rsl::internal::to_xtime_clamped(relTime);
        return wait_until(lock, xtime);
      }

      template <typename Rep, typename Period, typename Predicate>
      bool wait_for(unique_lock<mutex>& lock, const chrono::duration<Rep, Period>& relTime, Predicate pred)
      {
        // wait for signal with timeout and check predicate
        return wait_until_impl(lock, chrono::internal::to_abs_time(relTime), pred);
      }

      template <typename Clock, typename Duration>
      cv_status wait_until(unique_lock<mutex>& lock, const chrono::time_point<Clock, Duration>& absTime)
      {
#ifdef REX_ENABLE_WITH_CPP20
        static_assert(chrono::is_clock_v<Clock>, "Clock type required");
#endif

        for(;;)
        {
          const auto now = Clock::now();
          if(absTime <= now)
          {
            return cv_status::timeout;
          }

          rsl::internal::xtime xtime = rsl::internal::to_xtime_clamped(absTime - now);
          const cv_status result     = wait_until(lock, xtime);
          if(result == cv_status::no_timeout)
          {
            return cv_status::no_timeout;
          }
        }
      }

      template <typename Clock, typename Duration, typename Predicate>
      bool wait_until(unique_lock<mutex>& lock, const chrono::time_point<Clock, Duration>& absTime, Predicate pred)
      {
        // wait for signal with timeout and check predicate
#if REX_ENABLE_WITH_CPP20
        static_assert(chrono::is_clock_v<Clock>, "Clock type required");
#endif // REX_ENABLE_WITH_CPP20

        return wait_until_impl(lock, absTime, pred);
      }

      cv_status wait_until(unique_lock<mutex>& lock, const internal::xtime& absTime);

      template <typename Predicate>
      bool wait_until(unique_lock<mutex>& lock, const internal::xtime* absTime, Predicate pred)
      {
        // wait for signal with timeout and check predicate
        return wait_until_impl(lock, absTime, pred);
      }

      REX_NO_DISCARD native_handle_type native_handle();

      void register_at_thread_exit(unique_lock<mutex>& lock, int* ready);

      static void unregister_at_thread_exit(unique_lock<mutex>& lock);

    private:
      impl* internal_impl();

      template <typename Predicate>
      bool wait_until_impl(unique_lock<mutex>& lock, const xtime* absTime, Predicate& pred)
      {
        while(!pred())
        {
          if(wait_until(lock, absTime) == cv_status::timeout)
          {
            return pred();
          }
        }

        return true;
      }

      template <typename Clock, typename Duration, typename Predicate>
      bool wait_until_impl(unique_lock<mutex>& lock, const chrono::time_point<Clock, Duration>& absTime, Predicate& pred)
      {
        while(!pred())
        {
          const auto now = Clock::now();
          if(absTime <= now)
          {
            return false;
          }

          rsl::internal::xtime xtime = rsl::internal::to_xtime_clamped(absTime - now);
          if(wait_until(lock, xtime) == cv_status::timeout)
          {
            return pred();
          }
        }

        return true;
      }

    private:
      aligned_storage<internal::g_condition_variable_size, internal::g_condition_variable_alignment> m_storage;
    };
  } // namespace v1
} // namespace rsl
