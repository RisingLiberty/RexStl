// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_load.h
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
    uint8 atomic_load_relaxed(uint8* obj);
    uint8 atomic_load_acquire(uint8* obj);
    uint8 atomic_load_release(uint8* obj);
    uint8 atomic_load_acq_rel(uint8* obj);
    uint8 atomic_load_seq_cst(uint8* obj);

    // int8
    int8 atomic_load_relaxed(int8* obj);
    int8 atomic_load_acquire(int8* obj);
    int8 atomic_load_release(int8* obj);
    int8 atomic_load_acq_rel(int8* obj);
    int8 atomic_load_seq_cst(int8* obj);

    // uint16
    uint16 atomic_load_relaxed(uint16* obj);
    uint16 atomic_load_acquire(uint16* obj);
    uint16 atomic_load_release(uint16* obj);
    uint16 atomic_load_acq_rel(uint16* obj);
    uint16 atomic_load_seq_cst(uint16* obj);

    // int16
    int16 atomic_load_relaxed(int16* obj);
    int16 atomic_load_acquire(int16* obj);
    int16 atomic_load_release(int16* obj);
    int16 atomic_load_acq_rel(int16* obj);
    int16 atomic_load_seq_cst(int16* obj);

    // uint32
    uint32 atomic_load_relaxed(uint32* obj);
    uint32 atomic_load_acquire(uint32* obj);
    uint32 atomic_load_release(uint32* obj);
    uint32 atomic_load_acq_rel(uint32* obj);
    uint32 atomic_load_seq_cst(uint32* obj);

    // int32
    int32 atomic_load_relaxed(int32* obj);
    int32 atomic_load_acquire(int32* obj);
    int32 atomic_load_release(int32* obj);
    int32 atomic_load_acq_rel(int32* obj);
    int32 atomic_load_seq_cst(int32* obj);

    // uint64
    uint64 atomic_load_relaxed(uint64* obj);
    uint64 atomic_load_acquire(uint64* obj);
    uint64 atomic_load_release(uint64* obj);
    uint64 atomic_load_acq_rel(uint64* obj);
    uint64 atomic_load_seq_cst(uint64* obj);

    // int64
    int64 atomic_load_relaxed(int64* obj, int64 valToSub);
    int64 atomic_load_acquire(int64* obj, int64 valToSub);
    int64 atomic_load_release(int64* obj, int64 valToSub);
    int64 atomic_load_acq_rel(int64* obj, int64 valToSub);
    int64 atomic_load_seq_cst(int64* obj, int64 valToSub);
  }
}
