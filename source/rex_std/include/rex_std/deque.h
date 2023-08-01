// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: deque.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/algorithm.h"
#include "rex_std/memory.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename T>
      constexpr size_t deque_default_sub_array_size()
      {
        size_t res = 4;
        if constexpr(sizeof(T) <= 4)
        {
          res = 64;
        }

        if constexpr(sizeof(T) <= 8)
        {
          res = 32;
        }

        if constexpr(sizeof(T) <= 16)
        {
          res = 16;
        }

        if constexpr(sizeof(T) <= 32)
        {
          res = 8;
        }

        return res;
      }
    } // namespace internal

    template <typename T, card32 SubArraySize = static_cast<card32>(internal::deque_default_sub_array_size<T>())>
    struct deque_iterator
    {
    private:
      using this_type = deque_iterator<T>;

    public:
      using iterator          = deque_iterator<T>;
      using const_iterator    = deque_iterator<T>;
      using difference_type   = ptrdiff;
      using iterator_category = random_access_iterator_tag;
      using value_type        = T;
      using pointer           = T*;
      using reference         = T&;

    public:
      deque_iterator()
          : m_current(nullptr)
          , m_begin(nullptr)
          , m_end(nullptr)
          , m_current_array_ptr(nullptr)
      {
      }

      pointer operator->() const
      {
        return m_current;
      }
      reference operator*() const
      {
        return *m_current;
      }

      this_type& operator++()
      {
        if(++m_current == m_end)
        {
          m_begin   = *++m_current_array_ptr;
          m_end     = m_begin + internal::deque_default_sub_array_size<T>();
          m_current = m_begin;
        }
        return *this;
      }
      this_type operator++(int)
      {
        const this_type temp(*this);
        operator++();
        return temp;
      }

      this_type& operator--()
      {
        if(m_current == m_begin)
        {
          m_begin   = *--m_current_array_ptr;
          m_end     = m_begin + internal::deque_default_sub_array_size<T>();
          m_current = m_end; // fall through...
        }
        --m_current;
        return *this;
      }
      this_type operator--(int)
      {
        const this_type temp(*this);
        operator--();
        return temp;
      }

      this_type& operator+=(difference_type n)
      {
        const difference_type subarray_pos = (m_current - m_begin) + n;

        if((size_t)subarray_pos < (size_t)internal::deque_default_sub_array_size<T>())
        {
          m_current += n;
        }
        else
        {
          RSL_ASSERT_X((internal::deque_default_sub_array_size<T>() & (internal::deque_default_sub_array_size<T>() - 1)) == 0, "subarray size needs to be a power of 2"); // Verify that it is a power of 2.
          const difference_type subarray_idx = (((16777216 + subarray_pos) / (difference_type)internal::deque_default_sub_array_size<T>())) - (16777216 / (difference_type)internal::deque_default_sub_array_size<T>());

          set_sub_array(m_current_array_ptr + subarray_idx);
          m_current = m_begin + (subarray_pos - (subarray_idx * (difference_type)internal::deque_default_sub_array_size<T>()));
        }
        return *this;
      }
      this_type& operator-=(difference_type n)
      {
        return (*this).operator+=(-n);
      }

      this_type operator+(difference_type n) const
      {
        return this_type(*this).operator+=(n);
      }
      this_type operator-(difference_type n) const
      {
        return this_type(*this).operator+=(-n);
      }

      void copy_backward(const iterator& first, const iterator& last)
      {
        rsl::copy_backward(rsl::make_move_iterator(first), rsl::make_move_iterator(last), rsl::make_move_iterator(*this)).base();
      }

      void set_sub_array(T** currentArrayPtr)
      {
        m_current_array_ptr = currentArrayPtr;
        m_begin             = *currentArrayPtr;
        m_end               = m_begin + SubArraySize;
      }

      template <typename U, card32 SubArraySize2>
      friend bool operator==(const deque_iterator<U, SubArraySize2>& lhs, const deque_iterator<U, SubArraySize2>& rhs);

      // private:
      T* m_current;
      T* m_begin;
      T* m_end;
      T** m_current_array_ptr;
    };

    template <typename T, card32 SubArraySize>
    bool operator==(const deque_iterator<T, SubArraySize>& lhs, const deque_iterator<T, SubArraySize>& rhs)
    {
      return lhs.m_current == rhs.m_current;
    }

    template <typename T, card32 SubArraySize>
    bool operator!=(const deque_iterator<T, SubArraySize>& lhs, const deque_iterator<T, SubArraySize>& rhs)
    {
      return !(lhs == rhs);
    }

    template <typename T, card32 SubArraySize>
    typename deque_iterator<T, SubArraySize>::difference_type operator-(const deque_iterator<T, SubArraySize>& lhs, const deque_iterator<T, SubArraySize>& rhs)
    {
      using difference_type = typename deque_iterator<T, SubArraySize>::difference_type;
      return ((difference_type)internal::deque_default_sub_array_size<T>() * ((lhs.m_current_array_ptr - rhs.m_current_array_ptr) - 1)) + (lhs.m_current - lhs.m_begin) + (rhs.m_end - rhs.m_current);
    }

    template <typename T, typename Allocator = rsl::allocator, card32 SubArraySize = static_cast<card32>(internal::deque_default_sub_array_size<T>())>
    class deque
    {
    private:
      using this_type = deque<T, Allocator>;

      static_assert((SubArraySize & (SubArraySize - 1)) == 0, "SubArraySize is not a multiple of 2");

      constexpr static card32 s_min_array_size = 8;
      enum class Side
      {
        Front,
        Back
      };

    public:
      using value_type             = T;
      using pointer                = T*;
      using const_pointer          = const T*;
      using reference              = T&;
      using const_reference        = const T&;
      using iterator               = deque_iterator<T, SubArraySize>;
      using const_iterator         = deque_iterator<T, SubArraySize>;
      using reverse_iterator       = rsl::reverse_iterator<iterator>;
      using const_reverse_iterator = rsl::reverse_iterator<const_iterator>;
      using size_type              = card32;
      using difference_type        = int32;
      using allocator_type         = Allocator;

      // template<typename T2, card32>
      // friend class deque_iterator<T2, SubArraySize>;

    public:
      deque()
          : m_ptr_array(nullptr)
          , m_ptr_array_size(0)
          , m_begin_it()
          , m_end_it()
          , m_allocator()
      {
      }
      explicit deque(const allocator_type& allocator)
          : m_ptr_array(nullptr)
          , m_ptr_array_size(0)
          , m_begin_it()
          , m_end_it()
          , m_allocator(allocator)
      {
      }
      explicit deque(size_type n, const allocator_type& allocator = allocator_type())
          : m_ptr_array(nullptr)
          , m_ptr_array_size(0)
          , m_begin_it()
          , m_end_it()
          , m_allocator(allocator)
      {
        init(n);
        fill_default();
      }
      deque(size_type n, const value_type& value, const allocator_type& allocator = allocator_type())
          : m_ptr_array(nullptr)
          , m_ptr_array_size(0)
          , m_begin_it()
          , m_end_it()
          , m_allocator(allocator)
      {
        init(n);
        fill_init(value);
      }

      deque(const this_type& other)
          : m_ptr_array(nullptr)
          , m_ptr_array_size(0)
          , m_begin_it()
          , m_end_it()
          , m_allocator(allocator)
      {
        init(other.size());
        rsl::uninitialized_copy(other.m_begin_it, other.m_end_it, m_begin_it);
      }
      deque(this_type&& other)
      {
        swap(other);
      }

      deque(rsl::initializer_list<value_type> ilist, const allocator_type& allocator = allocator_type())
      {
        init_from_it(ilist.begin(), ilist.end());
      }

      template <typename InputIterator>
      deque(InputIterator first, InputIterator last)
      {
        init_from_it(first, last);
      }

      ~deque()
      {
        for(iterator current = m_begin_it; current != m_end_it; ++current)
        {
          current.m_current->~value_type();
        }
      }

      deque& operator=(const this_type& other)
      {
        REX_ASSERT_X(this != &other, "Cannot copy assign to yourself");
        RSL_ASSERT_X(get_allocator() == other.get_allocator(), "Different allocators in copy assignment, this is not allowed");

        assign(other.cbegin(), other.cend());

        return *this;
      }

      deque& operator=(const this_type&& other)
      {
        REX_ASSERT_X(this != &other, "Cannot move assign to yourself");
        RSL_ASSERT_X(get_allocator() == other.get_allocator(), "Different allocators in move assignment, this is not allowed");

        swap(other);

        return *this;
      }

      deque& operator=(rsl::initializer_list<value_type> ilist)
      {
        assign(ilist.begin(), ilist.end());
        return *this;
      }

      void assign(size_type n, const value_type& value)
      {
        assign(n, value);
      }

      void assign(rsl::initializer_list<value_type> ilist)
      {
        assign(ilist.begin(), ilist.end());
      }

      template <typename InputIterator>
      void assign(InputIterator first, InputIterator last)
      {
        assign(first, last);
      }

      iterator begin()
      {
        return m_begin_it;
      }
      const_iterator cbegin() const
      {
        return m_begin_it;
      }
      iterator end()
      {
        return m_end_it;
      }
      const_iterator end() const
      {
        return m_end_it;
      }
      const_iterator cend() const
      {
        return m_end_it;
      }

      reverse_iterator rbegin()
      {
        return reverse_iterator(end());
      }
      const_reverse_iterator rbegin() const
      {
        return const_reverse_iterator(cend());
      }
      const_reverse_iterator crbegin() const
      {
        return const_reverse_iterator(cend());
      }

      reverse_iterator rend()
      {
        return reverse_iterator(begin());
      }
      const_reverse_iterator rend() const
      {
        return const_reverse_iterator(cbegin());
      }
      const_reverse_iterator crend() const
      {
        return const_reverse_iterator(cbegin());
      }

      bool empty() const
      {
        return m_begin_it.m_current == m_end_it.m_current;
      }

      size_type size() const
      {
        return static_cast<size_type>(m_end_it - m_begin_it);
      }

      void resize(size_type n, const value_type& value)
      {
        const size_type current_size = size();

        if(n > current_size)
        {
          insert(m_end_it, n - current_size, value);
        }
        else
        {
          erase(m_begin_it + static_cast<difference_type>(n), m_end_it);
        }
      }

      void resize(size_type n)
      {
        resize(n);
      }

      void shrink_to_fit()
      {
        this_type tmp(rsl::make_move_iterator(begin()), rsl::make_move_iterator(end()));
        swap(tmp);
      }

      reference operator[](size_type n)
      {
        iterator it = m_begin_it;

        const difference_type subarray_pos   = static_cast<difference_type>(it.m_current - it.m_begin) + static_cast<difference_type>(n);
        const difference_type subarray_index = ((16777216 + subarray_pos) / static_cast<difference_type>(SubArraySize)) - (16777216 / static_cast<difference_type>(SubArraySize));

        return *(*(it.m_current_array_ptr + subarray_index) + (subarray_pos - (subarray_index * static_cast<difference_type>(SubArraySize))));
      }

      const_reference operator[](size_type n) const
      {
        iterator it = m_begin_it;

        const difference_type subarray_pos   = static_cast<difference_type>(it.m_current - it.m_begin) + static_cast<difference_type>(n);
        const difference_type subarray_index = ((16777216 + subarray_pos) / static_cast<difference_type>(SubArraySize)) - (16777216 / static_cast<difference_type>(SubArraySize));

        return *(*(it.m_current_array_ptr + subarray_index) + (subarray_pos - (subarray_index * static_cast<difference_type>(SubArraySize))));
      }

      reference at(size_type n)
      {
        RSL_ASSERT_X(n >= 0 && n <= size(), "deque - index out of range");
        return operator[](n);
      }

      const_reference at(size_type n) const
      {
        RSL_ASSERT_X(n >= 0 && n <= size(), "deque - index out of range");
        return operator[](n);
      }

      reference front()
      {
        return *begin();
      }

      const_reference front() const
      {
        return *begin();
      }

      reference back()
      {
        return *(--end());
      }

      const_reference back() const
      {
        return *(--end());
      }

      void push_front(const value_type& value)
      {
        emplace_front(value);
      }

      void push_front(value_type&& value)
      {
        emplace_front(rsl::move(value));
      }

      reference push_front()
      {
        emplace_front(value_type());
        return *m_begin_it;
      }

      void push_back(const value_type& value)
      {
        emplace_back(value);
      }

      void push_back(value_type&& value)
      {
        emplace_back(rsl::move(value));
      }

      reference push_back()
      {
        emplace_back(value_type());
        return back();
      }

      void pop_front()
      {
        RSL_ASSERT_X(!empty(), "deque pop front on empty deque");
        if((m_begin_it.m_current + 1) != m_begin_it.m_end)
        {
          (m_begin_it.m_current++)->~value_type();
        }

        // only executed if we're popping the last item off the front most sub-array
        else
        {
          m_begin_it.m_current->~value_type();
          free_sub_array(m_begin_it.m_begin);
          m_begin_it.set_sub_array(m_begin_it.m_current_array_ptr + 1);
          m_begin_it.m_current = m_begin_it.m_begin;
        }
      }

      void pop_back()
      {
        RSL_ASSERT_X(!empty(), "deque pop front on empty deque");

        if(m_end_it.m_current != m_end_it.m_begin)
        {
          (--m_end_it.m_current)->~value_type();
        }

        // only executed if we're poppoing the first item of the last subarray
        else
        {
          free_sub_array(m_end_it.m_begin);
          m_end_it.set_sub_array(m_end_it.m_current_array_ptr - 1);
          m_end_it.m_current = m_end_it.m_end - 1;
          m_end_it->m_current->~value_type();
        }
      }

      template <typename... Args>
      iterator emplace(const_iterator position, Args&&... args)
      {
        if(position.m_current == m_end_it.m_current)
        {
          emplace_back(rsl::forward<Args>(args)...);
          return --end();
        }
        else if(position.m_current == m_begin_it.m_current)
        {
          emplace_front(rsl::forward<Args>(args)...);
          return m_begin_it;
        }

        iterator it_pos(position);
        value_type value_saved(rsl::forward<Args>(args)...);
        const difference_type i(it_pos - m_begin_it);

        RSL_ASSERT_X(!empty(), "non empty deque when an empty is expected");

        if(i < static_cast<difference_type>(size() / 2)) // should we insert at the front or the back?
        {
          emplace_front(rsl::move(*m_begin_it));

          it_pos = m_begin_it + i;

          const iterator new_pos(it_pos + 1);
          iterator old_begin(m_begin_it + 1);
          const iterator old_begin_plus1(old_begin + 1);

          old_begin.copy(old_begin_plus1, new_pos);
        }
        else
        {
          emplace_back(rsl::move(*iterator(m_end_it - 1)));

          it_pos = m_begin_it + i;

          iterator old_back(m_end_it - 1);
          const iterator old_back_minus_1(old_back - 1);

          old_back.copy_backward(it_pos, old_back_minus_1);
        }

        *it_pos = rsl::move(value_saved);

        return it_pos;
      }

      template <typename... Args>
      void emplace_front(Args&&... args)
      {
        if(m_begin_it.m_current != m_begin_it.m_begin)
        {
          new(--m_begin_it.m_current) value_type(rsl::forward<Args>(args)...);
        }
        else
        {
          value_type value_saved(rsl::forward<Args>(args)...);

          if(m_begin_it.m_current_array_ptr == m_ptr_array)
          {
            reallocate_ptr_array(1, Side::Front);
          }

          m_begin_it.m_current_array_ptr[-1] = allocate_sub_array();

          m_begin_it.set_sub_array(m_begin_it.m_current_array_ptr - 1);
          m_begin_it.m_current = m_begin_it.m_end - 1;
          new(m_begin_it.m_current) value_type(rsl::move(value_saved));
        }
      }

      template <typename... Args>
      void emplace_back(Args&&... args)
      {
        if((m_end_it.m_current + 1) != m_end_it.m_end)
        {
          new(m_end_it.m_current++) value_type(rsl::forward<Args>(args)...);
        }
        else
        {
          value_type value_saved(rsl::forward<Args>(args)...);
          if(((m_end_it.m_current_array_ptr - m_ptr_array) + 1) >= static_cast<difference_type>(m_ptr_array_size))
          {
            reallocate_ptr_array(1, Side::Back);
          }

          m_end_it.m_current_array_ptr[1] = allocate_sub_array();

          new(m_end_it.m_current) value_type(rsl::move(value_saved));
          m_end_it.set_sub_array(m_end_it.m_current_array_ptr + 1);
          m_end_it.m_current = m_end_it.m_begin;
        }
      }

      iterator insert(const_iterator position, const value_type& value)
      {
        return emplace(position, value);
      }

      iterator insert(const_iterator position, value_type&& value)
      {
        return emplace(position, rsl::move(value));
      }

      void insert(const_iterator position, size_type n, const value_type& value)
      {
        insert_values(position, n, value);
      }

      template <typename InputIterator>
      void insert(const_iterator position, InputIterator first, InputIterator last)
      {
        insert(position, first, last);
      }

      iterator insert(const_iterator position, rsl::initializer_list<value_type> ilist)
      {
        const difference_type i(position - m_begin_it);
        insert(position, ilist.begin(), ilist.end());
        return (m_begin_it + i);
      }

      iterator erase(const_iterator position)
      {
        RSL_ASSERT_X(!empty(), "trying to erase from an empty deque");

        iterator it_pos(position);
        iterator it_next(it_pos + 1);

        const difference_type i(it_pos - m_begin_it);

        if(i < static_cast<difference_type>(size() / 2))
        {
          it_next.copy_backward(m_begin_it, it_pos);
          pop_front();
        }
        else
        {
          it_pos.copy(it_next, m_end_it);
          pop_back();
        }

        return m_begin_it + i;
      }

      iterator erase(const_iterator first, const_iterator last)
      {
        iterator it_first(first);
        iterator it_last(last);

        if(it_first != m_begin_it || (it_last != m_end_it))
        {
          const iterator it_new_begin(m_begin_it + n);
          value_type** const ptr_array_begin = m_begin_it.m_current_array_ptr;

          it_last.copy_backward(m_begin_it, it_first);

          for(; m_begin_it != it_new_begin; it_new_begin)
          {
            m_begin_it.m_current->~value_type();
          }

          free_sub_arrays(ptr_array_begin, it_new_begin.m_current_array_ptr);
        }
        else
        {
          iterator it_new_end(m_end_it - n);
          value_type** const ptr_array_end = it_new_end.m_current_array_ptr + 1;

          it_first.copy(it_last, m_end_it);

          for(iterator it_temp(it_new_end); it_temp != m_end_it; ++it_temp)
          {
            it_temp.m_current->~value_type();
          }

          free_sub_arrays(ptr_array_end, m_end_it.m_current + 1);

          m_end_it = it_new_end;
        }

        clear();
        return m_end_it;
      }

      reverse_iterator erase(reverse_iterator position)
      {
        return reverse_iterator(erase((++position).base()));
      }

      reverse_iterator erase(reverse_iterator first, reverse_iterator last)
      {
        return reverse_iterator(erase(last.base(), first.base()));
      }

      void clear()
      {
        if(m_begin_it.m_current_array_ptr != m_end_it.m_current_array_ptr)
        {
          for(value_type* p1 = m_begin_it.m_current; p1 < m_begin_it.m_end; ++p1)
          {
            p1->~value_type();
          }
          for(value_type* p2 = m_end_it.m_begin; p2 < m_end_it.m_current; ++p2)
          {
            p2->~value_type();
          }
          free_sub_array(m_end_it.m_begin);
        }
        else
        {
          for(value_type* p = m_begin_it.m_current; p < m_end_it.m_current; ++p)
          {
            p->~value_type();
          }
        }

        for(value_type** ptr_array = m_begin_it.m_current_array_ptr + 1; ptr_array < m_end_it.m_current_array_ptr; ++ptr_array)
        {
          for(value_type *p = *ptr_array, *end = *ptr_array + SubArraySize; p < end; ++p)
          {
            p->~value_type();
          }

          free_sub_array(ptr_array);
        }

        m_end_it = m_begin_it;
      }

      void swap(deque& other)
      {
        rsl::swap(m_ptr_array, other.m_ptr_array);
        rsl::swap(m_ptr_array_size, other.m_ptr_array_size);
        rsl::swap(m_begin_it, other.m_begin_it);
        rsl::swap(m_end_it, other.m_end_it);
        rsl::swap(m_allocator, other.m_allocator);
      }

      const allocator_type& get_allocator() const
      {
        return m_allocator;
      }

    private:
      void init(size_type n)
      {
        const size_type new_ptr_array_size = static_cast<size_type>((n / SubArraySize) + 1);
        const size_type min_ptr_array_size = s_min_array_size;

        m_ptr_array_size = rsl::max(min_ptr_array_size, (new_ptr_array_size + 2));
        m_ptr_array      = allocate_ptr_array(m_ptr_array_size);

        value_type** const ptr_array_begin = m_ptr_array + ((m_ptr_array_size - new_ptr_array_size) / 2);
        value_type** const ptr_array_end   = ptr_array_begin + new_ptr_array_size;
        value_type** ptr_array_current     = ptr_array_begin;

        while(ptr_array_current < ptr_array_end)
        {
          *ptr_array_current++ = allocate_sub_array();
        }

        m_begin_it.set_sub_array(ptr_array_begin);
        m_begin_it.m_current = m_begin_it.m_begin;

        m_end_it.set_sub_array(ptr_array_end - 1);
        m_end_it.m_current = m_end_it.m_begin + static_cast<difference_type>(n % SubArraySize);
      }

      template <typename Integer, rsl::enable_if_t<rsl::is_integral_v<Integer>, bool> = true>
      void init(Integer n, Integer value)
      {
        init(n);
        fill_init(value);
      }

      template <typename InputIterator>
      void init_from_iterator(InputIterator first, InputIterator last, rsl::input_iterator_tag)
      {
        init(0);

        for(; first != last; ++first)
        {
          push_back(*first);
        }
      }

      template <typename ForwardIterator>
      void init_from_iterator(ForwardIterator first, ForwardIterator last, rsl::forward_iterator_tag)
      {
        using non_const_iterator_type = typename rsl::remove_const_t<ForwardIterator>;
        using non_const_value_type    = typename rsl::remove_const_t<value_type>;

        const size_type n = static_cast<size_type>(rsl::distance(first, last));

        init(n);

        for(value_type** ptr_array_current = m_begin_it.m_current_array_ptr; ptr_array_current < m_end_it.m_current_array_ptr; ++ptr_array_current)
        {
          ForwardIterator current(first);

          rsl::advance(current, SubArraySize);
          rsl::uninitialized_copy(static_cast<non_const_iterator_type>(first), static_cast<non_const_iterator_type>(last), static_cast<non_const_value_type*>(*ptr_array_current));
          first = current;
        }

        rsl::uninitialized_copy(static_cast<non_const_iterator_type>(first), static_cast<non_const_iterator_type>(last, static_cast<non_const_iterator_type*>(m_end_it.m_begin)));
      }

      template <typename InputIterator>
      void init_from_it(InputIterator first, InputIterator last)
      {
        using IC = typename rsl::iterator_traits<InputIterator>::iterator_category;
        init_from_iterator(first, last, IC());
      }

      void fill_default()
      {
        value_type** ptr_array_current = m_begin_it.m_current_array_ptr;

        while(ptr_array_current < m_end_it.m_current_array_ptr)
        {
          rsl::uninitialized_default_construct(*ptr_array_current, *ptr_array_current + SubArraySize);
          ++ptr_array_current;
        }
        rsl::uninitialized_default_construct(m_end_it.m_begin, m_end_it.m_current);
      }

      void fill_init(const value_type& val)
      {
        value_type** ptr_array_current = m_begin_it.m_current_array_ptr;

        while(ptr_array_current < m_end_it.m_current_array_ptr)
        {
          rsl::uninitialized_fill(*ptr_array_current, *ptr_array_current + SubArraySize, val);
          ++ptr_array_current;
        }
        rsl::uninitialized_fill(m_end_it.m_begin, m_end_it.m_current, val);
      }

      void set_capacity(size_type n)
      {
        if(n == 0)
        {
          this_type tmp(get_allocator());
          swap(tmp);
        }
        else if(n < size())
        {
          resize(n);
        }
      }

      template <typename Integer, rsl::enable_if_t<rsl::is_integral_v<Integer>, bool> = true>
      void assign(Integer n, Integer value)
      {
        assign_values(static_cast<size_type>(n), static_cast<value_type>(value));
      }

      template <typename InputIterator, rsl::enable_if_t<!rsl::is_integral_v<InputIterator>, bool> = true>
      void assign(InputIterator first, InputIterator last)
      {
        const size_type n    = static_cast<size_type>(rsl::distance(first, last));
        const size_type size = size();

        if(n > size)
        {
          InputIterator at_end(first);

          rsl::advance(at_end, static_cast<difference_type>(size));
          rsl::copy(first, at_end, m_begin_it);
          insert(m_end_it, at_end, last);
        }
        else
        {
          iterator it_end(rsl::copy(first, last, m_begin_it));

          if(n < size)
          {
            erase(it_end, m_end_it);
          }
        }
      }

      void assign_values(size_type n, const value_type& value)
      {
        const size_type size = size();

        if(n > size)
        {
          rsl::fill(m_begin_it, m_end_it, value);
          insert(m_end_it, n - size, value);
        }
        else
        {
          erase(m_begin_it + static_cast<difference_type>(n), m_end_it);
          rsl::fill(m_begin_it, m_end_it, value);
        }
      }

      template <typename Integer, rsl::enable_if_t<rsl::is_integral_v<Integer>, bool> = true>
      void insert(const const_iterator& position, Integer n, Integer value)
      {
        insert_values(position, static_cast<size_type>(n), static_cast<value_type>(value));
      }

      template <typename InputIterator>
      void insert(const const_iterator& position, const InputIterator& first, const InputIterator& last)
      {
        using IC = typename rsl::iterator_traits<InputIterator>::iterator_category;
        init_from_iterator(position, first, last, IC());
      }

      template <typename InputIterator>
      void insert_from_iterator(const_iterator position, const InputIterator& first, const InputIterator& last, rsl::forward_iterator_tag)
      {
        if(position.m_current == m_begin_it.m_current)
        {
          iterator it_new_begin(reallocate_sub_array(n, Side::Front));

          rsl::uninitialized_copy(first, last, it_new_begin);
          m_begin_it = it_new_begin;
        }
        else if(position.m_current == m_end_it.m_current)
        {
          const iterator it_new_end(reallocate_sub_array(n, Side::Back));

          rsl::uninitialized_default_construct(first, last, m_end_it);
          m_end_it = it_new_end;
        }
        else
        {
          const difference_type insertion_index = position - m_begin_it;
          const size_type size                  = size();

          if(insertion_index < static_cast<difference_type>(size / 2))
          {
            const iterator it_new_begin(reallocate_sub_array(n, Side::Front));
            const iterator it_old_begin(m_begin_it);
            const iterator it_pos(m_begin_it + insertion_index);

            if(insertion_index > static_cast<difference_type>(n))
            {
              iterator it_u_copy_end(m_begin_it + static_cast<difference_type>(n));

              rsl::uninitialized_default_construct(m_begin_it, it_u_copy_end, it_new_begin);
              it_u_copy_end = rsl::copy(it_u_copy_end, it_pos, it_old_begin);
              rsl::copy(first, last, it_u_copy_end);
            }
            else
            {
              InputIterator mid(first);

              rsl::advance(mid, static_cast<difference_type>(n - insertion_index));
              rsl::uninitialized_copy_copy(m_begin_it, it_pos, first, mid, it_new_begin);
              rsl::copy(mid, last, it_old_begin);
            }

            m_begin_it = it_new_begin;
          }
          else
          {
            const iterator it_new_end(reallocate_sub_array(n, Side::Back));
            const iterator it_old_end(m_end_it);
            const difference_type pushed_count = static_cast<difference_type>(size) - insertion_index;
            const iterator it_pos(m_end_it - pushed_count);

            if(pushed_count > static_cast<difference_type>(n))
            {
              const iterator it_u_copy_end(m_end_it - static_cast<difference_type>(n));

              rsl::uninitialized_copy(it_u_copy_end, m_end_it, m_end_it);
              rsl::copy_backward(it_pos, it_u_copy_end, it_old_end);
              rsl::copy(first, last, it_pos);
            }
            else
            {
              InputIterator mid(first);

              rsl::advance(mid, pushed_count);
              rsl::uninitialized_copy_copy(mid, last, it_pos, m_end_it, m_end_it);
              rsl::copy(first, mid, it_pos);
            }
            m_end_it = it_new_end;
          }
        }
      }

      void insert_values(const_iterator position, size_type n, const value_type& value)
      {
        if(position.m_current == m_begin_it.m_current)
        {
          const iterator it_new_begin(reallocate_sub_array(n, Side::Front));

          rsl::uninitialized_fill(it_new_begin, m_begin_it, value);
          m_begin_it = it_new_begin;
        }
        else if(position.m_current == m_end_it.m_current)
        {
          const iterator it_new_end(reallocate_sub_array(n, Side::Back));

          rsl::uninitialized_default_construct(m_end_it, it_new_end, value);
          m_end_it = it_new_end;
        }
        else
        {
          const difference_type insertion_index = position - m_begin_it;
          const size_type size                  = size();
          const value_type value_saved(value);

          if(insertion_index < static_cast<difference_type>(size / 2))
          {
            const iterator it_new_begin(reallocate_sub_array(n, Side::Front));
            const iterator it_old_begin(m_begin_it);
            const iterator it_position(m_begin_it + insertion_index);

            if(insertion_index >= static_cast<difference_type>(n))
            {
              iterator it_u_copy_end(m_begin_it + static_cast<difference_type>(n));

              rsl::uninitialized_move(m_begin_it, it_u_copy_end, it_new_begin);
              it_u_copy_end = rsl::move(it_u_copy_end, it_position, it_old_begin);
              rsl::fill(it_u_copy_end, it_position, value_saved);
            }
            else
            {
              rsl::uninitialized_move_fill(m_begin_it, it_position, it_new_begin, m_begin_it, value_saved);
              rsl::fill(it_old_begin, it_position, value_saved);
            }
            m_begin_it = it_new_begin;
          }
          else
          {
            const iterator it_new_end(reallocate_sub_array(n, Side::Back));
            const iterator it_old_end(m_end_it);
            const difference_type pushed_count = static_cast<difference_type>(size) - insertion_index;
            const iterator it_pos(m_end_it - pushed_count);

            if(pushed_count > static_cast<difference_type>(n))
            {
              iterator it_u_copy_end(m_end_it - static_cast<difference_type>(n));

              rsl::uninitialized_move(it_u_copy_end, m_end_it, m_end_it);
              it_u_copy_end = rsl::move_backward(it_pos, it_u_copy_end, it_old_end);
              rsl::fill(it_pos, it_u_copy_end, value_saved);
            }
            else
            {
              rsl::uninitialized_fill_move(m_end_it, it_pos + static_cast<difference_type>(n), value_saved, it_pos, m_end_it);
              rsl::fill(it_pos, it_old_end, value_saved);
            }
            m_end_it = it_new_end;
          }
        }
      }

      T* allocate_sub_array()
      {
        T* p = static_cast<T*>(m_allocator.allocate(SubArraySize * sizeof(T)));
        rsl::memset(p, 0, SubArraySize * sizeof(T));

        return p;
      }

      void free_sub_array(T* p)
      {
        m_allocator.deallocate(p, SubArraySize * sizeof(T));
      }

      void free_sub_arrays(T** begin, T** end)
      {
        while(begin < end)
        {
          free_sub_array(*begin++);
        }
      }

      T** allocate_ptr_array(size_type n)
      {
        T** pp = static_cast<T**>(m_allocator.allocate(n * sizeof(T*)));

        rsl::memset(pp, 0, n * sizeof(T*));

        return pp;
      }

      void free_ptr_array(T** pp, size_type n)
      {
        m_allocator.deallocate(pp, n * sizeof(T*));
      }

      void reallocate_sub_array(size_type additionalCapacity, Side allocationSide)
      {
        if(allocationSide == Side::Front)
        {
          const size_type current_additional_capacity = static_cast<size_type>(m_begin_it.m_current - m_begin_it.m_begin);

          if(current_additional_capacity < additionalCapacity)
          {
            const difference_type sub_array_inc = static_cast<difference_type>(((additionalCapacity - current_additional_capacity) + SubArraySize - 1) / SubArraySize);

            if(sub_array_inc > (m_begin_it.m_current_array_ptr - m_ptr_array))
            {
              reallocate_ptr_array(static_cast<size_type>(sub_array_inc - (m_begin_it.m_current_array_ptr - m_ptr_array)), Side::Front);
            }

            for(difference_type i = 1; i < sub_array_inc; ++i)
            {
              m_begin_it.m_current_array_ptr[-i] = allocate_sub_array();
            }
          }

          return m_begin_it - static_cast<difference_type>(additionalCapacity);
        }
        else
        {
          const size_type current_additional_capacity = static_cast<size_type>((m_end_it.m_end - 1) - m_end_it.m_current);

          if(current_additional_capacity < additionalCapacity)
          {
            const difference_type sub_array_inc = static_cast<difference_type>(((additionalCapacity - current_additional_capacity) + SubArraySize - 1) / SubArraySize);

            if(sub_array_inc > ((m_ptr_array + m_ptr_array_size) - m_end_it.m_current_array_ptr) - 1)
            {
              reallocate_ptr_array(static_cast<size_type>(sub_array_inc - (((m_ptr_array + m_ptr_array_size) - m_end_it.m_current_array_ptr) - 1)), Side::Back);
            }

            for(difference_type i = 1; i < sub_array_inc; ++i)
            {
              m_end_it.m_current_array_ptr[i] = allocate_sub_array();
            }
          }

          return m_end_it + static_cast<difference_type>(additionalCapacity);
        }
      }

      void reallocate_ptr_array(size_type additionalCapacity, Side allocationSide)
      {
        const size_type unused_ptr_count_at_front = static_cast<size_type>(m_begin_it.m_current_array_ptr - m_ptr_array);
        const size_type used_ptr_count            = static_cast<size_type>(m_end_it.m_current_array_ptr - m_begin_it.m_current_array_ptr) + 1;
        const size_type used_ptr_space            = used_ptr_count * sizeof(void*);
        const size_type unused_ptr_count_at_back  = (m_ptr_array_size - unused_ptr_count_at_front) - used_ptr_count;
        value_type** ptr_array_begin              = nullptr;

        if((allocationSide == Side::Back) && (additionalCapacity <= unused_ptr_count_at_front))
        {
          if(additionalCapacity < (unused_ptr_count_at_front / 2))
          {
            additionalCapacity = (unused_ptr_count_at_front / 2);
          }

          ptr_array_begin = m_ptr_array + (unused_ptr_count_at_front - additionalCapacity);
          rsl::memmove(ptr_array_begin, m_begin_it.m_current_array_ptr, used_ptr_space);
          rsl::memset(ptr_array_begin + used_ptr_count, 0, static_cast<card64>(m_ptr_array + m_ptr_array_size) - static_cast<card64>(ptr_array_begin + used_ptr_count));
        }
        else if((allocationSide == Side::Front) && (additionalCapacity <= unused_ptr_count_at_back))
        {
          if(additionalCapacity < (unused_ptr_count_at_back / 2))
          {
            additionalCapacity = (unused_ptr_count_at_back / 2);
          }

          ptr_array_begin = m_begin_it.m_current_array_ptr + additionalCapacity;
          rsl::memmove(ptr_array_begin, m_begin_it.m_current_array_ptr, used_ptr_space);
          rsl::memset(m_ptr_array, 0, static_cast<size_t>(static_cast<uintptr>(ptr_array_begin) - static_cast<uintptr>(m_ptr_array)));
        }
        else
        {
          const size_type new_ptr_array_size = m_ptr_array_size + rsl::max(m_ptr_array_size, additionalCapacity) + 2;
          value_type** new_ptr_array         = allocate_ptr_array(new_ptr_array_size);

          ptr_array_begin = new_ptr_array + (m_begin_it.m_current_array_ptr - m_ptr_array) + ((allocationSide == Side::Front) ? additionalCapacity : 0);

          if(m_ptr_array)
          {
            rsl::memcpy(ptr_array_begin, m_begin_it.m_current_array_ptr, used_ptr_space);
          }

          free_ptr_array(m_ptr_array, m_ptr_array_size);

          m_ptr_array      = new_ptr_array;
          m_ptr_array_size = new_ptr_array_size;
        }

        m_begin_it.set_sub_array(ptr_array_begin);
        m_end_it.set_sub_array((ptr_array_begin + used_ptr_count) - 1);
      }

    private:
      T** m_ptr_array;
      size_type m_ptr_array_size;
      iterator m_begin_it;
      iterator m_end_it;
      allocator_type m_allocator;
    };
  } // namespace v1
} // namespace rsl
