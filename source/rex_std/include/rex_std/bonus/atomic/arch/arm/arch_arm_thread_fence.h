

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_THREAD_FENCE_*()
//
#if defined(REX_COMPILER_MSVC)

  #define REX_ARCH_ATOMIC_THREAD_FENCE_RELAXED()

  #define REX_ARCH_ATOMIC_THREAD_FENCE_ACQUIRE() REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_THREAD_FENCE_RELEASE() REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_THREAD_FENCE_ACQ_REL() REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_THREAD_FENCE_SEQ_CST() REX_ATOMIC_CPU_MB()

#endif
