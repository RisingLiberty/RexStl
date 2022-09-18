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

REX_RSL_BEGIN_NAMESPACE

    template <typename T>
	struct is_pod : public bool_constant<__is_pod(T)>
    {};

    template <typename T>
    constexpr bool is_pod_v = is_pod<T>::value;

REX_RSL_END_NAMESPACE
