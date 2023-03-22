


#ifndef REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_SUB_H
#define REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_SUB_H

#pragma once


#define REX_MSVC_FETCH_SUB_PRE_INTRIN_COMPUTE(ret, val) \
	ret = REX_ATOMIC_NEGATE_OPERAND((val))

#define REX_MSVC_ATOMIC_FETCH_SUB_N(integralType, subIntrinsic, type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_OP_N(integralType, subIntrinsic, type, ret, ptr, val, MemoryOrder, \
								 REX_MSVC_FETCH_SUB_PRE_INTRIN_COMPUTE)


#define REX_MSVC_ATOMIC_FETCH_SUB_8(type, ret, ptr, val, MemoryOrder)	\
	REX_MSVC_ATOMIC_FETCH_SUB_N(char, _InterlockedExchangeAdd8, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_SUB_16(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_SUB_N(short, _InterlockedExchangeAdd16, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_SUB_32(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_SUB_N(long, _InterlockedExchangeAdd, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_SUB_64(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_SUB_N(__int64, _InterlockedExchangeAdd64, type, ret, ptr, val, MemoryOrder)


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_FETCH_SUB_*_N(type, type ret, type * ptr, type val)
//
#define REX_COMPILER_ATOMIC_FETCH_SUB_RELAXED_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_8(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_SUB_RELAXED_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_16(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_SUB_RELAXED_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_32(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_SUB_RELAXED_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_64(type, ret, ptr, val, RELAXED)


#define REX_COMPILER_ATOMIC_FETCH_SUB_ACQUIRE_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_8(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_SUB_ACQUIRE_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_16(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_SUB_ACQUIRE_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_32(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_SUB_ACQUIRE_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_64(type, ret, ptr, val, ACQUIRE)


#define REX_COMPILER_ATOMIC_FETCH_SUB_RELEASE_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_8(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_SUB_RELEASE_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_16(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_SUB_RELEASE_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_32(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_SUB_RELEASE_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_64(type, ret, ptr, val, RELEASE)


#define REX_COMPILER_ATOMIC_FETCH_SUB_ACQ_REL_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_8(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_SUB_ACQ_REL_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_16(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_SUB_ACQ_REL_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_32(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_SUB_ACQ_REL_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_64(type, ret, ptr, val, ACQ_REL)


#define REX_COMPILER_ATOMIC_FETCH_SUB_SEQ_CST_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_8(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_SUB_SEQ_CST_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_16(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_SUB_SEQ_CST_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_32(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_SUB_SEQ_CST_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_SUB_64(type, ret, ptr, val, SEQ_CST)


#endif /* REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_SUB_H */
