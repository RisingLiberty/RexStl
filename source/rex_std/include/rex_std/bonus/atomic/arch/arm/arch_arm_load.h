#pragma once

#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
#if defined(REX_COMPILER_MSVC) && defined(REX_PLATFORM_ARM64)
      atomic_fixed_width_type_t<8> arm_atomic_load(atomic_fixed_width_type_t<8>* ptr);
      atomic_fixed_width_type_t<16> arm_atomic_load(atomic_fixed_width_type_t<16>* ptr);
      atomic_fixed_width_type_t<32> arm_atomic_load(atomic_fixed_width_type_t<32>* ptr);
      atomic_fixed_width_type_t<64> arm_atomic_load(atomic_fixed_width_type_t<64>* ptr);
#endif
    } // namespace internal
  }   // namespace v1
} // namespace rsl

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_LOAD_*_N(type, type ret, type * ptr)
//
#if defined(REX_COMPILER_MSVC)

  /**
   * NOTE:
   *
   * The ARM documentation states the following:
   * A 64-bit pair requires the address to be quadword aligned and is single-copy atomic for each doubleword at doubleword granularity
   *
   * Thus we must ensure the store succeeds inorder for the load to be observed as atomic.
   * Thus we must use the full cmpxchg in order to do a proper atomic load.
   */
  #define REX_ARCH_ATOMIC_ARM_LOAD_128(type, ret, ptr, MemoryOrder)                                                                                                                                                                                      \
    {                                                                                                                                                                                                                                                    \
      bool cmpxchgRetBool;                                                                                                                                                                                                                               \
      ret = *(ptr);                                                                                                                                                                                                                                      \
      do                                                                                                                                                                                                                                                 \
      {                                                                                                                                                                                                                                                  \
        MERGE(MERGE(REX_ATOMIC_CMPXCHG_STRONG_, MemoryOrder), _128)(type, cmpxchgRetBool, ptr, &(ret), ret);                                                                                                                                             \
      } while(!cmpxchgRetBool);                                                                                                                                                                                                                          \
    }

  #define REX_ARCH_ATOMIC_LOAD_RELAXED_8(type, ret, ptr) rsl::internal::arm_atomic_load(ptr)

  #define REX_ARCH_ATOMIC_LOAD_RELAXED_16(type, ret, ptr) rsl::internal::arm_atomic_load(ptr)

  #define REX_ARCH_ATOMIC_LOAD_RELAXED_32(type, ret, ptr) rsl::internal::arm_atomic_load(ptr)

  #define REX_ARCH_ATOMIC_LOAD_RELAXED_64(type, ret, ptr) rsl::internal::arm_atomic_load(ptr)

  #define REX_ARCH_ATOMIC_LOAD_RELAXED_128(type, ret, ptr) REX_ARCH_ATOMIC_ARM_LOAD_128(type, ret, ptr, RELAXED)

  #define REX_ARCH_ATOMIC_LOAD_ACQUIRE_8(type, ret, ptr)                                                                                                                                                                                                 \
    rsl::internal::arm_atomic_load(ptr);                                                                                                                                                                                                                 \
    REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_LOAD_ACQUIRE_16(type, ret, ptr)                                                                                                                                                                                                \
    rsl::internal::arm_atomic_load(ptr);                                                                                                                                                                                                                 \
    REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_LOAD_ACQUIRE_32(type, ret, ptr)                                                                                                                                                                                                \
    rsl::internal::arm_atomic_load(ptr);                                                                                                                                                                                                                 \
    REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_LOAD_ACQUIRE_64(type, ret, ptr)                                                                                                                                                                                                \
    rsl::internal::arm_atomic_load(ptr);                                                                                                                                                                                                                 \
    REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_LOAD_ACQUIRE_128(type, ret, ptr) REX_ARCH_ATOMIC_ARM_LOAD_128(type, ret, ptr, ACQUIRE)

  #define REX_ARCH_ATOMIC_LOAD_SEQ_CST_8(type, ret, ptr)                                                                                                                                                                                                 \
    rsl::internal::arm_atomic_load(ptr);                                                                                                                                                                                                                 \
    REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_LOAD_SEQ_CST_16(type, ret, ptr)                                                                                                                                                                                                \
    rsl::internal::arm_atomic_load(ptr);                                                                                                                                                                                                                 \
    REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_LOAD_SEQ_CST_32(type, ret, ptr)                                                                                                                                                                                                \
    rsl::internal::arm_atomic_load(ptr);                                                                                                                                                                                                                 \
    REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_LOAD_SEQ_CST_64(type, ret, ptr)                                                                                                                                                                                                \
    rsl::internal::arm_atomic_load(ptr);                                                                                                                                                                                                                 \
    REX_ATOMIC_CPU_MB()

  #define REX_ARCH_ATOMIC_LOAD_SEQ_CST_128(type, ret, ptr) REX_ARCH_ATOMIC_ARM_LOAD_128(type, ret, ptr, SEQ_CST)

#endif
