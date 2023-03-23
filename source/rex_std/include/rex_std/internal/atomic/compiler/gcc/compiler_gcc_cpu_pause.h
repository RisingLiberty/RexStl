

#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_CPU_PAUSE_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_CPU_PAUSE_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_CPU_PAUSE()
//
#if defined(REX_PLATFORM_X86) || defined(REX_PLATFORM_X64)

  #define REX_COMPILER_ATOMIC_CPU_PAUSE() __asm__ __volatile__("pause")

#elif defined(REX_PLATFORM_ARM32) || defined(REX_PLATFORM_ARM64)

  #define REX_COMPILER_ATOMIC_CPU_PAUSE() __asm__ __volatile__("yield")

#endif

#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_CPU_PAUSE_H */
