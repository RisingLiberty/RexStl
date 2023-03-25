// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: arch_arm_memory_barrier.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
#if defined(REX_PLATFORM_ARM64)
      void arm_memory_barrier()
      {
#if defined(REX_COMPILER_MSVC)
        // NOTE:
        //
        // While it makes no sense for a hardware memory barrier to not imply a compiler barrier.
        // MSVC docs do not explicitly state that, so better to be safe than sorry chasing down
        // hard to find bugs due to the compiler deciding to reorder things.
        REX_ATOMIC_COMPILER_BARRIER();
        __dmb(REX_ARM_DMB_ISH);
        REX_ATOMIC_COMPILER_BARRIER();

#elif defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)
        __asm__ __volatile__("dmb " STRINGIZE(REX_ARM_DMB_ISH) ::: "memory")
#endif
      }
      void arm_read_memory_barrier()
      {
#if defined(REX_COMPILER_MSVC)
        // NOTE:
        //
        // While it makes no sense for a hardware memory barrier to not imply a compiler barrier.
        // MSVC docs do not explicitly state that, so better to be safe than sorry chasing down
        // hard to find bugs due to the compiler deciding to reorder things.
        REX_ATOMIC_COMPILER_BARRIER();
        __dmb(REX_ARM_DMB_ISHST);
        REX_ATOMIC_COMPILER_BARRIER();

#elif defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)
        __asm__ __volatile__("dmb " STRINGIZE(REX_ARM_DMB_ISHST) ::: "memory")
#endif
      }
      void arm_write_memory_barrier()
      {
#if defined(REX_COMPILER_MSVC)
        // NOTE:
        //
        // While it makes no sense for a hardware memory barrier to not imply a compiler barrier.
        // MSVC docs do not explicitly state that, so better to be safe than sorry chasing down
        // hard to find bugs due to the compiler deciding to reorder things.
        REX_ATOMIC_COMPILER_BARRIER();
        __dmb(REX_ARM_DMB_ISHLD);
        REX_ATOMIC_COMPILER_BARRIER();

#elif defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)
        __asm__ __volatile__("dmb " STRINGIZE(REX_ARM_DMB_ISHLD) ::: "memory")
#endif
      }
#endif
    }
  }
}
