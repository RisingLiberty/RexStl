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

REX_RSL_BEGIN_NAMESPACE

    struct in_place_t { explicit in_place_t() = default; };
    constexpr in_place_t in_place{};

REX_RSL_END_NAMESPACE
