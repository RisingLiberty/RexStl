

#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_CMPXCHG_STRONG_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_CMPXCHG_STRONG_H

#pragma once

#define REX_GCC_ATOMIC_CMPXCHG_STRONG_N(integralType, type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_INTRIN_N(integralType, type, ret, ptr, expected, desired, false, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_STRONG_N(rsl::uint8, type, ret, ptr, expected, desired, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_STRONG_N(uint16, type, ret, ptr, expected, desired, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_STRONG_N(uint32, type, ret, ptr, expected, desired, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_STRONG_N(uint64, type, ret, ptr, expected, desired, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_STRONG_N(__uint128_t, type, ret, ptr, expected, desired, successOrder, failOrder)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_CMPXCHG_STRONG_*_*_N(type, bool ret, type * ptr, type * expected, type desired)
//
#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_8(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_16(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_32(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_64(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_STRONG_128(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_CMPXCHG_STRONG_H */
