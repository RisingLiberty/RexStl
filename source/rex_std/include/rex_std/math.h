// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: math.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/math/abs.h"
#include "rex_std/internal/math/acos.h"
#include "rex_std/internal/math/asin.h"
#include "rex_std/internal/math/atan.h"
#include "rex_std/internal/math/ceil.h"
#include "rex_std/internal/math/clamp.h"
#include "rex_std/internal/math/cos.h"
#include "rex_std/internal/math/exp.h"
#include "rex_std/internal/math/factorial.h"
#include "rex_std/internal/math/floor.h"
#include "rex_std/internal/math/is_nan.h"
#include "rex_std/internal/math/pow.h"
#include "rex_std/internal/math/round.h"
#include "rex_std/internal/math/signbit.h"
#include "rex_std/internal/math/sin.h"
#include "rex_std/internal/math/sqrt.h"
#include "rex_std/internal/math/tan.h"
#include "rex_std/internal/type_traits/is_integral.h"

namespace rsl
{
  inline namespace v1
  {
    using float_t  = float32;
    using double_t = float64;

#define HUGE_ENUF 1e+300

#ifndef INFINITY
  #define INFINITY ((float32)(HUGE_ENUF * HUGE_ENUF))
#endif

#ifndef HUGE_VAL
  #define HUGE_VAL ((float64)INFINITY)
#endif
#ifndef HUGE_VALF
  #define HUGE_VALF ((float32)INFINITY)
#endif
#ifndef HUGE_VALL
  #define HUGE_VALL ((lfloat64)INFINITY)
#endif

#ifndef NAN
  #define NAN (-(float32)(INFINITY * 0.0f))
#endif

#define MATH_ERRNO       1
#define MATH_ERREXCEPT   2
#define MATH_ERRHANDLING (MATH_ERRNO | MATH_ERREXCEPT)

#ifndef FP_INFINITE
  #define FP_INFINITE 1
#endif
#ifndef FP_NAN
  #define FP_NAN 2
#endif
#ifndef FP_NORMAL
  #define FP_NORMAL (-1)
#endif
#ifndef FP_SUBNORMAL
  #define FP_SUBNORMAL (-2)
#endif
#ifdef FP_ZERO
  #define FP_ZERO 0
#endif

    enum class rounding_mode
    {
      downward,
      to_nearest,
      toward_zero,
      upward
    };

    namespace internal
    {
      template <typename T>
      constexpr T fmod(T x, T div)
      {
        // if div or x is nan, return x directly
        if(div != div || x != x)
        {
          return x;
        }

        if(div == 0)
        {
          return NAN;
        }

        return x - static_cast<card32>(x / div) * div;
      }

      template <typename T>
      constexpr T sqrt(T arg)
      {
        REX_ASSERT_X(arg >= (T)0, "sqrt called on negative value");

        float64 s    = 0;
        float64 last = 0;

        if(arg > 0)
        {
          if(arg > 1)
          {
            s = static_cast<float64>(arg);
          }
          else
          {
            s = 1;
          }

          do
          {
            last = s;
            s    = static_cast<float64>((arg / s + s) / 2);
          } while(s < last);

          return static_cast<T>(last);
        }

        return 0;
      }

      template <typename T>
      constexpr T round_downward(T arg)
      {
        const int64 target = static_cast<int64>(arg);
        return static_cast<T>(target);
      }
      template <typename T>
      constexpr T round_to_nearest(T arg)
      {
        const int64 target = static_cast<int64>(arg);
        if(arg - target > 0.5f)
        {
          return static_cast<T>(target + 1);
        }
        else
        {
          return static_cast<T>(target);
        }
      }
      template <typename T>
      constexpr T round_upward(T arg)
      {
        const int64 target = static_cast<int64>(arg);
        return static_cast<T>(target + 1);
      }
      template <typename T>
      constexpr T round_toward_zero(T arg)
      {
        if(arg < 0)
        {
          return round_upward(arg);
        }
        else
        {
          return round_downward(arg);
        }
      }
      template <typename T>
      constexpr T rint(T arg, rounding_mode rmode)
      {
        switch(rmode)
        {
          case rounding_mode::downward: return round_downward(arg);
          case rounding_mode::to_nearest: return round_to_nearest(arg);
          case rounding_mode::toward_zero: return round_toward_zero(arg);
          case rounding_mode::upward: return round_upward(arg);
        }

        REX_ASSERT("Invalid round mode passed in");
        return 0;
      }
    } // namespace internal

    constexpr float32 abs(float32 arg)
    {
      return internal::abs(arg);
    }
    constexpr float64 abs(float64 arg)
    {
      return internal::abs(arg);
    }
    constexpr lfloat64 abs(lfloat64 arg)
    {
      return internal::abs(arg);
    }

    constexpr float32 fabs(float32 arg)
    {
      return internal::abs(arg);
    }
    constexpr float32 fabsf(float32 arg)
    {
      return internal::abs(arg);
    }
    constexpr float64 fabs(float64 arg)
    {
      return internal::abs(arg);
    }
    constexpr lfloat64 fabs(lfloat64 arg)
    {
      return internal::abs(arg);
    }
    constexpr lfloat64 fabsl(lfloat64 arg)
    {
      return internal::abs(arg);
    }

    template <typename IntegralType>
    constexpr float64 fabs(IntegralType arg)
    {
      return abs(static_cast<float64>(arg));
    }

    constexpr float32 fmod(float32 x, float32 div)
    {
      return internal::fmod(x, div);
    }
    constexpr float32 fmodf(float32 x, float32 div)
    {
      return internal::fmod(x, div);
    }
    constexpr float64 fmod(float64 x, float64 div)
    {
      return internal::fmod(x, div);
    }
    constexpr lfloat64 fmod(lfloat64 x, lfloat64 div)
    {
      return internal::fmod(x, div);
    }
    constexpr lfloat64 fmodl(lfloat64 x, lfloat64 div)
    {
      return internal::fmod(x, div);
    }
    template <typename Arithmetic>
    constexpr auto fmod(Arithmetic x, Arithmetic div)
    {
      return internal::fmod(static_cast<float64>(x), static_cast<float64>(div));
    }

    constexpr float32 sqrt(float32 arg)
    {
      return internal::sqrt(arg);
    }
    constexpr float32 sqrtf(float32 arg)
    {
      return internal::sqrt(arg);
    }
    constexpr float64 sqrt(float64 arg)
    {
      return internal::sqrt(arg);
    }
    constexpr lfloat64 sqrt(lfloat64 arg)
    {
      return internal::sqrt(arg);
    }
    constexpr lfloat64 sqrtl(lfloat64 arg)
    {
      return internal::sqrt(arg);
    }
    template <typename IntegralType>
    constexpr float64 sqrt(IntegralType arg)
    {
      return internal::sqrt(arg);
    }

    /// RSL Comment: Different from ISO C++ Standard at time of writing (22/Jan/2023)
    // the standard says that rint and it's equivalents should use the current rounding option.
    // this rounding option would be queried from a global state which is not recommended.
    // therefore, in rsl, the rounding option has to be specified.
    // It is however defaulted to round to near, which is the default in MSVC, Clang and GCC.
    constexpr float32 rint(float32 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return internal::rint(arg, rmode);
    }
    constexpr float32 rintf(float32 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return internal::rint(arg, rmode);
    }
    constexpr float64 rint(float64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return internal::rint(arg, rmode);
    }
    constexpr lfloat64 rint(lfloat64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return internal::rint(arg, rmode);
    }
    constexpr lfloat64 rintl(lfloat64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return internal::rint(arg, rmode);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (22/Jan/2023)
    // the standard cast this value to a double and then performs rounding.
    // for optimization purposes, we just return the input as there's no point rounding an int
    template <typename IntegralType>
    constexpr float64 rint(IntegralType arg, rounding_mode /*rmode*/ = rounding_mode::to_nearest)
    {
      static_assert(rsl::is_integral_v<IntegralType>, "arg must be an integral type");
      return arg;
    }
    constexpr long lrint(float32 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<long>(internal::rint(arg, rmode));
    }
    constexpr long lrintf(float32 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<long>(internal::rint(arg, rmode));
    }
    constexpr long lrint(float64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<long>(internal::rint(arg, rmode));
    }
    constexpr long lrint(lfloat64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<long>(internal::rint(arg, rmode));
    }
    constexpr long lrintl(lfloat64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<long>(internal::rint(arg, rmode));
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (22/Jan/2023)
    // the standard cast this value to a double and then performs rounding.
    // for optimization purposes, we just return the input as there's no point rounding an int
    template <typename IntegralType>
    constexpr long lrint(IntegralType arg, rounding_mode /*rmode*/ = rounding_mode::to_nearest)
    {
      static_assert(rsl::is_integral_v<IntegralType>, "arg must be an integral type");
      return arg;
    }

    constexpr int64 llrint(float32 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<int64>(internal::rint(arg, rmode));
    }
    constexpr int64 llrintf(float32 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<int64>(internal::rint(arg, rmode));
    }
    constexpr int64 llrint(float64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<int64>(internal::rint(arg, rmode));
    }
    constexpr int64 llrint(lfloat64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<int64>(internal::rint(arg, rmode));
    }
    constexpr int64 llrintl(lfloat64 arg, rounding_mode rmode = rounding_mode::to_nearest)
    {
      return static_cast<int64>(internal::rint(arg, rmode));
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (22/Jan/2023)
    // the standard cast this value to a double and then performs rounding.
    // for optimization purposes, we just return the input as there's no point rounding an int
    template <typename IntegralType>
    constexpr int64 llrint(IntegralType arg, rounding_mode /*rmode*/ = rounding_mode::to_nearest)
    {
      static_assert(rsl::is_integral_v<IntegralType>, "arg must be an integral type");
      return arg;
    }

  } // namespace v1
} // namespace rsl

#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <cmath>

namespace rsl
{
  inline namespace v1
  {

    REX_STD_FUNC_ALIAS(remainder);
    REX_STD_FUNC_ALIAS(remquo);
    REX_STD_FUNC_ALIAS(fma);
    REX_STD_FUNC_ALIAS(fmax);
    REX_STD_FUNC_ALIAS(fmin);
    REX_STD_FUNC_ALIAS(fdim);
    REX_STD_FUNC_ALIAS(nan);
    REX_STD_FUNC_ALIAS(lerp);
    REX_STD_FUNC_ALIAS(exp2);
    REX_STD_FUNC_ALIAS(expm1);
    REX_STD_FUNC_ALIAS(log);
    REX_STD_FUNC_ALIAS(log10);
    REX_STD_FUNC_ALIAS(log2);
    REX_STD_FUNC_ALIAS(log1p);
    REX_STD_FUNC_ALIAS(atan2);
    REX_STD_FUNC_ALIAS(sinh);
    REX_STD_FUNC_ALIAS(cosh);
    REX_STD_FUNC_ALIAS(tanh);
    REX_STD_FUNC_ALIAS(asinh);
    REX_STD_FUNC_ALIAS(acosh);
    REX_STD_FUNC_ALIAS(atanh);
    REX_STD_FUNC_ALIAS(erf);
    REX_STD_FUNC_ALIAS(erfc);
    REX_STD_FUNC_ALIAS(tgamma);
    REX_STD_FUNC_ALIAS(lgamma);
    REX_STD_FUNC_ALIAS(trunc);
    REX_STD_FUNC_ALIAS(round);
    REX_STD_FUNC_ALIAS(nearbyint);
    REX_STD_FUNC_ALIAS(rint);
    REX_STD_FUNC_ALIAS(frexp);
    REX_STD_FUNC_ALIAS(ldexp);
    REX_STD_FUNC_ALIAS(modf);
    REX_STD_FUNC_ALIAS(scalbn);
    REX_STD_FUNC_ALIAS(ilogb);
    REX_STD_FUNC_ALIAS(logb);
    REX_STD_FUNC_ALIAS(nextafter);
    REX_STD_FUNC_ALIAS(copysign);
    REX_STD_FUNC_ALIAS(fpclassify);
    REX_STD_FUNC_ALIAS(isfinite);
    REX_STD_FUNC_ALIAS(isinf);
    REX_STD_FUNC_ALIAS(isnormal);
    REX_STD_FUNC_ALIAS(isgreater);
    REX_STD_FUNC_ALIAS(isgreaterequal);
    REX_STD_FUNC_ALIAS(isless);
    REX_STD_FUNC_ALIAS(islessequal);
    REX_STD_FUNC_ALIAS(islessgreater);
    REX_STD_FUNC_ALIAS(isunordered);
    REX_STD_FUNC_ALIAS(assoc_laguerre);
    REX_STD_FUNC_ALIAS(assoc_legendre);
    REX_STD_FUNC_ALIAS(beta);
    REX_STD_FUNC_ALIAS(comp_ellint_1);
    REX_STD_FUNC_ALIAS(comp_ellint_2);
    REX_STD_FUNC_ALIAS(comp_ellint_3);
    REX_STD_FUNC_ALIAS(expint);
    REX_STD_FUNC_ALIAS(hermite);
    REX_STD_FUNC_ALIAS(legendre);
    REX_STD_FUNC_ALIAS(laguerre);
    REX_STD_FUNC_ALIAS(riemann_zeta);
    REX_STD_FUNC_ALIAS(sph_bessel);
    REX_STD_FUNC_ALIAS(sph_legendre);
    REX_STD_FUNC_ALIAS(sph_neumann);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"