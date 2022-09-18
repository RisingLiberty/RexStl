// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: piecewise_construct.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

    struct piecewise_construct_t 
    { 
        explicit piecewise_construct_t() = default; 
    };

    constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();

REX_RSL_END_NAMESPACE
