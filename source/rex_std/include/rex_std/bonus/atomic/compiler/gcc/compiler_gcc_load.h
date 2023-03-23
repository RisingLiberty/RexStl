

#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_LOAD_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_LOAD_H

#pragma once

#define REX_GCC_ATOMIC_LOAD_N(integralType, type, ret, ptr, gccMemoryOrder)                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                      \
    integralType retIntegral;                                                                                                                                                                                                                            \
    __atomic_load(REX_ATOMIC_VOLATILE_INTEGRAL_CAST(integralType, (ptr)), &retIntegral, gccMemoryOrder);                                                                                                                                                 \
                                                                                                                                                                                                                                                         \
    ret = REX_ATOMIC_TYPE_PUN_CAST(type, retIntegral);                                                                                                                                                                                                   \
  }

#define REX_GCC_ATOMIC_LOAD_8(type, ret, ptr, gccMemoryOrder) REX_GCC_ATOMIC_LOAD_N(rsl::uint8, type, ret, ptr, gccMemoryOrder)

#define REX_GCC_ATOMIC_LOAD_16(type, ret, ptr, gccMemoryOrder) REX_GCC_ATOMIC_LOAD_N(uint16, type, ret, ptr, gccMemoryOrder)

#define REX_GCC_ATOMIC_LOAD_32(type, ret, ptr, gccMemoryOrder) REX_GCC_ATOMIC_LOAD_N(uint32, type, ret, ptr, gccMemoryOrder)

#define REX_GCC_ATOMIC_LOAD_64(type, ret, ptr, gccMemoryOrder) REX_GCC_ATOMIC_LOAD_N(uint64, type, ret, ptr, gccMemoryOrder)

#define REX_GCC_ATOMIC_LOAD_128(type, ret, ptr, gccMemoryOrder) REX_GCC_ATOMIC_LOAD_N(__uint128_t, type, ret, ptr, gccMemoryOrder)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_LOAD_*_N(type, type ret, type * ptr)
//
#define REX_COMPILER_ATOMIC_LOAD_RELAXED_8(type, ret, ptr) REX_GCC_ATOMIC_LOAD_8(type, ret, ptr, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_LOAD_RELAXED_16(type, ret, ptr) REX_GCC_ATOMIC_LOAD_16(type, ret, ptr, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_LOAD_RELAXED_32(type, ret, ptr) REX_GCC_ATOMIC_LOAD_32(type, ret, ptr, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_LOAD_RELAXED_64(type, ret, ptr) REX_GCC_ATOMIC_LOAD_64(type, ret, ptr, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_LOAD_RELAXED_128(type, ret, ptr) REX_GCC_ATOMIC_LOAD_128(type, ret, ptr, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_8(type, ret, ptr) REX_GCC_ATOMIC_LOAD_8(type, ret, ptr, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_16(type, ret, ptr) REX_GCC_ATOMIC_LOAD_16(type, ret, ptr, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_32(type, ret, ptr) REX_GCC_ATOMIC_LOAD_32(type, ret, ptr, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_64(type, ret, ptr) REX_GCC_ATOMIC_LOAD_64(type, ret, ptr, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_128(type, ret, ptr) REX_GCC_ATOMIC_LOAD_128(type, ret, ptr, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_8(type, ret, ptr) REX_GCC_ATOMIC_LOAD_8(type, ret, ptr, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_16(type, ret, ptr) REX_GCC_ATOMIC_LOAD_16(type, ret, ptr, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_32(type, ret, ptr) REX_GCC_ATOMIC_LOAD_32(type, ret, ptr, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_64(type, ret, ptr) REX_GCC_ATOMIC_LOAD_64(type, ret, ptr, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_128(type, ret, ptr) REX_GCC_ATOMIC_LOAD_128(type, ret, ptr, __ATOMIC_SEQ_CST)

#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_LOAD_H */
