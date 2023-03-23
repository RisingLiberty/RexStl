

#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_FETCH_ADD_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_FETCH_ADD_H

#pragma once

#define REX_GCC_ATOMIC_FETCH_ADD_N(integralType, type, ret, ptr, val, gccMemoryOrder) REX_GCC_ATOMIC_FETCH_INTRIN_N(integralType, __atomic_fetch_add, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, gccMemoryOrder) REX_GCC_ATOMIC_FETCH_ADD_N(rsl::uint8, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, gccMemoryOrder) REX_GCC_ATOMIC_FETCH_ADD_N(uint16, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, gccMemoryOrder) REX_GCC_ATOMIC_FETCH_ADD_N(uint32, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, gccMemoryOrder) REX_GCC_ATOMIC_FETCH_ADD_N(uint64, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_FETCH_ADD_128(type, ret, ptr, val, gccMemoryOrder) REX_GCC_ATOMIC_FETCH_ADD_N(__uint128_t, type, ret, ptr, val, gccMemoryOrder)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_FETCH_ADD_*_N(type, type ret, type * ptr, type val)
//
#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_8(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_16(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_32(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_64(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_128(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_128(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_8(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_16(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_32(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_64(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_128(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_128(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_8(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_16(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_32(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_64(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_128(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_128(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_8(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_16(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_32(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_64(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_128(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_128(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_8(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_16(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_32(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_64(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_128(type, ret, ptr, val) REX_GCC_ATOMIC_FETCH_ADD_128(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_FETCH_ADD_H */
