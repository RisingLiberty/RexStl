// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_constructible.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template<typename T, typename... Args>
    struct is_constructible : public bool_constant<__is_constructible(T, Args...) > {};

    template <typename T, typename ... Args>
    constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T, typename ... Args>
    using IsConstructibleStruct = is_constructible<T, Args...>;

    template <typename T, typename ... Args>
    constexpr bool IsConstructible = IsConstructibleStruct<T, Args...>::value;
#endif
}
