// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: node_iterator_base.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/hashtable/hash_node.h"

REX_RSL_BEGIN_NAMESPACE

  template <typename Value>
  class node_iterator_base
  {
  public:
    using node_type = hash_node<Value>;

    node_iterator_base(node_type* node)
      : m_node(node)
    {}

    void increment()
    {
      m_node = m_node->next;
    }

  protected:
    node_type* node()
    {
      return m_node;
    }
    
  private:
    node_type* m_node;
  };

REX_RSL_END_NAMESPACE