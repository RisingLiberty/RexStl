// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stack_allocator.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/types.h"
#include "rex_std/memory.h"

namespace rsl
{
  inline namespace v1
  {

    using StackMarker = card32;

    class stack_allocator
    {
    public:
      using size_type = count_t;
      using pointer   = void*;

      explicit stack_allocator(size_type size);

      REX_NO_DISCARD pointer allocate(const size_type size);
      void deallocate(pointer ptr, const size_type size);

      void reset();

      StackMarker current_marker() const;
      void set_market(StackMarker marker);

    private:
      rsl::unique_array<rsl::byte> m_base_ptr;
      card32 m_current_marker;
    };

  } // namespace v1
} // namespace rsl