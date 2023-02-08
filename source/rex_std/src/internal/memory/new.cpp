// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: new.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/new.h"

#include <cstdlib>

void* operator new(size_t size)
{
  malloc(size);
}

void* operator new(size_t size, void* where) noexcept
{
  (void)size;
  return where;
}
