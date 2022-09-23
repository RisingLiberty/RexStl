// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: remove_cv.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct remove_cv
{
  using type = T;
  template <template <typename> typename Fn>
  using apply = Fn<T>;
};

template <typename T>
struct remove_cv<const T>
{
  using type = T;

  template <template <typename> typename Fn>
  using apply = const Fn<T>;
};

template <typename T>
struct remove_cv<volatile T>
{
  using type = T;
};

template <typename T>
struct remove_cv<const volatile T>
{
  using type = T;
};

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

REX_RSL_END_NAMESPACE
