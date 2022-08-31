// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_pointer_interconvertible_with_class.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename S, typename M>
    constexpr bool is_pointer_interconvertible_with_class(M S::* mp)
    {
        return __is_pointer_interconvertible_with_class(S, M);
    } 
}