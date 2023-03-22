


#ifndef REX_ATOMIC_INTERNAL_COMPILER_STORE_H
#define REX_ATOMIC_INTERNAL_COMPILER_STORE_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_STORE_*_N(type, type * ptr, type val)
//
#if defined(REX_COMPILER_ATOMIC_STORE_RELAXED_8)
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_8_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_8_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_RELEASE_8)
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_8_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_8_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_SEQ_CST_8)
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_8_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_8_AVAILABLE 0
#endif


#if defined(REX_COMPILER_ATOMIC_STORE_RELAXED_16)
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_16_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_16_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_RELEASE_16)
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_16_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_16_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_SEQ_CST_16)
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_16_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_16_AVAILABLE 0
#endif


#if defined(REX_COMPILER_ATOMIC_STORE_RELAXED_32)
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_32_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_32_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_RELEASE_32)
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_32_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_32_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_SEQ_CST_32)
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_32_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_32_AVAILABLE 0
#endif


#if defined(REX_COMPILER_ATOMIC_STORE_RELAXED_64)
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_64_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_64_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_RELEASE_64)
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_64_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_64_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_SEQ_CST_64)
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_64_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_64_AVAILABLE 0
#endif


#if defined(REX_COMPILER_ATOMIC_STORE_RELAXED_128)
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_128_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELAXED_128_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_RELEASE_128)
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_128_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_RELEASE_128_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_STORE_SEQ_CST_128)
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_128_AVAILABLE 1
#else
	#define REX_COMPILER_ATOMIC_STORE_SEQ_CST_128_AVAILABLE 0
#endif


#endif /* REX_ATOMIC_INTERNAL_COMPILER_STORE_H */
