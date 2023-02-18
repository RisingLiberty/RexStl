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
      public:
        internal()
            : m_thread_id(0)
        {
          InitializeSRWLock(&m_srw_lock);
        }

        void lock()
        {
          DWORD thread_id = GetCurrentThreadId();
          REX_ASSERT_X(m_thread_id != thread_id, "deadlock! trying to lock the same mutex twice on the same thread");
          m_thread_id = thread_id;
          AcquireSRWLockExclusive(&m_srw_lock);
        }

        bool try_lock()
        {
          return TryAcquireSRWLockExclusive(&m_srw_lock);
        }

        void unlock()
        {
          m_thread_id = 0;
          ReleaseSRWLockExclusive(&m_srw_lock);
        }

      private:
        SRWLOCK m_srw_lock;
        DWORD m_thread_id;
      };

      static_assert(sizeof(mutex_base::internal) <= g_mutex_size, "incorrect g_mutex_size");
      static_assert(alignof(mutex_base::internal) <= g_mutex_alignment, "incorrect g_mutex_alignment");

      mutex_base::mutex_base()
      {
        m_internal_storage.set<mutex_base::internal>();
        m_internal = m_internal_storage.get<mutex_base::internal>();
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