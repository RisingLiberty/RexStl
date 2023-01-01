// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: chrono_test.cpp
// Copyright (c) Nick De Breuck 2022
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

  REQUIRE(rsl::chrono::duration_cast<rsl::chrono::seconds>(h).count() == 3600);
  REQUIRE(rsl::chrono::duration_cast<rsl::chrono::minutes>(h).count() == 60);
  REQUIRE(rsl::chrono::duration_cast<rsl::chrono::seconds>(ms).count() == 0);
  REQUIRE(rsl::chrono::duration_cast<rsl::chrono::seconds>(ks).count() == 3000);
}

TEST_CASE("duration operators")
{
  rsl::chrono::hours h(1);
  rsl::chrono::minutes half_hour = h - rsl::chrono::minutes(30);
  REQUIRE(half_hour.count() == 30);
}

TEST_CASE("time_point operators")
{
  auto now            = rsl::chrono::high_resolution_clock::now();
  auto one_hour_later = now + rsl::chrono::hours(1);

  auto dur = rsl::chrono::duration_cast<rsl::chrono::seconds>(one_hour_later - now);
  REQUIRE(dur.count() == 3600);
}

// NOLINTEND
