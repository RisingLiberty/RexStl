


#ifndef REX_ATOMIC_INTERNAL_COMPILER_MSVC_XOR_FETCH_H
#define REX_ATOMIC_INTERNAL_COMPILER_MSVC_XOR_FETCH_H

#pragma once


#if defined(REX_PLATFORM_X64)

	#define REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_8 _InterlockedXor8_np
	#define REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_16 _InterlockedXor16_np
	#define REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_32 _InterlockedXor_np
	#define REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_64 _InterlockedXor64_np

#else

	#define REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_8 _InterlockedXor8
	#define REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_16 _InterlockedXor16
	#define REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_32 _InterlockedXor
	#define REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_64 _InterlockedXor64

#endif


#define REX_MSVC_XOR_FETCH_POST_INTRIN_COMPUTE(ret, val, xorend)	\
	ret = (val) ^ (xorend)

#define REX_MSVC_ATOMIC_XOR_FETCH_N(integralType, xorIntrinsic, type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_OP_FETCH_N(integralType, xorIntrinsic, type, ret, ptr, val, MemoryOrder, \
								 REX_MSVC_NOP_PRE_INTRIN_COMPUTE, REX_MSVC_XOR_FETCH_POST_INTRIN_COMPUTE)


#define REX_MSVC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, MemoryOrder)	\
	REX_MSVC_ATOMIC_XOR_FETCH_N(char, REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_8, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_XOR_FETCH_N(short, REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_16, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_XOR_FETCH_N(long, REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_32, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_XOR_FETCH_N(__int64, REX_MSVC_ATOMIC_XOR_FETCH_INTRIN_64, type, ret, ptr, val, MemoryOrder)


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_XOR_FETCH_*_N(type, type ret, type * ptr, type val)
//
#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELAXED_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, RELAXED)


#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQUIRE_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, ACQUIRE)


#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_XOR_FETCH_RELEASE_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, RELEASE)


#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_XOR_FETCH_ACQ_REL_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, ACQ_REL)


#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_8(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_16(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_32(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_XOR_FETCH_SEQ_CST_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_XOR_FETCH_64(type, ret, ptr, val, SEQ_CST)


#endif /* REX_ATOMIC_INTERNAL_COMPILER_MSVC_XOR_FETCH_H */
