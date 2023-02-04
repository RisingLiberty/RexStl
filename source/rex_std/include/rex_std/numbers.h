// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: numbers.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/bonus/utility/always_false.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <typename T>
      struct invalid
      {
        static_assert(internal::always_false<T>, "A program that instantiates a primary template of a mathematical constant variable template is ill-formed");
      };
    } // namespace internal

    template <typename T>
    inline constexpr T e_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T log2e_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T log10e_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T pi_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T log2pi_v = internal::invalid<T> {}; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <typename T>
    inline constexpr T log_sqrt_2pi_v = internal::invalid<T> {}; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <typename T>
    inline constexpr T half_pi_v = internal::invalid<T> {}; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <typename T>
    inline constexpr T sqrt_pi_v = internal::invalid<T> {}; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <typename T>
    inline constexpr T sqrt_half_pi_v = internal::invalid<T> {}; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <typename T>
    inline constexpr T inv_pi_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T inv_sqrtpi_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T ln2_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T ln10_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T sqrt2_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T sqrt3_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T inv_sqrt3_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T egamma_v = internal::invalid<T> {};
    template <typename T>
    inline constexpr T phi_v = internal::invalid<T> {};

    template <>
    inline constexpr float64 e_v<float64> = 2.718281828459045;
    template <>
    inline constexpr float64 log2e_v<float64> = 1.4426950408889634;
    template <>
    inline constexpr float64 log10e_v<float64> = 0.4342944819032518;
    template <>
    inline constexpr float64 pi_v<float64> = 3.141592653589793;
    template <>
    inline constexpr float64 log2pi_v<float64> = 1.8378770664093454; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float64 log_sqrt_2pi_v<float64> = 0.9189385332046727; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float64 half_pi_v<float64> = 1.5707963267948966; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float64 sqrt_pi_v<float64> = 1.7724538509055160; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float64 sqrt_half_pi_v<float64> = 1.2533141373155002; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float64 inv_pi_v<float64> = 0.3183098861837907;
    template <>
    inline constexpr float64 inv_sqrtpi_v<float64> = 0.5641895835477563;
    template <>
    inline constexpr float64 ln2_v<float64> = 0.6931471805599453;
    template <>
    inline constexpr float64 ln10_v<float64> = 2.302585092994046;
    template <>
    inline constexpr float64 sqrt2_v<float64> = 1.4142135623730951;
    template <>
    inline constexpr float64 sqrt3_v<float64> = 1.7320508075688772;
    template <>
    inline constexpr float64 inv_sqrt3_v<float64> = 0.5773502691896257;
    template <>
    inline constexpr float64 egamma_v<float64> = 0.5772156649015329;
    template <>
    inline constexpr float64 phi_v<float64> = 1.618033988749895;

    template <>
    inline constexpr float32 e_v<float32> = static_cast<float32>(e_v<float64>);
    template <>
    inline constexpr float32 log2e_v<float32> = static_cast<float32>(log2e_v<float64>);
    template <>
    inline constexpr float32 log10e_v<float32> = static_cast<float32>(log10e_v<float64>);
    template <>
    inline constexpr float32 pi_v<float32> = static_cast<float32>(pi_v<float64>);
    template <>
    inline constexpr float32 log2pi_v<float32> = static_cast<float32>(log2pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float32 log_sqrt_2pi_v<float32> = static_cast<float32>(log_sqrt_2pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float32 half_pi_v<float32> = static_cast<float32>(half_pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float32 sqrt_pi_v<float32> = static_cast<float32>(sqrt_pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float32 sqrt_half_pi_v<float32> = static_cast<float32>(sqrt_half_pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr float32 inv_pi_v<float32> = static_cast<float32>(inv_pi_v<float64>);
    template <>
    inline constexpr float32 inv_sqrtpi_v<float32> = static_cast<float32>(inv_sqrtpi_v<float64>);
    template <>
    inline constexpr float32 ln2_v<float32> = static_cast<float32>(ln2_v<float64>);
    template <>
    inline constexpr float32 ln10_v<float32> = static_cast<float32>(ln10_v<float64>);
    template <>
    inline constexpr float32 sqrt2_v<float32> = static_cast<float32>(sqrt2_v<float64>);
    template <>
    inline constexpr float32 sqrt3_v<float32> = static_cast<float32>(sqrt3_v<float64>);
    template <>
    inline constexpr float32 inv_sqrt3_v<float32> = static_cast<float32>(inv_sqrt3_v<float64>);
    template <>
    inline constexpr float32 egamma_v<float32> = static_cast<float32>(egamma_v<float64>);
    template <>
    inline constexpr float32 phi_v<float32> = static_cast<float32>(phi_v<float64>);

    template <>
    inline constexpr lfloat64 e_v<lfloat64> = e_v<float64>;
    template <>
    inline constexpr lfloat64 log2e_v<lfloat64> = log2e_v<float64>;
    template <>
    inline constexpr lfloat64 log10e_v<lfloat64> = log10e_v<float64>;
    template <>
    inline constexpr lfloat64 pi_v<lfloat64> = pi_v<float64>;
    template <>
    inline constexpr lfloat64 log2pi_v<lfloat64> = static_cast<lfloat64>(log2pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr lfloat64 log_sqrt_2pi_v<lfloat64> = static_cast<lfloat64>(log_sqrt_2pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr lfloat64 half_pi_v<lfloat64> = static_cast<lfloat64>(half_pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr lfloat64 sqrt_pi_v<lfloat64> = static_cast<lfloat64>(sqrt_pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr lfloat64 sqrt_half_pi_v<lfloat64> = static_cast<lfloat64>(sqrt_half_pi_v<float64>); /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    template <>
    inline constexpr lfloat64 inv_pi_v<lfloat64> = inv_pi_v<float64>;
    template <>
    inline constexpr lfloat64 inv_sqrtpi_v<lfloat64> = inv_sqrtpi_v<float64>;
    template <>
    inline constexpr lfloat64 ln2_v<lfloat64> = ln2_v<float64>;
    template <>
    inline constexpr lfloat64 ln10_v<lfloat64> = ln10_v<float64>;
    template <>
    inline constexpr lfloat64 sqrt2_v<lfloat64> = sqrt2_v<float64>;
    template <>
    inline constexpr lfloat64 sqrt3_v<lfloat64> = sqrt3_v<float64>;
    template <>
    inline constexpr lfloat64 inv_sqrt3_v<lfloat64> = inv_sqrt3_v<float64>;
    template <>
    inline constexpr lfloat64 egamma_v<lfloat64> = egamma_v<float64>;
    template <>
    inline constexpr lfloat64 phi_v<lfloat64> = phi_v<float64>;

    inline constexpr float32 e            = e_v<float32>;
    inline constexpr float32 log2_e       = log2e_v<float32>;
    inline constexpr float32 log10_e      = log10e_v<float32>;
    inline constexpr float32 pi           = pi_v<float32>;
    inline constexpr float32 log2_pi      = log2pi_v<float32>;       /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    inline constexpr float32 log_sqrt2_pi = log_sqrt_2pi_v<float32>; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    inline constexpr float32 half_pi      = half_pi_v<float32>;      /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    inline constexpr float32 sqrt_pi      = sqrt_pi_v<float32>;      /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    inline constexpr float32 sqrt_half_pi = sqrt_half_pi_v<float32>; /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Aug/2022)
    inline constexpr float32 inv_pi       = inv_pi_v<float32>;
    inline constexpr float32 inv_sqrt_pi  = inv_sqrtpi_v<float32>;
    inline constexpr float32 ln2          = ln2_v<float32>;
    inline constexpr float32 ln10         = ln10_v<float32>;
    inline constexpr float32 sqrt2        = sqrt2_v<float32>;
    inline constexpr float32 sqrt3        = sqrt3_v<float32>;
    inline constexpr float32 inv_sqrt3    = inv_sqrt3_v<float32>;
    inline constexpr float32 e_gamma      = egamma_v<float32>;
    inline constexpr float32 phi          = phi_v<float32>;

  } // namespace v1
} // namespace rsl
