// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: unordered_map.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/hashtable/hash_map.h"
#include "rex_std/internal/functional/equal_to.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename Key, typename Value, typename Hash = rsl::hash<Key>, typename Equal = rsl::equal_to<Key>, typename Alloc = rsl::allocator>
    using unordered_map = hash_map<Key, Value, Hash, Equal, Alloc>;

    template <typename Key, typename Value, typename Hash = rsl::hash<Key>, typename Equal = rsl::equal_to<Key>, typename Alloc = rsl::allocator>
    using unordered_multimap = hash_multimap<Key, Value, Hash, Equal, Alloc>;

  } // namespace v1
} // namespace rsl

#include "rex_std/assert.h"