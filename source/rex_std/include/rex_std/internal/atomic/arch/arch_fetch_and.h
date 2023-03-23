

#ifndef REX_ATOMIC_INTERNAL_ARCH_FETCH_AND_H
#define REX_ATOMIC_INTERNAL_ARCH_FETCH_AND_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_ARCH_ATOMIC_FETCH_AND_*_N(type, type ret, type * ptr, type val)
//
#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELAXED_8)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_8_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_8_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_8)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_8_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_8_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELEASE_8)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_8_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_8_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_8)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_8_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_8_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_8)
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_8_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_8_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELAXED_16)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_16_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_16_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_16)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_16_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_16_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELEASE_16)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_16_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_16_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_16)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_16_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_16_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_16)
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_16_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_16_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELAXED_32)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_32_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_32_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_32)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_32_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_32_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELEASE_32)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_32_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_32_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_32)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_32_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_32_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_32)
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_32_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_32_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELAXED_64)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_64_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_64_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_64)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_64_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_64_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELEASE_64)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_64_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_64_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_64)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_64_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_64_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_64)
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_64_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_64_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELAXED_128)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_128_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELAXED_128_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_128)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_128_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQUIRE_128_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_RELEASE_128)
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_128_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_RELEASE_128_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_128)
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_128_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_ACQ_REL_128_AVAILABLE 0
#endif

#if defined(REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_128)
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_128_AVAILABLE 1
#else
  #define REX_ARCH_ATOMIC_FETCH_AND_SEQ_CST_128_AVAILABLE 0
#endif

#endif /* REX_ATOMIC_INTERNAL_ARCH_FETCH_AND_H */
