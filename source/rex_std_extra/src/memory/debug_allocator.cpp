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

#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::DebugAllocator::pointer rsl::DebugAllocator::allocate([[maybe_unused]] const size_type size)
{
#ifndef RETAIL
  return static_cast<pointer>(operator new(size));
#else
  return nullptr;
#endif
}

void rsl::DebugAllocator::deallocate(pointer ptr, const size_type size)
{
  operator delete(ptr, size);
}

bool rsl::DebugAllocator::operator==(const DebugAllocator&) const
{
  return true;
}
bool rsl::DebugAllocator::operator!=(const DebugAllocator&) const
{
  return false;
}