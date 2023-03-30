

#ifndef REX_ATOMIC_INTERNAL_MACROS_EXCHANGE_H
#define REX_ATOMIC_INTERNAL_MACROS_EXCHANGE_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_EXCHANGE_*_N(type, type ret, type * ptr, type val)
//
#define REX_ATOMIC_EXCHANGE_RELAXED_8(type, ret, ptr, val) rsl::atomic_exchange_relaxed(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQUIRE_8(type, ret, ptr, val) rsl::atomic_exchange_acquire(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELEASE_8(type, ret, ptr, val) rsl::atomic_exchange_release(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQ_REL_8(type, ret, ptr, val) rsl::atomic_exchange_acq_rel(ptr, val)

#define REX_ATOMIC_EXCHANGE_SEQ_CST_8(type, ret, ptr, val) rsl::atomic_exchange_seq_cst(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELAXED_16(type, ret, ptr, val) rsl::atomic_exchange_relaxed(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQUIRE_16(type, ret, ptr, val) rsl::atomic_exchange_acquire(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELEASE_16(type, ret, ptr, val) rsl::atomic_exchange_release(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQ_REL_16(type, ret, ptr, val) rsl::atomic_exchange_acq_rel(ptr, val)

#define REX_ATOMIC_EXCHANGE_SEQ_CST_16(type, ret, ptr, val) rsl::atomic_exchange_seq_cst(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELAXED_32(type, ret, ptr, val) rsl::atomic_exchange_relaxed(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQUIRE_32(type, ret, ptr, val) rsl::atomic_exchange_acquire(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELEASE_32(type, ret, ptr, val) rsl::atomic_exchange_release(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQ_REL_32(type, ret, ptr, val) rsl::atomic_exchange_acq_rel(ptr, val)

#define REX_ATOMIC_EXCHANGE_SEQ_CST_32(type, ret, ptr, val) rsl::atomic_exchange_seq_cst(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELAXED_64(type, ret, ptr, val) rsl::atomic_exchange_relaxed(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQUIRE_64(type, ret, ptr, val) rsl::atomic_exchange_acquire(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELEASE_64(type, ret, ptr, val) rsl::atomic_exchange_release(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQ_REL_64(type, ret, ptr, val) rsl::atomic_exchange_acq_rel(ptr, val)

#define REX_ATOMIC_EXCHANGE_SEQ_CST_64(type, ret, ptr, val) rsl::atomic_exchange_seq_cst(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELAXED_128(type, ret, ptr, val) rsl::atomic_exchange_relaxed(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQUIRE_128(type, ret, ptr, val) rsl::atomic_exchange_acquire(ptr, val)

#define REX_ATOMIC_EXCHANGE_RELEASE_128(type, ret, ptr, val) rsl::atomic_exchange_release(ptr, val)

#define REX_ATOMIC_EXCHANGE_ACQ_REL_128(type, ret, ptr, val) rsl::atomic_exchange_acq_rel(ptr, val)

#define REX_ATOMIC_EXCHANGE_SEQ_CST_128(type, ret, ptr, val) rsl::atomic_exchange_seq_cst(ptr, val)

#endif /* REX_ATOMIC_INTERNAL_MACROS_EXCHANGE_H */
