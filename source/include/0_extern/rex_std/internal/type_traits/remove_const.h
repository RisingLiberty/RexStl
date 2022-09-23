// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: remove_const.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct remove_const
{
  using type = T;
};

template <typename T>
struct remove_const<const T>
{
  using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

REX_RSL_END_NAMESPACE
