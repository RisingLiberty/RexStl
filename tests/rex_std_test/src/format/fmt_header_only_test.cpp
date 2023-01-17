// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fmt_header_only_test.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#ifdef REX_ENABLE_FMT_TESTING

TEST(header_only_test, format) { EXPECT_EQ(fmt::format("foo"), "foo"); }

#endif