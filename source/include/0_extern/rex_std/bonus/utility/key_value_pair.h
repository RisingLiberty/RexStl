// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: key_value_pair.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename Key, typename Value>
struct key_value_pair
{
  using key_type   = Key;
  using value_type = Value;

  Key key;
  Value value;
};

REX_RSL_END_NAMESPACE
