// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: back_insert_iterator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

//-----------------------------------------------------------------------------
// https://en.cppreference.com/w/cpp/iterator/back_insert_iterator
//
// Appends elements to a container for which it was constructed.
//-----------------------------------------------------------------------------

#pragma once

#include "rex_std/bonus/types.h"

#include "rex_std/internal/iterator/iterator_tags.h"

REX_RSL_BEGIN_NAMESPACE

  template <typename Container>
  class back_insert_iterator
  {
  public:
    using iterator_category = output_iterator_tag;
    using value_type = void;
    using difference_type = ptrdiff;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    constexpr back_insert_iterator()
      : m_container(nullptr)
    {}

    constexpr back_insert_iterator(Container& c)
      : m_container(&c)
    {}

    constexpr back_insert_iterator& operator=(const typename Container::value_type& value)
    {
      m_container->push_back(value);

      return *this;
    }
    constexpr back_insert_iterator& operator=(typename Container::value_type&& value)
    {
      m_container->push_back(rsl::move(value));
      
      return *this;
    }

    constexpr back_insert_iterator& operator*()
    {
      return *this;
    }
    
    constexpr back_insert_iterator& operator++()
    {
      return *this;
    }
    constexpr back_insert_iterator& operator++(int)
    {
      return *this;
    }

  private:
    Container* m_container;
  };

REX_RSL_END_NAMESPACE