// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_math.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

// math.h uses RSL_ASSERT_X but doesn't include rex_std/assert.h itself
#include "rex_std/assert.h"

#include "rex_std/limits.h"
#include "rex_std/math.h"
#include "rex_std/numbers.h"
#include "rex_std/stdlib.h"

#include <cmath>

namespace math_test
{
  template <typename T>
  bool is_close(T lhs, T rhs, T epsilon = static_cast<T>(0.0001))
  {
    const T diff = lhs - rhs;
    return (diff < 0 ? -diff : diff) <= epsilon;
  }

  // values used to compare rsl math functions against the C runtime's
  constexpr float32 g_test_values[] = {-10.75f, -3.5f, -2.5f, -1.0f, -0.75f, -0.5f, -0.25f, 0.0f, 0.25f, 0.5f, 0.75f, 1.0f, 2.5f, 3.5f, 10.75f};
} // namespace math_test

TEST_CASE("math abs")
{
  CHECK(rsl::abs(5) == 5);
  CHECK(rsl::abs(-5) == 5);
  CHECK(rsl::abs(0) == 0);
  CHECK(rsl::abs(-5ll) == 5ll);
  CHECK(rsl::labs(-5l) == 5l);
  CHECK(rsl::llabs(-5ll) == 5ll);

  CHECK(rsl::abs(-1.5f) == 1.5f);
  CHECK(rsl::abs(1.5f) == 1.5f);
  CHECK(rsl::abs(-2.5) == 2.5);
  CHECK(rsl::fabs(-3.0f) == 3.0f);
  CHECK(rsl::fabsf(-3.0f) == 3.0f);
  CHECK(rsl::fabs(-3.0) == 3.0);
  CHECK(rsl::fabs(-4) == 4.0);

  static_assert(rsl::abs(-1.0f) == 1.0f);
}

TEST_CASE("math div")
{
  {
    auto res = rsl::div(7, 2);
    CHECK(res.quot == 3);
    CHECK(res.rem == 1);
  }
  {
    auto res = rsl::div(-7, 2);
    CHECK(res.quot == -3);
    CHECK(res.rem == -1);
  }
  {
    auto res = rsl::div(6, 3);
    CHECK(res.quot == 2);
    CHECK(res.rem == 0);
  }
  {
    auto res = rsl::div(7ll, 2ll);
    CHECK(res.quot == 3);
    CHECK(res.rem == 1);
  }
  {
    auto res = rsl::ldiv(7l, -2l);
    CHECK(res.quot == -3);
    CHECK(res.rem == 1);
  }
  {
    auto res = rsl::lldiv(-7ll, -2ll);
    CHECK(res.quot == 3);
    CHECK(res.rem == -1);
  }
}

TEST_CASE("math fmod")
{
  CHECK(math_test::is_close(rsl::fmod(5.5f, 2.0f), 1.5f));
  CHECK(math_test::is_close(rsl::fmod(-5.5f, 2.0f), -1.5f));
  CHECK(math_test::is_close(rsl::fmod(5.5, 2.0), 1.5));
  CHECK(math_test::is_close(rsl::fmodf(9.0f, 3.0f), 0.0f));
  CHECK(math_test::is_close(rsl::fmod(1.0f, 3.0f), 1.0f));

  for(float32 val : math_test::g_test_values)
  {
    CHECK(math_test::is_close(rsl::fmod(val, 0.3f), std::fmod(val, 0.3f)));
  }
}

TEST_CASE("math sqrt")
{
  CHECK(math_test::is_close(rsl::sqrt(4.0f), 2.0f));
  CHECK(math_test::is_close(rsl::sqrt(2.0f), 1.41421356f));
  CHECK(math_test::is_close(rsl::sqrt(0.25f), 0.5f));
  CHECK(math_test::is_close(rsl::sqrt(0.0f), 0.0f));
  CHECK(math_test::is_close(rsl::sqrt(1.0f), 1.0f));
  CHECK(math_test::is_close(rsl::sqrt(16.0), 4.0));
  CHECK(math_test::is_close(rsl::sqrtf(9.0f), 3.0f));

  for(float32 val : {0.001f, 0.5f, 3.0f, 10.0f, 1234.5f, 1000000.0f})
  {
    CHECK(math_test::is_close(rsl::sqrt(val), std::sqrt(val), std::sqrt(val) * 0.0001f));
  }
}

