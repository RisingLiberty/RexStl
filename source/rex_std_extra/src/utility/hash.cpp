// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_extra/utility/hash.h"

#include "rex_std_extra/random/rand.h"

rsl::hash_val rsl::hash_val::new_hash()
{
  static rand rand;
  static card64 new_hash = rand.new_rand();
  card64 seed            = 0;

  seed     = hash_combine(seed, new_hash);
  new_hash = seed;
  return rsl::hash_val(new_hash);
}