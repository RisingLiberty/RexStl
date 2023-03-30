// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_store.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"

namespace rsl
{
  inline namespace v1
  {
    // bool
    void atomic_store_relaxed(bool* obj, bool valToStore);
    void atomic_store_acquire(bool* obj, bool valToStore);
    void atomic_store_release(bool* obj, bool valToStore);
    void atomic_store_acq_rel(bool* obj, bool valToStore);
    void atomic_store_seq_cst(bool* obj, bool valToStore);

    // char8
    void atomic_store_relaxed(char8* obj, char8 valToStore);
    void atomic_store_acquire(char8* obj, char8 valToStore);
    void atomic_store_release(char8* obj, char8 valToStore);
    void atomic_store_acq_rel(char8* obj, char8 valToStore);
    void atomic_store_seq_cst(char8* obj, char8 valToStore);

    // uint8
    void atomic_store_relaxed(uint8* obj, uint8 valToStore);
    void atomic_store_acquire(uint8* obj, uint8 valToStore);
    void atomic_store_release(uint8* obj, uint8 valToStore);
    void atomic_store_acq_rel(uint8* obj, uint8 valToStore);
    void atomic_store_seq_cst(uint8* obj, uint8 valToStore);

    // int8
    void atomic_store_relaxed(int8* obj, int8 valToStore);
    void atomic_store_acquire(int8* obj, int8 valToStore);
    void atomic_store_release(int8* obj, int8 valToStore);
    void atomic_store_acq_rel(int8* obj, int8 valToStore);
    void atomic_store_seq_cst(int8* obj, int8 valToStore);

    // uint16
    void atomic_store_relaxed(uint16* obj, uint16 valToStore);
    void atomic_store_acquire(uint16* obj, uint16 valToStore);
    void atomic_store_release(uint16* obj, uint16 valToStore);
    void atomic_store_acq_rel(uint16* obj, uint16 valToStore);
    void atomic_store_seq_cst(uint16* obj, uint16 valToStore);

    // int16
    void atomic_store_relaxed(int16* obj, int16 valToStore);
    void atomic_store_acquire(int16* obj, int16 valToStore);
    void atomic_store_release(int16* obj, int16 valToStore);
    void atomic_store_acq_rel(int16* obj, int16 valToStore);
    void atomic_store_seq_cst(int16* obj, int16 valToStore);

    // uint32
    void atomic_store_relaxed(uint32* obj, uint32 valToStore);
    void atomic_store_acquire(uint32* obj, uint32 valToStore);
    void atomic_store_release(uint32* obj, uint32 valToStore);
    void atomic_store_acq_rel(uint32* obj, uint32 valToStore);
    void atomic_store_seq_cst(uint32* obj, uint32 valToStore);

    // int32
    void atomic_store_relaxed(int32* obj, int32 valToStore);
    void atomic_store_acquire(int32* obj, int32 valToStore);
    void atomic_store_release(int32* obj, int32 valToStore);
    void atomic_store_acq_rel(int32* obj, int32 valToStore);
    void atomic_store_seq_cst(int32* obj, int32 valToStore);

    // uint64
    void atomic_store_relaxed(uint64* obj, uint64 valToStore);
    void atomic_store_acquire(uint64* obj, uint64 valToStore);
    void atomic_store_release(uint64* obj, uint64 valToStore);
    void atomic_store_acq_rel(uint64* obj, uint64 valToStore);
    void atomic_store_seq_cst(uint64* obj, uint64 valToStore);

    // int64
    void atomic_store_relaxed(int64* obj, int64 valToStore);
    void atomic_store_acquire(int64* obj, int64 valToStore);
    void atomic_store_release(int64* obj, int64 valToStore);
    void atomic_store_acq_rel(int64* obj, int64 valToStore);
    void atomic_store_seq_cst(int64* obj, int64 valToStore);
  }
}
