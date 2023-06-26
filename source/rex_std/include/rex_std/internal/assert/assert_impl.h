// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: assert_impl.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

//-----------------------------------------------------------------------------
// Implementation of the assert function. This is implemented in a different file
// to avoid circular inclusion issues.
//-----------------------------------------------------------------------------

#pragma once

#include "rex_std/bonus/attributes.h"
#include "rex_std/bonus/defines.h"
#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/bonus/types.h"
#include "rex_std/internal/assert/assert_fwd.h"
#include "rex_std/internal/format/fmt_string.h"
#include "rex_std/internal/memory/allocator.h"
#include "rex_std/internal/string/basic_string.h"
#include "rex_std/internal/string/char_traits.h"
#include "rex_std/internal/string_view/basic_string_view.h"
#include "rex_std/internal/utility/forward.h"
#include "rex_std/internal/utility/swap.h"

namespace rsl
{
  inline namespace v1
  {
    class allocator; // IWYU pragma: keep
    template <typename CharType, typename Traits, typename Allocator>
    class basic_string; // IWYU pragma: keep
    using string = basic_string<char8, char_traits<char8>, allocator>;

    using fmt_stack_string = rsl::stack_string<char8, 500>;

    namespace internal
    {
      void log_assert(const fmt_stack_string& msg);
    } // namespace internal

    template <typename... T>
    REX_NO_DISCARD inline rsl::fmt_stack_string format(format_string<T...> fmt, T&&... args); // NOLINT(misc-no-recursion, readability-redundant-declaration)

    template <typename... Args>
    bool rex_assert(bool cond, Args&&... args) // NOLINT(misc-no-recursion)
    {
      if(!cond)
      {
        thread_local static bool is_processing_assert = false;
        if(!is_processing_assert)
        {
          is_processing_assert        = true;
          const fmt_stack_string& str = rsl::format(rsl::forward<Args>(args)...);
          internal::log_assert(str);
          DEBUG_BREAK();
          return true;
        }
        else
        {
          // if this is hit, an assert occurred while processing another one.
          // to avoid circular dependency, we break here if there's a debugger attached
          DEBUG_BREAK();
        }
      }

      return false;
    }

  } // namespace v1
} // namespace rsl

#include "rex_std/format.h" // IWYU pragma: keep