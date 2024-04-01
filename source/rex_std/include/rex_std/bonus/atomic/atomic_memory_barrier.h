// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_memory_barrier.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/types.h"

#include <intrin.h>

namespace rsl
{
  inline namespace v1
  {
#if defined(RSL_PLATFORM_ARM64)
  #if defined(RSL_COMPILER_MSVC)
    #define RSL_ARM_DMB_ISH   _ARM64_BARRIER_ISH
    #define RSL_ARM_DMB_ISHST _ARM64_BARRIER_ISHST
    #define RSL_ARM_DMB_ISHLD _ARM64_BARRIER_ISHLD
  #elif defined(RSL_COMPILER_GCC) || defined(RSL_COMPILED_CLANG)
    #define RSL_ARM_DMB_ISH   ish
    #define RSL_ARM_DMB_ISHST ishst
    #define RSL_ARM_DMB_ISHLD ishld
  #endif
#endif

    RSL_FORCE_INLINE void memory_barrier()
    {
#if defined(RSL_COMPILER_MSVC)
  #if defined(RSL_PLATFORM_X64)
      // NOTE:
      // While it makes no sense for a hardware memory barrier to not imply a compiler barrier.
      // MSVC docs do not explicitly state that, so better to be safe than sorry chasing down
      // hard to find bugs due to the compiler deciding to reorder things.

      volatile long _;
      _InterlockedExchangeAdd(&_, 0);
  #elif defined(RSL_PLATFORM_ARM64)
      compiler_barrier();
      __dmb(RSL_ARM_DMB_ISH);
      compiler_barrier();
  #endif
#elif defined(RSL_COMPILER_GCC) || defined(RSL_COMPILER_CLANG)
  #if defined(RSL_PLATFORM_X64)
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
      __asm__ __volatile__("lock; addl $0, -8(%%rsp)" ::: "memory", "cc");    // NOLINT(hicpp-no-assembler)
  #elif defined(RSL_PLATFORM_ARM64)
      __asm__ __volatile__("dmb " STRINGIZE(RSL_ARM_DMB_ISH) ::: "memory"); // NOLINT(hicpp-no-assembler)
  #endif
#else
      static_assert("memory barrier not implemented");
#endif
    }
    RSL_FORCE_INLINE void read_memory_barrier()
    {
#ifdef RSL_PLATFORM_X64
      compiler_barrier();
#else
      __asm__ __volatile__("dmb " STRINGIZE(RSL_ARM_DMB_ISHLD) ::: "memory"); // NOLINT(hicpp-no-assembler)
#endif
    }
    RSL_FORCE_INLINE void write_memory_barrier()
    {
#ifdef RSL_PLATFORM_X64
      compiler_barrier();
#else
      __asm__ __volatile__("dmb " STRINGIZE(RSL_ARM_DMB_ISHST) ::: "memory"); // NOLINT(hicpp-no-assembler)
#endif
    }
  } // namespace v1
} // namespace rsl
