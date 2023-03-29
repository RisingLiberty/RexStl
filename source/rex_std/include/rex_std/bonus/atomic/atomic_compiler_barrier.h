// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_compiler_barrier.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include <intrin.h>

namespace rsl
{
  inline namespace v1
  {
    REX_FORCE_INLINE void compiler_barrier()
    {
#if defined(REX_COMPILER_MSVC)
      _ReadWriteBarrier();
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      __asm__ __volatile__("" ::: "memory");
#endif
    }

    template <typename T>
    REX_FORCE_INLINE void compiler_barrier(const T* ptr)
    {
#if defined(REX_COMPILER_MSVC)
      _ReadWriteBarrier(const_cast<T*>(rsl::addressof(ptr)));
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      __asm__ __volatile__("" ::: "memory");
#endif
    }
  }
}
