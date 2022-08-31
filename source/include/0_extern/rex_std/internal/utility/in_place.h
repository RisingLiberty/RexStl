// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: in_place.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    struct in_place_t { explicit in_place_t() = default; };
    constexpr in_place_t in_place{};

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    using in_placeStruct = in_place_t;

    constexpr in_place_t InPlace;
#endif
}