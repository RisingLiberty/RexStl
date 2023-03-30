// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_exchange.h
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
    bool atomic_exchange_relaxed(bool* obj, bool value);
    bool atomic_exchange_acquire(bool* obj, bool value);
    bool atomic_exchange_release(bool* obj, bool value);
    bool atomic_exchange_acq_rel(bool* obj, bool value);
    bool atomic_exchange_seq_cst(bool* obj, bool value);

    // char8
    char8 atomic_exchange_relaxed(char8* obj, char8 value);
    char8 atomic_exchange_acquire(char8* obj, char8 value);
    char8 atomic_exchange_release(char8* obj, char8 value);
    char8 atomic_exchange_acq_rel(char8* obj, char8 value);
    char8 atomic_exchange_seq_cst(char8* obj, char8 value);

    // uint8
    uint8 atomic_exchange_relaxed(uint8* obj, uint8 value);
    uint8 atomic_exchange_acquire(uint8* obj, uint8 value);
    uint8 atomic_exchange_release(uint8* obj, uint8 value);
    uint8 atomic_exchange_acq_rel(uint8* obj, uint8 value);
    uint8 atomic_exchange_seq_cst(uint8* obj, uint8 value);

    // int8
    int8 atomic_exchange_relaxed(int8* obj, int8 value);
    int8 atomic_exchange_acquire(int8* obj, int8 value);
    int8 atomic_exchange_release(int8* obj, int8 value);
    int8 atomic_exchange_acq_rel(int8* obj, int8 value);
    int8 atomic_exchange_seq_cst(int8* obj, int8 value);

    // uint16
    uint16 atomic_exchange_relaxed(uint16* obj, uint16 value);
    uint16 atomic_exchange_acquire(uint16* obj, uint16 value);
    uint16 atomic_exchange_release(uint16* obj, uint16 value);
    uint16 atomic_exchange_acq_rel(uint16* obj, uint16 value);
    uint16 atomic_exchange_seq_cst(uint16* obj, uint16 value);

    // int16
    int16 atomic_exchange_relaxed(int16* obj, int16 value);
    int16 atomic_exchange_acquire(int16* obj, int16 value);
    int16 atomic_exchange_release(int16* obj, int16 value);
    int16 atomic_exchange_acq_rel(int16* obj, int16 value);
    int16 atomic_exchange_seq_cst(int16* obj, int16 value);

    // uint32
    uint32 atomic_exchange_relaxed(uint32* obj, uint32 value);
    uint32 atomic_exchange_acquire(uint32* obj, uint32 value);
    uint32 atomic_exchange_release(uint32* obj, uint32 value);
    uint32 atomic_exchange_acq_rel(uint32* obj, uint32 value);
    uint32 atomic_exchange_seq_cst(uint32* obj, uint32 value);

    // int32
    int32 atomic_exchange_relaxed(int32* obj, int32 value);
    int32 atomic_exchange_acquire(int32* obj, int32 value);
    int32 atomic_exchange_release(int32* obj, int32 value);
    int32 atomic_exchange_acq_rel(int32* obj, int32 value);
    int32 atomic_exchange_seq_cst(int32* obj, int32 value);

    // uint64
    uint64 atomic_exchange_relaxed(uint64* obj, uint64 value);
    uint64 atomic_exchange_acquire(uint64* obj, uint64 value);
    uint64 atomic_exchange_release(uint64* obj, uint64 value);
    uint64 atomic_exchange_acq_rel(uint64* obj, uint64 value);
    uint64 atomic_exchange_seq_cst(uint64* obj, uint64 value);

    // int64
    int64 atomic_exchange_relaxed(int64* obj, int64 value);
    int64 atomic_exchange_acquire(int64* obj, int64 value);
    int64 atomic_exchange_release(int64* obj, int64 value);
    int64 atomic_exchange_acq_rel(int64* obj, int64 value);
    int64 atomic_exchange_seq_cst(int64* obj, int64 value);
  }
}