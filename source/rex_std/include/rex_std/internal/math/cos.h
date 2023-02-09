// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: cos.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/math/return_type.h"
#include "rex_std/internal/math/is_nan.h"
#include "rex_std/limits.h"
#include "rex_std/numbers.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {

      template <typename T>
      constexpr T cos_compute(const T x)
      {
        return (T(1) - x * x) / (T(1) + x * x); // NOLINT(google-readability-casting)
      }

      template <typename T>
      constexpr T cos_check(const T x)
      {
        return ( // NaN check
            is_nan(x) ? numeric_limits<T>::quiet_nan() :
                      // indistinguishable from 0
                (numeric_limits<T>::min)() > abs(x) ? T(1) // NOLINT(google-readability-casting)
                                                  :
                                                  // special cases: pi/2 and pi
                (numeric_limits<T>::min)() > abs(x - T(rsl::half_pi_v<lfloat64>)) ? T(0)  // NOLINT(google-readability-casting)
            : (numeric_limits<T>::min)() > abs(x + T(rsl::half_pi_v<lfloat64>))   ? T(0)  // NOLINT(google-readability-casting)
            : (numeric_limits<T>::min)() > abs(x - T(rsl::pi_v<lfloat64>))        ? -T(1) // NOLINT(google-readability-casting)
            : (numeric_limits<T>::min)() > abs(x + T(rsl::pi_v<lfloat64>))        ? -T(1) // NOLINT(google-readability-casting)
                                                                                :
                                                                         // else
                cos_compute(tan(x / T(2)))); // NOLINT(google-readability-casting)
      }

    } // namespace internal

    /**
     * Compile-time cosine function
     *
     * @param x a real-valued input.
     * @return the cosine function using \f[ \cos(x) = \frac{1-\tan^2(x/2)}{1+\tan^2(x/2)} \f]
     */

    template <typename T>
    constexpr return_t<T> cos(const T x)
    {
      return internal::cos_check(static_cast<return_t<T>>(x));
    }

  } // namespace v1
} // namespace rsl
