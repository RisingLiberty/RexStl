#pragma once

/**
 * NOTE: We use this mapping
 *
 * ARMv7 Mapping 'trailing sync;':
 *
 * Load Relaxed       : ldr
 * Load Acquire       : ldr; dmb ish
 * Load Seq_Cst       : ldr; dmb ish
 *
 * Store Relaxed      : str
 * Store Release      : dmb ish; str
 * Store Seq_Cst      : dmb ish; str; dmb ish
 *
 * Relaxed Fence      :
 * Acquire Fence      : dmb ish
 * Release Fence      : dmb ish
 * Acq_Rel Fence      : dmb ish
 * Seq_Cst Fence      : dmb ish
 */

/**
 * ARMv7 Mapping 'leading sync;';
 *
 * Load Relaxed       : ldr
 * Load Acquire       : ldr; dmb ish
 * Load Seq_Cst       : dmb ish; ldr; dmb ish
 *
 * Store Relaxed      : str
 * Store Release      : dmb ish; str
 * Store Seq_Cst      : dmb ish: str
 *
 * Relaxed Fence      :
 * Acquire Fence      : dmb ish
 * Release Fence      : dmb ish
 * Acq_Rel Fence      : dmb ish
 * Seq_Cst Fence      : dmb ish
 */

/**
 * NOTE:
 *
 * On ARM32/64, we use the 'trailing sync;' convention with the stricter load acquire that uses
 * a dmb instead of a control dependency + isb to ensure the IRIW litmus test is satisfied
 * as one reason. See rex_std/atomic.h for futher explanation and deep-dive.
 *
 * For ARMv8 we could move to use the new proper store release and load acquire, RCsc variant.
 * All ARMv7 approaches work on ARMv8 and this code path is only used on msvc which isn't used
 * heavily. Most of the ARM code will end up going thru clang or gcc since microsoft arm devices
 * aren't that abundant.
 */

/////////////////////////////////////////////////////////////////////////////////

#if defined(REX_COMPILER_MSVC)

  #if REX_PLATFORM_PTR_SIZE == 8
    #define REX_ARCH_ATOMIC_HAS_128BIT
  #endif

#endif

/////////////////////////////////////////////////////////////////////////////////

#include "arch_arm_load.h"
#include "arch_arm_memory_barrier.h"
#include "arch_arm_store.h"
#include "arch_arm_thread_fence.h"

