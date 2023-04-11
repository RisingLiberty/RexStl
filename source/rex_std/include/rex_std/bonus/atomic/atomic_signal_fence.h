// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_signal_fence.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/compiler.h"
#include "rex_std/bonus/types.h"
#include "rex_std/internal/assert/assert_fwd.h"

namespace rsl
{
  inline namespace v1
  {
    REX_FORCE_INLINE void atomic_signal_fence(rsl::memory_order order)
    {
#if defined(REX_COMPILER_MSVC)
      (void)order;
      compiler_barrier();
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      switch(order)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_signal_fence(__ATOMIC_RELAXED);
        case rsl::v1::memory_order::consume: return __atomic_signal_fence(__ATOMIC_CONSUME);
        case rsl::v1::memory_order::acquire: return __atomic_signal_fence(__ATOMIC_ACQUIRE);
        case rsl::v1::memory_order::release: return __atomic_signal_fence(__ATOMIC_RELEASE);
        case rsl::v1::memory_order::acq_rel: return __atomic_signal_fence(__ATOMIC_ACQ_REL);
        case rsl::v1::memory_order::seq_cst: return __atomic_signal_fence(__ATOMIC_SEQ_CST);
        default: REX_ASSERT("Invalid memory order for atomic signal_fence"); break;
      }
#endif
    }
  } // namespace v1
} // namespace rsl
