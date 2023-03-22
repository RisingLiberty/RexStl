


#ifndef REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_OR_H
#define REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_OR_H

#pragma once


#if defined(REX_PLATFORM_X64)

	#define REX_MSVC_ATOMIC_FETCH_OR_INTRIN_8 _InterlockedOr8_np
	#define REX_MSVC_ATOMIC_FETCH_OR_INTRIN_16 _InterlockedOr16_np
	#define REX_MSVC_ATOMIC_FETCH_OR_INTRIN_32 _InterlockedOr_np
	#define REX_MSVC_ATOMIC_FETCH_OR_INTRIN_64 _InterlockedOr64_np

#else

	#define REX_MSVC_ATOMIC_FETCH_OR_INTRIN_8 _InterlockedOr8
	#define REX_MSVC_ATOMIC_FETCH_OR_INTRIN_16 _InterlockedOr16
	#define REX_MSVC_ATOMIC_FETCH_OR_INTRIN_32 _InterlockedOr
	#define REX_MSVC_ATOMIC_FETCH_OR_INTRIN_64 _InterlockedOr64

#endif


#define REX_MSVC_ATOMIC_FETCH_OR_N(integralType, orIntrinsic, type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_OP_N(integralType, orIntrinsic, type, ret, ptr, val, MemoryOrder, \
								 REX_MSVC_NOP_PRE_INTRIN_COMPUTE)


#define REX_MSVC_ATOMIC_FETCH_OR_8(type, ret, ptr, val, MemoryOrder)	\
	REX_MSVC_ATOMIC_FETCH_OR_N(char, REX_MSVC_ATOMIC_FETCH_OR_INTRIN_8, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_OR_16(type, ret, ptr, val, MemoryOrder)	\
	REX_MSVC_ATOMIC_FETCH_OR_N(short, REX_MSVC_ATOMIC_FETCH_OR_INTRIN_16, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_OR_32(type, ret, ptr, val, MemoryOrder)	\
	REX_MSVC_ATOMIC_FETCH_OR_N(long, REX_MSVC_ATOMIC_FETCH_OR_INTRIN_32, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_OR_64(type, ret, ptr, val, MemoryOrder)	\
	REX_MSVC_ATOMIC_FETCH_OR_N(long long, REX_MSVC_ATOMIC_FETCH_OR_INTRIN_64, type, ret, ptr, val, MemoryOrder)


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_FETCH_OR_*_N(type, type ret, type * ptr, type val)
//
#define REX_COMPILER_ATOMIC_FETCH_OR_RELAXED_8(type, ret, ptr, val) \
	REX_MSVC_ATOMIC_FETCH_OR_8(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_OR_RELAXED_16(type, ret, ptr, val) \
	REX_MSVC_ATOMIC_FETCH_OR_16(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_OR_RELAXED_32(type, ret, ptr, val) \
	REX_MSVC_ATOMIC_FETCH_OR_32(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_OR_RELAXED_64(type, ret, ptr, val) \
	REX_MSVC_ATOMIC_FETCH_OR_64(type, ret, ptr, val, RELAXED)


#define REX_COMPILER_ATOMIC_FETCH_OR_ACQUIRE_8(type, ret, ptr, val) \
	REX_MSVC_ATOMIC_FETCH_OR_8(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_OR_ACQUIRE_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_16(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_OR_ACQUIRE_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_32(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_OR_ACQUIRE_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_64(type, ret, ptr, val, ACQUIRE)


#define REX_COMPILER_ATOMIC_FETCH_OR_RELEASE_8(type, ret, ptr, val) \
	REX_MSVC_ATOMIC_FETCH_OR_8(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_OR_RELEASE_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_16(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_OR_RELEASE_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_32(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_OR_RELEASE_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_64(type, ret, ptr, val, RELEASE)


#define REX_COMPILER_ATOMIC_FETCH_OR_ACQ_REL_8(type, ret, ptr, val) \
	REX_MSVC_ATOMIC_FETCH_OR_8(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_OR_ACQ_REL_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_16(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_OR_ACQ_REL_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_32(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_OR_ACQ_REL_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_64(type, ret, ptr, val, ACQ_REL)


#define REX_COMPILER_ATOMIC_FETCH_OR_SEQ_CST_8(type, ret, ptr, val) \
	REX_MSVC_ATOMIC_FETCH_OR_8(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_OR_SEQ_CST_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_16(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_OR_SEQ_CST_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_32(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_OR_SEQ_CST_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_OR_64(type, ret, ptr, val, SEQ_CST)


#endif /* REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_OR_H */
