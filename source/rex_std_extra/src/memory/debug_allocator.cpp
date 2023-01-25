// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: debug_allocator.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/memory/debug_allocator.h"

#include "rex_std/memory.h"

rsl::debug_allocator::pointer rsl::debug_allocator::allocate([[maybe_unused]] const size_type size)
{
#ifndef RETAIL
  return static_cast<pointer>(operator new(size));
#else
  return nullptr;
#endif
}

void rsl::debug_allocator::deallocate(pointer ptr, const size_type size)
{
  operator delete(ptr, size);
}

bool rsl::debug_allocator::operator==(const debug_allocator&) const
{
  return true;
}
bool rsl::debug_allocator::operator!=(const debug_allocator&) const
{
  return false;
}