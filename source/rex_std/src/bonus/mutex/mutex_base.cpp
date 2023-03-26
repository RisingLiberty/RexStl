// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: mutex_base.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/mutex/mutex_base.h"

#include "rex_std/assert.h"

#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      class mutex_base::internal
      {
        friend bool does_current_thread_own_mtx(mutex_base* mtx);

      public:
        internal()
            : m_srw_lock()
            , m_thread_id(0)
        {
          InitializeSRWLock(&m_srw_lock);
        }

        void lock()
        {
          const DWORD thread_id = GetCurrentThreadId();
          REX_ASSERT_X(m_thread_id != thread_id, "deadlock! trying to lock the same mutex twice on the same thread");
          m_thread_id = thread_id;
          AcquireSRWLockExclusive(&m_srw_lock);
        }
        bool try_lock()
        {
          return TryAcquireSRWLockExclusive(&m_srw_lock) != 0;
        }
        void unlock()
        {
          m_thread_id = 0;
          ReleaseSRWLockExclusive(&m_srw_lock);
        }

        void clear_owner()
        {
          m_thread_id = static_cast<DWORD>(-1);
          --m_count;
        }
        void reset_owner()
        {
          m_thread_id = GetCurrentThreadId();
          ++m_count;
        }
        SRWLOCK* os_handle()
        {
          return &m_srw_lock;
        }

      private:
        SRWLOCK m_srw_lock;
        card32 m_count;
        DWORD m_thread_id;
      };

      bool does_current_thread_own_mtx(mutex_base* mtx)
      {
        return mtx->native_handle()->m_count != 0 && mtx->native_handle()->m_thread_id == GetCurrentThreadId();
      }

      void mtx_clear_owner(mutex_base::internal* mtx)
      {
        mtx->clear_owner();
      }
      void mtx_reset_owner(mutex_base::internal* mtx)
      {
        mtx->reset_owner();
      }
      void* mtx_os_handle(mutex_base::internal* mtx)
      {
        return mtx->os_handle();
      }

      static_assert(sizeof(mutex_base::internal) <= g_mutex_size, "incorrect g_mutex_size");
      static_assert(alignof(mutex_base::internal) <= g_mutex_alignment, "incorrect g_mutex_alignment");

      mutex_base::mutex_base()
          : m_internal_storage()
          , m_internal(nullptr)
      {
        m_internal_storage.set<mutex_base::internal>();
        m_internal = m_internal_storage.get<mutex_base::internal>(); // NOLINT(cppcoreguidelines-prefer-member-initializer)
      }

      void mutex_base::lock()
      {
        m_internal->lock();
      }
      bool mutex_base::try_lock()
      {
        return m_internal->try_lock();
      }
      void mutex_base::unlock()
      {
        m_internal->unlock();
      }

      mutex_base::native_handle_type mutex_base::native_handle()
      {
        return m_internal;
      }

    } // namespace internal
  }   // namespace v1
} // namespace rsl