TEST_CASE("math floor and ceil")
{
  CHECK(rsl::floor(1.5f) == 1.0f);
  CHECK(rsl::floor(-1.5f) == -2.0f);
  CHECK(rsl::floor(2.0f) == 2.0f);
  CHECK(rsl::floor(-2.0f) == -2.0f);
  CHECK(rsl::floor(0.0f) == 0.0f);

  CHECK(rsl::ceil(1.5f) == 2.0f);
  CHECK(rsl::ceil(-1.5f) == -1.0f);
  CHECK(rsl::ceil(2.0f) == 2.0f);
  CHECK(rsl::ceil(-2.0f) == -2.0f);
  CHECK(rsl::ceil(0.0f) == 0.0f);

  for(float32 val : math_test::g_test_values)
  {
    CHECK(rsl::floor(val) == std::floor(val));
    CHECK(rsl::ceil(val) == std::ceil(val));
  }

  static_assert(rsl::floor(1.5) == 1.0);
  static_assert(rsl::ceil(1.5) == 2.0);
}

TEST_CASE("math round")
{
  CHECK(rsl::round(1.2f) == 1.0f);
  CHECK(rsl::round(1.5f) == 2.0f);
  CHECK(rsl::round(1.7f) == 2.0f);
  CHECK(rsl::round(-1.2f) == -1.0f);
  CHECK(rsl::round(-1.5f) == -2.0f);
  CHECK(rsl::round(-1.7f) == -2.0f);
  CHECK(rsl::round(0.0f) == 0.0f);
  CHECK(rsl::round(3.0f) == 3.0f);

  for(float32 val : math_test::g_test_values)
  {
    CHECK(rsl::round(val) == std::round(val));
  }
}

TEST_CASE("math rint")
{
  using rsl::rounding_mode;

  CHECK(rsl::rint(2.3f, rounding_mode::downward) == 2.0f);
  CHECK(rsl::rint(-2.3f, rounding_mode::downward) == -3.0f);

  CHECK(rsl::rint(2.3f, rounding_mode::upward) == 3.0f);
  CHECK(rsl::rint(-2.3f, rounding_mode::upward) == -2.0f);

  CHECK(rsl::rint(2.7f, rounding_mode::toward_zero) == 2.0f);
  CHECK(rsl::rint(-2.7f, rounding_mode::toward_zero) == -2.0f);

  CHECK(rsl::rint(2.3f, rounding_mode::to_nearest) == 2.0f);
  CHECK(rsl::rint(2.7f, rounding_mode::to_nearest) == 3.0f);
  CHECK(rsl::rint(-2.7f, rounding_mode::to_nearest) == -3.0f);

  // to nearest is the default
  CHECK(rsl::rint(2.7f) == 3.0f);
  CHECK(rsl::rint(2.7) == 3.0);
  CHECK(rsl::rintf(2.2f) == 2.0f);

  // integers are returned as is
  CHECK(rsl::rint(5) == 5.0);

  CHECK(rsl::lrint(2.7f) == 3l);
  CHECK(rsl::lrint(2.2) == 2l);
  CHECK(rsl::lrint(7) == 7l);
  CHECK(rsl::llrint(2.7f) == 3ll);
  CHECK(rsl::llrint(-2.7) == -3ll);
  CHECK(rsl::llrint(7) == 7ll);
}

TEST_CASE("math pow")
{
  CHECK(rsl::pow(2, 0) == 1);
  CHECK(rsl::pow(2, 1) == 2);
  CHECK(rsl::pow(2, 10) == 1024);
  CHECK(rsl::pow(-2, 3) == -8);
  CHECK(rsl::pow(0, 5) == 0);
  CHECK(math_test::is_close(rsl::pow(1.5f, 2), 2.25f));
  CHECK(math_test::is_close(rsl::pow(0.5, 3), 0.125));

  static_assert(rsl::pow(3, 4) == 81);
}

