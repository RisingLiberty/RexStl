// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: forward.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/remove_reference.h"
#include "rex_std/internal/type_traits/is_lvalue_reference.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    constexpr T&& forward(typename rsl::remove_reference_t<T>& x) noexcept
    {
        return static_cast<T&&>(x);
    }

    template <typename T>
    constexpr T&& forward(typename rsl::remove_reference_t<T>&& x) noexcept
    {
        static_assert(!rsl::is_lvalue_reference_v<T>, "forward T isn't lvalue reference");
        return static_cast<T&&>(x);
    }

REX_RSL_END_NAMESPACE
