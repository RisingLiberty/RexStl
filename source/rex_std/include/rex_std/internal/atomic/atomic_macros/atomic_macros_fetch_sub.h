

#ifndef REX_ATOMIC_INTERNAL_MACROS_FETCH_SUB_H
#define REX_ATOMIC_INTERNAL_MACROS_FETCH_SUB_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ATOMIC_FETCH_SUB_*_N(type, type ret, type * ptr, type val)
//
#define REX_ATOMIC_FETCH_SUB_RELAXED_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELAXED_8)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQUIRE_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQUIRE_8)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELEASE_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELEASE_8)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQ_REL_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQ_REL_8)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_SEQ_CST_8(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_SEQ_CST_8)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELAXED_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELAXED_16)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQUIRE_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQUIRE_16)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELEASE_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELEASE_16)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQ_REL_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQ_REL_16)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_SEQ_CST_16(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_SEQ_CST_16)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELAXED_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELAXED_32)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQUIRE_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQUIRE_32)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELEASE_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELEASE_32)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQ_REL_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQ_REL_32)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_SEQ_CST_32(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_SEQ_CST_32)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELAXED_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELAXED_64)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQUIRE_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQUIRE_64)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELEASE_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELEASE_64)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQ_REL_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQ_REL_64)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_SEQ_CST_64(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_SEQ_CST_64)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELAXED_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELAXED_128)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQUIRE_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQUIRE_128)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_RELEASE_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_RELEASE_128)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_ACQ_REL_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_ACQ_REL_128)(type, ret, ptr, val)

#define REX_ATOMIC_FETCH_SUB_SEQ_CST_128(type, ret, ptr, val) REX_ATOMIC_CHOOSE_OP_IMPL(ATOMIC_FETCH_SUB_SEQ_CST_128)(type, ret, ptr, val)

#endif /* REX_ATOMIC_INTERNAL_MACROS_FETCH_SUB_H */
