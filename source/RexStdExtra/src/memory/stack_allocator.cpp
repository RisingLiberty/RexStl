// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stack_allocator.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/memory/stack_allocator.h"

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::StackAllocator::StackAllocator(size_type size)
    : m_base_ptr(rsl::make_unique<rsl::byte[]>(size))
    , m_current_marker(0)
{
}

rsl::StackAllocator::pointer rsl::StackAllocator::allocate(const size_type size)
{
  REX_ASSERT_X(m_current_marker + size <= m_base_ptr.count(), "Stack allocator out of bounds! \nmax size: ", m_base_ptr.count(), " new size: ", m_current_marker + size);

  void* mem = &m_base_ptr[m_current_marker];
  m_current_marker += size;
  return mem;
}
void rsl::StackAllocator::deallocate(pointer, const size_type)
{
  // Nothing to implement
}

void rsl::StackAllocator::reset()
{
  set_market(0);
}

rsl::StackMarker rsl::StackAllocator::current_marker() const
{
  return m_current_marker;
}

void rsl::StackAllocator::set_market(StackMarker marker)
{
  m_current_marker = marker;
}