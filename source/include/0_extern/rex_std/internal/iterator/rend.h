// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: rend.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template <typename C>
    auto rend(C& c) -> decltype(c.rend())
    {
        return c.rend();
    }
    template <typename C>
    auto rend(const C& c) -> decltype(c.rend())
    {
        return c.rend();
    }
    template <typename C>
    auto crend(const C& c) -> decltype(c.crend())
    {
        return c.crend();
    }

REX_RSL_END_NAMESPACE
