// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: rbegin.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    template <typename C>
    auto rbegin(C& c) -> decltype(c.rbegin())
    {
        return c.rbegin();
    }
    template <typename C>
    auto rbegin(const C& c) -> decltype(c.rbegin())
    {
        return c.rbegin();
    }
    template <typename C>
    auto crbegin(const C& c) -> decltype(c.crbegin())
    {
        return c.crbegin();
    }

REX_RSL_END_NAMESPACE
