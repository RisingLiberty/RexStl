// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: queue.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"

#include "rex_std/compare.h"
#include "rex_std/initializer_list.h"

#include "rex_std/internal/functional/less.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <queue>

REX_RSL_BEGIN_NAMESPACE

    class allocator;
    
    template <typename T, typename Allocator>
    class vector;

    template <typename T, typename Container = rsl::deque<T, rsl::allocator>>
    REX_STD_TEMPLATED_CLASS_ALIAS(queue, T, Container);

    template <typename T, typename Container = rsl::deque<T, rsl::allocator>, typename Compare = rsl::less<typename Container::value_type>>
    REX_STD_TEMPLATED_CLASS_ALIAS(priority_queue, T, Container, Compare);

    template <typename T, typename Alloc>
    REX_STD_TEMPLATED_CLASS_ALIAS(uses_allocator, T, Alloc);

    REX_STD_FUNC_ALIAS(operator==);
    REX_STD_FUNC_ALIAS(operator!=);
    REX_STD_FUNC_ALIAS(operator<);
    REX_STD_FUNC_ALIAS(operator<=);
    REX_STD_FUNC_ALIAS(operator>);
    REX_STD_FUNC_ALIAS(operator>=);
    
REX_RSL_END_NAMESPACE

#include "rex_std/enable_std_checking.h"
