// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: debug_allocator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

class DebugAllocator
{
public:
  using size_type = count_t;
  using pointer   = void*;

  REX_NO_DISCARD pointer allocate(const size_type size);
  void deallocate(pointer ptr, const size_type size);

  bool operator==(const DebugAllocator& rhs) const;
  bool operator!=(const DebugAllocator& rhs) const;
};

REX_RSL_END_NAMESPACE