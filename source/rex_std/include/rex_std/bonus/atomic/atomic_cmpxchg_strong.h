// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_cmpxchg_strong.h
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
    void atomic_cmpxchg_strong_relaxed(uint8 val, uint8* address);
    void atomic_cmpxchg_strong_acquire(uint8 val, uint8* address);
    void atomic_cmpxchg_strong_release(uint8 val, uint8* address);
    void atomic_cmpxchg_strong_acq_rel(uint8 val, uint8* address);
    void atomic_cmpxchg_strong_seq_cst(uint8 val, uint8* address);

    // int8
    void atomic_cmpxchg_strong_relaxed(int8 val, int8* address);
    void atomic_cmpxchg_strong_acquire(int8 val, int8* address);
    void atomic_cmpxchg_strong_release(int8 val, int8* address);
    void atomic_cmpxchg_strong_acq_rel(int8 val, int8* address);
    void atomic_cmpxchg_strong_seq_cst(int8 val, int8* address);

    // uint16
    void atomic_cmpxchg_strong_relaxed(uint16 val, uint16* address);
    void atomic_cmpxchg_strong_acquire(uint16 val, uint16* address);
    void atomic_cmpxchg_strong_release(uint16 val, uint16* address);
    void atomic_cmpxchg_strong_acq_rel(uint16 val, uint16* address);
    void atomic_cmpxchg_strong_seq_cst(uint16 val, uint16* address);

    // int16
    void atomic_cmpxchg_strong_relaxed(int16 val, int16* address);
    void atomic_cmpxchg_strong_acquire(int16 val, int16* address);
    void atomic_cmpxchg_strong_release(int16 val, int16* address);
    void atomic_cmpxchg_strong_acq_rel(int16 val, int16* address);
    void atomic_cmpxchg_strong_seq_cst(int16 val, int16* address);

    // uint32
    void atomic_cmpxchg_strong_relaxed(uint32 val, uint32* address);
    void atomic_cmpxchg_strong_acquire(uint32 val, uint32* address);
    void atomic_cmpxchg_strong_release(uint32 val, uint32* address);
    void atomic_cmpxchg_strong_acq_rel(uint32 val, uint32* address);
    void atomic_cmpxchg_strong_seq_cst(uint32 val, uint32* address);

    // int32
    void atomic_cmpxchg_strong_relaxed(int32 val, int32* address);
    void atomic_cmpxchg_strong_acquire(int32 val, int32* address);
    void atomic_cmpxchg_strong_release(int32 val, int32* address);
    void atomic_cmpxchg_strong_acq_rel(int32 val, int32* address);
    void atomic_cmpxchg_strong_seq_cst(int32 val, int32* address);

    // uint64
    void atomic_cmpxchg_strong_relaxed(uint64 val, uint64* address);
    void atomic_cmpxchg_strong_acquire(uint64 val, uint64* address);
    void atomic_cmpxchg_strong_release(uint64 val, uint64* address);
    void atomic_cmpxchg_strong_acq_rel(uint64 val, uint64* address);
    void atomic_cmpxchg_strong_seq_cst(uint64 val, uint64* address);

    // int64
    void atomic_cmpxchg_strong_relaxed(int64 val, int64* address);
    void atomic_cmpxchg_strong_acquire(int64 val, int64* address);
    void atomic_cmpxchg_strong_release(int64 val, int64* address);
    void atomic_cmpxchg_strong_acq_rel(int64 val, int64* address);
    void atomic_cmpxchg_strong_seq_cst(int64 val, int64* address);
  }
}
