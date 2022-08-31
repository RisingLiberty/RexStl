// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: forward_iterator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_tags.h"

/// [21/Aug/2022] RSL Comment: deprecate this file

namespace rsl
{
    template <typename T>
    class ForwardIterator
    {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using iterator_category = rsl::forward_iterator_tag;
        using difference_type = int32;

        constexpr ForwardIterator(pointer value = nullptr)
            : m_value(value)
        {}

        constexpr reference operator*()
        {
            return *m_value;
        }
        constexpr pointer operator->()
        {
            return m_value;
        }

        constexpr const_reference operator*() const
        {
            return *m_value;
        }
        constexpr const_pointer operator->() const
        {
            return m_value;
        }

        constexpr bool operator==(const ForwardIterator other) const
        {
            return m_value == other.m_value;
        }
        constexpr bool operator!=(const ForwardIterator other) const
        {
            return m_value != other.m_value;
        }

        constexpr bool operator<(const ForwardIterator other) const
        {
            return m_value < other.m_value;
        }
        constexpr bool operator<=(const ForwardIterator other) const
        {
            return m_value <= other.m_value;
        }
        constexpr bool operator>(const ForwardIterator other) const
        {
            return m_value > other.m_value;
        }
        constexpr bool operator>=(const ForwardIterator other) const
        {
            return m_value >= other.m_value;
        }

        constexpr ForwardIterator operator++()
        {
            ++m_value;
            return *this;
        }
        constexpr ForwardIterator operator++(int)
        {
            ForwardIterator tmp = *this;
            operator++();
            return tmp;
        }

    private:
        pointer m_value;
    };

    template <typename T>
    class ConstForwardIterator
    {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = const T&;
        using const_reference = const T&;
        using iterator_category = rsl::forward_iterator_tag;
        using difference_type = int32;

        constexpr ConstForwardIterator(pointer value = nullptr)
            : m_value(value)
        {}

        constexpr const_reference operator*() const
        {
            return *m_value;
        }
        constexpr const_pointer operator->() const
        {
            return m_value;
        }

        constexpr bool operator==(const ConstForwardIterator other) const
        {
            return m_value == other.m_value;
        }
        constexpr bool operator!=(const ConstForwardIterator other) const
        {
            return m_value != other.m_value;
        }

        constexpr bool operator<(const ConstForwardIterator other) const
        {
            return m_value < other.m_value;
        }
        constexpr bool operator<=(const ConstForwardIterator other) const
        {
            return m_value <= other.m_value;
        }
        constexpr bool operator>(const ConstForwardIterator other) const
        {
            return m_value > other.m_value;
        }
        constexpr bool operator>=(const ConstForwardIterator other) const
        {
            return m_value >= other.m_value;
        }

        constexpr ConstForwardIterator operator++()
        {
            ++m_value;
            return *this;
        }
        constexpr ConstForwardIterator operator++(int)
        {
            ConstForwardIterator tmp = *this;
            operator++();
            return tmp;
        }

    private:
        pointer m_value;
    };
}
