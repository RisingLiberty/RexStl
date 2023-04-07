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

#include "rex_std/bonus/atomic/compiler.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {

      static void rex_compiler_barrier_data_dependency_func(void* /*unused*/) {}

      volatile CompilerBarrierDataDependencyFuncPtr g_compiler_barrier_data_dependency_func = &rex_compiler_barrier_data_dependency_func;
    } // namespace internal
  }   // namespace v1
} // namespace rsl