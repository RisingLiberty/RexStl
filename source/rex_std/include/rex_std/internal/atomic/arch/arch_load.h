


#ifndef REX_ATOMIC_INTERNAL_ARCH_LOAD_H
#define REX_ATOMIC_INTERNAL_ARCH_LOAD_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_LOAD_*_N(type, type ret, type * ptr)
//
#if defined(REX_ARCH_ATOMIC_LOAD_RELAXED_8)
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_8_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_8_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_ACQUIRE_8)
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_8_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_8_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_SEQ_CST_8)
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_8_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_8_AVAILABLE 0
#endif


#if defined(REX_ARCH_ATOMIC_LOAD_RELAXED_16)
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_16_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_16_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_ACQUIRE_16)
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_16_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_16_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_SEQ_CST_16)
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_16_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_16_AVAILABLE 0
#endif


#if defined(REX_ARCH_ATOMIC_LOAD_RELAXED_32)
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_32_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_32_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_ACQUIRE_32)
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_32_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_32_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_SEQ_CST_32)
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_32_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_32_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_READ_DEPENDS_32)
	#define REX_ARCH_ATOMIC_LOAD_READ_DEPENDS_32_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_READ_DEPENDS_32_AVAILABLE 0
#endif


#if defined(REX_ARCH_ATOMIC_LOAD_RELAXED_64)
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_64_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_64_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_ACQUIRE_64)
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_64_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_64_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_SEQ_CST_64)
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_64_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_64_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_READ_DEPENDS_64)
	#define REX_ARCH_ATOMIC_LOAD_READ_DEPENDS_64_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_READ_DEPENDS_64_AVAILABLE 0
#endif


#if defined(REX_ARCH_ATOMIC_LOAD_RELAXED_128)
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_128_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_RELAXED_128_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_ACQUIRE_128)
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_128_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_ACQUIRE_128_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_LOAD_SEQ_CST_128)
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_128_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_LOAD_SEQ_CST_128_AVAILABLE 0
#endif


#endif /* REX_ATOMIC_INTERNAL_ARCH_LOAD_H */
