// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_rex_std.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/test_rex_std.h"

namespace rsl::test
{
  inline namespace v1
  {
    uint32 g_rand_seed;

    uint32 rand_seed()
    {
      return g_rand_seed;
    }
    void set_rand_seed(uint32 seed)
    {
      g_rand_seed = seed;
    }
  }
}