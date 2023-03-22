


#ifndef REX_ATOMIC_INTERNAL_COMPILER_GCC_STORE_H
#define REX_ATOMIC_INTERNAL_COMPILER_GCC_STORE_H

#pragma once


#define REX_GCC_ATOMIC_STORE_N(integralType, ptr, val, gccMemoryOrder) \
	{																	 \
		integralType valIntegral = REX_ATOMIC_TYPE_PUN_CAST(integralType, (val)); \
		__atomic_store(REX_ATOMIC_VOLATILE_INTEGRAL_CAST(integralType, (ptr)), &valIntegral, gccMemoryOrder); \
	}


#define REX_GCC_ATOMIC_STORE_8(ptr, val, gccMemoryOrder)		\
	REX_GCC_ATOMIC_STORE_N(uint8_t, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_STORE_16(ptr, val, gccMemoryOrder)		\
	REX_GCC_ATOMIC_STORE_N(uint16_t, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_STORE_32(ptr, val, gccMemoryOrder)		\
	REX_GCC_ATOMIC_STORE_N(uint32_t, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_STORE_64(ptr, val, gccMemoryOrder)		\
	REX_GCC_ATOMIC_STORE_N(uint64_t, ptr, val, gccMemoryOrder)

#define REX_GCC_ATOMIC_STORE_128(ptr, val, gccMemoryOrder)	\
	REX_GCC_ATOMIC_STORE_N(__uint128_t, ptr, val, gccMemoryOrder)


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_STORE_*_N(type, type * ptr, type val)
//
#define REX_COMPILER_ATOMIC_STORE_RELAXED_8(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_8(ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_STORE_RELAXED_16(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_16(ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_STORE_RELAXED_32(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_32(ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_STORE_RELAXED_64(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_64(ptr, val, __ATOMIC_RELAXED)

#define REX_COMPILER_ATOMIC_STORE_RELAXED_128(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_128(ptr, val, __ATOMIC_RELAXED)


#define REX_COMPILER_ATOMIC_STORE_RELEASE_8(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_8(ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_STORE_RELEASE_16(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_16(ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_STORE_RELEASE_32(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_32(ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_STORE_RELEASE_64(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_64(ptr, val, __ATOMIC_RELEASE)

#define REX_COMPILER_ATOMIC_STORE_RELEASE_128(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_128(ptr, val, __ATOMIC_RELEASE)


#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_8(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_8(ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_16(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_16(ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_32(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_32(ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_64(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_64(ptr, val, __ATOMIC_SEQ_CST)

#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_128(type, ptr, val)	\
	REX_GCC_ATOMIC_STORE_128(ptr, val, __ATOMIC_SEQ_CST)


#endif /* REX_ATOMIC_INTERNAL_COMPILER_GCC_STORE_H */
