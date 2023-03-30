// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/compiler/compiler.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {

      static void EastlCompilerBarrierDataDependencyFunc(void*) {}

      volatile CompilerBarrierDataDependencyFuncPtr gCompilerBarrierDataDependencyFunc = &EastlCompilerBarrierDataDependencyFunc;
    } // namespace internal
  }   // namespace v1
} // namespace rsl