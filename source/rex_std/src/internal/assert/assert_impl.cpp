// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: assert_impl.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/internal/assert/assert_impl.h"
#include "rex_std/stacktrace.h"

#include "rex_std/iostream.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      void log_assert(const fmt_stack_string& msg) // NOLINT(misc-no-recursion)
      {
        rsl::cerr << "Assert: " << msg.data() << "\n";
        rsl::cerr << rsl::stacktrace::current() << "\n";
      }
    } // namespace internal
  }   // namespace v1
} // namespace rsl