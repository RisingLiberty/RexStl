#pragma once

// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: circular_q.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/types.h"
#include "rex_std/vector.h"
#include "rex_std/internal/utility/move.h"

#include "rex_std/assert.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename T, typename Alloc = rsl::allocator>
    class circular_q
    {
      card32 m_max_items = 0;
      typename rsl::vector<T, Alloc>::size_type m_head = 0;
      typename rsl::vector<T, Alloc>::size_type m_tail = 0;
      card32 m_overrun_counter = 0;
      rsl::vector<T, Alloc> m_v;

    public:
      using value_type = T;

      // empty ctor - create a disabled queue with no elements allocated at all
      circular_q() = default;

      explicit circular_q(card32 maxItems)
        : m_max_items(maxItems + 1)   // one item is reserved as marker for full q
        , m_v(rsl::Size(m_max_items)) // NOLINT(google-readability-casting)
      {
      }

      circular_q(const circular_q&) = default;

      // move cannot be default,
      // since we need to reset m_head, m_tail, etc to zero in the moved object
      circular_q(circular_q&& other) noexcept
      {
        copy_moveable(rsl::move(other));
      }

      ~circular_q() = default;

      circular_q& operator=(const circular_q&) = default;
      circular_q& operator=(circular_q&& other) noexcept
      {
        copy_moveable(rsl::move(other));
        return *this;
      }

      // push back, overrun (oldest) item if no room left
      void push_back(T&& item)
      {
        if (m_max_items > 0)
        {
          m_v[m_tail] = rsl::move(item);
          m_tail = (m_tail + 1) % m_max_items;

          if (m_tail == m_head) // overrun last item if full
          {
            m_head = (m_head + 1) % m_max_items;
            ++m_overrun_counter;
          }
        }
      }

      // Return reference to the front item.
      // If there are no elements in the container, the behavior is undefined.
      const T& front() const
      {
        return m_v[m_head];
      }

      T& front()
      {
        return m_v[m_head];
      }

      // Return number of elements actually stored
      card32 size() const
      {
        if (m_tail >= m_head)
        {
          return m_tail - m_head;
        }
        else
        {
          return m_max_items - (m_head - m_tail);
        }
      }

      // Return const reference to item by index.
      // If index is out of range 0…size()-1, the behavior is undefined.
      const T& at(card32 i) const
      {
        RSL_ASSERT_X(i < size(), "Index out of bounds");
        return m_v[(m_head + i) % m_max_items];
      }

      // Pop item from front.
      // If there are no elements in the container, the behavior is undefined.
      void pop_front()
      {
        m_head = (m_head + 1) % m_max_items;
      }

      bool empty() const
      {
        return m_tail == m_head;
      }

      bool full() const
      {
        // head is ahead of the tail by 1
        if (m_max_items > 0)
        {
          return ((m_tail + 1) % m_max_items) == m_head;
        }
        return false;
      }

      card32 overrun_counter() const
      {
        return m_overrun_counter;
      }

      void reset_overrun_counter()
      {
        m_overrun_counter = 0;
      }

    private:
      // copy from other&& and reset it to disabled state
      void copy_moveable(circular_q&& other) noexcept
      {
        m_max_items = other.m_max_items;
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_overrun_counter = other.m_overrun_counter;
        m_v = rsl::move(other.m_v);

        // put &&other in disabled, but valid state
        other.m_max_items = 0;
        other.m_head = other.m_tail = 0;
        other.m_overrun_counter = 0;
      }
    };
  }
}
