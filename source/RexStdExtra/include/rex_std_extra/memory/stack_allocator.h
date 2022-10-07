// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stack_allocator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/memory/unique_array.h"
#include "rex_std/bonus/types.h"

REX_RSL_BEGIN_NAMESPACE

using StackMarker = card32;

class StackAllocator
{
public:
  using size_type = count_t;
  using pointer   = void*;

  explicit StackAllocator(size_type size);

  REX_NO_DISCARD pointer allocate(const size_type size);
  void deallocate(pointer ptr, const size_type size);

  void reset();

  StackMarker current_marker() const;
  void set_market(StackMarker marker);

private:
  rsl::UniqueArray<rsl::byte> m_base_ptr;
  card32 m_current_marker;
};

REX_RSL_END_NAMESPACE