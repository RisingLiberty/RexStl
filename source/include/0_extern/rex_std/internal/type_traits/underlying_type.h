// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: underlying_type.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/is_enum.h"

namespace rsl
{
    namespace internal
    {
        template <typename T, bool = is_enum_v<T>>
        struct UnderlyingTypeHelper
        {
            using type = __underlying_type(T);
        };

        template <typename T>
        struct UnderlyingTypeHelper<T, false>
        {};
    }
    template <typename T>
    struct underlying_type : internal::UnderlyingTypeHelper<T>
    {};

    template <typename T>
    using underlying_type_t = typename underlying_type<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using UnderlyingTypeStruct = underlying_type_t<T>;

    template <typename T>
    using UnderlyingType = typename underlying_type<T>::type;
#endif
}