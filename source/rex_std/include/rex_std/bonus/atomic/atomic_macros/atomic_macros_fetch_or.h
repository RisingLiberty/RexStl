

#ifndef REX_ATOMIC_INTERNAL_MACROS_FETCH_OR_H
#define REX_ATOMIC_INTERNAL_MACROS_FETCH_OR_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_FETCH_OR_*_N(type, type ret, type * ptr, type val)
//
#define REX_ATOMIC_FETCH_OR_RELAXED_8(type, ret, ptr, val) rsl::atomic_fetch_or_relaxed(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQUIRE_8(type, ret, ptr, val) rsl::atomic_fetch_or_acquire(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELEASE_8(type, ret, ptr, val) rsl::atomic_fetch_or_release(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQ_REL_8(type, ret, ptr, val) rsl::atomic_fetch_or_acq_rel(ptr, val)

#define REX_ATOMIC_FETCH_OR_SEQ_CST_8(type, ret, ptr, val) rsl::atomic_fetch_or_seq_cst(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELAXED_16(type, ret, ptr, val) rsl::atomic_fetch_or_relaxed(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQUIRE_16(type, ret, ptr, val) rsl::atomic_fetch_or_acquire(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELEASE_16(type, ret, ptr, val) rsl::atomic_fetch_or_release(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQ_REL_16(type, ret, ptr, val) rsl::atomic_fetch_or_acq_rel(ptr, val)

#define REX_ATOMIC_FETCH_OR_SEQ_CST_16(type, ret, ptr, val) rsl::atomic_fetch_or_seq_cst(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELAXED_32(type, ret, ptr, val) rsl::atomic_fetch_or_relaxed(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQUIRE_32(type, ret, ptr, val) rsl::atomic_fetch_or_acquire(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELEASE_32(type, ret, ptr, val) rsl::atomic_fetch_or_release(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQ_REL_32(type, ret, ptr, val) rsl::atomic_fetch_or_acq_rel(ptr, val)

#define REX_ATOMIC_FETCH_OR_SEQ_CST_32(type, ret, ptr, val) rsl::atomic_fetch_or_seq_cst(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELAXED_64(type, ret, ptr, val) rsl::atomic_fetch_or_relaxed(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQUIRE_64(type, ret, ptr, val) rsl::atomic_fetch_or_acquire(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELEASE_64(type, ret, ptr, val) rsl::atomic_fetch_or_release(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQ_REL_64(type, ret, ptr, val) rsl::atomic_fetch_or_acq_rel(ptr, val)

#define REX_ATOMIC_FETCH_OR_SEQ_CST_64(type, ret, ptr, val) rsl::atomic_fetch_or_seq_cst(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELAXED_128(type, ret, ptr, val) rsl::atomic_fetch_or_relaxed(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQUIRE_128(type, ret, ptr, val) rsl::atomic_fetch_or_acquire(ptr, val)

#define REX_ATOMIC_FETCH_OR_RELEASE_128(type, ret, ptr, val) rsl::atomic_fetch_or_release(ptr, val)

#define REX_ATOMIC_FETCH_OR_ACQ_REL_128(type, ret, ptr, val) rsl::atomic_fetch_or_acq_rel(ptr, val)

#define REX_ATOMIC_FETCH_OR_SEQ_CST_128(type, ret, ptr, val) rsl::atomic_fetch_or_seq_cst(ptr, val)

#endif /* REX_ATOMIC_INTERNAL_MACROS_FETCH_OR_H */
