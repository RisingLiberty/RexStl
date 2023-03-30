// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Authsub: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_fetch_sub.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    // uint8
    uint8 atomic_fetch_sub_relaxed(uint8* obj, uint8 valToSub);
    uint8 atomic_fetch_sub_acquire(uint8* obj, uint8 valToSub);
    uint8 atomic_fetch_sub_release(uint8* obj, uint8 valToSub);
    uint8 atomic_fetch_sub_acq_rel(uint8* obj, uint8 valToSub);
    uint8 atomic_fetch_sub_seq_cst(uint8* obj, uint8 valToSub);

    // int8
    int8 atomic_fetch_sub_relaxed(int8* obj, int8 valToSub);
    int8 atomic_fetch_sub_acquire(int8* obj, int8 valToSub);
    int8 atomic_fetch_sub_release(int8* obj, int8 valToSub);
    int8 atomic_fetch_sub_acq_rel(int8* obj, int8 valToSub);
    int8 atomic_fetch_sub_seq_cst(int8* obj, int8 valToSub);

    // uint16
    uint16 atomic_fetch_sub_relaxed(uint16* obj, uint16 valToSub);
    uint16 atomic_fetch_sub_acquire(uint16* obj, uint16 valToSub);
    uint16 atomic_fetch_sub_release(uint16* obj, uint16 valToSub);
    uint16 atomic_fetch_sub_acq_rel(uint16* obj, uint16 valToSub);
    uint16 atomic_fetch_sub_seq_cst(uint16* obj, uint16 valToSub);

    // int16
    int16 atomic_fetch_sub_relaxed(int16* obj, int16 valToSub);
    int16 atomic_fetch_sub_acquire(int16* obj, int16 valToSub);
    int16 atomic_fetch_sub_release(int16* obj, int16 valToSub);
    int16 atomic_fetch_sub_acq_rel(int16* obj, int16 valToSub);
    int16 atomic_fetch_sub_seq_cst(int16* obj, int16 valToSub);

    // uint32
    uint32 atomic_fetch_sub_relaxed(uint32* obj, uint32 valToSub);
    uint32 atomic_fetch_sub_acquire(uint32* obj, uint32 valToSub);
    uint32 atomic_fetch_sub_release(uint32* obj, uint32 valToSub);
    uint32 atomic_fetch_sub_acq_rel(uint32* obj, uint32 valToSub);
    uint32 atomic_fetch_sub_seq_cst(uint32* obj, uint32 valToSub);

    // int32
    int32 atomic_fetch_sub_relaxed(int32* obj, int32 valToSub);
    int32 atomic_fetch_sub_acquire(int32* obj, int32 valToSub);
    int32 atomic_fetch_sub_release(int32* obj, int32 valToSub);
    int32 atomic_fetch_sub_acq_rel(int32* obj, int32 valToSub);
    int32 atomic_fetch_sub_seq_cst(int32* obj, int32 valToSub);

    // uint64
    uint64 atomic_fetch_sub_relaxed(uint64* obj, uint64 valToSub);
    uint64 atomic_fetch_sub_acquire(uint64* obj, uint64 valToSub);
    uint64 atomic_fetch_sub_release(uint64* obj, uint64 valToSub);
    uint64 atomic_fetch_sub_acq_rel(uint64* obj, uint64 valToSub);
    uint64 atomic_fetch_sub_seq_cst(uint64* obj, uint64 valToSub);

    // int64
    int64 atomic_fetch_sub_relaxed(int64* obj, int64 valToSub);
    int64 atomic_fetch_sub_acquire(int64* obj, int64 valToSub);
    int64 atomic_fetch_sub_release(int64* obj, int64 valToSub);
    int64 atomic_fetch_sub_acq_rel(int64* obj, int64 valToSub);
    int64 atomic_fetch_sub_seq_cst(int64* obj, int64 valToSub);
  } // namespace v1
} // namespace rsl
