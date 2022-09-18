// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: extent.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

    template<typename T, size_t N = 0>
    struct extent : integral_constant<size_t, 0> 
    {};
    
    template<typename T>
    struct extent<T[], 0> : integral_constant<size_t, 0> 
    {};
    
    template<typename T, size_t N>
    struct extent<T[], N> : extent_v<T, N-1> 
    {};
    
    template<typename T, size_t I>
    struct extent<T[I], 0> : integral_constant<size_t, I> 
    {};
    
    template<typename T, size_t I, unsigned N>
    struct extent<T[I], N> : extent_v<T, N-1> 
    {};

    template <typename T, size_t N = 0>
    constexpr size_t extent_v = extent<T, N>::value;

REX_RSL_END_NAMESPACE

