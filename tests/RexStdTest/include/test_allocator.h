// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_allocator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/utility/forward.h"
#include "rex_std/limits.h"

namespace rsl
{
  inline namespace v1
  {
    class test_allocator
    {
    public:
      using size_type = size_t;
      using difference_type = ptrdiff;

      test_allocator() = default;
      test_allocator(const test_allocator&) = default;
      test_allocator(test_allocator&&) = default;

      ~test_allocator() = default;

      test_allocator& operator=(const test_allocator&) = default;
      test_allocator& operator=(test_allocator&&) = default;

      REX_NO_DISCARD void* allocate(const size_type count);
      void deallocate(void* const ptr);

      size_type max_size() const;

      // construct an object of type T in allocated uninitialized storage pointer to by p
      template <typename U, typename... Args>
      void construct(U* p, Args&&... args)
      {
        new(static_cast<void*>(p)) U(rsl::forward<Args>(args)...);
      }
      // calls the destructor of the object pointed to by p
      template <typename U>
      void destroy(U* p)
      {
        p->~U();
      }

      card32 num_allocs() const;
      card32 num_frees() const;
      card32 num_bytes_allocated() const;

      card32 all_num_allocs();
      card32 all_num_frees();
      card32 all_num_bytes_allocated();

      void reset();

    private:
      card32 m_num_allocs;
      card32 m_num_frees;
      card32 m_num_bytes_allocated;

      static card32 s_all_num_allocs;
      static card32 s_all_num_frees;
      static card32 s_all_num_bytes_allocated;
    };

    constexpr bool operator==(const test_allocator& /*unused*/, const test_allocator& /*unused*/)
    {
      return true;
    }
    constexpr bool operator!=(const test_allocator& /*unused*/, const test_allocator& /*unused*/)
    {
      return false;
    }
  }
}