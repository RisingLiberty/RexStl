// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: unordered_map.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/hashtable/hash_map.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename Key, typename Value, typename Hash = rsl::hash<Key>, typename Equal = rsl::equal_to<Key>, typename Allocator = rsl::allocator>
    using unordered_map = hash_map<Key, Value, Hash, Equal, Allocator>;

    template <typename Key, typename Value, typename Hash = rsl::hash<Key>, typename Equal = rsl::equal_to<Key>, typename Allocator = rsl::allocator>
    using unordered_multimap = hash_multimap<Key, Value, Hash, Equal, Allocator>;

REX_RSL_END_NAMESPACE