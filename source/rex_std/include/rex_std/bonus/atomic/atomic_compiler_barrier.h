// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_compiler_barrier.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/compiler.h"
#include "rex_std/bonus/types.h"

#include <intrin.h>

namespace rsl
{
  inline namespace v1
  {
    RSL_FORCE_INLINE void compiler_barrier()
    {
#if defined(RSL_COMPILER_MSVC)
      _ReadWriteBarrier();
#elif defined(RSL_COMPILER_GCC) || defined(RSL_COMPILER_CLANG)
      __asm__ __volatile__("" ::: "memory"); // NOLINT(hicpp-no-assembler)
#endif
    }

    template <typename T>
    RSL_FORCE_INLINE void compiler_barrier(const T* ptr)
    {
#if defined(RSL_COMPILER_MSVC)
      internal::g_compiler_barrier_data_dependency_func(ptr);
      compiler_barrier();
#elif defined(RSL_COMPILER_GCC) || defined(RSL_COMPILER_CLANG)
      __asm__ __volatile__("" : /* Output Operands */ : "r"(ptr) : "memory");
#endif
    }
  } // namespace v1
} // namespace rsl
