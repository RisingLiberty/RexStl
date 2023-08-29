// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: move_iterator.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_traits.h"
#include "rex_std/internal/type_traits/conditional.h"
#include "rex_std/internal/type_traits/is_reference.h"
#include "rex_std/internal/type_traits/remove_reference.h"
#include "rex_std/internal/type_traits/conditional.h"
#include "rex_std/internal/utility/move.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename Iter>
    class move_iterator
    {
    private:
      using wrapped_iterator_reference = typename iterator_traits<Iter>::reference;

    public:
      using iterator_type     = Iter;
      using iterator_category = typename iterator_traits<Iter>::iterator_category;
      using value_type        = typename iterator_traits<Iter>::value_type;
      using difference_type   = typename iterator_traits<Iter>::difference_type;
      using pointer           = Iter;
      using reference = conditional_t<is_reference_v<wrapped_iterator_reference>, remove_reference_t<wrapped_iterator_reference>&&, wrapped_iterator_reference>;

      constexpr move_iterator()
        : m_iterator()
      {}
      constexpr explicit move_iterator(iterator_type it)
        : m_iterator(it)
      {}
      template <typename U>
      constexpr explicit move_iterator(const move_iterator<U>& other)
        : m_iterator(other.base())
      {}

      template <typename U>
      constexpr move_iterator& operator=(const move_iterator<U>& other)
      {
        m_iterator = other.base();
        return *this;
      }

      constexpr const iterator_type& base() const
      {
        return m_iterator;
      }

      constexpr reference operator*() const
      {
        return static_cast<reference>(*m_iterator);
      }
      constexpr pointer operator->() const
      {
        return m_iterator;
      }

      constexpr auto operator[](difference_type n) const
      {
        return rsl::move(m_iterator[n]);
      }

      constexpr move_iterator& operator++()
      {
        ++m_iterator;
        return *this;
      }
      constexpr move_iterator& operator--()
      {
        --m_iterator;
        return *this;
      }

      constexpr move_iterator operator++(int)
      {
        move_iterator tmp = *this;
        ++m_iterator;
        return tmp;
      }
      constexpr move_iterator operator--(int)
      {
        move_iterator tmp = *this;
        --m_iterator;
        return tmp;
      }

      constexpr move_iterator operator+(difference_type n) const
      {
        return move_iterator(m_iterator + n);
      }
      constexpr move_iterator operator-(difference_type n) const
      {
        return move_iterator(m_iterator - n);
      }
      constexpr move_iterator& operator+=(difference_type n)
      {
        m_iterator += n;
        return *this;
      }
      constexpr move_iterator& operator-=(difference_type n)
      {
        m_iterator -= n;
        return *this;
      }

    private:
      iterator_type m_iterator;
    };

    template <typename Iterator1, typename Iterator2>
    constexpr bool operator==(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs)
    {
      return lhs.base() == rhs.base();
    }
    template <typename Iterator1, typename Iterator2>
    constexpr bool operator!=(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs)
    {
      return !(lhs == rhs);
    }

    template <typename Iterator1, typename Iterator2>
    constexpr bool operator<(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs)
    {
      return lhs.base() < rhs.base();
    }
    template <typename Iterator1, typename Iterator2>
    constexpr bool operator<=(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs)
    {
      return !(rhs < lhs);
    }
    template <typename Iterator1, typename Iterator2>
    constexpr bool operator>(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs)
    {
      return rhs < lhs;
    }
    template <typename Iterator1, typename Iterator2>
    constexpr bool operator>=(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs)
    {
      return !(lhs < rhs);
    }

    template <typename Iter>
    constexpr move_iterator<Iter> operator+(typename move_iterator<Iter>::difference_type n, const move_iterator<Iter>& it)
    {
      return it + n;
    }

    template <typename Iterator1, typename Iterator2>
    constexpr auto operator-(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs) -> decltype(lhs.base() - rhs.base())
    {
      return lhs.base() - rhs.base();
    }

    template <typename Iter>
    constexpr move_iterator<Iter> make_move_iterator(Iter i)
    {
      return move_iterator<Iter>(i);
    }

  } // namespace v1
} // namespace rsl
