// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: reverse_iterator.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/type_traits/void.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename Iter>
    class reverse_iterator
    {
    public:
      using iterator_type = Iter;

      using value_type        = typename iterator_traits<iterator_type>::value_type;
      using pointer           = typename iterator_traits<iterator_type>::pointer;
      using const_pointer     = typename iterator_traits<iterator_type>::const_pointer;
      using reference         = typename iterator_traits<iterator_type>::reference;
      using const_reference   = typename iterator_traits<iterator_type>::const_reference;
      using iterator_category = typename iterator_traits<iterator_type>::iterator_category;
      using difference_type   = typename iterator_traits<iterator_type>::difference_type;

      constexpr explicit reverse_iterator(Iter baseIterator)
          : m_base_iterator(baseIterator)
      {
      }

      constexpr iterator_type base() const
      {
        return m_base_iterator;
      }

      constexpr reference operator*()
      {
        iterator_type tmp = m_base_iterator;
        return *--tmp;
      }
      constexpr const_reference operator*() const
      {
        iterator_type tmp = m_base_iterator;
        return *--tmp;
      }
      constexpr pointer operator->()
      {
        iterator_type tmp = m_base_iterator;
        --tmp;
        return tmp.operator->();
      }
      constexpr const_pointer operator->() const
      {
        iterator_type tmp = m_base_iterator;
        --tmp;
        return tmp.operator->();
      }

      constexpr reverse_iterator operator++()
      {
        --m_base_iterator;
        return *this;
      }
      constexpr reverse_iterator operator++(int)
      {
        reverse_iterator tmp = *this;
        --m_base_iterator;
        return *tmp;
      }

      constexpr reverse_iterator operator--()
      {
        ++m_base_iterator;
        return *this;
      }
      constexpr reverse_iterator operator--(int)
      {
        reverse_iterator tmp = *this;
        ++m_base_iterator;
        return tmp;
      }

      constexpr reverse_iterator operator+(card32 index) const
      {
        return reverse_iterator(m_base_iterator - index);
      }
      constexpr reverse_iterator& operator+=(card32 index)
      {
        m_base_iterator -= index;
        return *this;
      }

      constexpr reverse_iterator operator-(card32 index) const
      {
        return reverse_iterator(m_base_iterator + index);
      }
      constexpr reverse_iterator& operator-=(card32 index)
      {
        m_base_iterator += index;
        return *this;
      }
      constexpr difference_type operator-(reverse_iterator it) const
      {
        return it.base() - base();
      }

      constexpr reference operator[](card32 index)
      {
        return *(*this + index);
      }
      constexpr const_reference operator[](card32 index) const
      {
        return *(*this + index);
      }

    private:
      Iter m_base_iterator;
    };

    template <typename It1, typename It2>
    constexpr bool operator==(const reverse_iterator<It1> lhs, const reverse_iterator<It2> rhs)
    {
      return lhs.base() == rhs.base();
    }
    template <typename It1, typename It2>
    constexpr bool operator!=(const reverse_iterator<It1> lhs, const reverse_iterator<It2> rhs)
    {
      return lhs.base() != rhs.base();
    }

    template <typename It1, typename It2>
    constexpr bool operator<(const reverse_iterator<It1> lhs, const reverse_iterator<It2> rhs)
    {
      return lhs.base() < rhs.base();
    }
    template <typename It1, typename It2>
    constexpr bool operator<=(const reverse_iterator<It1> lhs, const reverse_iterator<It2> rhs)
    {
      return lhs.base() <= rhs.base();
    }
    template <typename It1, typename It2>
    constexpr bool operator>(const reverse_iterator<It1> lhs, const reverse_iterator<It2> rhs)
    {
      return lhs.base() > rhs.base();
    }
    template <typename It1, typename It2>
    constexpr bool operator>=(const reverse_iterator<It1> lhs, const reverse_iterator<It2> rhs)
    {
      return lhs.base() >= rhs.base();
    }

  } // namespace v1
} // namespace rsl
