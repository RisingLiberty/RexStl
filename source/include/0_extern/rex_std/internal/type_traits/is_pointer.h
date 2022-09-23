// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_pointer.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/type_and.h"
#include "rex_std/bonus/type_traits/type_not.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_member_pointer.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_pointer : public false_type
{
};

template <typename T>
struct is_pointer<T*> : public true_type
{
};
template <typename T>
struct is_pointer<T* const> : public true_type
{
};
template <typename T>
struct is_pointer<T* volatile> : public true_type
{
};
template <typename T>
struct is_pointer<T* const volatile> : public true_type
{
};

template <typename T>
constexpr bool is_pointer_v = is_pointer<T>::value;

REX_RSL_END_NAMESPACE