TEST_CASE("math exp")
{
  CHECK(math_test::is_close(rsl::exp(0), 1.0f));
  CHECK(math_test::is_close(rsl::exp(1), 2.7182818f));
  CHECK(math_test::is_close(rsl::exp(2), std::exp(2.0f), 0.001f));
  CHECK(math_test::is_close(rsl::exp(5), std::exp(5.0f), 0.01f));
}

TEST_CASE("math factorial")
{
  CHECK(rsl::factorial(0) == 1);
  CHECK(rsl::factorial(1) == 1);
  CHECK(rsl::factorial(2) == 2);
  CHECK(rsl::factorial(5) == 120);
  CHECK(rsl::factorial(10) == 3628800);
  CHECK(rsl::factorial(20ll) == 2432902008176640000ll);

  static_assert(rsl::factorial(4) == 24);
}

TEST_CASE("math trigonometry")
{
  constexpr float32 pi = rsl::pi_v<float32>;

  // sin
  CHECK(math_test::is_close(rsl::sin(0.0f), 0.0f));
  CHECK(math_test::is_close(rsl::sin(pi / 2), 1.0f));
  CHECK(math_test::is_close(rsl::sin(pi), 0.0f));
  CHECK(math_test::is_close(rsl::sin(-pi / 2), -1.0f));

  // cos
  CHECK(math_test::is_close(rsl::cos(0.0f), 1.0f));
  CHECK(math_test::is_close(rsl::cos(pi / 2), 0.0f));
  CHECK(math_test::is_close(rsl::cos(pi), -1.0f));

  // tan
  CHECK(math_test::is_close(rsl::tan(0.0f), 0.0f));
  CHECK(math_test::is_close(rsl::tan(pi / 4), 1.0f));
  CHECK(math_test::is_close(rsl::tan(-pi / 4), -1.0f));

  // note: asin, acos and atan don't compile at the moment as they use numeric_limits::quiet_NaN, which is named quiet_nan in rsl

  // compare against the C runtime on a range of values
  for(float32 val : math_test::g_test_values)
  {
    CHECK(math_test::is_close(rsl::sin(val), std::sin(val), 0.001f));
    CHECK(math_test::is_close(rsl::cos(val), std::cos(val), 0.001f));
  }
  for(float32 val : {-0.9f, -0.5f, -0.1f, 0.0f, 0.1f, 0.5f, 0.9f})
  {
    CHECK(math_test::is_close(rsl::tan(val), std::tan(val), 0.001f));
  }
}

TEST_CASE("math classification")
{
  CHECK(!rsl::is_nan(1.0f));
  CHECK(!rsl::is_nan(0.0));
  CHECK(!rsl::is_nan(rsl::numeric_limits<float32>::infinity()));

  CHECK(rsl::is_finite(1.0f));
  CHECK(rsl::is_finite(0.0));
  CHECK(rsl::is_finite(-1000.0));

  CHECK(rsl::signbit(-1));
  CHECK(!rsl::signbit(1));
  CHECK(!rsl::signbit(0));
  CHECK(rsl::signbit(-1.0f));
  CHECK(!rsl::signbit(1.0f));
  CHECK(rsl::signbit(-2.0));
  CHECK(!rsl::signbit(2.0));
  CHECK(!rsl::signbit(5u));
}

TEST_CASE("math clamp")
{
  CHECK(rsl::clamp(5, 0, 10) == 5);
  CHECK(rsl::clamp(-5, 0, 10) == 0);
  CHECK(rsl::clamp(15, 0, 10) == 10);
  CHECK(rsl::clamp(0, 0, 10) == 0);
  CHECK(rsl::clamp(10, 0, 10) == 10);
  CHECK(rsl::clamp(0.5f, 0.0f, 1.0f) == 0.5f);
  CHECK(rsl::clamp(1.5f, 0.0f, 1.0f) == 1.0f);

  static_assert(rsl::clamp(20, 0, 10) == 10);
}

// NOLINTEND
