

#ifndef REX_ATOMIC_INTERNAL_MACROS_SIGNAL_FENCE_H
#define REX_ATOMIC_INTERNAL_MACROS_SIGNAL_FENCE_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_SIGNAL_FENCE_*()
//
#define REX_ATOMIC_SIGNAL_FENCE_RELAXED() rsl::atomic_signal_fence(rsl::memory_order::relaxed)

#define REX_ATOMIC_SIGNAL_FENCE_ACQUIRE() rsl::atomic_signal_fence(rsl::memory_order::acquire)

#define REX_ATOMIC_SIGNAL_FENCE_RELEASE() rsl::atomic_signal_fence(rsl::memory_order::release)

#define REX_ATOMIC_SIGNAL_FENCE_ACQ_REL() rsl::atomic_signal_fence(rsl::memory_order::acq_rel)

#define REX_ATOMIC_SIGNAL_FENCE_SEQ_CST() rsl::atomic_signal_fence(rsl::memory_order::seq_cst)

#endif /* REX_ATOMIC_INTERNAL_MACROS_SIGNAL_FENCE_H */
