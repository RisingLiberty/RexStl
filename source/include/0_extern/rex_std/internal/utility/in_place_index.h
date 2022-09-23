// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: in_place_index.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <size_t I>
struct in_place_index_t
{
  explicit in_place_index_t() = default;
};
template <size_t I>
struct in_place_index_t<I> in_place_index
{
};

REX_RSL_END_NAMESPACE
