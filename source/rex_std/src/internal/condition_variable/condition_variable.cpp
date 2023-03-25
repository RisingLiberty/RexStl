// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: condition_variable.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/condition_variable/condition_variable.h"
#include "rex_std/bonus/mutex/mutex_base.h"
#include "rex_std/assert.h"
#include "rex_std/internal/exception/teminate.h"

#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {
    class condition_variable::impl
    {
    public:
      impl()
        : m_condition_variable()
      {
        InitializeConditionVariable(&m_condition_variable);
      }

      impl(const impl&) = delete;
      ~impl() = delete;
      impl& operator=(const impl&) = delete;

      void destroy()
      {}

      void wait(const mutex::native_handle_type mtx)
      {
        if (!wait_for(mtx, INFINITE))
        {
          rsl::terminate();
        }
      }

      bool wait_for(const mutex::native_handle_type mtx, int32 timeoutMs)
      {
        SRWLOCK* lock = reinterpret_cast<SRWLOCK*>(mtx_os_handle(mtx));
        return SleepConditionVariableSRW(&m_condition_variable, lock, timeoutMs, 0) != 0;
      }

      void notify_one()
      {
        WakeConditionVariable(&m_condition_variable);
      }
      void notify_all()
      {
        WakeAllConditionVariable(&m_condition_variable);
      }

    private:
      CONDITION_VARIABLE m_condition_variable;
    };

    namespace internal
    {
      bool cnd_timedwait(condition_variable::impl* cond, const mutex::native_handle_type mtx, const xtime& target)
      {
        int res = true;

        rsl::internal::xtime now = rsl::internal::xtime::get();
        mtx_clear_owner(mtx);
        if (!cond->wait_for(mtx, target.diff_in_ms(now)))
        {
          now = rsl::internal::xtime::get();
          if (target.diff_in_ms(now) == 0)
          {
            res = false;
          }
        }
        mtx_reset_owner(mtx);
        return res;
      }

      inline constexpr card32 num_items = 20;
      struct at_thread_exit_data
      {
        DWORD thread_id;
        mutex::native_handle_type mtx;
        condition_variable::impl* cv;
        card32* res;
      };

      struct at_thread_exit_block
      {
        at_thread_exit_data data[num_items];
        card32 num_used;
        at_thread_exit_block* next;
      };

      void cnd_register_at_thread_exit(condition_variable::impl*, const mutex::native_handle_type mtx, int* p)
      {

      }
      void cnd_unregister_at_thread_exit(const mutex::native_handle_type mtx)
      {

      }
    }

    condition_variable::condition_variable()
    {
      m_storage.set<condition_variable::impl>();
    }

    condition_variable::condition_variable(const condition_variable&) = delete;

    condition_variable::~condition_variable() = default;

    void condition_variable::notify_one()
    {
      internal_impl()->notify_one();
    }

    void condition_variable::notify_all()
    {
      internal_impl()->notify_all();
    }

    void condition_variable::wait(unique_lock<mutex>& lock)
    {
      internal_impl()->wait(lock.mutex()->native_handle());
    }

    cv_status condition_variable::wait_until(unique_lock<mutex>& lock, const internal::xtime& absTime)
    {
      // wait for signal with timeout
      if (!rsl::internal::does_current_thread_own_mtx(lock.mutex()))
      {
        REX_ASSERT("Trying to wait for a mutex that's not locked or owned by thead");
      }

      // Nothing to do to comply with LWG-2135 because std::mutex lock/unlock are nothrow
      const bool res = internal::cnd_timedwait(internal_impl(), lock.mutex()->native_handle(), absTime);

      return res
        ? cv_status::no_timeout
        : cv_status::timeout;
    }

    condition_variable::native_handle_type condition_variable::native_handle()
    {
      return internal_impl();
    }

    void condition_variable::register_at_thread_exit(unique_lock<mutex>& lock, int* ready)
    {
      _Cnd_register_at_thread_exit(_Mycnd(), lock.release()->_Mymtx(), ready);
    }

    void condition_variable::unregister_at_thread_exit(mutex& _Mtx)
    {
      _Cnd_unregister_at_thread_exit(_Mtx._Mymtx());
    }

    condition_variable::impl* condition_variable::internal_impl()
    {
      return m_storage.get<condition_variable::impl>();
    }
  }
}