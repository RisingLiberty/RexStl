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

REX_RSL_BEGIN_NAMESPACE

template <typename T, typename... Args>
struct is_constructible : public bool_constant<__is_constructible(T, Args...)>
{
};

template <typename T, typename... Args>
constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

REX_RSL_END_NAMESPACE
