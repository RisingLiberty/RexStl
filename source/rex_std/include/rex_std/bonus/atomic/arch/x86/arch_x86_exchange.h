

#ifndef REX_ATOMIC_INTERNAL_ARCH_X86_EXCHANGE_H
#define REX_ATOMIC_INTERNAL_ARCH_X86_EXCHANGE_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_EXCHANGE_*_N(type, type ret, type * ptr, type val)
//
#if defined(REX_COMPILER_MSVC) && defined(REX_PLATFORM_X86)

  #define REX_ARCH_ATOMIC_X86_EXCHANGE_PRE_COMPUTE_DESIRED(ret, observed, val) ret = (val)

  #define REX_ARCH_ATOMIC_EXCHANGE_RELAXED_64(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, RELAXED, REX_ARCH_ATOMIC_X86_EXCHANGE_PRE_COMPUTE_DESIRED, REX_ARCH_ATOMIC_X86_NOP_POST_COMPUTE_RET)

  #define REX_ARCH_ATOMIC_EXCHANGE_ACQUIRE_64(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, ACQUIRE, REX_ARCH_ATOMIC_X86_EXCHANGE_PRE_COMPUTE_DESIRED, REX_ARCH_ATOMIC_X86_NOP_POST_COMPUTE_RET)

  #define REX_ARCH_ATOMIC_EXCHANGE_RELEASE_64(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, RELEASE, REX_ARCH_ATOMIC_X86_EXCHANGE_PRE_COMPUTE_DESIRED, REX_ARCH_ATOMIC_X86_NOP_POST_COMPUTE_RET)

  #define REX_ARCH_ATOMIC_EXCHANGE_ACQ_REL_64(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, ACQ_REL, REX_ARCH_ATOMIC_X86_EXCHANGE_PRE_COMPUTE_DESIRED, REX_ARCH_ATOMIC_X86_NOP_POST_COMPUTE_RET)

  #define REX_ARCH_ATOMIC_EXCHANGE_SEQ_CST_64(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_OP_64_IMPL(type, ret, ptr, val, SEQ_CST, REX_ARCH_ATOMIC_X86_EXCHANGE_PRE_COMPUTE_DESIRED, REX_ARCH_ATOMIC_X86_NOP_POST_COMPUTE_RET)

#endif

#if((defined(REX_COMPILER_CLANG) || defined(REX_COMPILER_GCC)) && defined(REX_PLATFORM_X64))

  #define REX_ARCH_ATOMIC_X86_EXCHANGE_128(type, ret, ptr, val, MemoryOrder)                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                    \
      bool cmpxchgRet;                                                                                                                                                                                                                                   \
      /* This is intentionally a non-atomic 128-bit load which may observe shearing. */                                                                                                                                                                  \
      /* Either we do not observe *(ptr) but then the cmpxchg will fail and the observed */                                                                                                                                                              \
      /* atomic load will be returned. Or the non-atomic load got lucky and the cmpxchg succeeds */                                                                                                                                                      \
      /* because the observed value equals the value in *(ptr) thus we optimistically do a non-atomic load. */                                                                                                                                           \
      ret = *(ptr);                                                                                                                                                                                                                                      \
      do                                                                                                                                                                                                                                                 \
      {                                                                                                                                                                                                                                                  \
        MERGE(MERGE(REX_ATOMIC_CMPXCHG_STRONG_, MemoryOrder), _128)(type, cmpxchgRet, ptr, &(ret), val);                                                                                                                                                 \
      } while(!cmpxchgRet);                                                                                                                                                                                                                              \
    }

  #define REX_ARCH_ATOMIC_EXCHANGE_RELAXED_128(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_EXCHANGE_128(type, ret, ptr, val, RELAXED)

  #define REX_ARCH_ATOMIC_EXCHANGE_ACQUIRE_128(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_EXCHANGE_128(type, ret, ptr, val, ACQUIRE)

  #define REX_ARCH_ATOMIC_EXCHANGE_RELEASE_128(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_EXCHANGE_128(type, ret, ptr, val, RELEASE)

  #define REX_ARCH_ATOMIC_EXCHANGE_ACQ_REL_128(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_EXCHANGE_128(type, ret, ptr, val, ACQ_REL)

  #define REX_ARCH_ATOMIC_EXCHANGE_SEQ_CST_128(type, ret, ptr, val) REX_ARCH_ATOMIC_X86_EXCHANGE_128(type, ret, ptr, val, SEQ_CST)

#endif

#endif /* REX_ATOMIC_INTERNAL_ARCH_X86_EXCHANGE_H */
