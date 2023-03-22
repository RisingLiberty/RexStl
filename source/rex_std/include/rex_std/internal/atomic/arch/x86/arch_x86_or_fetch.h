


#ifndef REX_ATOMIC_INTERNAL_ARCH_X86_OR_FETCH_H
#define REX_ATOMIC_INTERNAL_ARCH_X86_OR_FETCH_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_OR_FETCH_*_N(type, type ret, type * ptr, type val)
//
#if defined(REX_COMPILER_MSVC) && defined(REX_PLATFORM_X86)


	#define REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED(ret, observed, val) \
		ret = ((observed) | (val))

	#define REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET(ret, prevObserved, val) \
		ret = ((prevObserved) | (val))


	#define REX_ARCH_ATOMIC_OR_FETCH_RELAXED_64(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, RELAXED,		\
										 REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										 REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)

	#define REX_ARCH_ATOMIC_OR_FETCH_ACQUIRE_64(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, ACQUIRE,		\
										 REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										 REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)

	#define REX_ARCH_ATOMIC_OR_FETCH_RELEASE_64(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, RELEASE,		\
										 REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										 REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)

	#define REX_ARCH_ATOMIC_OR_FETCH_ACQ_REL_64(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, ACQ_REL,		\
										 REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										 REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)

	#define REX_ARCH_ATOMIC_OR_FETCH_SEQ_CST_64(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, SEQ_CST,		\
										 REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										 REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)


#endif


#if ((defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)) && defined(REX_PLATFORM_X64))


	#define REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED(ret, observed, val) \
		ret = ((observed) | (val))

	#define REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET(ret, prevObserved, val) \
		ret = ((prevObserved) | (val))


	#define REX_ARCH_ATOMIC_OR_FETCH_RELAXED_128(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_128_IMPL(type, ret, ptr, val, RELAXED,		\
										  REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										  REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)

	#define REX_ARCH_ATOMIC_OR_FETCH_ACQUIRE_128(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_128_IMPL(type, ret, ptr, val, ACQUIRE,		\
										  REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										  REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)

	#define REX_ARCH_ATOMIC_OR_FETCH_RELEASE_128(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_128_IMPL(type, ret, ptr, val, RELEASE,		\
										  REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										  REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)

	#define REX_ARCH_ATOMIC_OR_FETCH_ACQ_REL_128(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_128_IMPL(type, ret, ptr, val, ACQ_REL,		\
										  REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										  REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)

	#define REX_ARCH_ATOMIC_OR_FETCH_SEQ_CST_128(type, ret, ptr, val)		\
		REX_ARCH_ATOMIC_X86_OP_128_IMPL(type, ret, ptr, val, SEQ_CST,		\
										  REX_ARCH_ATOMIC_X86_OR_FETCH_PRE_COMPUTE_DESIRED, \
										  REX_ARCH_ATOMIC_X86_OR_FETCH_POST_COMPUTE_RET)


#endif


#endif /* REX_ATOMIC_INTERNAL_ARCH_X86_OR_FETCH_H */
