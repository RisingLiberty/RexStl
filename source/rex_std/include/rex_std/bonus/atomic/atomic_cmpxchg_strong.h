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

#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    // bool
    bool atomic_cmpxchg_strong_relaxed(bool* obj, bool expected, bool desired, rsl::memory_order failureOrder);
    bool atomic_cmpxchg_strong_acquire(bool* obj, bool expected, bool desired, rsl::memory_order failureOrder);
    bool atomic_cmpxchg_strong_release(bool* obj, bool expected, bool desired, rsl::memory_order failureOrder);
    bool atomic_cmpxchg_strong_acq_rel(bool* obj, bool expected, bool desired, rsl::memory_order failureOrder);
    bool atomic_cmpxchg_strong_seq_cst(bool* obj, bool expected, bool desired, rsl::memory_order failureOrder);

    // char8
    char8 atomic_cmpxchg_strong_relaxed(char8* obj, char8 expected, char8 desired, rsl::memory_order failureOrder);
    char8 atomic_cmpxchg_strong_acquire(char8* obj, char8 expected, char8 desired, rsl::memory_order failureOrder);
    char8 atomic_cmpxchg_strong_release(char8* obj, char8 expected, char8 desired, rsl::memory_order failureOrder);
    char8 atomic_cmpxchg_strong_acq_rel(char8* obj, char8 expected, char8 desired, rsl::memory_order failureOrder);
    char8 atomic_cmpxchg_strong_seq_cst(char8* obj, char8 expected, char8 desired, rsl::memory_order failureOrder);

    // uint8
    uint8 atomic_cmpxchg_strong_relaxed(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder);
    uint8 atomic_cmpxchg_strong_acquire(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder);
    uint8 atomic_cmpxchg_strong_release(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder);
    uint8 atomic_cmpxchg_strong_acq_rel(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder);
    uint8 atomic_cmpxchg_strong_seq_cst(uint8* obj, uint8 expected, uint8 desired, rsl::memory_order failureOrder);

    // int8
    int8 atomic_cmpxchg_strong_relaxed(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder);
    int8 atomic_cmpxchg_strong_acquire(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder);
    int8 atomic_cmpxchg_strong_release(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder);
    int8 atomic_cmpxchg_strong_acq_rel(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder);
    int8 atomic_cmpxchg_strong_seq_cst(int8* obj, int8 expected, int8 desired, rsl::memory_order failureOrder);

    // uint16
    uint16 atomic_cmpxchg_strong_relaxed(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder);
    uint16 atomic_cmpxchg_strong_acquire(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder);
    uint16 atomic_cmpxchg_strong_release(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder);
    uint16 atomic_cmpxchg_strong_acq_rel(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder);
    uint16 atomic_cmpxchg_strong_seq_cst(uint16* obj, uint16 expected, uint16 desired, rsl::memory_order failureOrder);

    // int16
    int16 atomic_cmpxchg_strong_relaxed(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder);
    int16 atomic_cmpxchg_strong_acquire(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder);
    int16 atomic_cmpxchg_strong_release(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder);
    int16 atomic_cmpxchg_strong_acq_rel(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder);
    int16 atomic_cmpxchg_strong_seq_cst(int16* obj, int16 expected, int16 desired, rsl::memory_order failureOrder);

    // uint32
    uint32 atomic_cmpxchg_strong_relaxed(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder);
    uint32 atomic_cmpxchg_strong_acquire(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder);
    uint32 atomic_cmpxchg_strong_release(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder);
    uint32 atomic_cmpxchg_strong_acq_rel(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder);
    uint32 atomic_cmpxchg_strong_seq_cst(uint32* obj, uint32 expected, uint32 desired, rsl::memory_order failureOrder);

    // int32
    int32 atomic_cmpxchg_strong_relaxed(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder);
    int32 atomic_cmpxchg_strong_acquire(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder);
    int32 atomic_cmpxchg_strong_release(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder);
    int32 atomic_cmpxchg_strong_acq_rel(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder);
    int32 atomic_cmpxchg_strong_seq_cst(int32* obj, int32 expected, int32 desired, rsl::memory_order failureOrder);

    // uint64
    uint64 atomic_cmpxchg_strong_relaxed(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder);
    uint64 atomic_cmpxchg_strong_acquire(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder);
    uint64 atomic_cmpxchg_strong_release(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder);
    uint64 atomic_cmpxchg_strong_acq_rel(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder);
    uint64 atomic_cmpxchg_strong_seq_cst(uint64* obj, uint64 expected, uint64 desired, rsl::memory_order failureOrder);

    // int64
    int64 atomic_cmpxchg_strong_relaxed(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder);
    int64 atomic_cmpxchg_strong_acquire(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder);
    int64 atomic_cmpxchg_strong_release(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder);
    int64 atomic_cmpxchg_strong_acq_rel(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder);
    int64 atomic_cmpxchg_strong_seq_cst(int64* obj, int64 expected, int64 desired, rsl::memory_order failureOrder);
  } // namespace v1
} // namespace rsl
