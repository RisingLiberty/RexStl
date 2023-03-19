// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_read.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
    int8 atomic_read(int8& val);
    int16 atomic_read(int16& val);
    int32 atomic_read(int32& val);
    int64 atomic_read(int64& val);

    uint8 atomic_read(uint8& val);
    uint16 atomic_read(uint16& val);
    uint32 atomic_read(uint32& val);
    uint64 atomic_read(uint64& val);
  }
}
