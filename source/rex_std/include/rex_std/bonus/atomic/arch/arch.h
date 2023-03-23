

#ifndef REX_ATOMIC_INTERNAL_ARCH_H
#define REX_ATOMIC_INTERNAL_ARCH_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// Include the architecture specific implementations
//
#if defined(REX_PLATFORM_X86) || defined(REX_PLATFORM_X64)

  #include "x86/arch_x86.h"

#elif defined(REX_PLATFORM_ARM32) || defined(REX_PLATFORM_ARM64)

  #include "arm/arch_arm.h"

#endif

/////////////////////////////////////////////////////////////////////////////////

#include "arch_add_fetch.h"
#include "arch_and_fetch.h"
#include "arch_cmpxchg_strong.h"
#include "arch_cmpxchg_weak.h"
#include "arch_compiler_barrier.h"
#include "arch_cpu_pause.h"
#include "arch_exchange.h"
#include "arch_fetch_add.h"
#include "arch_fetch_and.h"
#include "arch_fetch_or.h"
#include "arch_fetch_sub.h"
#include "arch_fetch_xor.h"
#include "arch_load.h"
#include "arch_memory_barrier.h"
#include "arch_or_fetch.h"
#include "arch_signal_fence.h"
#include "arch_store.h"
#include "arch_sub_fetch.h"
#include "arch_thread_fence.h"
#include "arch_xor_fetch.h"

#endif /* REX_ATOMIC_INTERNAL_ARCH_H */
