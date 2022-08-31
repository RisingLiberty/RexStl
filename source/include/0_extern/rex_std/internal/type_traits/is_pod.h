// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: is_pod.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
    template <typename T>
	struct is_pod : public bool_constant<__is_pod(T)>
    {};

    template <typename T>
    constexpr bool is_pod_v = is_pod<T>::value;

#ifdef REX_USE_REX_CODING_GUIDELINES_FOR_RSL
    template <typename T>
    using IsPodStruct = is_pod<T>;

    template <typename T>
    constexpr bool IsPod = is_pod<T>::value;
#endif
}