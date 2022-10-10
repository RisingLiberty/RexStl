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

namespace rsl
{
  inline namespace v1
  {

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

  } // namespace v1
} // namespace rsl
