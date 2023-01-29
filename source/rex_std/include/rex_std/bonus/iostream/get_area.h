// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: get_area.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      class get_area
      {
      public:
        get_area()
          : m_begin(nullptr)
          , m_current(nullptr)
          , m_end(nullptr)
          , m_last(nullptr)
        {
        }

        void allocate()
        {
          m_begin = new char8[s_stream_size];
          m_current = m_begin;
          m_end = m_current;
          m_last = m_begin + s_stream_size;
        }

        void deallocate()
        {
          delete[] m_begin;
        }

        bool is_allocated() const
        {
          return m_begin != nullptr;
        }

        char8*& begin()
        {
          return m_begin;
        }
        char8*& current()
        {
          return m_current;
        }
        char8*& end()
        {
          return m_end;
        }
        char8*& last()
        {
          return m_last;
        }

        void inc_current(count_t amount = 1)
        {
          m_current += amount;
        }
        void inc_end(count_t amount = 1)
        {
          m_end += amount;
        }
        void reset_current()
        {
          m_current = m_begin;
        }
        void reset()
        {
          reset_current();
          m_end = m_current;
        }

        streamsize num_available() const
        {
          return static_cast<streamsize>(m_end - m_current);
        }
        streamsize num_available_to_load() const
        {
          return static_cast<streamsize>(m_last - m_end);
        }

      private:
        char8* m_begin;   // beginning of buffer
        char8* m_current; // next char in the buffer to read
        char8* m_end;     // end of chars loaded into the buffer
        char8* m_last;    // 1 past the end of the buffer

        static constexpr streamsize s_stream_size = 256;
      };
    }
  }
}
