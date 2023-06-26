#pragma once

#include "rex_std/bonus/types.h"

#include "rex_std/internal/iterator/iterator_traits.h"

namespace rsl
{
  namespace test
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
  }
}