// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stacktrace.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    class stacktrace_entry
    {
    public:
      using native_handle_type = void*;

      constexpr stacktrace_entry();
      constexpr stacktrace_entry(const stacktrace_entry& other);

      constexpr stacktrace_entry& operator=(const stacktrace_entry& other);

      constexpr native_handle_type native_handle() const;
      constexpr operator bool() const;



    private:
    };

    template <typename Allocator>
    class basic_stacktrace
    {

    };
  }
}

#ifdef REX_ENABLE_WITH_CPP23

  #include "rex_std/disable_std_checking.h"
  #include "rex_std/std_alias_defines.h"

  #include <stacktrace>

namespace rsl
{
  inline namespace v1
  {

    REX_STD_CLASS_ALIAS(stacktrace_entry);

    REX_STD_TEMPLATED_CLASS_ALIAS(template <typename Allocator>, basic_stacktrace, Allocator);

    REX_STD_CLASS_ALIAS(stacktrace);
    namespace pmr
    {
      using stacktrace = std::pmr::stacktrace;
    }

    REX_STD_TEMPLATED_CLASS_ALIAS(template <typename T>, hash, T);

    REX_STD_FUNC_ALIAS(to_string);
    REX_STD_FUNC_ALIAS(operator<<);

  } // namespace v1
} // namespace rsl

  #include "rex_std/enable_std_checking.h"

#endif
