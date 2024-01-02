// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: unordered_set.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/hashtable/hash_set.h"
#include "rex_std/internal/functional/equal_to.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename Value, typename Hash = rsl::hash<Value>, typename Predicate = rsl::equal_to<Value>, typename Allocator = rsl::allocator>
    using unordered_set = hash_set<Value, Hash, Predicate, Allocator>;

    template <typename Value, typename Hash = rsl::hash<Value>, typename Predicate = rsl::equal_to<Value>, typename Allocator = rsl::allocator>
    using unordered_multiset = hash_multiset<Value, Hash, Predicate, Allocator>;

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
