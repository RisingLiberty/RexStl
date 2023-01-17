// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_thread.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/concurrency/win/win_thread.h"

#include "rex_std_extra/diagnostics/assert.h"
#include "rex_std_extra/diagnostics/win/win_call.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

#define NOMINMAX
#include <Windows.h>

rsl::Thread::Thread()
    : m_handle(win::InvalidThreadHandle)
    , m_thread_id(0)
{
}

rsl::Thread::Thread(win::ThreadHandle handle)
    : m_handle(handle)
    , m_thread_id(GetThreadId(m_handle))
{
}

rsl::Thread::Thread(Thread&& other)
    : m_handle(other.m_handle)
    , m_thread_id(other.m_thread_id)
{
  other.m_handle    = win::InvalidThreadHandle;
  other.m_thread_id = 0;
}

rsl::Thread& rsl::Thread::operator=(Thread&& other)
{
  m_handle    = other.m_handle;
  m_thread_id = other.m_thread_id;

  other.m_handle    = win::InvalidThreadHandle;
  other.m_thread_id = 0;

  return *this;
}

rsl::Thread::~Thread()
{
  REX_ASSERT_X(m_thread_id == rsl::this_thread::get_id() || !joinable(), "joinable thread on destruction");
}

rsl::ThreadID rsl::Thread::id() const
{
  return m_thread_id;
}

bool rsl::Thread::joinable() const
{
  return m_handle != win::InvalidThreadHandle;
}

void rsl::Thread::join()
{
  WaitForSingleObject(m_handle, INFINITE);
  CloseHandle(m_handle);

  m_handle    = win::InvalidThreadHandle;
  m_thread_id = 0;
}

void rsl::Thread::detach()
{
  CloseHandle(m_handle);
  m_handle = win::InvalidThreadHandle;
}

bool rsl::Thread::operator==(const Thread& other) const
{
  return m_thread_id == other.m_thread_id;
}
bool rsl::Thread::operator!=(const Thread& other) const
{
  return m_thread_id != other.m_thread_id;
}

void rsl::Thread::create(thread_start_func func, void* param)
{
  m_handle = WIN_CALL(CreateThread(NULL, 0, func, param, 0, &m_thread_id));
}

rsl::ThreadID rsl::this_thread::get_id()
{
  return GetCurrentThreadId();
}