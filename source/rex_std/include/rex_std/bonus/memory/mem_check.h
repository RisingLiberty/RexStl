// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: mem_check.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    const void* memcheck(const void* p, uint8 value, count_t byteCount);
    const void* memcheck(const void* p, uint16 value, count_t byteCount);
    const void* memcheck(const void* p, uint32 value, count_t byteCount);
    const void* memcheck(const void* p, uint64 value, count_t byteCount);

    const void* memcheck(const void* p, int8 value, count_t byteCount);
    const void* memcheck(const void* p, int16 value, count_t byteCount);
    const void* memcheck(const void* p, int32 value, count_t byteCount);
    const void* memcheck(const void* p, int64 value, count_t byteCount);
  }
}