// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_fetch_or.h
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
    bool atomic_fetch_or_relaxed(bool* obj, bool valToOr);
    bool atomic_fetch_or_acquire(bool* obj, bool valToOr);
    bool atomic_fetch_or_release(bool* obj, bool valToOr);
    bool atomic_fetch_or_acq_rel(bool* obj, bool valToOr);
    bool atomic_fetch_or_seq_cst(bool* obj, bool valToOr);

    // char8
    char8 atomic_fetch_or_relaxed(char8* obj, char8 valToOr);
    char8 atomic_fetch_or_acquire(char8* obj, char8 valToOr);
    char8 atomic_fetch_or_release(char8* obj, char8 valToOr);
    char8 atomic_fetch_or_acq_rel(char8* obj, char8 valToOr);
    char8 atomic_fetch_or_seq_cst(char8* obj, char8 valToOr);

    // uint8
    uint8 atomic_fetch_or_relaxed(uint8* obj, uint8 valToOr);
    uint8 atomic_fetch_or_acquire(uint8* obj, uint8 valToOr);
    uint8 atomic_fetch_or_release(uint8* obj, uint8 valToOr);
    uint8 atomic_fetch_or_acq_rel(uint8* obj, uint8 valToOr);
    uint8 atomic_fetch_or_seq_cst(uint8* obj, uint8 valToOr);

    // int8
    int8 atomic_fetch_or_relaxed(int8* obj, int8 valToOr);
    int8 atomic_fetch_or_acquire(int8* obj, int8 valToOr);
    int8 atomic_fetch_or_release(int8* obj, int8 valToOr);
    int8 atomic_fetch_or_acq_rel(int8* obj, int8 valToOr);
    int8 atomic_fetch_or_seq_cst(int8* obj, int8 valToOr);

    // uint16
    uint16 atomic_fetch_or_relaxed(uint16* obj, uint16 valToOr);
    uint16 atomic_fetch_or_acquire(uint16* obj, uint16 valToOr);
    uint16 atomic_fetch_or_release(uint16* obj, uint16 valToOr);
    uint16 atomic_fetch_or_acq_rel(uint16* obj, uint16 valToOr);
    uint16 atomic_fetch_or_seq_cst(uint16* obj, uint16 valToOr);

    // int16
    int16 atomic_fetch_or_relaxed(int16* obj, int16 valToOr);
    int16 atomic_fetch_or_acquire(int16* obj, int16 valToOr);
    int16 atomic_fetch_or_release(int16* obj, int16 valToOr);
    int16 atomic_fetch_or_acq_rel(int16* obj, int16 valToOr);
    int16 atomic_fetch_or_seq_cst(int16* obj, int16 valToOr);

    // uint32
    uint32 atomic_fetch_or_relaxed(uint32* obj, uint32 valToOr);
    uint32 atomic_fetch_or_acquire(uint32* obj, uint32 valToOr);
    uint32 atomic_fetch_or_release(uint32* obj, uint32 valToOr);
    uint32 atomic_fetch_or_acq_rel(uint32* obj, uint32 valToOr);
    uint32 atomic_fetch_or_seq_cst(uint32* obj, uint32 valToOr);

    // int32
    int32 atomic_fetch_or_relaxed(int32* obj, int32 valToOr);
    int32 atomic_fetch_or_acquire(int32* obj, int32 valToOr);
    int32 atomic_fetch_or_release(int32* obj, int32 valToOr);
    int32 atomic_fetch_or_acq_rel(int32* obj, int32 valToOr);
    int32 atomic_fetch_or_seq_cst(int32* obj, int32 valToOr);

    // uint64
    uint64 atomic_fetch_or_relaxed(uint64* obj, uint64 valToOr);
    uint64 atomic_fetch_or_acquire(uint64* obj, uint64 valToOr);
    uint64 atomic_fetch_or_release(uint64* obj, uint64 valToOr);
    uint64 atomic_fetch_or_acq_rel(uint64* obj, uint64 valToOr);
    uint64 atomic_fetch_or_seq_cst(uint64* obj, uint64 valToOr);

    // int64
    int64 atomic_fetch_or_relaxed(int64* obj, int64 valToOr);
    int64 atomic_fetch_or_acquire(int64* obj, int64 valToOr);
    int64 atomic_fetch_or_release(int64* obj, int64 valToOr);
    int64 atomic_fetch_or_acq_rel(int64* obj, int64 valToOr);
    int64 atomic_fetch_or_seq_cst(int64* obj, int64 valToOr);
  } // namespace v1
} // namespace rsl
