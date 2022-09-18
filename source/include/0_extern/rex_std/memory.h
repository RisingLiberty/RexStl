// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: memory.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/header/memory
//
// High level memory management utilities
//-----------------------------------------------------------------------------

#pragma once

#include "rex_std/internal/memory/pointer_traits.h" // yes
#include "rex_std/internal/memory/allocator.h" // yes
#include "rex_std/internal/memory/allocator_traits.h" // yes
#include "rex_std/internal/memory/allocator_arg_t.h" // yes
#include "rex_std/internal/memory/uses_allocator.h" // yes
#include "rex_std/internal/memory/unique_ptr.h" // yes 
#include "rex_std/internal/memory/shared_ptr.h" // yes
// #include "rex_std/internal/memory/weak_ptr.h" // yes, low priority
// #include "rex_std/internal/memory/owner_less.h" // yes, low priority
// #include "rex_std/internal/memory/enable_shared_from_this.h" // yes, low priority
// #include "rex_std/internal/memory/bad_weak_ptr.h" // yes, low priority
#include "rex_std/internal/memory/default_delete.h" // yes
#include "rex_std/internal/memory/uninitialized_copy.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_copy_n.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_default_construct.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_default_construct_n.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_fill.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_fill_n.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_move.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_move_n.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_value_construct.h" // yes, low priority
#include "rex_std/internal/memory/uninitialized_value_construct_n.h" // yes, low priority
#include "rex_std/internal/memory/construct_at.h" // yes
#include "rex_std/internal/memory/destroy_at.h" // yes
#include "rex_std/internal/memory/destroy.h" // yes
#include "rex_std/internal/memory/destroy_n.h" // yes

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    struct hash;

    template <typename T>
    class atomic;

REX_RSL_END_NAMESPACE
