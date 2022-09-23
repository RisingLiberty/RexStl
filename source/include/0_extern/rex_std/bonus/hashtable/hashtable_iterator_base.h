// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hashtable_iterator_base.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

template <typename Value>
class hashtable_iterator_base
{
public:
  using this_type = hashtable_iterator_base<Value>;
  using node_type = hash_node<Value>;

  hashtable_iterator_base(node_type* node, node_type** bucket)
      : m_node(node)
      , m_bucket(bucket)
  {
  }

  void increment_bucket()
  {
    ++m_bucket;
    while(*m_bucket == nullptr)
    {
      ++m_bucket;
    }
    m_node = *m_bucket;
  }

protected:
  node_type* node()
  {
    return m_node;
  }
  node_type** bucket()
  {
    return m_bucket;
  }

private:
  node_type* m_node;
  node_type** m_bucket;
};

REX_RSL_END_NAMESPACE