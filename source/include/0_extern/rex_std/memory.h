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

#pragma once

#include "rex_std/internal/config.h"

#include "rex_std/compare.h"

#include "internal/memory/allocator.h"
#include "internal/memory/unique_ptr.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <memory>

namespace rsl
{
    REX_STD_CLASS_ALIAS(allocator_arg_t);
    REX_STD_OBJECT_ALIAS(allocator_arg);

    template <typename T, typename Alloc>
    REX_STD_TEMPLATED_CLASS_ALIAS(uses_allocator, T, Alloc);

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(weak_ptr, T);

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(atomic, T);

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(owner_less, T);

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(enable_shared_from_this, T);

    REX_STD_FUNC_ALIAS(assume_aligned);
    REX_STD_FUNC_ALIAS(uninitialized_copy);
    REX_STD_FUNC_ALIAS(uninitialized_copy_n);
    REX_STD_FUNC_ALIAS(uninitialized_fill);
    REX_STD_FUNC_ALIAS(uninitialized_fill_n);
    REX_STD_FUNC_ALIAS(uninitialized_move);
    REX_STD_FUNC_ALIAS(uninitialized_move_n);
    REX_STD_FUNC_ALIAS(uninitialized_default_construct);
    REX_STD_FUNC_ALIAS(uninitialized_default_construct_n);
    REX_STD_FUNC_ALIAS(uninitialized_value_construct);
    REX_STD_FUNC_ALIAS(uninitialized_value_construct_n);
    REX_STD_FUNC_ALIAS(construct_at);
    REX_STD_FUNC_ALIAS(destroy_at);
    REX_STD_FUNC_ALIAS(destroy);
    REX_STD_FUNC_ALIAS(destroy_n);
    REX_STD_FUNC_ALIAS(allocate_shared);
    REX_STD_FUNC_ALIAS(static_pointer_cast);
    REX_STD_FUNC_ALIAS(dynamic_pointer_cast);
    REX_STD_FUNC_ALIAS(const_pointer_cast);
    REX_STD_FUNC_ALIAS(reinterpret_pointer_cast);
    REX_STD_FUNC_ALIAS(get_deleter);
    REX_STD_FUNC_ALIAS(operator<<);
    

    template <typename T>
    REX_STD_TEMPLATED_CLASS_ALIAS(atomic, T);

#ifdef REX_ENABLE_WITH_CPP20
    REX_STD_FUNC_ALIAS(to_address);

    REX_STD_FUNC_ALIAS(make_unique_for_overwrite);
    REX_STD_FUNC_ALIAS(make_shared_for_overwrite);
    REX_STD_FUNC_ALIAS(allocate_shared_for_overwrite);
#endif

#ifdef REX_ENABLE_WITH_CPP23
    template <typename Pointer>
    REX_STD_TEMPLATED_CLASS_ALIAS(allocation_result, Pointer);

    template <typename Smart, typename Pointer, typename ... Args>
    REX_STD_TEMPLATED_CLASS_ALIAS(out_ptr_t, Smart, Pointer, Args...);

    template <typename Smart, typename Pointer, typename ... Args>
    REX_STD_TEMPLATED_CLASS_ALIAS(inout_ptr_t, Smart, Pointer, Args...);

    REX_STD_FUNC_ALIAS(allocate_at_least);

    REX_STD_FUNC_ALIAS(out_ptr);
    REX_STD_FUNC_ALIAS(inout_ptr);
#endif

}

#include "rex_std/enable_std_checking.h"