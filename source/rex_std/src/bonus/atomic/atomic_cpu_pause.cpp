// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_cpu_pause.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include <Windows.h> // IWYU pragma: keep

namespace rsl
{
  inline namespace v1
  {
    void cpu_pause()
    {
#if defined(RSL_COMPILER_MSVC)
      YieldProcessor();
#elif defined(RSL_COMPILER_GCC) || defined(RSL_COMPILER_CLANG)
  #if defined(RSL_PLATFORM_ARM64)
      __asm__ __volatile__("yield"); // NOLINT(hicpp-no-assembler)
  #elif defined(RSL_PLATFORM_X64)
      __asm__ __volatile__("pause"); // NOLINT(hicpp-no-assembler)
  #else
      static_assert(false, "cpu pause not implemented");
  #endif
#endif
    }
  } // namespace v1
} // namespace rsl