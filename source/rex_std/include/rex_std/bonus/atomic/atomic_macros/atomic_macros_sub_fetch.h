

#ifndef REX_ATOMIC_INTERNAL_MACROS_SUB_FETCH_H
#define REX_ATOMIC_INTERNAL_MACROS_SUB_FETCH_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_SUB_FETCH_*_N(type, type ret, type * ptr, type val)
//
#define REX_ATOMIC_SUB_FETCH_RELAXED_8(type, ret, ptr, val) rsl::atomic_sub_fetch_relaxed(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQUIRE_8(type, ret, ptr, val) rsl::atomic_sub_fetch_acquire(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELEASE_8(type, ret, ptr, val) rsl::atomic_sub_fetch_release(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQ_REL_8(type, ret, ptr, val) rsl::atomic_sub_fetch_acq_rel(ptr, val)

#define REX_ATOMIC_SUB_FETCH_SEQ_CST_8(type, ret, ptr, val) rsl::atomic_sub_fetch_seq_cst(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELAXED_16(type, ret, ptr, val) rsl::atomic_sub_fetch_relaxed(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQUIRE_16(type, ret, ptr, val) rsl::atomic_sub_fetch_acquire(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELEASE_16(type, ret, ptr, val) rsl::atomic_sub_fetch_release(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQ_REL_16(type, ret, ptr, val) rsl::atomic_sub_fetch_acq_rel(ptr, val)

#define REX_ATOMIC_SUB_FETCH_SEQ_CST_16(type, ret, ptr, val) rsl::atomic_sub_fetch_seq_cst(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELAXED_32(type, ret, ptr, val) rsl::atomic_sub_fetch_relaxed(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQUIRE_32(type, ret, ptr, val) rsl::atomic_sub_fetch_acquire(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELEASE_32(type, ret, ptr, val) rsl::atomic_sub_fetch_release(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQ_REL_32(type, ret, ptr, val) rsl::atomic_sub_fetch_acq_rel(ptr, val)

#define REX_ATOMIC_SUB_FETCH_SEQ_CST_32(type, ret, ptr, val) rsl::atomic_sub_fetch_seq_cst(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELAXED_64(type, ret, ptr, val) rsl::atomic_sub_fetch_relaxed(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQUIRE_64(type, ret, ptr, val) rsl::atomic_sub_fetch_acquire(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELEASE_64(type, ret, ptr, val) rsl::atomic_sub_fetch_release(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQ_REL_64(type, ret, ptr, val) rsl::atomic_sub_fetch_acq_rel(ptr, val)

#define REX_ATOMIC_SUB_FETCH_SEQ_CST_64(type, ret, ptr, val) rsl::atomic_sub_fetch_seq_cst(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELAXED_128(type, ret, ptr, val) rsl::atomic_sub_fetch_relaxed(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQUIRE_128(type, ret, ptr, val) rsl::atomic_sub_fetch_acquire(ptr, val)

#define REX_ATOMIC_SUB_FETCH_RELEASE_128(type, ret, ptr, val) rsl::atomic_sub_fetch_release(ptr, val)

#define REX_ATOMIC_SUB_FETCH_ACQ_REL_128(type, ret, ptr, val) rsl::atomic_sub_fetch_acq_rel(ptr, val)

#define REX_ATOMIC_SUB_FETCH_SEQ_CST_128(type, ret, ptr, val) rsl::atomic_sub_fetch_seq_cst(ptr, val)

#endif /* REX_ATOMIC_INTERNAL_MACROS_SUB_FETCH_H */
