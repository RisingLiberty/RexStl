


#ifndef REX_ATOMIC_INTERNAL_ATOMIC_MACROS_H
#define REX_ATOMIC_INTERNAL_ATOMIC_MACROS_H

#pragma once


#include "atomic_macros_base.h"

#include "atomic_macros_fetch_add.h"
#include "atomic_macros_fetch_sub.h"

#include "atomic_macros_fetch_and.h"
#include "atomic_macros_fetch_xor.h"
#include "atomic_macros_fetch_or.h"

#include "atomic_macros_add_fetch.h"
#include "atomic_macros_sub_fetch.h"

#include "atomic_macros_and_fetch.h"
#include "atomic_macros_xor_fetch.h"
#include "atomic_macros_or_fetch.h"

#include "atomic_macros_exchange.h"

#include "atomic_macros_cmpxchg_weak.h"
#include "atomic_macros_cmpxchg_strong.h"

#include "atomic_macros_load.h"
#include "atomic_macros_store.h"

#include "atomic_macros_compiler_barrier.h"

#include "atomic_macros_cpu_pause.h"

#include "atomic_macros_memory_barrier.h"

#include "atomic_macros_signal_fence.h"

#include "atomic_macros_thread_fence.h"


/////////////////////////////////////////////////////////////////////////////////


#if defined(REX_COMPILER_ATOMIC_HAS_8BIT) || defined(REX_ARCH_ATOMIC_HAS_8BIT)

	#define REX_ATOMIC_HAS_8BIT

#endif


#if defined(REX_COMPILER_ATOMIC_HAS_16BIT) || defined(REX_ARCH_ATOMIC_HAS_16BIT)

	#define REX_ATOMIC_HAS_16BIT

#endif


#if defined(REX_COMPILER_ATOMIC_HAS_32BIT) || defined(REX_ARCH_ATOMIC_HAS_32BIT)

	#define REX_ATOMIC_HAS_32BIT

#endif


#if defined(REX_COMPILER_ATOMIC_HAS_64BIT) || defined(REX_ARCH_ATOMIC_HAS_64BIT)

	#define REX_ATOMIC_HAS_64BIT

#endif


#if defined(REX_COMPILER_ATOMIC_HAS_128BIT) || defined(REX_ARCH_ATOMIC_HAS_128BIT)

	#define REX_ATOMIC_HAS_128BIT

#endif


/////////////////////////////////////////////////////////////////////////////////


#if defined(REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_8)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_8 REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_8

#elif defined(REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_8)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_8 REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_8

#endif


#if defined(REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_16)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_16 REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_16

#elif defined(REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_16)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_16 REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_16

#endif


#if defined(REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_32)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_32 REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_32

#elif defined(REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_32)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_32 REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_32

#endif


#if defined(REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_64)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_64 REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_64

#elif defined(REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_64)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_64 REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_64

#endif


#if defined(REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_128)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_128 REX_ARCH_ATOMIC_FIXED_WIDTH_TYPE_128

#elif defined(REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_128)

	#define REX_ATOMIC_FIXED_WIDTH_TYPE_128 REX_COMPILER_ATOMIC_FIXED_WIDTH_TYPE_128

#endif


#endif /* REX_ATOMIC_INTERNAL_ATOMIC_MACROS_H */
