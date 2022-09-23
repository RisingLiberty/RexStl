// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: type_not_equal.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <int b1, int b2>
struct type_not_equal
{
  static const bool value = (b1 != b2);
};

REX_RSL_END_NAMESPACE
