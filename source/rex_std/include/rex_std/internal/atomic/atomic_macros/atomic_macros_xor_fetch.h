

#ifndef REX_ATOMIC_INTERNAL_MACROS_XOR_FETCH_H
#define REX_ATOMIC_INTERNAL_MACROS_XOR_FETCH_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_XOR_FETCH_*_N(type, type ret, type * ptr, type val)
//
#define REX_ATOMIC_XOR_FETCH_RELAXED_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELAXED_8)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQUIRE_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQUIRE_8)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELEASE_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELEASE_8)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQ_REL_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQ_REL_8)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_SEQ_CST_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_SEQ_CST_8)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELAXED_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELAXED_16)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQUIRE_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQUIRE_16)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELEASE_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELEASE_16)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQ_REL_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQ_REL_16)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_SEQ_CST_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_SEQ_CST_16)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELAXED_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELAXED_32)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQUIRE_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQUIRE_32)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELEASE_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELEASE_32)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQ_REL_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQ_REL_32)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_SEQ_CST_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_SEQ_CST_32)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELAXED_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELAXED_64)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQUIRE_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQUIRE_64)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELEASE_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELEASE_64)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQ_REL_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQ_REL_64)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_SEQ_CST_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_SEQ_CST_64)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELAXED_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELAXED_128)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQUIRE_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQUIRE_128)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_RELEASE_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_RELEASE_128)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_ACQ_REL_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_ACQ_REL_128)(type, ret, ptr, val)

#define REX_ATOMIC_XOR_FETCH_SEQ_CST_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_XOR_FETCH_SEQ_CST_128)(type, ret, ptr, val)

#endif /* REX_ATOMIC_INTERNAL_MACROS_XOR_FETCH_H */
