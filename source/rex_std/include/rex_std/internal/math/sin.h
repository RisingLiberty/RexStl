// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: sin.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/math/return_type.h"
#include "rex_std/limits.h"
#include "rex_std/numbers.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <typename T>
      constexpr T sin_compute(const T x)
      {
        return T(2) * x / (T(1) + x * x); // NOLINT(google-readability-casting)
      }

      template <typename T>
      constexpr T sin_check(const T x)
      {
        return ( // NaN check
            is_nan(x) ? numeric_limits<T>::quiet_nan() :
                      // indistinguishable from zero
                (numeric_limits<T>::min)() > abs(x) ? T(0) // NOLINT(google-readability-casting)
                                                    :
                                                    // special cases: pi/2 and pi
                (numeric_limits<T>::min)() > abs(x - T(rsl::half_pi_v<lfloat64>)) ? T(1)  // NOLINT(google-readability-casting)
            : (numeric_limits<T>::min)() > abs(x + T(rsl::half_pi_v<lfloat64>))   ? -T(1) // NOLINT(google-readability-casting)
            : (numeric_limits<T>::min)() > abs(x - T(rsl::pi_v<lfloat64>))        ? T(0)  // NOLINT(google-readability-casting)
            : (numeric_limits<T>::min)() > abs(x + T(rsl::pi_v<lfloat64>))        ? -T(0) // NOLINT(google-readability-casting)
                                                                                  :
                                                                           // else
                sin_compute(tan(x / T(2)))); // NOLINT(google-readability-casting)
      }
    } // namespace internal

    template <typename T>
    constexpr return_t<T> sin(const T x)
    {
      return internal::sin_check(static_cast<return_t<T>>(x));
    }

  } // namespace v1
} // namespace rsl
