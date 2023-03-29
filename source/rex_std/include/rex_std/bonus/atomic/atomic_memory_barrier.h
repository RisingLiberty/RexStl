// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_memory_barrier.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include <intrin.h>

namespace rsl
{
  inline namespace v1
  {
    REX_FORCE_INLINE void memory_barrier()
    {
#if defined (REX_COMPILER_MSVC)
      // NOTE:
      // While it makes no sense for a hardware memory barrier to not imply a compiler barrier.
      // MSVC docs do not explicitly state that, so better to be safe than sorry chasing down
      // hard to find bugs due to the compiler deciding to reorder things.

      volatile long _;
      _InterlockedExchangeAdd(&_, 0);
#elif defined (REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      // NOTE:
       //
       // mfence orders all loads/stores to/from all memory types.
       // We only care about ordinary cacheable memory so lighter weight locked instruction
       // is far faster than a mfence to get a full memory barrier.
       // lock; addl against the top of the stack is good because:
       //     distinct for every thread so prevents false sharing
       //     that cacheline is most likely cache hot
       //
       // We intentionally do it below the stack pointer to avoid false RAW register dependencies,
       // in cases where the compiler reads from the stack pointer after the lock; addl instruction
       //
       // Accounting for Red Zones or Cachelines doesn't provide extra benefit.
      __asm__ __volatile__("lock; addl $0, -8(%%rsp)" ::: "memory", "cc");
#endif
    }
    REX_FORCE_INLINE void read_memory_barrier()
    {
#if defined (REX_COMPILER_MSVC)
      compiler_barrier();
#elif defined (REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      __asm__ __volatile__("" ::: "memory");
#endif
    }
    REX_FORCE_INLINE void write_memory_barrier()
    {
#if defined (REX_COMPILER_MSVC)
      compiler_barrier();
#elif defined (REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      __asm__ __volatile__("" ::: "memory");
#endif
    }
  }
}
