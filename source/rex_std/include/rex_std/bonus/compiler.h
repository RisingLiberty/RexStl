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
  #define REX_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
  #define REX_COMPILER_NAME "Clang"
#elif defined(REX_COMPILER_MSVC)
  #define REX_COMPILER_VERSION _MSC_VER
  #define REX_COMPILER_NAME "MSVC"
#elif defined(REX_COMPILER_GCC)
  #define REX_COMPILER_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
  #define REX_COMPILER_NAME "GCC"
#else
  #define REX_COMPILER_VERSION = 0
  #define REX_COMPILER_NAME "Unknown Compiler"
#endif

      constexpr compiler get_compiler()
      {
#if defined(REX_COMPILER_CLANG)
      return compiler::clang;
#elif defined(REX_COMPILER_MSVC)
      return compiler::msvc;
#elif defined(REX_COMPILER_GCC)
      return compiler::gcc;
#else
  #error unknown compiler used
#endif
      }
    } // namespace internal
  }   // namespace v1
} // namespace rsl