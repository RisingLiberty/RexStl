

#ifndef REX_ATOMIC_INTERNAL_COMPILER_LOAD_H
#define REX_ATOMIC_INTERNAL_COMPILER_LOAD_H

#pragma once

/////////////////////////////////////////////////////////////////////////////////
//
// void REX_COMPILER_ATOMIC_LOAD_*_N(type, type ret, type * ptr)
//
#if defined(REX_COMPILER_ATOMIC_LOAD_RELAXED_8)
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_8_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_8_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_ACQUIRE_8)
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_8_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_8_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_SEQ_CST_8)
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_8_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_8_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_RELAXED_16)
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_16_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_16_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_ACQUIRE_16)
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_16_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_16_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_SEQ_CST_16)
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_16_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_16_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_RELAXED_32)
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_32_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_32_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_ACQUIRE_32)
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_32_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_32_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_SEQ_CST_32)
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_32_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_32_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_RELAXED_64)
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_64_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_64_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_ACQUIRE_64)
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_64_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_64_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_SEQ_CST_64)
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_64_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_64_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_RELAXED_128)
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_128_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_RELAXED_128_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_ACQUIRE_128)
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_128_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_ACQUIRE_128_AVAILABLE 0
#endif

#if defined(REX_COMPILER_ATOMIC_LOAD_SEQ_CST_128)
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_128_AVAILABLE 1
#else
  #define REX_COMPILER_ATOMIC_LOAD_SEQ_CST_128_AVAILABLE 0
#endif

/**
 * NOTE:
 *
 * These are used for data-dependent reads thru a pointer. It is safe
 * to assume that pointer-sized reads are atomic on any given platform.
 * This implementation assumes the hardware doesn't reorder dependent
 * loads unlike the DEC Alpha.
 */
#define REX_COMPILER_ATOMIC_LOAD_READ_DEPENDS_N(type, ret, ptr)                                                                                                                                                                                          \
  {                                                                                                                                                                                                                                                      \
    static_assert(rsl::is_pointer_v<type>, "rsl::atomic<T> : Read Depends Type must be a Pointer Type!");                                                                                                                                                \
    static_assert(rsl::is_pointer_v<rsl::remove_pointer_t<decltype(ptr)>>, "rsl::atomic<T> : Read Depends Ptr must be a Pointer to a Pointer!");                                                                                                         \
                                                                                                                                                                                                                                                         \
    ret = (*REX_ATOMIC_VOLATILE_CAST(ptr));                                                                                                                                                                                                              \
  }

#define REX_COMPILER_ATOMIC_LOAD_READ_DEPENDS_32(type, ret, ptr) REX_COMPILER_ATOMIC_LOAD_READ_DEPENDS_N(type, ret, ptr)

#define REX_COMPILER_ATOMIC_LOAD_READ_DEPENDS_64(type, ret, ptr) REX_COMPILER_ATOMIC_LOAD_READ_DEPENDS_N(type, ret, ptr)

#define REX_COMPILER_ATOMIC_LOAD_READ_DEPENDS_32_AVAILABLE 1
#define REX_COMPILER_ATOMIC_LOAD_READ_DEPENDS_64_AVAILABLE 1

#endif /* REX_ATOMIC_INTERNAL_COMPILER_LOAD_H */