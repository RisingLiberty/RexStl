// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_union.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_union : public bool_constant<__is_union(T)>
{
};

template <typename T>
inline constexpr bool is_union_v = is_union<T>::value;

REX_RSL_END_NAMESPACE
