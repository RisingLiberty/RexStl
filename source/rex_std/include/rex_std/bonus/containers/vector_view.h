// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: vector_view.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/vector.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename T, typename Alloc = rsl::allocator>
    class ConstVectorView
    {
    public:
      using value_type             = typename vector<T, Alloc>::value_type;
      using size_type              = typename vector<T, Alloc>::size_type;
      using difference_type        = typename vector<T, Alloc>::difference_type;
      using reference              = typename vector<T, Alloc>::reference;
      using const_reference        = typename vector<T, Alloc>::const_reference;
      using pointer                = typename vector<T, Alloc>::pointer;
      using const_pointer          = typename vector<T, Alloc>::const_pointer;
      using iterator               = typename vector<T, Alloc>::iterator;
      using const_iterator         = typename vector<T, Alloc>::const_iterator;
      using reverse_iterator       = typename vector<T, Alloc>::reverse_iterator;
      using const_reverse_iterator = typename vector<T, Alloc>::const_reverse_iterator;

      ConstVectorView(const rsl::vector<T, Alloc>& vector)
          : m_vector(vector)
      {
      }

      const_reference at(size_type idx) const
      {
        return m_vector.at(idx);
      }
      const_reference operator[](size_type idx) const
      {
        return m_vector[idx];
      }
      const_reference front() const
      {
        return m_vector.front();
      }
      const_reference back() const
      {
        return m_vector.back();
      }
      const T* data() const
      {
        return m_vector.data();
      }
      const_iterator begin() const
      {
        return m_vector.begin();
      }
      const_iterator cbegin() const
      {
        return m_vector.cbegin();
      }
      const_iterator end() const
      {
        return m_vector.end();
      }
      const_iterator cend() const
      {
        return m_vector.cend();
      }

      const_reverse_iterator crbegin() const
      {
        return m_vector.crbegin();
      }
      const_reverse_iterator crend() const
      {
        return m_vector.crend();
      }

      bool empty() const
      {
        return m_vector.empty();
      }
      size_type size() const
      {
        return m_vector.size();
      }
      size_type max_size() const
      {
        return m_vector.max_size();
      }
      size_type capacity() const
      {
        return m_vector.capacity();
      }

    private:
      const rsl::vector<T, Alloc>& m_vector;
    };

    template <typename T, typename Alloc, rsl::allocator>
    class VectorView
    {
    public:
      using value_type             = typename vector<T, Alloc>::value_type;
      using size_type              = typename vector<T, Alloc>::size_type;
      using difference_type        = typename vector<T, Alloc>::difference_type;
      using reference              = typename vector<T, Alloc>::reference;
      using const_reference        = typename vector<T, Alloc>::const_reference;
      using pointer                = typename vector<T, Alloc>::pointer;
      using const_pointer          = typename vector<T, Alloc>::const_pointer;
      using iterator               = typename vector<T, Alloc>::iterator;
      using const_iterator         = typename vector<T, Alloc>::const_iterator;
      using reverse_iterator       = typename vector<T, Alloc>::reverse_iterator;
      using const_reverse_iterator = typename vector<T, Alloc>::const_reverse_iterator;

      VectorView(rsl::vector<T, Alloc>& vector)
          : m_vector(vector)
      {
      }

      const_reference at(size_type idx) const
      {
        return m_vector.at(idx);
      }
      reference at(size_type idx)
      {
        return m_vector.at(idx);
      }
      const_reference operator[](size_type idx) const
      {
        return m_vector[idx];
      }
      reference operator[](size_type idx)
      {
        return m_vector[idx];
      }
      const_reference front() const
      {
        return m_vector.front();
      }
      reference front()
      {
        return m_vector.front();
      }
      const_reference back() const
      {
        return m_vector.back();
      }
      reference back()
      {
        return m_vector.back();
      }
      const T* data() const
      {
        return m_vector.data();
      }
      T* data()
      {
        return m_vector.data();
      }
      const_iterator begin() const
      {
        return m_vector.begin();
      }
      iterator begin()
      {
        return m_vector.begin();
      }
      const_iterator cbegin() const
      {
        return m_vector.cbegin();
      }
      iterator cbegin()
      {
        return m_vector.cbegin();
      }
      const_iterator end() const
      {
        return m_vector.end();
      }
      iterator end()
      {
        return m_vector.end();
      }
      const_iterator cend() const
      {
        return m_vector.cend();
      }
      iterator cend()
      {
        return m_vector.cend();
      }
      const_reverse_iterator crbegin() const
      {
        return m_vector.crbegin();
      }
      reverse_iterator crbegin()
      {
        return m_vector.crbegin();
      }
      const_reverse_iterator crend() const
      {
        return m_vector.crend();
      }
      reverse_iterator crend()
      {
        return m_vector.crend();
      }

      bool empty() const
      {
        return m_vector.empty();
      }
      size_type size() const
      {
        return m_vector.size();
      }
      size_type max_size() const
      {
        return m_vector.max_size();
      }
      size_type capacity() const
      {
        return m_vector.capacity();
      }

    private:
      rsl::vector<T, Alloc>& m_vector;
    };

  } // namespace v1
} // namespace rsl