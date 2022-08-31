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

namespace rsl
{
    struct piecewise_construct_t 
    { 
        explicit piecewise_construct_t() = default; 
    };

    constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    using PiecewiseConstructStruct = piecewise_construct_t;

    constexpr piecewise_construct_t PiecewiseConstruct;
#endif

}
