// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vector.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

// Forward declare here to avoid annoying compiler errors caused by include orders
namespace rsl 
{
    inline namespace v1
    {
        class allocator;

        template <typename T, typename Alloc = allocator>
        class vector;
    } // namespace v1
} // namespace rsl

#include "rex_std/internal/assert/assert_impl.h"
#include "rex_std/internal/vector/vector.h"