// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_thread_fence.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/atomic/atomic_memory_barrier.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    REX_FORCE_INLINE void atomic_thread_fence(rsl::memory_order order)
    {
#if defined(REX_COMPILER_MSVC)
      (void)order;
  #if defined(REX_PLATFORM_ARM64)
      memory_barrier();
  #elif defined(REX_PLATFORM_X64)
      compiler_barrier();
  #endif
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      switch(order)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_thread_fence(__ATOMIC_RELAXED);
        case rsl::v1::memory_order::consume: return __atomic_thread_fence(__ATOMIC_CONSUME);
        case rsl::v1::memory_order::acquire: return __atomic_thread_fence(__ATOMIC_ACQUIRE);
        case rsl::v1::memory_order::release: return __atomic_thread_fence(__ATOMIC_RELEASE);
        case rsl::v1::memory_order::acq_rel: return __atomic_thread_fence(__ATOMIC_ACQ_REL);
        case rsl::v1::memory_order::seq_cst: return __atomic_thread_fence(__ATOMIC_SEQ_CST);
        default: RSL_ASSERT("Invalid memory order for atomic thread_fence"); break;
      }
#endif
    }
  } // namespace v1
} // namespace rsl
