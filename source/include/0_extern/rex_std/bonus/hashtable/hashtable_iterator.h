// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hashtable_iterator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/hashtable/hashtable_iterator_base.h"
#include "rex_std/bonus/type_traits/type_select.h"

REX_RSL_BEGIN_NAMESPACE

template <typename Value, bool IsConst>
class hashtable_iterator : public hashtable_iterator_base<Value>
{
public:
  using base_type           = hashtable_iterator_base<Value>;
  using this_type           = hashtable_iterator<Value, IsConst>;
  using this_type_non_const = using hashtable_iterator<Value, false>;
  using node_type           = typename base_type::node_type;
  using value_type          = Value;
  using pointer             = typename type_select<IsConst, const Value*, Value*>::type;
  using reference           = typename type_select<IsConst, const Value&, Value&>::type;
  using difference_type     = ptrdiff_t;
  using iterator_category   = forward_iterator_tag;

  hashtable_iterator(node_type* node = nullptr, node_type** bucket = nullptr)
      : base_type(node, bucket)
  {
  }
  hashtable_iterator(node_type** bucket)
      : base_type(*bucket, bucket)
  {
  }
  hashtable_iterator(const this_type_non_const& other)
      : base_type(other.m_node, other.m_bucket)
  {
  }

  reference operator*() const
  {
    return base_type::node()->value();
  }
  pointer operator->() const
  {
    return &(base_type::node()->value());
  }
  hashtable_iterator& operator++()
  {
    base_type::increment();
    return *this;
  }
  hashtable_iterator operator++(int)
  {
    hashtable_iterator temp(*this);
    base_type::increment();
    return temp;
  }
  node_type* node()
  {
    return base_type::node();
  }
  node_type** bucket()
  {
    return base_type::bucket();
  }
};

REX_RSL_END_NAMESPACE