// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: in_place_type.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename T>
struct in_place_type_t
{
  explicit in_place_type_t() = default;
};
template <typename T>
constexpr in_place_type_t in_place {};

REX_RSL_END_NAMESPACE
