// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_bounded_array.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
    struct is_bounded_array : public false_type
    {};

    template <typename T, size_t N>
    struct is_bounded_array<T[N]> : public true_type
    {};

    template <typename T>
    constexpr bool is_bounded_array_v = is_bounded_array<T>::value;

REX_RSL_END_NAMESPACE
