// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_limits.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/limits.h"

#include <limits>
#include <string.h>

namespace limits_test
{
  // compares rsl::numeric_limits<T> against the compiler's std::numeric_limits<T>
  template <typename T>
  void compare_common_values()
  {
    using rsl_limits = rsl::numeric_limits<T>;
    using std_limits = std::numeric_limits<T>;

    CHECK((rsl_limits::min)() == (std_limits::min)());
    CHECK((rsl_limits::max)() == (std_limits::max)());
    CHECK(rsl_limits::lowest() == std_limits::lowest());

    CHECK(rsl_limits::is_specialized == std_limits::is_specialized);
    CHECK(rsl_limits::is_signed == std_limits::is_signed);
    CHECK(rsl_limits::is_integer == std_limits::is_integer);
    CHECK(rsl_limits::is_exact == std_limits::is_exact);
    CHECK(rsl_limits::is_bounded == std_limits::is_bounded);
    CHECK(rsl_limits::has_infinity == std_limits::has_infinity);
    CHECK(rsl_limits::has_quiet_nan == std_limits::has_quiet_NaN);
    CHECK(rsl_limits::radix == std_limits::radix);
    CHECK(rsl_limits::digits == std_limits::digits);
    CHECK(rsl_limits::digits10 == std_limits::digits10);
  }

  template <typename T>
  void compare_integer_values()
  {
    compare_common_values<T>();

    using rsl_limits = rsl::numeric_limits<T>;
    using std_limits = std::numeric_limits<T>;

    CHECK(rsl_limits::epsilon() == std_limits::epsilon());
    CHECK(rsl_limits::round_error() == std_limits::round_error());
  }

  template <typename T>
  void compare_float_values()
  {
    compare_common_values<T>();

    using rsl_limits = rsl::numeric_limits<T>;
    using std_limits = std::numeric_limits<T>;

    CHECK(rsl_limits::epsilon() == std_limits::epsilon());
    CHECK(rsl_limits::round_error() == std_limits::round_error());
    CHECK(rsl_limits::denorm_min() == std_limits::denorm_min());
    CHECK(rsl_limits::infinity() == std_limits::infinity());
    CHECK(rsl_limits::max_digits10 == std_limits::max_digits10);
    CHECK(rsl_limits::min_exponent == std_limits::min_exponent);
    CHECK(rsl_limits::min_exponent10 == std_limits::min_exponent10);
    CHECK(rsl_limits::max_exponent == std_limits::max_exponent);
    CHECK(rsl_limits::max_exponent10 == std_limits::max_exponent10);
    CHECK(rsl_limits::is_iec559 == std_limits::is_iec559);

    // the test project is compiled with /fp:fast, which makes NaN comparisons unreliable
    // so we compare the bit pattern with the one of std instead
    const T rsl_nan = rsl_limits::quiet_nan();
    const T std_nan = std_limits::quiet_NaN();
    CHECK(memcmp(&rsl_nan, &std_nan, sizeof(T)) == 0);
  }
} // namespace limits_test

TEST_CASE("numeric limits bool")
{
  CHECK((rsl::numeric_limits<bool>::min)() == false);
  CHECK((rsl::numeric_limits<bool>::max)() == true);
  CHECK(rsl::numeric_limits<bool>::lowest() == false);
  CHECK(rsl::numeric_limits<bool>::digits == 1);
  CHECK(rsl::numeric_limits<bool>::is_integer == true);
  CHECK(rsl::numeric_limits<bool>::is_signed == false);
}

TEST_CASE("numeric limits char types")
{
  limits_test::compare_integer_values<char>();
  limits_test::compare_integer_values<signed char>();
  limits_test::compare_integer_values<unsigned char>();
  limits_test::compare_integer_values<wchar_t>();
  limits_test::compare_integer_values<char16_t>();
  limits_test::compare_integer_values<char32_t>();
}

TEST_CASE("numeric limits signed integers")
{
  limits_test::compare_integer_values<short>();
  limits_test::compare_integer_values<int>();
  limits_test::compare_integer_values<long>();
  limits_test::compare_integer_values<long long>();
}

TEST_CASE("numeric limits unsigned integers")
{
  limits_test::compare_integer_values<unsigned short>();
  limits_test::compare_integer_values<unsigned int>();
  limits_test::compare_integer_values<unsigned long>();
  limits_test::compare_integer_values<unsigned long long>();
}

TEST_CASE("numeric limits floating point")
{
  limits_test::compare_float_values<float>();
  limits_test::compare_float_values<double>();
  limits_test::compare_float_values<long double>();
}

TEST_CASE("numeric limits cv qualified")
{
  CHECK((rsl::numeric_limits<const int>::max)() == (rsl::numeric_limits<int>::max)());
  CHECK((rsl::numeric_limits<volatile int>::max)() == (rsl::numeric_limits<int>::max)());
  CHECK((rsl::numeric_limits<const volatile int>::max)() == (rsl::numeric_limits<int>::max)());
  CHECK((rsl::numeric_limits<const float>::min)() == (rsl::numeric_limits<float>::min)());
}

// NOLINTEND
