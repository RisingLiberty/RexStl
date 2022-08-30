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

#include "rex_std/internal/config.h"

namespace rsl
{
    using int8 = signed char;
    using int16 = short;
    using int32 = int;
    using int64 = long long;
    using uint8 = unsigned char;
    using uint16 = unsigned short;
    using uint32 = unsigned int;
    using uint64 = unsigned long long;

    using int_least8 = signed char;
    using int_least16 = short;
    using int_least32 = int;
    using int_least64 = long long;
    using uint_least8 = unsigned char;
    using uint_least16 = unsigned short;
    using uint_least32 = unsigned int;
    using uint_least64 = unsigned long long;

    using int_fast8 = signed char;
    using int_fast16 = int;
    using int_fast32 = int;
    using int_fast64 = long long;
    using uint_fast8 = unsigned char;
    using uint_fast16 = unsigned int;
    using uint_fast32 = unsigned int;
    using uint_fast64 = unsigned long long;

    using intmax = long long;
    using uintmax = unsigned long long;

#define INT8_MIN (-127i8 - 1)
#define INT16_MIN (-32767i16 - 1)
#define INT32_MIN (-2147483647i32 - 1)
#define INT64_MIN (-9223372036854775807i64 - 1)
#define INT8_MAX 127i8
#define INT16_MAX 32767i16
#define INT32_MAX 2147483647i32
#define INT64_MAX 9223372036854775807i64
#define UINT8_MAX 0xffui8
#define UINT16_MAX 0xffffui16
#define UINT32_MAX 0xffffffffui32
#define UINT64_MAX 0xffffffffffffffffui64

#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST64_MIN INT64_MIN
#define INT_LEAST8_MAX INT8_MAX
#define INT_LEAST16_MAX INT16_MAX
#define INT_LEAST32_MAX INT32_MAX
#define INT_LEAST64_MAX INT64_MAX
#define UINT_LEAST8_MAX UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

#define INT_FAST8_MIN INT8_MIN
#define INT_FAST16_MIN INT32_MIN
#define INT_FAST32_MIN INT32_MIN
#define INT_FAST64_MIN INT64_MIN
#define INT_FAST8_MAX INT8_MAX
#define INT_FAST16_MAX INT32_MAX
#define INT_FAST32_MAX INT32_MAX
#define INT_FAST64_MAX INT64_MAX
#define UINT_FAST8_MAX UINT8_MAX
#define UINT_FAST16_MAX UINT32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

#ifdef REX_PLATFORM_X86
    #define INTPTR_MIN INT32_MIN
    #define INTPTR_MAX INT32_MAX
    #define UINTPTR_MAX UINT32_MAX
#else
    #define INTPTR_MIN INT64_MIN
    #define INTPTR_MAX INT64_MAX
    #define UINTPTR_MAX UINT64_MAX
#endif

#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define PTRDIFF_MIN INTPTR_MIN
#define PTRDIFF_MAX INTPTR_MAX

#ifndef SIZE_MAX
    // SIZE_MAX definition must match exactly with climits.h for modules support.
    #ifdef REX_PLATFORM_X86
        #define SIZE_MAX 0xffffffffui32
    #else
        #define SIZE_MAX 0xffffffffffffffffui64
    #endif
#endif

#define SIG_ATOMIC_MIN INT32_MIN
#define SIG_ATOMIC_MAX INT32_MAX

#define WCHAR_MIN 0x0000
#define WCHAR_MAX 0xffff

#define WINT_MIN 0x0000
#define WINT_MAX 0xffff

#define INT8_C(x) (x)
#define INT16_C(x) (x)
#define INT32_C(x) (x)
#define INT64_C(x) (x##LL)

#define UINT8_C(x) (x)
#define UINT16_C(x) (x)
#define UINT32_C(x) (x##U)
#define UINT64_C(x) (x##ULL)

#define INTMAX_C(x) INT64_C(x)
#define UINTMAX_C(x) UINT64_C(x)
}