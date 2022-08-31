// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: in_place_type.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct in_place_type_t { explicit in_place_type_t() = default; };
    template <typename T>
    constexpr in_place_type_t in_place{};

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <size_t I>
    using InPlaceStruct = in_place_type_t<I>;

    template <size_t I>
    constexpr in_place_type_t<I> InPlace;
#endif
}