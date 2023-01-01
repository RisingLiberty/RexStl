// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_allocator.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "test_allocator.h"

namespace rsl
{
  inline namespace v1
  {
    card32 test_allocator::s_all_num_allocs = 0;
    card32 test_allocator::s_all_num_frees = 0;
    card32 test_allocator::s_all_num_bytes_allocated = 0;

    REX_NO_DISCARD void* test_allocator::allocate(const size_type count) // NOLINT(readability-convert-member-functions-to-static)
    {
      m_num_allocs++;
      m_num_bytes_allocated += static_cast<card32>(count);
      s_all_num_allocs++;
      s_all_num_bytes_allocated += static_cast<card32>(count);
      return (operator new(count));
    }
    void test_allocator::deallocate(void* const ptr) // NOLINT(readability-convert-member-functions-to-static)
    {
      m_num_frees++;
      s_all_num_frees++;
      operator delete(ptr);
    }

    test_allocator::size_type test_allocator::max_size() const // NOLINT(readability-convert-member-functions-to-static)
    {
      return rsl::numeric_limits<size_type>::max();
    }

    card32 test_allocator::num_allocs() const
    {
      return m_num_allocs;
    }
    card32 test_allocator::num_frees() const
    {
      return m_num_frees;
    }
    card32 test_allocator::num_bytes_allocated() const
    {
      return m_num_bytes_allocated;
    }

    card32 test_allocator::all_num_allocs()
    {
      return s_all_num_allocs;
    }

    card32 test_allocator::all_num_frees()
    {
      return s_all_num_frees;
    }

    card32 test_allocator::all_num_bytes_allocated()
    {
      return s_all_num_bytes_allocated;
    }

    void test_allocator::reset()
    {
      s_all_num_allocs -= m_num_allocs;
      s_all_num_frees -= m_num_frees;
      s_all_num_bytes_allocated -= m_num_bytes_allocated;

      m_num_allocs = 0;
      m_num_frees = 0;
      m_num_bytes_allocated = 0;
    }

  }
}
