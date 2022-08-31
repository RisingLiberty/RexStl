// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: reverse_iterator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

/// [21/Aug/2022] RSL Comment: deprecate this file

namespace rsl
{
    template <typename It>
    class reverse_iterator
    {
    public:
        using iterator_type = It;

        using value_type = typename iterator_type::value_type;
        using pointer = typename iterator_type::pointer;
        using const_pointer = typename iterator_type::const_pointer;
        using reference = typename iterator_type::reference;
        using const_reference = typename iterator_type::const_reference;
        using iterator_category = typename iterator_type::iterator_category;
        using difference_type = typename iterator_type::difference_type;

        constexpr reverse_iterator(It base_iterator)
            : m_base_iterator(base_iterator)
        {}

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
            return *(this + index);
        }
        constexpr const_reference operator[](card32 index) const
        {
            return *(this + index);
        }

        constexpr bool operator==(const reverse_iterator other) const
        {
            return m_base_iterator == other.m_base_iterator;
        }
        constexpr bool operator!=(const reverse_iterator other) const
        {
            return m_base_iterator != other.m_base_iterator;
        }

        constexpr bool operator<(const reverse_iterator other) const
        {
            return m_base_iterator < other.m_base_iterator;
        }
        constexpr bool operator<=(const reverse_iterator other) const
        {
            return m_base_iterator <= other.m_base_iterator;
        }
        constexpr bool operator>(const reverse_iterator other) const
        {
            return m_base_iterator > other.m_base_iterator;
        }
        constexpr bool operator>=(const reverse_iterator other) const
        {
            return m_base_iterator >= other.m_base_iterator;
        }

    private:
        It m_base_iterator;
    };
}
