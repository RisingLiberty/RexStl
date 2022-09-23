// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: rehash_base.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/hashtable/prime_rehash_policy.h"

REX_RSL_BEGIN_NAMESPACE

template <typename RehashPolicy, typename HashTable>
struct rehash_base
{
};

template <typename HashTable>
struct rehash_base<prime_rehash_policy, Hashtable>
{
  float32 get_max_load_factor() const
  {
    const HashTable* p_this = static_cast<const HashTable*>(this);
    return p_this->rehash_policy().get_max_load_factor();
  }

  void set_max_load_factor(float32 maxLoadFactor)
  {
    HashTable* p_this = static_cast<HashTable*>(this);
    return p_this->rehash_policy(prime_rehash_policy(maxLoadFactor));
  }
};

REX_RSL_END_NAMESPACE