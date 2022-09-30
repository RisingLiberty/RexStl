// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: cstdint.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

using int8   = signed char;
using int16  = short;
using int32  = int;
using int64  = long long;
using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

using int_least8   = signed char;
using int_least16  = short;
using int_least32  = int;
using int_least64  = long long;
using uint_least8  = unsigned char;
using uint_least16 = unsigned short;
using uint_least32 = unsigned int;
using uint_least64 = unsigned long long;

using int_fast8   = signed char;
using int_fast16  = int;
using int_fast32  = int;
using int_fast64  = long long;
using uint_fast8  = unsigned char;
using uint_fast16 = unsigned int;
using uint_fast32 = unsigned int;
using uint_fast64 = unsigned long long;

using intmax  = long long;
using uintmax = unsigned long long;

// NOLINTBEGIN(clang-diagnostic-macro-redefined)

#define REX_INT8_MIN   (-127i8 - 1)
#define REX_INT16_MIN  (-32767i16 - 1)
#define REX_INT32_MIN  (-2147483647i32 - 1)
#define REX_INT64_MIN  (-9223372036854775807i64 - 1)
#define REX_INT8_MAX   127i8
#define REX_INT16_MAX  32767i16
#define REX_INT32_MAX  2147483647i32
#define REX_INT64_MAX  9223372036854775807i64
#define REX_UINT8_MAX  0xffui8
#define REX_UINT16_MAX 0xffffui16
#define REX_UINT32_MAX 0xffffffffui32
#define REX_UINT64_MAX 0xffffffffffffffffui64

#define REX_INT_LEAST8_MIN   REX_INT8_MIN
#define REX_INT_LEAST16_MIN  REX_INT16_MIN
#define REX_INT_LEAST32_MIN  REX_INT32_MIN
#define REX_INT_LEAST64_MIN  REX_INT64_MIN
#define REX_INT_LEAST8_MAX   REX_INT8_MAX
#define REX_INT_LEAST16_MAX  REX_INT16_MAX
#define REX_INT_LEAST32_MAX  REX_INT32_MAX
#define REX_INT_LEAST64_MAX  REX_INT64_MAX
#define REX_UINT_LEAST8_MAX  REX_UINT8_MAX
#define REX_UINT_LEAST16_MAX REX_UINT16_MAX
#define REX_UINT_LEAST32_MAX REX_UINT32_MAX
#define REX_UINT_LEAST64_MAX REX_UINT64_MAX

#define REX_INT_FAST8_MIN   REX_INT8_MIN
#define REX_INT_FAST16_MIN  REX_INT32_MIN
#define REX_INT_FAST32_MIN  REX_INT32_MIN
#define REX_INT_FAST64_MIN  REX_INT64_MIN
#define REX_INT_FAST8_MAX   REX_INT8_MAX
#define REX_INT_FAST16_MAX  REX_INT32_MAX
#define REX_INT_FAST32_MAX  REX_INT32_MAX
#define REX_INT_FAST64_MAX  REX_INT64_MAX
#define REX_UINT_FAST8_MAX  REX_UINT8_MAX
#define REX_UINT_FAST16_MAX REX_UINT32_MAX
#define REX_UINT_FAST32_MAX REX_UINT32_MAX
#define REX_UINT_FAST64_MAX REX_UINT64_MAX

#ifdef REX_PLATFORM_X86
  #define REX_INTPTR_MIN  REX_INT32_MIN
  #define REX_INTPTR_MAX  REX_INT32_MAX
  #define REX_UINTPTR_MAX REX_UINT32_MAX
#else
  #define REX_INTPTR_MIN  REX_INT64_MIN
  #define REX_INTPTR_MAX  REX_INT64_MAX
  #define REX_UINTPTR_MAX REX_UINT64_MAX
#endif

#define REX_INTMAX_MIN  REX_INT64_MIN
#define REX_INTMAX_MAX  REX_INT64_MAX
#define REX_UINTMAX_MAX REX_UINT64_MAX

#define REX_PTRDIFF_MIN REX_INTPTR_MIN
#define REX_PTRDIFF_MAX REX_INTPTR_MAX

#ifndef REX_SIZE_MAX
  // SIZE_MAX definition must match exactly with climits.h for modules support.
  #ifdef REX_PLATFORM_X86
    #define REX_SIZE_MAX 0xffffffffui32
  #else
    #define REX_SIZE_MAX 0xffffffffffffffffui64
  #endif
#endif

#define REX_SIG_ATOMIC_MIN REX_INT32_MIN
#define REX_SIG_ATOMIC_MAX REX_INT32_MAX

#define REX_WCHAR_MIN 0x0000
#define REX_WCHAR_MAX 0xffff

#define REX_WINT_MIN 0x0000
#define REX_WINT_MAX 0xffff

#define REX_INT8_C(x)  (x)
#define REX_INT16_C(x) (x)
#define REX_INT32_C(x) (x)
#define REX_INT64_C(x) (x##LL)

#define REX_UINT8_C(x)  (x)
#define REX_UINT16_C(x) (x)
#define REX_UINT32_C(x) (x##U)
#define REX_UINT64_C(x) (x##ULL)

#define REX_INTMAX_C(x)  REX_INT64_C(x)
#define REX_UINTMAX_C(x) REX_UINT64_C(x)

// NOLINTEND(clang-diagnostic-macro-redefined)

REX_RSL_END_NAMESPACE
