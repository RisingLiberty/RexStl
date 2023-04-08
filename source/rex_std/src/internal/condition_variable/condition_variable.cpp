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

#include "rex_std/assert.h"
#include "rex_std/bonus/mutex/mutex_base.h"
#include "rex_std/internal/exception/teminate.h"
#include "rex_std/internal/thread/this_thread.h"

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

      impl(const impl&)            = delete;
      ~impl()                      = delete;
      impl& operator=(const impl&) = delete;

      void destroy() {}

      void wait(mutex::native_handle_type mtx)
      {
        if(!wait_for(mtx, INFINITE))
        {
          rsl::terminate();
        }
      }

      bool wait_for(mutex::native_handle_type mtx, int32 timeoutMs)
      {
        SRWLOCK* lock = reinterpret_cast<SRWLOCK*>(mtx_os_handle(mtx)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
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
      bool cnd_timedwait(condition_variable::impl* cond, mutex::native_handle_type mtx, const xtime& target)
      {
        int res = 1;

        rsl::internal::xtime now = rsl::internal::xtime::get();
        mtx_clear_owner(mtx);
        if(!cond->wait_for(mtx, target.diff_in_ms(now)))
        {
          now = rsl::internal::xtime::get();
          if(target.diff_in_ms(now) == 0)
          {
            res = 0;
          }
        }
        mtx_reset_owner(mtx);
        return res != 0;
      }

      inline constexpr card32 num_items = 20; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
      SRWLOCK g_thread_exit_mtx; // NOLINT(fuchsia-statically-constructed-objects, cppcoreguidelines-avoid-non-const-global-variables)

      void lock_thread_exit_mtx()
      {
        AcquireSRWLockExclusive(&g_thread_exit_mtx);
      }
      void unlock_thread_exit_mtx()
      {
        ReleaseSRWLockExclusive(&g_thread_exit_mtx);
      }

      struct at_thread_exit_data
      {
        DWORD thread_id;
        mutex::native_handle_type mtx;
        condition_variable::impl* cv;
        card32* res;
      };

      struct at_thread_exit_block
      {
        rsl::array<at_thread_exit_data, num_items> data;
        card32 num_used = 0;
        at_thread_exit_block* next = nullptr;
      };

      at_thread_exit_block g_thread_exit_data; // NOLINT(fuchsia-statically-constructed-objects, cppcoreguidelines-avoid-non-const-global-variables)

      void cnd_register_at_thread_exit(condition_variable::impl* cnd, mutex::native_handle_type mtx, int* p)
      {
        at_thread_exit_block* block = &g_thread_exit_data;
        lock_thread_exit_mtx();

        // loop through list of blocks
        while(block != nullptr)
        {
          // block is full. move to next block and allocate
          if(block->num_used == num_items)
          {
            if(block->next == nullptr)
            {
              block->next = static_cast<at_thread_exit_block*>(calloc(1, sizeof(at_thread_exit_block))); // NOLINT(cppcoreguidelines-no-malloc)
            }
            block = block->next;
          }

          // found block with available space
          else
          {
            // find an empty slot
            for(auto & i : block->data)
            {
              // store into empty slot
              if(i.mtx == nullptr)
              {
                i.thread_id = GetCurrentThreadId();
                i.mtx       = mtx;
                i.cv        = cnd;
                i.res       = p;
                ++block->num_used;
                break;
              }

              block = nullptr;
            }
          }
        }

        unlock_thread_exit_mtx();
      }
      void cnd_unregister_at_thread_exit(mutex::native_handle_type mtx)
      {
        at_thread_exit_block* block = &g_thread_exit_data;

        lock_thread_exit_mtx();

        // loop through list of blocks
        while(block != nullptr)
        {
          for(card32 i = 0; block->num_used != 0 && i < num_items; ++i)
          {
            // release slot
            if(block->data[i].mtx == mtx)
            {
              block->data[i].mtx = nullptr;
              --block->num_used;
            }
          }

          block = block->next;
        }

        unlock_thread_exit_mtx();
      }
    } // namespace internal

    condition_variable::condition_variable()
    {
      m_storage.set<condition_variable::impl>();
    }

    

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
      if(!rsl::internal::does_current_thread_own_mtx(lock.mutex()))
      {
        REX_ASSERT("Trying to wait for a mutex that's not locked or owned by thead");
      }

      // Nothing to do to comply with LWG-2135 because std::mutex lock/unlock are nothrow
      const bool res = internal::cnd_timedwait(internal_impl(), lock.mutex()->native_handle(), absTime);

      return res ? cv_status::no_timeout : cv_status::timeout;
    }

    condition_variable::native_handle_type condition_variable::native_handle()
    {
      return internal_impl();
    }

    void condition_variable::register_at_thread_exit(unique_lock<mutex>& lock, int* ready)
    {
      internal::cnd_register_at_thread_exit(internal_impl(), lock.mutex()->native_handle(), ready);
    }

    void condition_variable::unregister_at_thread_exit(unique_lock<mutex>& lock)
    {
      internal::cnd_unregister_at_thread_exit(lock.mutex()->native_handle());
    }

    condition_variable::impl* condition_variable::internal_impl()
    {
      return m_storage.get<condition_variable::impl>();
    }
  } // namespace v1
} // namespace rsl