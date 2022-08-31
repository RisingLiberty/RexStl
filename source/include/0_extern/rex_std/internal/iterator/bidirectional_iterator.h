// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: bidirectional_iterator.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/iterator/iterator_tags.h"

/// [21/Aug/2022] RSL Comment: deprecate this file

namespace rsl
{
    template <typename T>
    class BiDirectionalIterator
    {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using iterator_category = rsl::bidirectional_iterator_tag;
        using difference_type = int32;

        constexpr BiDirectionalIterator(pointer value = nullptr)
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

        constexpr bool operator==(const BiDirectionalIterator other) const
        {
            return m_value == other.m_value;
        }
        constexpr bool operator!=(const BiDirectionalIterator other) const
        {
            return m_value != other.m_value;
        }

        constexpr bool operator<(const BiDirectionalIterator other) const
        {
            return m_value < other.m_value;
        }
        constexpr bool operator<=(const BiDirectionalIterator other) const
        {
            return m_value <= other.m_value;
        }
        constexpr bool operator>(const BiDirectionalIterator other) const
        {
            return m_value > other.m_value;
        }
        constexpr bool operator>=(const BiDirectionalIterator other) const
        {
            return m_value >= other.m_value;
        }

        constexpr BiDirectionalIterator operator++()
        {
            ++m_value;
            return *this;
        }
        constexpr BiDirectionalIterator operator++(int)
        {
            BiDirectionalIterator tmp = *this;
            operator++();
            return tmp;
        }

        constexpr BiDirectionalIterator operator--()
        {
            m_value--;
            return *this;
        }
        constexpr BiDirectionalIterator operator--(int)
        {
            BiDirectionalIterator tmp = *this;
            operator--();
            return tmp;
        }

    private:
        pointer m_value;
    };

    template <typename T>
    class ConstBiDirectionalIterator
    {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = const T&;
        using const_reference = const T&;
        using iterator_category = rsl::bidirectional_iterator_tag;
        using difference_type = int32;

        constexpr ConstBiDirectionalIterator(pointer value = nullptr)
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

        constexpr bool operator==(const ConstBiDirectionalIterator other) const
        {
            return m_value == other.m_value;
        }
        constexpr bool operator!=(const ConstBiDirectionalIterator other) const
        {
            return m_value != other.m_value;
        }

        constexpr bool operator<(const ConstBiDirectionalIterator other) const
        {
            return m_value < other.m_value;
        }
        constexpr bool operator<=(const ConstBiDirectionalIterator other) const
        {
            return m_value <= other.m_value;
        }
        constexpr bool operator>(const ConstBiDirectionalIterator other) const
        {
            return m_value > other.m_value;
        }
        constexpr bool operator>=(const ConstBiDirectionalIterator other) const
        {
            return m_value >= other.m_value;
        }

        constexpr ConstBiDirectionalIterator operator++()
        {
            ++m_value;
            return *this;
        }
        constexpr ConstBiDirectionalIterator operator++(int)
        {
            ConstBiDirectionalIterator tmp = *this;
            operator++();
            return tmp;
        }

        constexpr ConstBiDirectionalIterator operator--()
        {
            m_value--;
            return *this;
        }
        constexpr ConstBiDirectionalIterator operator--(int)
        {
            ConstBiDirectionalIterator tmp = *this;
            operator--();
            return tmp;
        }

    private:
        pointer m_value;
    };
}
