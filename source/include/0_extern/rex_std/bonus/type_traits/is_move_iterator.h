//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: is_move_iterator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/move_iterator.h"
#include "rex_std/internal/type_traits/integral_constant.h"

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct is_move_iterator : public false_type
{
};

template <typename Iterator>
struct is_move_iterator<move_iterator<Iterator>> : public true_type
{
};

template <typename T>
inline constexpr bool is_move_iterator_v = is_move_iterator<T>::value;

REX_RSL_END_NAMESPACE
