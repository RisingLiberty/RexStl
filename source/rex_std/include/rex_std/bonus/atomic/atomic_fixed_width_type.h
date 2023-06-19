// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_fixed_width_type.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/limits/numeric_limits.h"

namespace rsl
{
  inline namespace v1
  {
    template <size_t Bytes>
    struct atomic_fixed_width_type
    {
    };

    template <>
    struct atomic_fixed_width_type<8>
    {
#ifdef REX_COMPILER_MSVC
      using type = char;
#elif REX_COMPILER_CLANG
      using type = rsl::uint8;
#endif
    };
    template <>
    struct atomic_fixed_width_type<16>
    {
#ifdef REX_COMPILER_MSVC
      using type = short;
#else
      using type = rsl::uint16;
#endif
    };
    template <>
    struct atomic_fixed_width_type<32>
    {
#ifdef REX_COMPILER_MSVC
      using type = long;
#elif REX_COMPILER_CLANG
      using type = rsl::uint32;
#endif
    };
    template <>
    struct atomic_fixed_width_type<64>
    {
#ifdef REX_COMPILER_MSVC
      using type = long long;
#elif REX_COMPILER_CLANG
      using type = rsl::uint64;
#endif
    };

    template <size_t Bits>
    using atomic_fixed_width_type_t = typename atomic_fixed_width_type<Bits>::type;

    template <typename T>
    using atomic_t = typename atomic_fixed_width_type<sizeof(T) * rsl::limits_byte::num_bits_per_byte>::type;
  } // namespace v1
} // namespace rsl
