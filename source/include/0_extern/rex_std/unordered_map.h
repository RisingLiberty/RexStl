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

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <unordered_map>

namespace rsl
{
    class allocator;

    template <typename T>
    struct hash;

    template <typename Key, typename Value, typename Hash = hash<Value>, typename Allocator = allocator>
    REX_STD_TEMPLATED_CLASS_ALIAS(unordered_map, Key, Value, Hash, Allocator);
    template <typename Key, typename Value, typename Hash = hash<Value>, typename Allocator = allocator>
    REX_STD_TEMPLATED_CLASS_ALIAS(unordered_multimap, Key, Value, Hash, Allocator);

    REX_STD_FUNC_ALIAS(operator==);
    REX_STD_FUNC_ALIAS(operator!=);
    REX_STD_FUNC_ALIAS(operator<);
    REX_STD_FUNC_ALIAS(operator<=);
    REX_STD_FUNC_ALIAS(operator>);
    REX_STD_FUNC_ALIAS(operator>=);

#ifdef REX_ENABLE_WITH_CPP20
    REX_STD_FUNC_ALIAS(erase);
    REX_STD_FUNC_ALIAS(erase_if);
#endif
}

#include "rex_std/enable_std_checking.h"