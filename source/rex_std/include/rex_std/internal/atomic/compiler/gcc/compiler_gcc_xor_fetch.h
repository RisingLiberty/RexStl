


#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_XOR_FETCH_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_XOR_FETCH_H

#pragma once


#define REX_GCC_ATOMIC_XOR_FETCH_N(integralType, type, ret, ptr, val, gccMemoryOrder) \
	REX_GCC_ATOMIC_FETCH_INTRIN_N(integralType, __atomic_xor_fetch, type, ret, ptr, val, gccMemoryOrder)


#define REX_GCC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, gccMemoryOrder) \
	REX_GCC_ATOMIC_XOR_FETCH_N(uint8_t, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, gccMemoryOrder) \
	REX_GCC_ATOMIC_XOR_FETCH_N(uint16_t, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, gccMemoryOrder) \
	REX_GCC_ATOMIC_XOR_FETCH_N(uint32_t, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, gccMemoryOrder) \
	REX_GCC_ATOMIC_XOR_FETCH_N(uint64_t, type, ret, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_XOR_FETCH_128(type, ret, ptr, val, gccMemoryOrder) \
	REX_GCC_ATOMIC_XOR_FETCH_N(__uint128_t, type, ret, ptr, val, gccMemoryOrder)


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_XOR_FETCH_*_N(type, type ret, type * ptr, type val)
//
#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_8(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_16(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_32(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_64(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_128(type, ret, ptr, val) \
	REX_GCC_ATOMIC_XOR_FETCH_128(type, ret, ptr, val, __ATOMIC_RELAXED)


#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_8(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_16(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_32(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_64(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, __ATOMIC_ACQUIRE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_128(type, ret, ptr, val) \
	REX_GCC_ATOMIC_XOR_FETCH_128(type, ret, ptr, val, __ATOMIC_ACQUIRE)


#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_8(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_16(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_32(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_64(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_128(type, ret, ptr, val) \
	REX_GCC_ATOMIC_XOR_FETCH_128(type, ret, ptr, val, __ATOMIC_RELEASE)


#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_8(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_16(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_32(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_64(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, __ATOMIC_ACQ_REL)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_128(type, ret, ptr, val) \
	REX_GCC_ATOMIC_XOR_FETCH_128(type, ret, ptr, val, __ATOMIC_ACQ_REL)


#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_8(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_16(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_32(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_64(type, ret, ptr, val)	\
	REX_GCC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_128(type, ret, ptr, val) \
	REX_GCC_ATOMIC_XOR_FETCH_128(type, ret, ptr, val, __ATOMIC_SEQ_CST)


#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_XOR_FETCH_H */
