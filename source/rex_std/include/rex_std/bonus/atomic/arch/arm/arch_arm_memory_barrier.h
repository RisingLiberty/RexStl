

#ifndef REX_ATOMIC_INTERNAL_ARCH_ARM_MEMORY_BARRIER_H
#define REX_ATOMIC_INTERNAL_ARCH_ARM_MEMORY_BARRIER_H

#pragma once

#if defined(REX_COMPILER_MSVC) && !defined(REX_COMPILER_CLANG_CL)

  #if defined(REX_PLATFORM_ARM32)

    #define REX_ARM_DMB_ISH _ARM_BARRIER_ISH

    #define REX_ARM_DMB_ISHST _ARM_BARRIER_ISHST

    #define REX_ARM_DMB_ISHLD _ARM_BARRIER_ISH

  #elif defined(REX_PLATFORM_ARM64)

    #define REX_ARM_DMB_ISH _ARM64_BARRIER_ISH

    #define REX_ARM_DMB_ISHST _ARM64_BARRIER_ISHST

    #define REX_ARM_DMB_ISHLD _ARM64_BARRIER_ISHLD

  #endif

  /**
   * NOTE:
   *
   * While it makes no sense for a hardware memory barrier to not imply a compiler barrier.
   * MSVC docs do not explicitly state that, so better to be safe than sorry chasing down
   * hard to find bugs due to the compiler deciding to reorder things.
   */

  #define REX_ARCH_ATOMIC_ARM_EMIT_DMB(option)                                                                                                                                                                                                           \
    REX_ATOMIC_COMPILER_BARRIER();                                                                                                                                                                                                                       \
    __dmb(option);                                                                                                                                                                                                                                       \
    REX_ATOMIC_COMPILER_BARRIER()

#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)

  #define REX_ARM_DMB_ISH ish

  #define REX_ARM_DMB_ISHST ishst

  #if defined(REX_PLATFORM_ARM32)

    #define REX_ARM_DMB_ISHLD ish

  #elif defined(REX_PLATFORM_ARM64)

    #define REX_ARM_DMB_ISHLD ishld

  #endif

  #define REX_ARCH_ATOMIC_ARM_EMIT_DMB(option) __asm__ __volatile__("dmb " STRINGIZE(option) ::: "memory")

#endif

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_MB()
//
#define REX_ARCH_ATOMIC_CPU_MB() REX_ARCH_ATOMIC_ARM_EMIT_DMB(REX_ARM_DMB_ISH)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_WMB()
//
#define REX_ARCH_ATOMIC_CPU_WMB() REX_ARCH_ATOMIC_ARM_EMIT_DMB(REX_ARM_DMB_ISHST)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_RMB()
//
#define REX_ARCH_ATOMIC_CPU_RMB() REX_ARCH_ATOMIC_ARM_EMIT_DMB(REX_ARM_DMB_ISHLD)

#endif /* REX_ATOMIC_INTERNAL_ARCH_ARM_MEMORY_BARRIER_H */
