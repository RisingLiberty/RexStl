#pragma once

#include "rex_std/bonus/types.h"

#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  namespace test
  {
    inline namespace v1
    {
      uint32 rand_seed();
      void set_rand_seed(uint32 seed);

      template <typename T>
      struct generate_incremental_integers
      {
        int m_x;

        generate_incremental_integers(int x = 0)
          : m_x(x)
        {}

        void reset(int x = 0)
        {
          m_x = x;
        }

        T x() const
        {
          return m_x;
        }

        T operator()()
        {
          return T(m_x++);
        }
      };

      template <typename T>
      struct set_incremental_integers
      {
        int m_x;

        set_incremental_integers(int x = 0)
          : m_x(x) { }

        void reset(int x = 0)
        {
          m_x = x;
        }

        T x() const
        {
          return m_x;
        }

        void operator()(T& t)
        {
          t = T(m_x++);
        }
      };

      struct missing_move_constructor
      {
        missing_move_constructor() {}
        missing_move_constructor(const missing_move_constructor&) {}
        missing_move_constructor& operator=(missing_move_constructor&&) { return *this; }
        missing_move_constructor& operator=(const missing_move_constructor&) { return *this; }
        bool operator<(const missing_move_constructor&) const { return true; }
      };

      struct missing_move_assignable
      {
        missing_move_assignable() {}
        missing_move_assignable(const missing_move_assignable&) {}
        missing_move_assignable(missing_move_assignable&&) {}
        missing_move_assignable& operator=(const missing_move_assignable&) { return *this; }
        bool operator<(const missing_move_assignable&) const { return true; }
      };

      class move_assignable
      {
      public:
        static move_assignable create()
        {
          return move_assignable{};
        }

        move_assignable(move_assignable&& x)
          : value(x.value) 
        {}
        move_assignable(const move_assignable&) = delete;
        move_assignable& operator=(const move_assignable&) = delete;

        ~move_assignable() = default;

        move_assignable& operator=(move_assignable&& x)
        {
          value = x.value;
          return *this;
        }

        static const int s_defaultValue = 42;
        int32 value;

      private:
        move_assignable()
          : value(s_defaultValue) 
        {}
      };

      class const_type
      {
      public:
        const_type(int value) 
          : m_dummy(value)
        {};
        int m_dummy;
      };
    }
  }
}