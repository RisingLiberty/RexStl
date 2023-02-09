// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: delete.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/memory/delete.h"

#include <cstdlib>

// Can't put this in a namespace
// adding noexcept to avoid warnings on Windows
//void operator delete(void* ptr) noexcept // NOLINT(misc-new-delete-overloads)
//{
//  free(ptr); // NOLINT(cppcoreguidelines-no-malloc)
//}
//void operator delete(void* ptr, size_t /*size*/) noexcept // NOLINT(misc-new-delete-overloads)
//{
//  free(ptr); // NOLINT(cppcoreguidelines-no-malloc)
//}