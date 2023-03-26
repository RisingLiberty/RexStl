#pragma once

#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      void x86_atomic_store(atomic_fixed_width_type_t<8>* ptr, atomic_fixed_width_type_t<8> val);
      void x86_atomic_store(atomic_fixed_width_type_t<16>* ptr, atomic_fixed_width_type_t<16> val);
      void x86_atomic_store(atomic_fixed_width_type_t<32>* ptr, atomic_fixed_width_type_t<32> val);
      void x86_atomic_store(atomic_fixed_width_type_t<64>* ptr, atomic_fixed_width_type_t<64> val);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_STORE_*_N(type, type * ptr, type val)
//
#if defined(REX_COMPILER_MSVC)

  #define REX_ARCH_ATOMIC_X86_STORE_128(type, ptr, val, MemoryOrder)                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
      type exchange128;                                                                                                                                                                                                                                  \
      (void)(exchange128);                                                                                                                                                                                                                               \
      MERGE(MERGE(REX_ATOMIC_EXCHANGE_, MemoryOrder), _128)(type, exchange128, ptr, val);                                                                                                                                                                \
    }

  #define REX_ARCH_ATOMIC_STORE_RELAXED_8(type, ptr, val) rsl::internal::x86_atomic_store(ptr, val)

  #define REX_ARCH_ATOMIC_STORE_RELAXED_16(type, ptr, val) rsl::internal::x86_atomic_store(ptr, val)

  #define REX_ARCH_ATOMIC_STORE_RELAXED_32(type, ptr, val) rsl::internal::x86_atomic_store(ptr, val)

  #define REX_ARCH_ATOMIC_STORE_RELAXED_64(type, ptr, val) rsl::internal::x86_atomic_store(ptr, val)

  #define REX_ARCH_ATOMIC_STORE_RELAXED_128(type, ptr, val) REX_ARCH_ATOMIC_X86_STORE_128(type, ptr, val, RELAXED)

  #define REX_ARCH_ATOMIC_STORE_RELEASE_8(type, ptr, val)                                                                                                                                                                                                \
    REX_ATOMIC_COMPILER_BARRIER();                                                                                                                                                                                                                       \
    rsl::internal::x86_atomic_store(ptr, val)

  #define REX_ARCH_ATOMIC_STORE_RELEASE_16(type, ptr, val)                                                                                                                                                                                               \
    REX_ATOMIC_COMPILER_BARRIER();                                                                                                                                                                                                                       \
    rsl::internal::x86_atomic_store(ptr, val)

  #define REX_ARCH_ATOMIC_STORE_RELEASE_32(type, ptr, val)                                                                                                                                                                                               \
    REX_ATOMIC_COMPILER_BARRIER();                                                                                                                                                                                                                       \
    rsl::internal::x86_atomic_store(ptr, val)

  #define REX_ARCH_ATOMIC_STORE_RELEASE_64(type, ptr, val)                                                                                                                                                                                               \
    REX_ATOMIC_COMPILER_BARRIER();                                                                                                                                                                                                                       \
    rsl::internal::x86_atomic_store(ptr, val)

  #define REX_ARCH_ATOMIC_STORE_RELEASE_128(type, ptr, val) REX_ARCH_ATOMIC_X86_STORE_128(type, ptr, val, RELEASE)

  #define REX_ARCH_ATOMIC_STORE_SEQ_CST_8(type, ptr, val)                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                    \
      type exchange8;                                                                                                                                                                                                                                    \
      (void)(exchange8);                                                                                                                                                                                                                                 \
      REX_ATOMIC_EXCHANGE_SEQ_CST_8(type, exchange8, ptr, val);                                                                                                                                                                                          \
    }

  #define REX_ARCH_ATOMIC_STORE_SEQ_CST_16(type, ptr, val)                                                                                                                                                                                               \
    {                                                                                                                                                                                                                                                    \
      type exchange16;                                                                                                                                                                                                                                   \
      (void)(exchange16);                                                                                                                                                                                                                                \
      REX_ATOMIC_EXCHANGE_SEQ_CST_16(type, exchange16, ptr, val);                                                                                                                                                                                        \
    }

  #define REX_ARCH_ATOMIC_STORE_SEQ_CST_32(type, ptr, val)                                                                                                                                                                                               \
    {                                                                                                                                                                                                                                                    \
      type exchange32;                                                                                                                                                                                                                                   \
      (void)(exchange32);                                                                                                                                                                                                                                \
      REX_ATOMIC_EXCHANGE_SEQ_CST_32(type, exchange32, ptr, val);                                                                                                                                                                                        \
    }

  #if defined(REX_PLATFORM_X64)

    #define REX_ARCH_ATOMIC_STORE_SEQ_CST_64(type, ptr, val)                                                                                                                                                                                             \
      {                                                                                                                                                                                                                                                  \
        type exchange64;                                                                                                                                                                                                                                 \
        (void)(exchange64);                                                                                                                                                                                                                              \
        REX_ATOMIC_EXCHANGE_SEQ_CST_64(type, exchange64, ptr, val);                                                                                                                                                                                      \
      }

  #endif

  #define REX_ARCH_ATOMIC_STORE_SEQ_CST_128(type, ptr, val) REX_ARCH_ATOMIC_X86_STORE_128(type, ptr, val, SEQ_CST)

#endif

#if((defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)) && defined(REX_PLATFORM_X64))

  #define REX_ARCH_ATOMIC_X86_STORE_128(type, ptr, val, MemoryOrder)                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
      type exchange128;                                                                                                                                                                                                                                  \
      (void)(exchange128);                                                                                                                                                                                                                               \
      MERGE(MERGE(REX_ATOMIC_EXCHANGE_, MemoryOrder), _128)(type, exchange128, ptr, val);                                                                                                                                                                \
    }

  #define REX_ARCH_ATOMIC_STORE_RELAXED_128(type, ptr, val) REX_ARCH_ATOMIC_X86_STORE_128(type, ptr, val, RELAXED)

  #define REX_ARCH_ATOMIC_STORE_RELEASE_128(type, ptr, val) REX_ARCH_ATOMIC_X86_STORE_128(type, ptr, val, RELEASE)

  #define REX_ARCH_ATOMIC_STORE_SEQ_CST_128(type, ptr, val) REX_ARCH_ATOMIC_X86_STORE_128(type, ptr, val, SEQ_CST)

#endif
