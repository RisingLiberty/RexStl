

#ifndef REX_ATOMIC_INTERNAL_MACROS_THREAD_FENCE_H
#define REX_ATOMIC_INTERNAL_MACROS_THREAD_FENCE_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_THREAD_FENCE_*()
//
#define REX_ATOMIC_THREAD_FENCE_RELAXED() rsl::atomic_thread_fence(rsl::memory_order::relaxed)

#define REX_ATOMIC_THREAD_FENCE_ACQUIRE() rsl::atomic_thread_fence(rsl::memory_order::acquire)

#define REX_ATOMIC_THREAD_FENCE_RELEASE() rsl::atomic_thread_fence(rsl::memory_order::release)

#define REX_ATOMIC_THREAD_FENCE_ACQ_REL() rsl::atomic_thread_fence(rsl::memory_order::acq_rel)

#define REX_ATOMIC_THREAD_FENCE_SEQ_CST() rsl::atomic_thread_fence(rsl::memory_order::seq_cst)

#endif /* REX_ATOMIC_INTERNAL_MACROS_THREAD_FENCE_H */
