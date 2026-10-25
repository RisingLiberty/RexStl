// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_chrono.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/chrono.h"

TEST_CASE("duration construction")
{
  rsl::chrono::hours h(1);
  rsl::chrono::milliseconds ms(3);
  rsl::chrono::duration<int32, rsl::kilo> ks(3);

  CHECK(rsl::chrono::duration_cast<rsl::chrono::seconds>(h).count() == 3600);
  CHECK(rsl::chrono::duration_cast<rsl::chrono::minutes>(h).count() == 60);
  CHECK(rsl::chrono::duration_cast<rsl::chrono::seconds>(ms).count() == 0);
  CHECK(rsl::chrono::duration_cast<rsl::chrono::seconds>(ks).count() == 3000);
}

TEST_CASE("duration operators")
{
  rsl::chrono::hours h(1);
  rsl::chrono::minutes half_hour = h - rsl::chrono::minutes(30);
  CHECK(half_hour.count() == 30);
}

TEST_CASE("time_point operators")
{
  auto now            = rsl::chrono::high_resolution_clock::now();
  auto one_hour_later = now + rsl::chrono::hours(1);

  auto dur = rsl::chrono::duration_cast<rsl::chrono::seconds>(one_hour_later - now);
  CHECK(dur.count() == 3600);
}

TEST_CASE("duration conversions")
{
  using namespace rsl::chrono;

  // implicit conversion to a finer duration is lossless
  milliseconds ms = seconds(2);
  CHECK(ms.count() == 2000);
  microseconds us = milliseconds(3);
  CHECK(us.count() == 3000);
  nanoseconds ns = microseconds(4);
  CHECK(ns.count() == 4000);
  seconds s = minutes(2);
  CHECK(s.count() == 120);
  hours h = days(1);
  CHECK(h.count() == 24);
  days d = weeks(2);
  CHECK(d.count() == 14);

  // duration_cast truncates towards zero
  CHECK(duration_cast<seconds>(milliseconds(1999)).count() == 1);
  CHECK(duration_cast<seconds>(milliseconds(-1999)).count() == -1);
  CHECK(duration_cast<minutes>(seconds(119)).count() == 1);
  CHECK(duration_cast<hours>(weeks(1)).count() == 168);

  // floating point durations
  duration<float64> fs = milliseconds(1500);
  CHECK(fs.count() == 1.5);
}

TEST_CASE("duration arithmetic")
{
  using namespace rsl::chrono;

  // different periods result in the common (finer) period
  auto sum = seconds(1) + milliseconds(500);
  CHECK(sum.count() == 1500);
  auto diff = minutes(1) - seconds(30);
  CHECK(diff.count() == 30);

  // scalar multiplication and division
  CHECK((seconds(3) * 2).count() == 6);
  CHECK((2 * seconds(3)).count() == 6);
  CHECK((seconds(9) / 3).count() == 3);
  CHECK((seconds(10) % 3).count() == 1);

  // note: the unary + and - operators return common_type<duration> instead of common_type_t<duration> at the moment,
  // so their result can't be used

  // increment and decrement
  seconds s(5);
  ++s;
  CHECK(s.count() == 6);
  --s;
  CHECK(s.count() == 5);
  seconds old = s++;
  CHECK(old.count() == 5);
  CHECK(s.count() == 6);
  old = s--;
  CHECK(old.count() == 6);
  CHECK(s.count() == 5);

  // compound assignment
  s += seconds(10);
  CHECK(s.count() == 15);
  s -= seconds(5);
  CHECK(s.count() == 10);
  s *= 3;
  CHECK(s.count() == 30);
  s /= 2;
  CHECK(s.count() == 15);
  s %= 4;
  CHECK(s.count() == 3);
  s = seconds(10);
  s %= seconds(4);
  CHECK(s.count() == 2);
}

TEST_CASE("duration comparison")
{
  using namespace rsl::chrono;

  CHECK(seconds(1) == milliseconds(1000));
  CHECK(seconds(1) != milliseconds(1001));
  CHECK(seconds(1) < milliseconds(1001));
  CHECK(milliseconds(999) < seconds(1));
  CHECK(minutes(1) > seconds(59));
  CHECK(minutes(1) >= seconds(60));
  CHECK(minutes(1) <= seconds(60));
  CHECK(hours(1) == minutes(60));
}

TEST_CASE("duration special values")
{
  using namespace rsl::chrono;

  CHECK(seconds::zero().count() == 0);
  CHECK((seconds::min)().count() < 0);
  CHECK((seconds::max)().count() > 0);
  CHECK((seconds::min)() < seconds::zero());
  CHECK((seconds::max)() > seconds::zero());

  // default construction
  seconds s {};
  CHECK(s.count() == 0);
}

TEST_CASE("duration rounding")
{
  using namespace rsl::chrono;

  // floor
  CHECK(rsl::chrono::floor<seconds>(milliseconds(1500)).count() == 1);
  CHECK(rsl::chrono::floor<seconds>(milliseconds(-1500)).count() == -2);
  CHECK(rsl::chrono::floor<seconds>(milliseconds(2000)).count() == 2);

  // ceil
  CHECK(rsl::chrono::ceil<seconds>(milliseconds(1500)).count() == 2);
  CHECK(rsl::chrono::ceil<seconds>(milliseconds(-1500)).count() == -1);
  CHECK(rsl::chrono::ceil<seconds>(milliseconds(2000)).count() == 2);

  // round, ties go to even
  CHECK(rsl::chrono::round<seconds>(milliseconds(1400)).count() == 1);
  CHECK(rsl::chrono::round<seconds>(milliseconds(1600)).count() == 2);
  CHECK(rsl::chrono::round<seconds>(milliseconds(1500)).count() == 2);
  CHECK(rsl::chrono::round<seconds>(milliseconds(2500)).count() == 2);

  // abs
  CHECK(rsl::chrono::abs(seconds(-5)).count() == 5);
  CHECK(rsl::chrono::abs(seconds(5)).count() == 5);
}

TEST_CASE("duration literals")
{
  using namespace rsl::chrono_literals;

  CHECK((2h).count() == 2);
  CHECK((30min).count() == 30);
  CHECK((5s).count() == 5);
  CHECK((100ms).count() == 100);
  CHECK((7us).count() == 7);
  CHECK((9ns).count() == 9);

  CHECK(1h == 60min);
  CHECK(1s == 1000ms);
  CHECK((1.5s).count() == 1.5);
}

// NOLINTEND
