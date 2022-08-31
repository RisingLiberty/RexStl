// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: stack.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/compare.h"
#include "rex_std/initializer_list.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include "rex_std/internal/memory/uses_allocator.h"

#include <stack>

namespace rsl
{
    class allocator;

    template <typename T, typename Container = rsl::deque<T, allocator>>
    REX_STD_TEMPLATED_CLASS_ALIAS(stack, T, Container);

    REX_STD_FUNC_ALIAS(operator==);
    REX_STD_FUNC_ALIAS(operator!=);
    REX_STD_FUNC_ALIAS(operator<);
    REX_STD_FUNC_ALIAS(operator<=);
    REX_STD_FUNC_ALIAS(operator>);
    REX_STD_FUNC_ALIAS(operator>=);
    
}

#include "rex_std/enable_std_checking.h"
