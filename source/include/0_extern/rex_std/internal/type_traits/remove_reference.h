// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_reference.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T> struct remove_reference { using type = T; };
    template <typename T> struct remove_reference<T&> { using type = T; };
    template <typename T> struct remove_reference<T&&> { using type = T; };

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using RemoveReferenceStruct = remove_reference<T>;

    template <typename T>
    using RemoveReference = typename remove_reference<T>::type;
#endif
}
