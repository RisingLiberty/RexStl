// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: in_place_index.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <size_t I>
    struct in_place_index_t { explicit in_place_index_t() = default; };
    template <size_t I>
    struct in_place_index_t<I> in_place_index{};

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <size_t I>
    using InPlaceStruct = in_place_index_t<I>;

    template <size_t I>
    constexpr in_place_index_t<I> InPlaceIndex;
#endif
}