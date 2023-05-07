// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: thread.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/thread/thread.h"

#include "rex_std/assert.h"
#include "rex_std/format.h"
#include "rex_std/internal/exception/teminate.h"
#include "rex_std/internal/utility/exchange.h"
#include "rex_std/internal/utility/swap.h"
#include "rex_std/sstream.h"

#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {
    thread::thread()
        : m_handle(INVALID_HANDLE_VALUE)
        , m_id(0)
    {
    }

    thread::thread(thread&& other)
        : m_handle(other.m_handle)
        , m_id(other.m_id)
    {
      other.m_id     = thread::id(0);
      other.m_handle = INVALID_HANDLE_VALUE;
    }

    thread::~thread()
    {
      if(RSL_ASSERT_X(!joinable(), "joinable thread on destruction!"))
      {
        rsl::terminate();
      }
    }

    thread& thread::operator=(thread&& other)
    {
      if(RSL_ASSERT_X(!joinable(), "joinable thread on move assignment!"))
      {
        rsl::terminate();
      }

      m_id     = rsl::exchange(other.m_id, thread::id(0));
      m_handle = rsl::exchange(other.m_handle, INVALID_HANDLE_VALUE);

      return *this;
    }

    bool thread::joinable() const
    {
      return m_handle != INVALID_HANDLE_VALUE;
    }

    void thread::join()
    {
      WaitForSingleObject(m_handle, INFINITE);
      CloseHandle(m_handle);

      m_handle = INVALID_HANDLE_VALUE;
      m_id     = thread::id(0);
    }

    void thread::detach()
    {
      CloseHandle(m_handle);
      m_handle = INVALID_HANDLE_VALUE;
    }

    void thread::swap(thread& other)
    {
      rsl::swap(m_id, other.m_id);
      rsl::swap(m_handle, other.m_handle);
    }

    void thread::create(thread_start_func func, void* param)
    {
      m_handle = CreateThread(nullptr, 0, func, param, 0, &m_id.m_id);
      RSL_ASSERT_X(m_handle != INVALID_HANDLE_VALUE, "Failed to create thread with error: {}", GetLastError());
    }

    void swap(thread& lhs, thread& rhs)
    {
      lhs.swap(rhs);
    }

  } // namespace v1
} // namespace rsl