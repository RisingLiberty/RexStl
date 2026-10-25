// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_ratio.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/ratio.h"
#include "rex_std/type_traits.h"

TEST_CASE("ratio creation")
{
  // ratios are always stored in their simplified form
  CHECK(rsl::ratio<1, 2>::num == 1);
  CHECK(rsl::ratio<1, 2>::den == 2);

  CHECK(rsl::ratio<2, 4>::num == 1);
  CHECK(rsl::ratio<2, 4>::den == 2);

  CHECK(rsl::ratio<10, 5>::num == 2);
  CHECK(rsl::ratio<10, 5>::den == 1);

  CHECK(rsl::ratio<7, 21>::num == 1);
  CHECK(rsl::ratio<7, 21>::den == 3);

  // the denominator defaults to 1
  CHECK(rsl::ratio<5>::num == 5);
  CHECK(rsl::ratio<5>::den == 1);

  // zero numerator
  CHECK(rsl::ratio<0, 5>::num == 0);
  CHECK(rsl::ratio<0, 5>::den == 1);

  // the sign is always stored in the numerator
  CHECK(rsl::ratio<-2, 4>::num == -1);
  CHECK(rsl::ratio<-2, 4>::den == 2);
  CHECK(rsl::ratio<2, -4>::num == -1);
  CHECK(rsl::ratio<2, -4>::den == 2);
  CHECK(rsl::ratio<-2, -4>::num == 1);
  CHECK(rsl::ratio<-2, -4>::den == 2);

  // ratio::type is the simplified ratio
  static_assert(rsl::is_same_v<rsl::ratio<10, 20>::type, rsl::ratio<1, 2>>);
  static_assert(rsl::is_same_v<rsl::ratio<3, 9>::type, rsl::ratio<1, 3>>);
  static_assert(rsl::is_same_v<rsl::ratio<1, 2>::type, rsl::ratio<1, 2>>);
}

TEST_CASE("ratio arithmetic")
{
  // multiply
  {
    using r = rsl::RatioMultiply<rsl::ratio<1, 2>, rsl::ratio<2, 3>>;
    CHECK(r::num == 1);
    CHECK(r::den == 3);

    using r2 = rsl::RatioMultiply<rsl::ratio<-3, 4>, rsl::ratio<4, 3>>;
    CHECK(r2::num == -1);
    CHECK(r2::den == 1);

    using r3 = rsl::RatioMultiply<rsl::ratio<0, 1>, rsl::ratio<4, 3>>;
    CHECK(r3::num == 0);
    CHECK(r3::den == 1);
  }

  // divide
  {
    using r = rsl::RatioDivide<rsl::ratio<1, 2>, rsl::ratio<2, 3>>;
    CHECK(r::num == 3);
    CHECK(r::den == 4);

    using r2 = rsl::RatioDivide<rsl::ratio<1, 2>, rsl::ratio<1, 2>>;
    CHECK(r2::num == 1);
    CHECK(r2::den == 1);

    using r3 = rsl::RatioDivide<rsl::ratio<1, 2>, rsl::ratio<-1, 4>>;
    CHECK(r3::num == -2);
    CHECK(r3::den == 1);
  }
}

TEST_CASE("ratio si prefixes")
{
  CHECK(rsl::atto::num == 1);
  CHECK(rsl::atto::den == 1000000000000000000);
  CHECK(rsl::femto::den == 1000000000000000);
  CHECK(rsl::pico::den == 1000000000000);
  CHECK(rsl::nano::den == 1000000000);
  CHECK(rsl::micro::den == 1000000);
  CHECK(rsl::milli::den == 1000);
  CHECK(rsl::centi::den == 100);
  CHECK(rsl::deci::den == 10);

  CHECK(rsl::deca::num == 10);
  CHECK(rsl::deca::den == 1);
  CHECK(rsl::hecto::num == 100);
  CHECK(rsl::kilo::num == 1000);
  CHECK(rsl::mega::num == 1000000);
  CHECK(rsl::giga::num == 1000000000);
  CHECK(rsl::tera::num == 1000000000000);
  CHECK(rsl::peta::num == 1000000000000000);
  CHECK(rsl::exa::num == 1000000000000000000);

  // multiplying inverse prefixes gives 1
  using one = rsl::RatioMultiply<rsl::kilo, rsl::milli>;
  CHECK(one::num == 1);
  CHECK(one::den == 1);

  using micro_from_milli = rsl::RatioDivide<rsl::milli, rsl::kilo>;
  CHECK(micro_from_milli::num == rsl::micro::num);
  CHECK(micro_from_milli::den == rsl::micro::den);
}

// NOLINTEND
