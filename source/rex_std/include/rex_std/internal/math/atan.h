// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atan.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/math/return_type.h"
#include "rex_std/bonus/types.h"
#include "rex_std/limits.h"
#include "rex_std/numbers.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {

      // Series

      template <typename T>
      constexpr T atan_series_order_calc(const T x, const T xPow, const card32 order)
      {
        return (T(1) / (T((order - 1) * 4 - 1) * xPow) - T(1) / (T((order - 1) * 4 + 1) * xPow * x));
      }

      template <typename T>
      constexpr T atan_series_order(const T x, const T xPow, const card32 order, const card32 maxOrder)
      {
        return (order == 1 ? rsl::half_pi_v<float64> - T(1) / x + atan_series_order(x * x, pow(x, 3), order + 1, maxOrder) :
                           // NOTE: x changes to x*x for order > 1
                    order < maxOrder ? atan_series_order_calc(x, xPow, order) + atan_series_order(x, xPow * x * x, order + 1, maxOrder)
                                     :
                                     // order == max_order
                    atan_series_order_calc(x, xPow, order));
      }

      template <typename T>
      constexpr T atan_series_main(const T x) // NOLINT(readability-function-cognitive-complexity)
      {
        return (x < T(3) ? atan_series_order(x, x, 1U, 10U) : // O(1/x^39)
                    x < T(4) ? atan_series_order(x, x, 1U, 9U)
                             : // O(1/x^35)
                    x < T(5) ? atan_series_order(x, x, 1U, 8U)
                             : // O(1/x^31)
                    x < T(7) ? atan_series_order(x, x, 1U, 7U)
                             : // O(1/x^27)
                    x < T(11) ? atan_series_order(x, x, 1U, 6U)
                              : // O(1/x^23)
                    x < T(25) ? atan_series_order(x, x, 1U, 5U)
                              : // O(1/x^19)
                    x < T(100) ? atan_series_order(x, x, 1U, 4U)
                               : // O(1/x^15)
                    x < T(1000) ? atan_series_order(x, x, 1U, 3U)
                                :                     // O(1/x^11)
                    atan_series_order(x, x, 1U, 2U)); // O(1/x^7)
      }

      // CF

      template <typename T>
      constexpr T atan_cf_recur(const T xx, const card32 depth, const card32 maxDepth)
      {
        return (depth < maxDepth ? // if
                    T(2 * depth - 1) + depth * depth * xx / atan_cf_recur(xx, depth + 1, maxDepth)
                                 :
                                 // else
                    T(2 * depth - 1));
      }

      template <typename T>
      constexpr T atan_cf_main(const T x)
      {
        return (x < T(0.5) ? x / atan_cf_recur(x * x, 1U, 15U) : x < T(1) ? x / atan_cf_recur(x * x, 1U, 25U) : x < T(1.5) ? x / atan_cf_recur(x * x, 1U, 35U) : x < T(2) ? x / atan_cf_recur(x * x, 1U, 45U) : x / atan_cf_recur(x * x, 1U, 52U));
      }

      //

      template <typename T>
      constexpr T atan_begin(const T x)
      {
        return (x > T(2.5) ? atan_series_main(x) : atan_cf_main(x));
      }

      template <typename T>
      constexpr T atan_check(const T x)
      {
        return ( // NaN check
            is_nan(x) ? numeric_limits<T>::quiet_NaN() :
                      // indistinguishable from zero
                (numeric_limits<T>::min)() > abs(x) ? T(0)
                                                  :
                                                  // negative or positive
                x < T(0) ? -atan_begin(-x)
                         : atan_begin(x));
      }
    } // namespace internal

    /**
     * Compile-time arctangent function
     *
     * @param x a real-valued input.
     * @return the inverse tangent function using \f[ \text{atan}(x) = \dfrac{x}{1 + \dfrac{x^2}{3 + \dfrac{4x^2}{5 + \dfrac{9x^2}{7 + \ddots}}}} \f]
     */

    template <typename T>
    constexpr return_t<T> atan(const T x)
    {
      return internal::atan_check(static_cast<return_t<T>>(x));
    }

  } // namespace v1
} // namespace rsl
