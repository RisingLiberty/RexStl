// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: destroy_at.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/memory/addressof.h"

namespace rsl
{
    template<typename T>
    constexpr void destroy_at(T* p)
    {
        if constexpr (rsl::is_array_v<T>)
        {
            for (auto& elem : *p)
            {
                rsl::destroy_at(rsl::addressof(elem));
            }
        }
        else
        {
            p->~T();
        }
    }
}
