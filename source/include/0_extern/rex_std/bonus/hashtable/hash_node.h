// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash_node.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename Value>
struct hash_node
{
  hash_node()                 = default;
  hash_node(const hash_node&) = default;
  hash_node(hash_node&&)      = default;

  Value value;
  hash_node* next;
};

REX_RSL_END_NAMESPACE