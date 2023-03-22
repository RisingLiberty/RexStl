


#ifndef REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_ADD_H
#define REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_ADD_H

#pragma once


#define REX_MSVC_ATOMIC_FETCH_ADD_N(integralType, addIntrinsic, type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_OP_N(integralType, addIntrinsic, type, ret, ptr, val, MemoryOrder, \
								 REX_MSVC_NOP_PRE_INTRIN_COMPUTE)


#define REX_MSVC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, MemoryOrder)	\
	REX_MSVC_ATOMIC_FETCH_ADD_N(char, _InterlockedExchangeAdd8, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_ADD_N(short, _InterlockedExchangeAdd16, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_ADD_N(long, _InterlockedExchangeAdd, type, ret, ptr, val, MemoryOrder)

#define REX_MSVC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, MemoryOrder) \
	REX_MSVC_ATOMIC_FETCH_ADD_N(__int64, _InterlockedExchangeAdd64, type, ret, ptr, val, MemoryOrder)


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_FETCH_ADD_*_N(type, type ret, type * ptr, type val)
//
#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, RELAXED)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELAXED_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, RELAXED)


#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, ACQUIRE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQUIRE_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, ACQUIRE)


#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, RELEASE)

#define REX_COMPILER_ATOMIC_FETCH_ADD_RELEASE_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, RELEASE)


#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, ACQ_REL)

#define REX_COMPILER_ATOMIC_FETCH_ADD_ACQ_REL_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, ACQ_REL)


#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_8(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_8(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_16(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_16(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_32(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_32(type, ret, ptr, val, SEQ_CST)

#define REX_COMPILER_ATOMIC_FETCH_ADD_SEQ_CST_64(type, ret, ptr, val)	\
	REX_MSVC_ATOMIC_FETCH_ADD_64(type, ret, ptr, val, SEQ_CST)


#endif /* REX_ATOMIC_INTERNAL_COMPILER_MSVC_FETCH_ADD_H */
