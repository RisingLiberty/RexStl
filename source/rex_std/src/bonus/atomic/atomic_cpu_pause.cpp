// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_cpu_pause.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include <Windows.h>

namespace rsl
{
  inline namespace v1
  {
    void cpu_pause()
    {
#if defined(REX_COMPILER_MSVC)
      YieldProcessor();
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
  #if defined(REX_PLATFORM_ARM64)
      __asm__ __volatile__("yield"); // NOLINT(hicpp-no-assembler)
  #elif defined(REX_PLATFORM_X64)
      __asm__ __volatile__("pause");// NOLINT(hicpp-no-assembler)
  #else
      static_assert(false, "cpu pause not implemented");
  #endif
#endif
    }
  } // namespace v1
} // namespace rsl