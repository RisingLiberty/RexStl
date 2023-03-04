// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: compiler.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      enum class compiler
      {
        clang,
        msvc,
        gcc
      };

#if defined(REX_COMPILER_CLANG)
      constexpr compiler g_compiler = compiler::clang;
#elif defined(REX_COMPILER_MSVC)
      constexpr compiler g_compiler = compiler::msvc;
#elif defined(REX_COMPILER_GCC)
      constexpr compiler g_compiler = compiler::gcc;
#else
  #error unknown compiler used
#endif
    } // namespace internal
  }   // namespace v1
} // namespace rsl