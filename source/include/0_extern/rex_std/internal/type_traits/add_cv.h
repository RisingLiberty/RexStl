// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: add_cv.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/add_const.h"
#include "rex_std/internal/type_traits/add_volatile.h"

namespace rsl
{
    template <typename T>
    struct add_cv
    {
        using type = add_const_t<add_volatile_t<T>>;
    };

    template <typename T>
    using add_cv_t = add_cv<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using AddCVStruct = add_cv<T>;

    template <typename T>
    using AddCV = typename AddCVStruct<T>::type;
#endif
}