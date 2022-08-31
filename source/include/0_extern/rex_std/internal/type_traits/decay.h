// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: decay.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/remove_reference.h"
#include "rex_std/internal/type_traits/conditional.h"
#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/type_traits/is_function.h"
#include "rex_std/internal/type_traits/add_pointer.h"
#include "rex_std/internal/type_traits/remove_cv.h"
#include "rex_std/internal/type_traits/remove_extent.h"

namespace rsl
{
    template <typename T>
    struct decay
    {
    private:
        using U = remove_reference_t<T>;
    public:
        using type = conditional_t<
        is_array_v<U>, typename remove_extent_t<U>*,
        typename conditional_t<is_function_v<U>, add_pointer_t<U>,
        remove_cv_t<U>>>;
    };

    template <typename T>
    using decay_t = decay<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using DecayStruct = decay<T>;

    template <typename T>
    using Decay = typename DecayStruct<T>::type;
#endif
}