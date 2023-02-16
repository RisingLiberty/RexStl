// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: unique_lock.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/utility/exchange.h"
#include "rex_std/assert.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename Mutex>
    class unique_lock
    {
    public:
      unique_lock()
        : m_mutex(nullptr)
      {}

      unique_lock(Mutex& mutex)
        : m_mutex(&mutex)
      {
        lock();
      }
      unique_lock(const unique_lock&) = delete;
      unique_lock(unique_lock&& other)
      {
        m_mutex = rsl::exchange(other.m_mutex, nullptr);
      }

      ~unique_lock()
      {
        safe_unlock();
      }

      unique_lock& operator=(const unique_lock&) = delete;
      unique_lock& operator=(unique_lock&& other)
      {
        safe_unlock();
        m_mutex = rsl::exchange(other.m_mutex, nullptr);
      }

      void lock()
      {
        REX_ASSERT_X(m_mutex != nullptr, "Trying to lock mutex, but no is provided");
        m_mutex->lock();
      }
      bool try_lock()
      {
        REX_ASSERT_X(m_mutex != nullptr, "Trying to lock mutex, but no is provided");
        return m_mutex->try_lock();
      }
      void unlock()
      {
        REX_ASSERT_X(m_mutex != nullptr, "Trying to unlock mutex, but no is provided");
        m_mutex->unlock();
        m_mutex = nullptr;
      }

    private:
      void safe_unlock()
      {
        if (m_mutex)
        {
          unlock();
        }
      }

    private:
      Mutex* m_mutex;
    };
  }
}