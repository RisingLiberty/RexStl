// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: disjunction.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    namespace internal
    {
        template <bool FirstValue, typename First, typename ... Rest>
        struct disjunction
        {
            using type = First;
        };

        template <typename False, typename Next, typename ... Rest>
        struct disjunction<false, False, Next, Rest...>
        {
            using type = typename disjunction<Next::value, Next, Rest...>::type;
        };
    }

    template <typename ... Traits>
    struct disjunction : false_type {};

    template <typename First, typename ... Rest>
    struct disjunction<First, Rest...> : internal::disjunction<First::value, First, Rest...>::type {};

    template <typename ... Traits>
    constexpr bool disjunction_t = disjunction<Traits>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename ... Traits>
    using DisjunctionStruct = disjunction<Traits...>;

    template <typename ... Traits>
    using Disjunction = typename DisjunctionStruct<Traits...>::type;
#endif
}
