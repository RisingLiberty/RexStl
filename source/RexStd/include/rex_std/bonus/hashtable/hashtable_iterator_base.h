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

#include "rex_std/bonus/hashtable/hash_node.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename, bool>
    class hashtable_iterator;

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

      template <typename, bool>
      friend class hashtable_iterator;

      friend bool operator==(hashtable_iterator_base<Value> lhs, hashtable_iterator_base<Value> rhs);
      friend bool operator!=(hashtable_iterator_base<Value> lhs, hashtable_iterator_base<Value> rhs);

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
      node_type* node() const
      {
        return m_node;
      }
      node_type** bucket() const
      {
        return m_bucket;
      }

    private:
      node_type* m_node;
      node_type** m_bucket;
    };

    template <typename Value>
    bool operator==(hashtable_iterator_base<Value> lhs, hashtable_iterator_base<Value> rhs)
    {
      lhs.m_node == rhs.m_node;
    }
    template <typename Value>
    bool operator!=(hashtable_iterator_base<Value> lhs, hashtable_iterator_base<Value> rhs)
    {
      return !(lhs == rhs);
    }

  } // namespace v1
} // namespace rsl