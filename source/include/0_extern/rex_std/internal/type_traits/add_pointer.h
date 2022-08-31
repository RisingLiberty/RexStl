// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: add_pointer.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/void.h"
#include "rex_std/internal/type_traits/remove_reference.h"

namespace rsl
{
    namespace internal
    {
        template <typename T, typename = void>
        struct add_pointer_impl
        {
            using type = T;
        };
        template <typename T>
        struct add_pointer_impl<T, void_t<remove_reference_t<T>*>>
        {
            using type = remove_reference_t<T>*;
        };
    }

    template <typename T>
    struct add_pointer
    {
        using type = typename internal::add_pointer_impl<T>::type;
    };

    template <typename T>
    using add_pointer_t = add_pointer<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using AddPointerStruct = add_pointer<T>;

    template <typename T>
    using AddPointer = typename AddPointerStruct<T>::type;
#endif
}