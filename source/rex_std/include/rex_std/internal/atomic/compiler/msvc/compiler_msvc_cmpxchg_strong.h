

#ifndef REX_ATOMIC_INTERNAL_COMPILER_MSVC_CMPXCHG_STRONG_H
#define REX_ATOMIC_INTERNAL_COMPILER_MSVC_CMPXCHG_STRONG_H

#pragma once

#if defined(REX_PLATFORM_X64)

  #define REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_8  _InterlockedCompareExchange8
  #define REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_16 _InterlockedCompareExchange16_np
  #define REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_32 _InterlockedCompareExchange_np
  #define REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_64 _InterlockedCompareExchange64_np

#else

  #define REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_8  _InterlockedCompareExchange8
  #define REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_16 _InterlockedCompareExchange16
  #define REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_32 _InterlockedCompareExchange
  #define REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_64 _InterlockedCompareExchange64

#endif

#define REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, MemoryOrder) REX_MSVC_ATOMIC_CMPXCHG_STRONG_OP_N(char, REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_8, type, ret, ptr, expected, desired, MemoryOrder)

#define REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, MemoryOrder) REX_MSVC_ATOMIC_CMPXCHG_STRONG_OP_N(short, REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_16, type, ret, ptr, expected, desired, MemoryOrder)

#define REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, MemoryOrder) REX_MSVC_ATOMIC_CMPXCHG_STRONG_OP_N(long, REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_32, type, ret, ptr, expected, desired, MemoryOrder)

#define REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, MemoryOrder) REX_MSVC_ATOMIC_CMPXCHG_STRONG_OP_N(__int64, REX_MSVC_ATOMIC_CMPXCHG_STRONG_INTRIN_64, type, ret, ptr, expected, desired, MemoryOrder)

#define REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, MemoryOrder) REX_MSVC_ATOMIC_CMPXCHG_STRONG_OP_128(type, ret, ptr, expected, desired, MemoryOrder)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_CMPXCHG_STRONG_*_*_N(type, bool ret, type * ptr, type * expected, type desired)
//
#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, RELEASE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, RELEASE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, RELEASE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, RELEASE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, RELEASE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, ACQ_REL)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_8(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_16(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_32(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_64(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_128(type, ret, ptr, expected, desired) REX_MSVC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, SEQ_CST)

#endif /* REX_ATOMIC_INTERNAL_COMPILER_MSVC_CMPXCHG_STRONG_H */
