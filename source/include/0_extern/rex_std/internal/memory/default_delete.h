// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: default_delete.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_convertible.h"

namespace rsl
{
    template <typename T>
    struct default_delete
    {
    public:
        constexpr default_delete() = default;
        template <typename T2, enable_if_t<is_convertible_v<T2*, T*>, bool> = true>
        constexpr default_delete(const default_delete<T2>&)
        {}

        constexpr void operator()(T* ptr) const
        {
            static_assert(sizeof(T) > 0, "can't delete an incomplete type");
            delete ptr;
        }
    };

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using DefaultDelete = default_delete<T>;
#endif
}