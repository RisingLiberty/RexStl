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

#include "rex_std/internal/format/fmt_string.h"
#include "rex_std/internal/utility/forward.h"

namespace rsl
{
  inline namespace v1
  {
    class allocator;
    template <typename CharType, typename Traits, typename Allocator>
    class basic_string;

    using string = basic_string<char8, char_traits<char8>, allocator>;

    namespace internal
    {
      void log_assert(const rsl::string& msg);
    } // namespace internal

    template <typename... T>
    REX_NO_DISCARD inline auto format(format_string<T...> fmt, T&&... args) -> rsl::string;

    template <typename... Args>
    bool rex_assert(bool cond, Args&&... args)
    {
      if(!cond)
      {
        const rsl::string& str = rsl::format(rsl::forward<Args>(args)...);
        internal::log_assert(str);
        DEBUG_BREAK();
        return true;
      }

      return false;
    }

  } // namespace v1
} // namespace rsl

#include "rex_std/format.h"