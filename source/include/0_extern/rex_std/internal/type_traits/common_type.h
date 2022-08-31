// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: common_type.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/decay.h"
#include "rex_std/internal/type_traits/void.h"

namespace rsl
{
    template <typename ... T>
    struct common_type;

    template <typename ... T>
    using common_type_t = typename common_type<T...>::type;

    template<>
    struct common_type<> 
    {};

    template <typename T1>
    struct common_type<T1> : common_type_t<T1, T1>{};

    namespace internal
    {
        template <typename T1, typename T2, typename Decayed1 = decay_t<T1>, typename Decayed2 = decay_t<T2>>
        struct CommonType2 : common_type<Decayed1, Decayed2>
        {
        };

        template <typename T1, typename T2>
        struct CommonType2<T1, T2> : CommonType2<T1, T2>
        {
        };

        template <typename void_t, typename T1, typename T2, typename... Rest>
        struct CommonType3
        {
        };

        template <typename T1, typename T2, typename... Rest>
        struct CommonType3<void_t<common_type_t<T1, T2>>, T1, T2, Rest...> : common_type<common_type_t<T1, T2>, Rest...>
        {
        };
    }

    template <typename T1, typename T2, typename ... Rest>
    struct common_type<T1, T2, Rest...> : internal::CommonType3<void, T1, T2, Rest...>
    {};

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using CommonTypeStruct = common_type<T>;

    template <typename T>
    using CommonType = typename CommonTypeStruct<T>::type;
#endif
}