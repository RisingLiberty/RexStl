// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: win_thread.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/memory.h"
#include "rex_std_extra/diagnostics/assert.h"

REX_RSL_BEGIN_NAMESPACE

namespace win
{
  using ThreadHandle                     = void*;
  const ThreadHandle InvalidThreadHandle = (ThreadHandle)-1; // this can't be constexpr, it'll cause a compiler error as -1 is an invalid address
} // namespace win

using ThreadID = unsigned long;

class Thread
{
private:
  template <typename Func>
  class FuncWrapper
  {
  public:
    FuncWrapper(Func func)
        : m_func(func)
    {
    }

    Func function()
    {
      return m_func;
    }

  private:
    Func m_func;
  };

public:
  using thread_start_func = unsigned long(__stdcall*)(void*);

  Thread();
  Thread(win::ThreadHandle handle);

  template <typename Func, rsl::EnableIf<rsl::IsInvocable<Func>, bool> = true>
  Thread(Func func)
      : m_handle(win::InvalidThreadHandle)
      , m_thread_id(0)
  {
    assign(func);
  }

  Thread(const Thread&) = delete;
  Thread(Thread&&);

  ~Thread();

  Thread& operator=(const Thread&) = delete;
  Thread& operator=(Thread&&);

  ThreadID id() const;

  template <typename Func>
  void assign(Func func)
  {
    REX_ASSERT_X(!joinable(), "Assigning new func to already executing thread");

    rsl::UniquePtr<FuncWrapper<Func>> func_wrapper = rsl::make_unique<FuncWrapper<Func>>(func);
    create(&invoke<Func>, func_wrapper.release());
  }

  bool joinable() const;

  void join();
  void detach();

  bool operator==(const Thread& other) const;
  bool operator!=(const Thread& other) const;

private:
  template <typename Func>
  static unsigned long __stdcall invoke(void* param)
  {
    // The reason why I copy the function ptr is so that we don't have a possible heap alloc
    // that lasts for the rest of the program
    // this could lead to "memory leaks" which wouldn't really be leaking
    rsl::UniquePtr<FuncWrapper<Func>> func(static_cast<FuncWrapper<Func>*>(param));
    auto function_ptr = func->function();
    func.reset();
    rsl::invoke(function_ptr);
    return 0;
  }

  void create(thread_start_func func, void* param);

private:
  win::ThreadHandle m_handle;
  ThreadID m_thread_id;
};

namespace this_thread
{
  ThreadID get_id();
}

REX_RSL_END_NAMESPACE