// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: remove_pointer.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
    struct remove_pointer
    {
        using type = T;
    };
    template <typename T>
    struct remove_pointer<T*>
    {
        using type = T;
    };
    template <typename T>
    struct remove_pointer<T* const>
    {
        using type = T;
    };
    template <typename T>
    struct remove_pointer<T* volatile>
    {
        using type = T;
    };
    template <typename T>
    struct remove_pointer<T* const volatile>
    {
        using type = T;
    };

    template <typename T>
    using remove_pointer_t = remove_pointer<T>::type;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using RemovePointerStruct = remove_pointer<T>;

    template <typename T>
    using RemovePointer = typename RemovePointerStruct<T>::type;
#endif
}