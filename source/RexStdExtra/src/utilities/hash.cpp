// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_extra/utilities/hash.h"

#include "rex_std_extra/random/rand.h"
#include "rex_std_extra/rex_stl_extra_pch.h"

rsl::Hash rsl::Hash::new_hash()
{
  static Rand rand;
  static card64 new_hash = rand.rand();
  card64 seed            = 0;

  seed     = hash_combine(seed, new_hash);
  new_hash = seed;
  return new_hash;
}