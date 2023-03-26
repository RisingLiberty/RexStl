#pragma once

#include "rex_std/bonus/compiler.h"

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_MB()
//
#if defined(REX_COMPILER_MSVC)
#include <intrin.h>
#endif

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      // this needs to be inlined
#if defined(REX_COMPILER_MSVC)
      REX_FORCE_INLINE void x86_memory_barrier()
      {
        // NOTE:
        // While it makes no sense for a hardware memory barrier to not imply a compiler barrier.
        // MSVC docs do not explicitly state that, so better to be safe than sorry chasing down
        // hard to find bugs due to the compiler deciding to reorder things.

        volatile long _;
        _InterlockedExchangeAdd(&_, 0);
      }
      REX_FORCE_INLINE void x86_read_memory_barrier()
      {
        _ReadWriteBarrier();
      }
      REX_FORCE_INLINE void x86_write_memory_barrier()
      {
        _ReadWriteBarrier();
      }
#elif defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)
      REX_FORCE_INLINE void x86_memory_barrier()
      {
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
        __asm__ __volatile__("lock; addl $0, -8(%%rsp)" ::: "memory", "cc")
      }
      REX_FORCE_INLINE void x86_read_memory_barrier()
      {
        static_assert(false, "read memory barrier not implemented for " REX_COMPILER_NAME)
      }
      REX_FORCE_INLINE void x86_write_memory_barrier()
      {
        static_assert(false, "write memory barrier not implemented for " REX_COMPILER_NAME)
      }
#else
      static_assert(false, "memory barrier not implemented for " REX_COMPILER_NAME)
#endif
    }
  }
}

#define REX_ARCH_ATOMIC_CPU_MB() rsl::internal::x86_memory_barrier()

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_WMB()
//
#define REX_ARCH_ATOMIC_CPU_WMB() REX_ATOMIC_COMPILER_BARRIER()

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_RMB()
//
#define REX_ARCH_ATOMIC_CPU_RMB() REX_ATOMIC_COMPILER_BARRIER()
