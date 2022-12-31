// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fmt_ranges_odr_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

// call fmt::format from another translation unit to test ODR
TEST(ranges_odr_test, format_vector) {
  auto v = std::vector<int>{ 1, 2, 3, 5, 7, 11 };
  EXPECT_EQ(fmt::format("{}", v), "[1, 2, 3, 5, 7, 11]");
}
