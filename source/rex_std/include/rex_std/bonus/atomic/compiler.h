#pragma once

#include "rex_std/bonus/defines.h"

/////////////////////////////////////////////////////////////////////////////////

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {

      /**
       * NOTE:
       *
       * This can be used by specific compiler implementations to implement a data dependency compiler barrier.
       * Some compiler barriers do not take in input dependencies as is possible with the gcc asm syntax.
       * Thus we need a way to create a false dependency on the input variable so the compiler does not dead-store
       * remove it.
       * A volatile function pointer ensures the compiler must always load the function pointer and call thru it
       * since the compiler cannot reason about any side effects. Thus the compiler must always assume the
       * input variable may be accessed and thus cannot be dead-stored. This technique works even in the presence
       * of Link-Time Optimization. A compiler barrier with a data dependency is useful in these situations.
       *
       * void foo()
       * {
       *    rsl::vector<int> v;
       *    while (Benchmark.ContinueRunning())
       *    {
       *      v.push_back(0);
       *      rsl::compiler_barrier(); OR rsl::compiler_barrier_data_dependency(v);
       *    }
       * }
       *
       * We are trying to benchmark the push_back function of a vector. The vector v has only local scope.
       * The compiler is well within its writes to remove all accesses to v even with the compiler barrier
       * because there are no observable uses of the vector v.
       * The compiler barrier data dependency ensures there is an input dependency on the variable so that
       * it isn't removed. This is also useful when writing test code that the compiler may remove.
       */

      using CompilerBarrierDataDependencyFuncPtr = void (*)(void*);

      extern volatile CompilerBarrierDataDependencyFuncPtr g_compiler_barrier_data_dependency_func; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

#define REX_COMPILER_ATOMIC_COMPILER_BARRIER_DATA_DEPENDENCY_FUNC(ptr) rsl::internal::g_compiler_barrier_data_dependency_func(ptr)

    } // namespace internal

  } // namespace v1

} // namespace rsl

/////////////////////////////////////////////////////////////////////////////////
