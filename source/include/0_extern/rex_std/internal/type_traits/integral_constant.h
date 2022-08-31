// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: internal_constant.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/attributes.h"

namespace rsl
{
    template <typename T, T Val>
    struct integral_constant
    {
        using value_type = T;
        using type = integral_constant;

        static constexpr value_type value = Val;

        constexpr operator value_type() const
        {
            return value;
        }

        REX_NO_DISCARD constexpr value_type operator()() const
        {
            return value;
        }
    };

    template <bool Val>
    using bool_constant = integral_constant<bool, Val>;

    using true_type = bool_constant<true>;
    using false_type = bool_constant<false>;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T, T Val>
    using IntegralConstant = integral_constant<T, Val>;

    template <bool Val>
    using BoolConstant = integral_constant<bool, Val>;

    using TrueType = true_type;
    using FalseType = false_type;
#endif
}