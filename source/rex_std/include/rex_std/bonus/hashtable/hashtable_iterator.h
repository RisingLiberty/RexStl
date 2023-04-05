// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hashtable_iterator.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/hashtable/hash_node.h"
#include "rex_std/bonus/type_traits/type_select.h"
#include "rex_std/bonus/types.h"
#include "rex_std/internal/iterator/distance.h"
#include "rex_std/internal/iterator/iterator_tags.h"
#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename KeyValPair>
    class const_hashtable_iterator;

    template <typename KeyValPair>
    class hashtable_iterator
    {
    public:
      using this_type         = hashtable_iterator<KeyValPair>;
      using node_type         = hash_node<KeyValPair>;
      using value_type        = KeyValPair;
      using pointer           = KeyValPair*;
      using reference         = KeyValPair&;
      using difference_type   = ptrdiff;
      using iterator_category = forward_iterator_tag;

      explicit hashtable_iterator(node_type* node = nullptr, node_type** bucket = nullptr)
          : m_node(node)
          , m_bucket(bucket)
      {
      }
      explicit hashtable_iterator(node_type** bucket)
          : m_node(*bucket)
          , m_bucket(bucket)
      {
      }

      reference operator*() const
      {
        return m_node->value;
      }
      pointer operator->() const
      {
        return m_node ? &m_node->value : nullptr;
      }
      hashtable_iterator& operator++()
      {
        increment();
        return *this;
      }
      hashtable_iterator operator++(int)
      {
        hashtable_iterator temp(*this);
        increment();
        return temp;
      }
      pointer node()
      {
        return m_node ? &m_node->value : nullptr;
      }
      node_type* hash_node()
      {
        return m_node;
      }
      node_type** bucket()
      {
        return m_bucket;
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

    private:
      void increment()
      {
        m_node = m_node->next;

        while(m_node == nullptr)
        {
          m_node = *++m_bucket;
        }
      }

    private:
      node_type* m_node;
      node_type** m_bucket;
    };

    template <typename T>
    bool operator==(hashtable_iterator<T> lhs, hashtable_iterator<T> rhs)
    {
      return lhs.node() == rhs.node();
    }
    template <typename T>
    bool operator!=(hashtable_iterator<T> lhs, hashtable_iterator<T> rhs)
    {
      return !(lhs == rhs);
    }

    template <typename KeyValPair>
    class const_hashtable_iterator
    {
    public:
      using this_type         = const_hashtable_iterator<KeyValPair>;
      using node_type         = hash_node<KeyValPair>;
      using value_type        = KeyValPair;
      using pointer           = const KeyValPair*;
      using reference         = const KeyValPair&;
      using difference_type   = ptrdiff;
      using iterator_category = forward_iterator_tag;

      explicit const_hashtable_iterator(const node_type* node = nullptr, node_type** bucket = nullptr)
          : m_node(node)
          , m_bucket(bucket)
      {
      }
      explicit const_hashtable_iterator(node_type** bucket)
          : m_node(*bucket)
          , m_bucket(bucket)
      {
      }
      const_hashtable_iterator(hashtable_iterator<KeyValPair> it)
          : m_node(it.hash_node())
          , m_bucket(it.bucket())
      {
      }

      reference operator*() const
      {
        return m_node->value;
      }
      pointer operator->() const
      {
        return m_node ? &m_node->value : nullptr;
      }
      const_hashtable_iterator& operator++()
      {
        increment();
        return *this;
      }
      const_hashtable_iterator operator++(int)
      {
        hashtable_iterator temp(*this);
        increment();
        return temp;
      }
      pointer node()
      {
        return m_node ? &m_node->value : nullptr;
      }
      node_type* hash_node()
      {
        return m_node;
      }
      const node_type** bucket()
      {
        return m_bucket;
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

    private:
      void increment()
      {
        m_node = m_node->next;

        while(m_node == nullptr)
        {
          m_node = *++m_bucket;
        }
      }

    private:
      const node_type* m_node;
      node_type** m_bucket;
    };

    template <typename T>
    bool operator==(const_hashtable_iterator<T> lhs, const_hashtable_iterator<T> rhs)
    {
      return lhs.node() == rhs.node();
    }
    template <typename T>
    bool operator!=(const_hashtable_iterator<T> lhs, const_hashtable_iterator<T> rhs)
    {
      return !(lhs == rhs);
    }
    template <typename T>
    bool operator==(hashtable_iterator<T> lhs, const_hashtable_iterator<T> rhs)
    {
      return lhs.node() == rhs.node();
    }
    template <typename T>
    bool operator==(const_hashtable_iterator<T> lhs, hashtable_iterator<T> rhs)
    {
      return lhs.node() == rhs.node();
    }
    template <typename T>
    bool operator!=(hashtable_iterator<T> lhs, const_hashtable_iterator<T> rhs)
    {
      return !(lhs == rhs);
    }
    template <typename T>
    bool operator!=(const_hashtable_iterator<T> lhs, hashtable_iterator<T> rhs)
    {
      return !(lhs == rhs);
    }

    namespace internal
    {
      template <typename Iterator>
      typename iterator_traits<Iterator>::difference_type distance_fw_impl(Iterator first, Iterator last, input_iterator_tag /*unused*/)
      {
        return 0;
      }
      template <typename Iterator>
      typename iterator_traits<Iterator>::difference_type distance_fw_impl(Iterator first, Iterator last, forward_iterator_tag /*unused*/)
      {
        return distance(first, last);
      }

      template <typename Iterator>
      typename iterator_traits<Iterator>::difference_type ht_distance(Iterator first, Iterator last)
      {
        using IC = typename iterator_traits<Iterator>::iterator_category;
        return distance_fw_impl(first, last, IC());
      }
    } // namespace internal

  } // namespace v1
} // namespace rsl