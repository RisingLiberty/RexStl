// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: conjunction.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/integral_constant.h"

namespace rsl
{
    namespace internal
    {
        // handle false trait or last trait
        template <bool FirstValue, typename First, typename... Rest>
        struct ConjunctionHelperStruct
        {
            using type = First;
        };

        // the first trait is true, try the next one
        template <typename True, typename Next, typename ... Rest>
        struct ConjunctionHelperStruct<true, True, Next, Rest...>
        { 
            using type = typename ConjunctionHelperStruct<Next::value, Next, Rest...>::type;
        };
    }

    template <typename... Traits>
    struct conjunction : true_type {}; // If _Traits is empty, true_type

    template <typename First, typename... Rest>
    struct conjunction<First, Rest...> : internal::ConjunctionHelperStruct<First::value, First, Rest...>::type
    { };

    template <typename ... Traits>
    constexpr bool conjunction_v = conjunction<Traits...>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename ... Traits>
    using ConjunctionStruct = conjunction<Traits...>;

    template <typename ... Traits>
    constexpr bool Conjunction = ConjunctionStruct<Traits...>::value;
#endif    
}
