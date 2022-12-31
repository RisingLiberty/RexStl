// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fmt_header_only_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

TEST(header_only_test, format) { EXPECT_EQ(fmt::format("foo"), "foo"); }
