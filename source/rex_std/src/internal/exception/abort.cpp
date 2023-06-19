// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: abort.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

// IWYU pragma: no_include <built-in>

#include "rex_std/bonus/types.h"
#include "rex_std/internal/exception/exit.h"

namespace rsl
{
  inline namespace v1
  {
    void abort()
    {
      const card32 abort_exit_code = 3;
      exit(abort_exit_code);
    }
  } // namespace v1
} // namespace rsl