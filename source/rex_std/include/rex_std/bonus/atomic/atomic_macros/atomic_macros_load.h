

#ifndef REX_ATOMIC_INTERNAL_MACROS_LOAD_H
#define REX_ATOMIC_INTERNAL_MACROS_LOAD_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_LOAD_*_N(type, type ret, type * ptr)
//
#define REX_ATOMIC_LOAD_RELAXED_8(type, ret, ptr) rsl::atomic_load_relaxed(ptr)

#define REX_ATOMIC_LOAD_ACQUIRE_8(type, ret, ptr) rsl::atomic_load_acquire(ptr)

#define REX_ATOMIC_LOAD_SEQ_CST_8(type, ret, ptr) rsl::atomic_load_seq_cst(ptr)

#define REX_ATOMIC_LOAD_RELAXED_16(type, ret, ptr) rsl::atomic_load_relaxed(ptr)

#define REX_ATOMIC_LOAD_ACQUIRE_16(type, ret, ptr) rsl::atomic_load_acquire(ptr)

#define REX_ATOMIC_LOAD_SEQ_CST_16(type, ret, ptr) rsl::atomic_load_seq_cst(ptr)

#define REX_ATOMIC_LOAD_RELAXED_32(type, ret, ptr) rsl::atomic_load_relaxed(ptr)

#define REX_ATOMIC_LOAD_ACQUIRE_32(type, ret, ptr) rsl::atomic_load_acquire(ptr)

#define REX_ATOMIC_LOAD_SEQ_CST_32(type, ret, ptr) rsl::atomic_load_seq_cst(ptr)

#define REX_ATOMIC_LOAD_RELAXED_64(type, ret, ptr) rsl::atomic_load_relaxed(ptr)

#define REX_ATOMIC_LOAD_ACQUIRE_64(type, ret, ptr) rsl::atomic_load_acquire(ptr)

#define REX_ATOMIC_LOAD_SEQ_CST_64(type, ret, ptr) rsl::atomic_load_seq_cst(ptr)

#define REX_ATOMIC_LOAD_RELAXED_128(type, ret, ptr) rsl::atomic_load_relaxed(ptr)

#define REX_ATOMIC_LOAD_ACQUIRE_128(type, ret, ptr) rsl::atomic_load_acquire(ptr)

#define REX_ATOMIC_LOAD_SEQ_CST_128(type, ret, ptr) rsl::atomic_load_seq_cst(ptr)

#define REX_ATOMIC_LOAD_READ_DEPENDS_32(type, ret, ptr) rsl::atomic_load_read_depends(ptr)

#define REX_ATOMIC_LOAD_READ_DEPENDS_64(type, ret, ptr) rsl::atomic_load_read_depends(ptr)

#endif /* REX_ATOMIC_INTERNAL_MACROS_LOAD_H */
