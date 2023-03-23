

#ifndef REX_ATOMIC_INTERNAL_ARCH_X86_CMPXCHG_STRONG_H
#define REX_ATOMIC_INTERNAL_ARCH_X86_CMPXCHG_STRONG_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_CMPXCHG_STRONG_*_*_N(type, bool ret, type * ptr, type * expected, type desired)
//
#if((defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)) && defined(REX_PLATFORM_X64))

  #define REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)                                                                                                                                                                 \
    {                                                                                                                                                                                                                                                    \
      /* Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX into m128. Else, clear ZF and load m128 into RDX:RAX. */                                                                                                                           \
      __asm__ __volatile__("lock; cmpxchg16b %2\n"                                                                                                                                                                  /* cmpxchg16b sets/clears ZF */      \
                           "sete %3" /* If ZF == 1, set the return value to 1 */                                                                                                                                    /* Output  Operands */               \
                           : "=a"((REX_ATOMIC_TYPE_CAST(uint64, (expected)))[0]), "=d"((REX_ATOMIC_TYPE_CAST(uint64, (expected)))[1]), "+m"(*(REX_ATOMIC_VOLATILE_INTEGRAL_CAST(__uint128_t, (ptr)))), "=rm"((ret)) /* Input Operands */                 \
                           : "b"((REX_ATOMIC_TYPE_CAST(uint64, &(desired)))[0]), "c"((REX_ATOMIC_TYPE_CAST(uint64, &(desired)))[1]), "a"((REX_ATOMIC_TYPE_CAST(uint64, (expected)))[0]),                                                                 \
                             "d"((REX_ATOMIC_TYPE_CAST(uint64, (expected)))[1]) /* Clobbers */                                                                                                                                                           \
                           : "memory", "cc");                                                                                                                                                                                                            \
    }

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

  #define REX_ARCH_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_128(type, ret, ptr, expected, desired) REX_ARCH_ATOMIC_X86_CMPXCHG_STRONG_128_IMPL(type, ret, ptr, expected, desired)

#endif

#endif /* REX_ATOMIC_INTERNAL_ARCH_X86_CMPXCHG_STRONG_H */
