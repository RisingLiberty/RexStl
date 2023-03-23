

#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_CMPXCHG_WEAK_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_CMPXCHG_WEAK_H

#pragma once

#define REX_GCC_ATOMIC_CMPXCHG_WEAK_N(integralType, type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_INTRIN_N(integralType, type, ret, ptr, expected, desired, true, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_WEAK_N(rsl::uint8, type, ret, ptr, expected, desired, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_WEAK_N(uint16, type, ret, ptr, expected, desired, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_WEAK_N(uint32, type, ret, ptr, expected, desired, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_WEAK_N(uint64, type, ret, ptr, expected, desired, successOrder, failOrder)

#define REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, successOrder, failOrder) REX_GCC_ATOMIC_CMPXCHG_WEAK_N(__uint128_t, type, ret, ptr, expected, desired, successOrder, failOrder)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_CMPXCHG_WEAK_*_*_N(type, bool ret, type * ptr, type * expected, type desired)
//
#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_RELAXED, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_RELEASE, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_8(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_8(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_16(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_16(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_32(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_32(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_64(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_64(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_128(type, ret, ptr, expected, desired) REX_GCC_ATOMIC_CMPXCHG_WEAK_128(type, ret, ptr, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)

#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_CMPXCHG_WEAK_H */
