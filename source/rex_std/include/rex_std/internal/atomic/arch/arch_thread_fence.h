


#ifndef REX_ATOMIC_INTERNAL_ARCH_THREAD_FENCE_H
#define REX_ATOMIC_INTERNAL_ARCH_THREAD_FENCE_H

#pragma once


/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_THREAD_FENCE_*()
//
#if defined(REX_ARCH_ATOMIC_THREAD_FENCE_RELAXED)
	#define REX_ARCH_ATOMIC_THREAD_FENCE_RELAXED_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_THREAD_FENCE_RELAXED_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_THREAD_FENCE_ACQUIRE)
	#define REX_ARCH_ATOMIC_THREAD_FENCE_ACQUIRE_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_THREAD_FENCE_ACQUIRE_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_THREAD_FENCE_RELEASE)
	#define REX_ARCH_ATOMIC_THREAD_FENCE_RELEASE_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_THREAD_FENCE_RELEASE_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_THREAD_FENCE_ACQ_REL)
	#define REX_ARCH_ATOMIC_THREAD_FENCE_ACQ_REL_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_THREAD_FENCE_ACQ_REL_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_THREAD_FENCE_SEQ_CST)
	#define REX_ARCH_ATOMIC_THREAD_FENCE_SEQ_CST_AVAILABLE 1
#else
	#define REX_ARCH_ATOMIC_THREAD_FENCE_SEQ_CST_AVAILABLE 0
#endif


#endif /* REX_ATOMIC_INTERNAL_ARCH_THREAD_FENCE_H */
