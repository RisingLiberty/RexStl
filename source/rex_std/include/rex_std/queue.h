// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: queue.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/compare.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/initializer_list.h"
#include "rex_std/internal/functional/less.h"
#include "rex_std/std_alias_defines.h"
#include "rex_std/deque.h"

#include <queue>

namespace rsl
{
  inline namespace v1
  {
    template <typename T, typename Container = rsl::deque<T>>
    using queue = std::queue<T, Container>;

    //class allocator;

    //template <typename T, typename Alloc>
    //class vector;

    //RSL_TEMPLATED_CLASS_ALIAS(template <typename T, typename Container = rsl::deque<T, rsl::allocator>>, queue, T, Container);

    //RSL_TEMPLATED_CLASS_ALIAS(template <typename T, typename Container = rsl::deque<T, rsl::allocator>, typename Compare = rsl::less<typename Container::value_type>>, priority_queue, T, Container, Compare);

    //RSL_TEMPLATED_CLASS_ALIAS(template <typename T, typename Alloc>, uses_allocator, T, Alloc);

    //RSL_FUNC_ALIAS(operator==);
    //RSL_FUNC_ALIAS(operator!=);
    //RSL_FUNC_ALIAS(operator<);
    //RSL_FUNC_ALIAS(operator<=);
    //RSL_FUNC_ALIAS(operator>);
    //RSL_FUNC_ALIAS(operator>=);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
