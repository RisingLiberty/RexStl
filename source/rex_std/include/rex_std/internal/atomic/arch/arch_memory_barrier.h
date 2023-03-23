

#ifndef REX_ATOMIC_INTERNAL_ARCH_MEMORY_BARRIER_H
#define REX_ATOMIC_INTERNAL_ARCH_MEMORY_BARRIER_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_MB()
//
#if defined(REX_ARCH_ATOMIC_CPU_MB)
  #define REX_ARCH_ATOMIC_CPU_MB_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_CPU_MB_AVAILABLE 0
#endif

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_WMB()
//
#if defined(REX_ARCH_ATOMIC_CPU_WMB)
  #define REX_ARCH_ATOMIC_CPU_WMB_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_CPU_WMB_AVAILABLE 0
#endif

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_RMB()
//
#if defined(REX_ARCH_ATOMIC_CPU_RMB)
  #define REX_ARCH_ATOMIC_CPU_RMB_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_CPU_RMB_AVAILABLE 0
#endif

#endif /* REX_ATOMIC_INTERNAL_ARCH_MEMORY_BARRIER_H */
