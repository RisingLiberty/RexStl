// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: type_identity.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct type_identity
    {
        using type = T;
    };

    template <typename T>
    using type_identity_t = typename type_identity<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using TypeIdentityStruct = type_identity<T>;

    template <typename T>
    using TypeIdentity = typename type_identity<T>::type;
#endif
}
