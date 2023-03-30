

#pragma once

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
#if defined(REX_PLATFORM_ARM64)
  #if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)
      void arm_memory_barrier();
      void arm_read_memory_barrier();
      void arm_write_memory_barrier();
  #endif
#endif
    } // namespace internal
  }   // namespace v1
} // namespace rsl

#if defined(REX_COMPILER_MSVC) && !defined(REX_COMPILER_CLANG_CL)

  #if defined(REX_PLATFORM_ARM64)

    #define REX_ARM_DMB_ISH _ARM64_BARRIER_ISH

    #define REX_ARM_DMB_ISHST _ARM64_BARRIER_ISHST

    #define REX_ARM_DMB_ISHLD _ARM64_BARRIER_ISHLD

  #endif

#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)

  #define REX_ARM_DMB_ISH ish

  #define REX_ARM_DMB_ISHST ishst

  #if defined(REX_PLATFORM_ARM64)

    #define REX_ARM_DMB_ISHLD ishld

  #endif

  #define REX_ARCH_ATOMIC_ARM_EMIT_DMB(option) __asm__ __volatile__("dmb " STRINGIZE(option) ::: "memory")

#endif

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_MB()
//
#define REX_ARCH_ATOMIC_CPU_MB() rsl::internal::arm_memory_barrier() REX_ARCH_ATOMIC_ARM_EMIT_DMB(REX_ARM_DMB_ISH)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_WMB()
//
#define REX_ARCH_ATOMIC_CPU_WMB() rsl::internal::arm_write_memory_barrier() REX_ARCH_ATOMIC_ARM_EMIT_DMB(REX_ARM_DMB_ISHST)

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CPU_RMB()
//
#define REX_ARCH_ATOMIC_CPU_RMB() rsl::internal::arm_read_memory_barrier() REX_ARCH_ATOMIC_ARM_EMIT_DMB(REX_ARM_DMB_ISHLD)
