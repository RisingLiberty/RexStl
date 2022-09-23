// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_class.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_class : public bool_constant<__is_class(T)>
{
};

template <typename T>
constexpr bool is_class_v = is_class<T>::value;

REX_RSL_END_NAMESPACE
