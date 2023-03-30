// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_fetch_xor.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    // bool
    bool atomic_fetch_xor_relaxed(bool* obj, bool valToXor);
    bool atomic_fetch_xor_acquire(bool* obj, bool valToXor);
    bool atomic_fetch_xor_release(bool* obj, bool valToXor);
    bool atomic_fetch_xor_acq_rel(bool* obj, bool valToXor);
    bool atomic_fetch_xor_seq_cst(bool* obj, bool valToXor);

    // char8
    char8 atomic_fetch_xor_relaxed(char8* obj, char8 valToXor);
    char8 atomic_fetch_xor_acquire(char8* obj, char8 valToXor);
    char8 atomic_fetch_xor_release(char8* obj, char8 valToXor);
    char8 atomic_fetch_xor_acq_rel(char8* obj, char8 valToXor);
    char8 atomic_fetch_xor_seq_cst(char8* obj, char8 valToXor);

    // uint8
    uint8 atomic_fetch_xor_relaxed(uint8* obj, uint8 valToXor);
    uint8 atomic_fetch_xor_acquire(uint8* obj, uint8 valToXor);
    uint8 atomic_fetch_xor_release(uint8* obj, uint8 valToXor);
    uint8 atomic_fetch_xor_acq_rel(uint8* obj, uint8 valToXor);
    uint8 atomic_fetch_xor_seq_cst(uint8* obj, uint8 valToXor);

    // int8
    int8 atomic_fetch_xor_relaxed(int8* obj, int8 valToXor);
    int8 atomic_fetch_xor_acquire(int8* obj, int8 valToXor);
    int8 atomic_fetch_xor_release(int8* obj, int8 valToXor);
    int8 atomic_fetch_xor_acq_rel(int8* obj, int8 valToXor);
    int8 atomic_fetch_xor_seq_cst(int8* obj, int8 valToXor);

    // uint16
    uint16 atomic_fetch_xor_relaxed(uint16* obj, uint16 valToXor);
    uint16 atomic_fetch_xor_acquire(uint16* obj, uint16 valToXor);
    uint16 atomic_fetch_xor_release(uint16* obj, uint16 valToXor);
    uint16 atomic_fetch_xor_acq_rel(uint16* obj, uint16 valToXor);
    uint16 atomic_fetch_xor_seq_cst(uint16* obj, uint16 valToXor);

    // int16
    int16 atomic_fetch_xor_relaxed(int16* obj, int16 valToXor);
    int16 atomic_fetch_xor_acquire(int16* obj, int16 valToXor);
    int16 atomic_fetch_xor_release(int16* obj, int16 valToXor);
    int16 atomic_fetch_xor_acq_rel(int16* obj, int16 valToXor);
    int16 atomic_fetch_xor_seq_cst(int16* obj, int16 valToXor);

    // uint32
    uint32 atomic_fetch_xor_relaxed(uint32* obj, uint32 valToXor);
    uint32 atomic_fetch_xor_acquire(uint32* obj, uint32 valToXor);
    uint32 atomic_fetch_xor_release(uint32* obj, uint32 valToXor);
    uint32 atomic_fetch_xor_acq_rel(uint32* obj, uint32 valToXor);
    uint32 atomic_fetch_xor_seq_cst(uint32* obj, uint32 valToXor);

    // int32
    int32 atomic_fetch_xor_relaxed(int32* obj, int32 valToXor);
    int32 atomic_fetch_xor_acquire(int32* obj, int32 valToXor);
    int32 atomic_fetch_xor_release(int32* obj, int32 valToXor);
    int32 atomic_fetch_xor_acq_rel(int32* obj, int32 valToXor);
    int32 atomic_fetch_xor_seq_cst(int32* obj, int32 valToXor);

    // uint64
    uint64 atomic_fetch_xor_relaxed(uint64* obj, uint64 valToXor);
    uint64 atomic_fetch_xor_acquire(uint64* obj, uint64 valToXor);
    uint64 atomic_fetch_xor_release(uint64* obj, uint64 valToXor);
    uint64 atomic_fetch_xor_acq_rel(uint64* obj, uint64 valToXor);
    uint64 atomic_fetch_xor_seq_cst(uint64* obj, uint64 valToXor);

    // int64
    int64 atomic_fetch_xor_relaxed(int64* obj, int64 valToXor);
    int64 atomic_fetch_xor_acquire(int64* obj, int64 valToXor);
    int64 atomic_fetch_xor_release(int64* obj, int64 valToXor);
    int64 atomic_fetch_xor_acq_rel(int64* obj, int64 valToXor);
    int64 atomic_fetch_xor_seq_cst(int64* obj, int64 valToXor);
  }
}
