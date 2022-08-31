// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: uses_allocator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/std_alias_defines.h"

#include <memory>

namespace rsl
{
    template <typename T, typename Alloc>
    REX_STD_TEMPLATED_CLASS_ALIAS(uses_allocator, T, Alloc);

    template <typename T, typename Alloc>
    REX_STD_TEMPLATED_OBJECT_ALIAS(uses_allocator_v, T, Alloc);
}
