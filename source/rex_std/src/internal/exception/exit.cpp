// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: exit.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/internal/exception/exit.h"

#include <Windows.h> // for ExitProcess
// IWYU pragma: no_include <built-in>

namespace rsl
{
  inline namespace v1
  {
    void exit(card32 exitCode)
    {
      ExitProcess(exitCode);
    }
  } // namespace v1
} // namespace rsl