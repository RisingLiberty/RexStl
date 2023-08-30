// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_deque.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/types.h"

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std_test/test_allocator.h"
#include "rex_std_test/test_rex_std.h"
#include "rex_std_test/test_object.h"
#include "rex_std/deque.h"
#include "rex_std/vector.h"
#include "rex_std/list.h"

namespace rsl::test
{
  inline namespace v1
  {
    struct deque_object
    {
      int32 m_x;
      static int32 s_do_count;

      deque_object(int32 x = 0)
        : m_x(x)
      {
        ++s_do_count;
      }
      deque_object(const deque_object& other)
        : m_x(other.m_x)
      {
        ++s_do_count;
      }

      deque_object& operator=(const deque_object& other)
      {
        m_x = other.m_x;
        return *this;
      }

      ~deque_object()
      {
        --s_do_count;
      }
    };

    int32 deque_object::s_do_count = 0;

    bool operator==(const deque_object& lhs, const deque_object& rhs)
    {
      return lhs.m_x == rhs.m_x;
    }
    bool operator<(const deque_object& lhs, const deque_object& rhs)
    {
      return lhs.m_x < rhs.m_x;
    }

    template <typename D1, typename D2>
    void compare_deques(const D1& d1, const D2& d2)
    {
      // Compare emptiness.
      CHECK(d1.empty() == d2.empty());

      // Compare sizes.
      const size_t nSize1 = d1.size();
      const size_t nSize2 = d2.size();

      CHECK(nSize1 == nSize2);

      // Compare values.
      if (nSize1 == nSize2)
      {
        // Test operator[]
        for (unsigned i = 0; i < nSize1; i++) // 1792
        {
          const typename D1::value_type& t1 = d1[i];
          const typename D2::value_type& t2 = d2[i];

          CHECK(t1 == t2);
        }

        // Test iteration
        typename D1::const_iterator it1 = d1.begin();
        typename D2::const_iterator it2 = d2.begin();

        for (unsigned j = 0; it1 != d1.end(); ++it1, ++it2, ++j)
        {
          const typename D1::value_type& t1 = *it1;
          const typename D2::value_type& t2 = *it2;

          CHECK(t1 == t2);
        }

        // Test reverse iteration
        typename D1::const_reverse_iterator itr1 = d1.rbegin();
        typename D2::const_reverse_iterator itr2 = d2.rbegin();

        for (typename D1::size_type j = d1.size() - 1; itr1 != d1.rend(); ++itr1, ++itr2, --j)
        {
          const typename D1::value_type& t1 = *itr1;
          const typename D2::value_type& t2 = *itr2;

          CHECK(t1 == t2);
        }
      }
    }

    template <typename D1, typename D2>
    void test_deque_construction()
    {
      {
        D1 d1A;
        D2 d2A;
        compare_deques(d1A, d2A);

        D1 d1B((typename D1::size_type)0);
        D2 d2B((typename D2::size_type)0);
        compare_deques(d1B, d2B);

        D1 d1C(1000);
        D2 d2C(1000);
        compare_deques(d1C, d2C);

        D1 d1D(2000, 1);
        D2 d2D(2000, 1);
        compare_deques(d1D, d2D);

        D1 d1E(d1C);
        D2 d2E(d2C);
        compare_deques(d1E, d2E);

        D1 d1F(d1C.begin(), d1C.end());
        D2 d2F(d2C.begin(), d2C.end());
        compare_deques(d1F, d2F);

        // operator=
        d1E = d1D;
        d2E = d2D;
        compare_deques(d1D, d2D);
        compare_deques(d1E, d2E);

        // swap
        d1E.swap(d1D);
        d2E.swap(d2D);
        compare_deques(d1D, d2D);
        compare_deques(d1E, d2E);

        // clear
        d1A.clear();
        d2A.clear();
        compare_deques(d1A, d2A);

        d1B.clear();
        d2B.clear();
        compare_deques(d1B, d2B);
      }

      CHECK(rsl::test::deque_object::s_do_count == 0);
    }

    template <typename D1, typename D2>
    void test_deque_simple_mutation()
    {
      {
        D1 d1;
        D2 d2;

        // push_back(value_type&)
        // front
        // back
        for (int32 i = 0; i < 1000; i++)
        {
          d1.push_back(i);
          d2.push_back(i);
          CHECK(d1.front() == d2.front());
          CHECK(d1.back() == d2.back());
        }
        compare_deques(d1, d2);
        // operator[]
        // at()
        for (typename D1::size_type i = 0, iEnd = d1.size(); i < iEnd; i++)
        {
          CHECK(d1[(unsigned)i] == d2[(unsigned)i]);
          CHECK(d1.at((unsigned)i) == d2.at((unsigned)i));
        }

        // push_back()
        for (int32 i = 0; i < 1000; i++)
        {
          d1.push_back(int32());
          typename D2::value_type& ref = d2.push_back();
          CHECK(d1.front() == d2.front());
          CHECK(d1.back() == d2.back());
          CHECK(&ref == &d2.back());
        }
        compare_deques(d1, d2);
        // operator[]
        // at()
        for (typename D1::size_type i = 0, iEnd = d1.size(); i < iEnd; i++)
        {
          CHECK(d1[(unsigned)i] == d2[(unsigned)i]);
          CHECK(d1.at((unsigned)i) == d2.at((unsigned)i));
        }

        // push_front(value_type&)
        for (int32 i = 0; i < 1000; i++)
        {
          d1.push_front(i);
          d2.push_front(i);
          CHECK(d1.front() == d2.front());
          CHECK(d1.back() == d2.back());
        }
        compare_deques(d1, d2);
        // operator[]
        // at()
        for (typename D1::size_type i = 0, iEnd = d1.size(); i < iEnd; i++)
        {
          CHECK(d1[(unsigned)i] == d2[(unsigned)i]);
          CHECK(d1.at((unsigned)i) == d2.at((unsigned)i));
        }

        // push_front()
        for (int32 i = 0; i < 1000; i++)
        {
          d1.push_front(int32());
          typename D2::value_type& ref = d2.push_front();
          CHECK(d1.front() == d2.front());
          CHECK(d1.back() == d2.back());
          CHECK(&ref == &d2.front());
        }
        compare_deques(d1, d2);
        // operator[]
        // at()
        for (typename D1::size_type i = 0, iEnd = d1.size(); i < iEnd; i++)
        {
          CHECK(d1[(unsigned)i] == d2[(unsigned)i]);
          CHECK(d1.at((unsigned)i) == d2.at((unsigned)i));
        }

        // pop_back()
        for (int32 i = 0; i < 500; i++)
        {
          d1.pop_back();
          d2.pop_back();
          CHECK(d1.front() == d2.front());
          CHECK(d1.back() == d2.back());
        }
        compare_deques(d1, d2);
        // operator[]
        // at()
        for (typename D1::size_type i = 0, iEnd = d1.size(); i < iEnd; i++)
        {
          CHECK(d1[(unsigned)i] == d2[(unsigned)i]);
          CHECK(d1.at((unsigned)i) == d2.at((unsigned)i));
        }

        // pop_front()
        for (int32 i = 0; i < 500; i++)
        {
          d1.pop_front();
          d2.pop_front();
          CHECK(d1.front() == d2.front());
          CHECK(d1.back() == d2.back());
        }
        compare_deques(d1, d2);
        // operator[]
        // at()
        for (typename D1::size_type i = 0, iEnd = d1.size(); i < iEnd; i++)
        {
          CHECK(d1[(unsigned)i] == d2[(unsigned)i]);
          CHECK(d1.at((unsigned)i) == d2.at((unsigned)i));
        }

        // resize(value_type&)
        for (int32 i = 0; i < 500; i++)
        {
          d1.resize(d1.size() + 3, i);
          d2.resize(d2.size() + 3, i);
          CHECK(d1.front() == d2.front());
          CHECK(d1.back() == d2.back());
        }
        compare_deques(d1, d2);
        // operator[]
        // at()
        for (typename D1::size_type i = 0, iEnd = d1.size(); i < iEnd; i++)
        {
          CHECK(d1[(unsigned)i] == d2[(unsigned)i]);
          CHECK(d1.at((unsigned)i) == d2.at((unsigned)i));
        }

        // resize()
        for (int32 i = 0; i < 500; i++)
        {
          d1.resize(d1.size() - 2);
          d2.resize(d2.size() - 2);
          CHECK(d1.front() == d2.front());
          CHECK(d1.back() == d2.back());
        }
        compare_deques(d1, d2);
        // operator[]
        // at()
        for (typename D1::size_type i = 0, iEnd = d1.size(); i < iEnd; i++)
        {
          CHECK(d1[(unsigned)i] == d2[(unsigned)i]);
          CHECK(d1.at((unsigned)i) == d2.at((unsigned)i));
        }
      }

      CHECK(rsl::test::deque_object::s_do_count == 0);
    }

    template <typename D1, typename D2>
    void test_deque_complex_mutation()
    {
      {
        D1 d1;
        D2 d2;


        //////////////////////////////////////////////////////////////////
        // void assign(size_type n, const value_type& value);
        //////////////////////////////////////////////////////////////////

        d1.assign(100, 1);
        d2.assign(100, 1);
        compare_deques(d1, d2);
        d1.assign(50, 2);
        d2.assign(50, 2);
        compare_deques(d1, d2);
        d1.assign(150, 2);
        d2.assign(150, 2);
        compare_deques(d1, d2);


        //////////////////////////////////////////////////////////////////
        // template <typename InputIterator>
        // void assign(InputIterator first, InputIterator last);
        //////////////////////////////////////////////////////////////////

        rsl::list<int32> intList1;
        for (int32 i = 0; i < 100; i++)
          intList1.push_back(i);

        rsl::list<int32> intList2;
        for (int32 i = 0; i < 100; i++)
          intList2.push_back(i);

        d1.assign(intList1.begin(), intList1.end());
        d2.assign(intList2.begin(), intList2.end());
        compare_deques(d1, d2);


        //////////////////////////////////////////////////////////////////
        // iterator insert(iterator position, const value_type& value);
        //////////////////////////////////////////////////////////////////

        d1.insert(d1.begin(), d1[1]);
        d2.insert(d2.begin(), d2[1]);
        compare_deques(d1, d2);
        d1.insert(d1.end(), d1[d1.size() - 2]);
        d2.insert(d2.end(), d2[d2.size() - 2]);
        compare_deques(d1, d2);
        typename D1::iterator itD1NearBegin = d1.begin();
        typename D2::iterator itD2NearBegin = d2.begin();

        rsl::advance(itD1NearBegin, 1);
        rsl::advance(itD2NearBegin, 1);

        d1.insert(itD1NearBegin, d1[3]);
        d2.insert(itD2NearBegin, d2[3]);
        compare_deques(d1, d2);
        typename D1::iterator itD1NearEnd = d1.begin();
        typename D2::iterator itD2NearEnd = d2.begin();

        rsl::advance(itD1NearEnd, d1.size() - 1);
        rsl::advance(itD2NearEnd, d2.size() - 1);

        d1.insert(itD1NearEnd, d1[d1.size() - 2]);
        d2.insert(itD2NearEnd, d2[d2.size() - 2]);
        compare_deques(d1, d2);

        //////////////////////////////////////////////////////////////////
        // void insert(iterator position, size_type n, const value_type& value);
        //////////////////////////////////////////////////////////////////

        d1.insert(d1.begin(), d1.size() * 2, 3); // Insert a large number of items at the front.
        d2.insert(d2.begin(), d2.size() * 2, 3);
        compare_deques(d1, d2);
        d1.insert(d1.end(), d1.size() * 2, 3); // Insert a large number of items at the end.
        d2.insert(d2.end(), d2.size() * 2, 3);
        compare_deques(d1, d2);
        itD1NearBegin = d1.begin();
        itD2NearBegin = d2.begin();

        rsl::advance(itD1NearBegin, 3);
        rsl::advance(itD2NearBegin, 3);

        d1.insert(itD1NearBegin, 3, 4);
        d2.insert(itD2NearBegin, 3, 4);
        compare_deques(d1, d2);
        itD1NearEnd = d1.begin();
        itD2NearEnd = d2.begin();

        rsl::advance(itD1NearEnd, d1.size() - 1);
        rsl::advance(itD2NearEnd, d2.size() - 1);

        d1.insert(d1.end(), 5, 6);
        d2.insert(d2.end(), 5, 6);
        compare_deques(d1, d2);


        //////////////////////////////////////////////////////////////////
        // template <typename InputIterator>
        // void insert(iterator position, InputIterator first, InputIterator last);
        //////////////////////////////////////////////////////////////////

        itD1NearBegin = d1.begin();
        itD2NearBegin = d2.begin();

        rsl::advance(itD1NearBegin, 3);
        rsl::advance(itD2NearBegin, 3);

        d1.insert(itD1NearBegin, intList1.begin(), intList1.end());
        d2.insert(itD2NearBegin, intList2.begin(), intList2.end());
        compare_deques(d1, d2);


        //////////////////////////////////////////////////////////////////
        // iterator erase(iterator position);
        //////////////////////////////////////////////////////////////////

        itD1NearBegin = d1.begin();
        itD2NearBegin = d2.begin();

        while (itD1NearBegin != d1.end()) // Run a loop whereby we erase every third element.
        {
          for (int32 i = 0; (i < 3) && (itD1NearBegin != d1.end()); ++i)
          {
            ++itD1NearBegin;
            ++itD2NearBegin;
          }

          if (itD1NearBegin != d1.end())
          {
            itD1NearBegin = d1.erase(itD1NearBegin);
            itD2NearBegin = d2.erase(itD2NearBegin);
            compare_deques(d1, d2);          }
        }


        //////////////////////////////////////////////////////////////////
        // iterator erase(iterator first, iterator last);
        //////////////////////////////////////////////////////////////////

        itD1NearBegin = d1.begin();
        itD2NearBegin = d2.begin();

        while (itD1NearBegin != d1.end()) // Run a loop whereby we erase spans of elements.
        {
          typename D1::iterator itD1Saved = itD1NearBegin;
          typename D2::iterator itD2Saved = itD2NearBegin;

          for (int32 i = 0; (i < 11) && (itD1NearBegin != d1.end()); ++i)
          {
            ++itD1NearBegin;
            ++itD2NearBegin;
          }

          if (itD1NearBegin != d1.end())
          {
            itD1NearBegin = d1.erase(itD1Saved, itD1NearBegin);
            itD2NearBegin = d2.erase(itD2Saved, itD2NearBegin);
            compare_deques(d1, d2);          }

          for (int32 i = 0; (i < 17) && (itD1NearBegin != d1.end()); ++i)
          {
            ++itD1NearBegin;
            ++itD2NearBegin;
          }

        }

      }


      {
        //////////////////////////////////////////////////////////////////
        // reverse_iterator erase(reverse_iterator position);
        // reverse_iterator erase(reverse_iterator first, reverse_iterator last);
        //////////////////////////////////////////////////////////////////

        //D1 d1Erase;
        D2 d2Erase;

        for (int32 i = 0; i < 20; i++)
        {
          typename D2::value_type val(i);
          d2Erase.push_back(val);
        }
        CHECK(d2Erase.size() == 20);
        CHECK(d2Erase[0] == 0);
        CHECK(d2Erase[19] == 19);


        typename D2::reverse_iterator r2A = d2Erase.rbegin();
        typename D2::reverse_iterator r2B = r2A + 3;
        d2Erase.erase(r2A, r2B);
        CHECK(d2Erase.size() == 17);
        CHECK(d2Erase[0] == 0);
        CHECK(d2Erase[16] == 16);


        r2B = d2Erase.rend();
        r2A = r2B - 3;
        d2Erase.erase(r2A, r2B);
        CHECK(d2Erase.size() == 14);
        CHECK(d2Erase[0] == 3);
        CHECK(d2Erase[13] == 16);


        r2B = d2Erase.rend() - 1;
        d2Erase.erase(r2B);
        CHECK(d2Erase.size() == 13);
        CHECK(d2Erase[0] == 4);
        CHECK(d2Erase[12] == 16);


        r2B = d2Erase.rbegin();
        d2Erase.erase(r2B);
        CHECK(d2Erase.size() == 12);
        CHECK(d2Erase[0] == 4);
        CHECK(d2Erase[11] == 15);


        r2A = d2Erase.rbegin();
        r2B = d2Erase.rend();
        d2Erase.erase(r2A, r2B);
        CHECK(d2Erase.size() == 0);
      }


      CHECK(rsl::test::deque_object::s_do_count == 0);
    }
	}
}

TEST_CASE("Deque")
{
  using  SIntDeque = rsl::deque<int32>;
  using SDODeque = rsl::deque<rsl::test::deque_object>;

  using EIntDeque = rsl::deque<int32>;
  using EIntDeque1 = rsl::deque<int32, rsl::allocator, 1>;
  using EIntDeque32768 = rsl::deque<int32, rsl::allocator, 32768>;

  using EDODeque = rsl::deque<rsl::test::deque_object>;
  using EDODeque1 = rsl::deque<rsl::test::deque_object, rsl::allocator, 1>;
  using EDODeque32768 = rsl::deque<rsl::test::deque_object, rsl::allocator, 32768>;

	{   // Test construction
    constexpr auto x = rsl::internal::deque_default_sub_array_size<int>();

		rsl::test::test_deque_construction<SIntDeque, EIntDeque>();
		rsl::test::test_deque_construction<SIntDeque, EIntDeque1>();
		rsl::test::test_deque_construction<SIntDeque, EIntDeque32768>();

		rsl::test::test_deque_construction<SIntDeque, EDODeque>();
		rsl::test::test_deque_construction<SIntDeque, EDODeque1>();
		rsl::test::test_deque_construction<SIntDeque, EDODeque32768>();
	}


	{   // Test simple mutating functionality.
		rsl::test::test_deque_simple_mutation<SIntDeque, EIntDeque>();
		rsl::test::test_deque_simple_mutation<SIntDeque, EIntDeque1>();
		rsl::test::test_deque_simple_mutation<SIntDeque, EIntDeque32768>();

		rsl::test::test_deque_simple_mutation<SIntDeque, EDODeque>();
		rsl::test::test_deque_simple_mutation<SIntDeque, EDODeque1>();
		rsl::test::test_deque_simple_mutation<SIntDeque, EDODeque32768>();
	}

	{   // Test complex mutating functionality.
		rsl::test::test_deque_complex_mutation<SIntDeque, EIntDeque>();
		rsl::test::test_deque_complex_mutation<SIntDeque, EIntDeque1>();
		rsl::test::test_deque_complex_mutation<SIntDeque, EIntDeque32768>();

		rsl::test::test_deque_complex_mutation<SIntDeque, EDODeque>();
		rsl::test::test_deque_complex_mutation<SIntDeque, EDODeque1>();
		rsl::test::test_deque_complex_mutation<SIntDeque, EDODeque32768>();
	}

	// test deque support of move-only types
	{
		{
			rsl::deque<rsl::test::move_assignable> d;
			d.emplace_back(rsl::test::move_assignable::create());
			d.emplace_front(rsl::test::move_assignable::create());

			auto cd = rsl::move(d);
			CHECK(d.size() == 0);
			CHECK(cd.size() == 2);
		}

		{
			// User regression but passing end() to deque::erase is not valid.  
			// Iterator passed to deque::erase but must valid and dereferencable.
			//
			// rsl::deque<rsl::test::move_assignable> d;  // empty deque
			// d.erase(d.begin());
			// CHECK(d.size() == 0);
		}

		// simply test the basic api of deque with a move-only type
		{
			rsl::deque<rsl::test::move_assignable> d;

			// emplace_back
			d.emplace_back(rsl::test::move_assignable::create());
			d.emplace_back(rsl::test::move_assignable::create());
			d.emplace_back(rsl::test::move_assignable::create());

			// erase
			d.erase(d.begin());
			CHECK(d.size() == 2);

			// at / front / back / operator[]
			CHECK(d[0].value == 42);
			CHECK(d.at(0).value == 42);
			CHECK(d.front().value == 42);
			CHECK(d.back().value == 42);

			// clear
			d.clear();
			CHECK(d.size() == 0);

			// emplace
			d.emplace(d.begin(), rsl::test::move_assignable::create());
			d.emplace(d.begin(), rsl::test::move_assignable::create());
			CHECK(d.size() == 2);

			// pop_back
			d.pop_back();
			CHECK(d.size() == 1);

			// push_back / push_front / resize requires T be 'CopyConstructible' 

			{
				rsl::deque<rsl::test::move_assignable> swapped_d;

				// emplace_front
				swapped_d.emplace_front(rsl::test::move_assignable::create());
				swapped_d.emplace_front(rsl::test::move_assignable::create());
				swapped_d.emplace_front(rsl::test::move_assignable::create());

				// swap
				swapped_d.swap(d);
				CHECK(swapped_d.size() == 1);
				CHECK(d.size() == 3);
			}

			// pop_front
			d.pop_front();
			CHECK(d.size() == 2);

			// insert
			d.insert(d.end(), rsl::test::move_assignable::create());
			CHECK(d.size() == 3);
		}
	}

	{
		// deque(rsl::initializer_list<value_type> ilist, const allocator_type& allocator = EASTL_DEQUE_DEFAULT_ALLOCATOR);
		// this_type& operator=(rsl::initializer_list<value_type> ilist);
		// void assign(rsl::initializer_list<value_type> ilist);
		// iterator insert(iterator position, rsl::initializer_list<value_type> ilist);
		rsl::deque<int32> intDeque = { 0, 1, 2 };
    CHECK(intDeque == rsl::deque{ 0, 1, 2 });

		intDeque = { 13, 14, 15 };
    CHECK(intDeque == rsl::deque{13, 14, 15});

		intDeque.assign({ 16, 17, 18 });
    CHECK(intDeque == rsl::deque{16, 17, 18});

		rsl::deque<int32>::iterator it = intDeque.insert(intDeque.begin(), { 14, 15 });
    CHECK(intDeque == rsl::deque{ 14, 15, 16, 17, 18 });
		CHECK(*it == 14);
	}


	{   // C++11 functionality
		// deque(this_type&& x);
		// deque(this_type&& x, const allocator_type& allocator);
		// this_type& operator=(this_type&& x);
		// void push_front(value_type&& value);
		// void push_back(value_type&& value);
		// iterator insert(const_iterator position, value_type&& value);

		using namespace rsl;

		deque<rsl::test::test_object> deque3TO33(3, rsl::test::test_object(33));
		deque<rsl::test::test_object> toDequeA(rsl::move(deque3TO33));
    CHECK(toDequeA.size() == 3);
    CHECK(toDequeA.front().x() == 33);
    CHECK(deque3TO33.size() == 0);

		// The following is not as strong a test of this ctor as it could be. A stronger test would be to use IntanceAllocator with different instances.
		deque<rsl::test::test_object, rsl::test::malloc_allocator> deque4TO44(4, rsl::test::test_object(44));
		deque<rsl::test::test_object, rsl::test::malloc_allocator> toDequeB(rsl::move(deque4TO44));
    CHECK(toDequeB.size() == 4);
    CHECK(toDequeB.front().x() == 44);
    CHECK(deque4TO44.size() == 0);

		deque<rsl::test::test_object, rsl::test::malloc_allocator> deque5TO55(5, rsl::test::test_object(55));
		toDequeB = rsl::move(deque5TO55);
    CHECK(toDequeB.size() == 5);
    CHECK(toDequeB.front().x() == 55);
	}


	{   
    // C++11 functionality
		// template<class... Args>
		// iterator emplace(const_iterator position, Args&&... args);

		// template<class... Args>
		// void emplace_front(Args&&... args);

		// template<class... Args>
		// void emplace_back(Args&&... args);
		rsl::test::test_object::reset();

		rsl::deque<rsl::test::test_object, rsl::allocator, 16> toDequeA;

		toDequeA.emplace_back(2);
    CHECK(toDequeA.size() == 1);
    CHECK(toDequeA.back().x() == 2);
    CHECK(rsl::test::test_object::num_ctor_calls() == 1);

		toDequeA.emplace(toDequeA.begin(), 3, 4, 5);                                                              
    CHECK(toDequeA.size() == 2);
    CHECK(toDequeA.front().x() == 12);
    CHECK(rsl::test::test_object::num_ctor_calls() == 2);

		toDequeA.emplace_front(6, 7, 8);
    CHECK(toDequeA.size() == 3);
    CHECK(toDequeA.front().x() == 21);
    CHECK(rsl::test::test_object::num_ctor_calls() == 3);

		// This test is similar to the emplace pathway above. 
		rsl::test::test_object::reset();

		//void push_front(T&& x);
		//void push_back(T&& x);
		//iterator insert(const_iterator position, T&& x);

		rsl::deque<rsl::test::test_object, rsl::allocator, 16> toDequeC; // Specify a non-small kSubarrayCount of 16 because the move count tests below assume there is no reallocation.

		toDequeC.push_back(rsl::test::test_object(2));
    CHECK(toDequeC.size() == 1);
    CHECK(toDequeC.back().x() == 2);
    CHECK(rsl::test::test_object::num_move_ctor_calls() == 1);

		toDequeC.insert(toDequeC.begin(), rsl::test::test_object(3));
    CHECK(toDequeC.size() == 2);
    CHECK(toDequeC.front().x() == 3);
    CHECK(rsl::test::test_object::num_move_ctor_calls() == 3);

		toDequeC.push_front(rsl::test::test_object(6));
    CHECK(toDequeC.size() == 3);
    CHECK(toDequeC.front().x() == 6);
    CHECK(rsl::test::test_object::num_move_ctor_calls() == 4);
	}

	{   // Regression of kDequeSubarraySize calculations
		CHECK(EIntDeque::s_subarray_size >= 4);
		CHECK(EIntDeque1::s_subarray_size == 1);
		CHECK(EIntDeque32768::s_subarray_size == 32768);

		CHECK(EDODeque::s_subarray_size >= 2);
		CHECK(EDODeque1::s_subarray_size == 1);
		CHECK(EDODeque32768::s_subarray_size == 32768);
	}


	{   // Regression of user-reported bug

		// The following was reported by Nicolas Mercier on April 9, 2008 as causing a crash:
		//     This code breaks on our machines because it overwrites the 
		//     first 4 bytes before the beginning of the memory that was 
		//     allocated for mpPtrArray. So when temp goes out of scope, 
		//     it will free this pointer and the debug allocator will detect 
		//     that these bytes have been changed.

		rsl::deque<rsl::string> testArray;
		rsl::string s("a");

		for (int32 j = 0; j < 65; j++)
			testArray.push_back(s);

		rsl::deque<rsl::string> temp;
		temp = testArray;                     // This is where the corruption occurred.
	}


	{   // Regression of user-reported bug

		// The problem is that the pointer arrays on the deques are growing without bound. 
		// This is causing our game to crash on a soak test due to its frame event queues 
		// consuming inordinate amounts of memory. It looks like the current version of 
		// rsl::deque is missing logic to recenter the pointer array, so it keeps growing 
		// slowly as blocks are allocated on the tail and removed from the head. 
		// Note: This bug was introduced by the (mistaken) fix for April 9 bug above.

		rsl::deque<int32, rsl::test::malloc_allocator> x;
		rsl::deque<int32, rsl::test::malloc_allocator> y;

		const rsl::test::malloc_allocator& maX = x.get_allocator();
		const rsl::test::malloc_allocator& maY = y.get_allocator();

		size_t allocVolumeX1 = 0;
		size_t allocVolumeY1 = 0;
		size_t allocVolumeX2 = 0;
		size_t allocVolumeY2 = 0;

		for (int32 i = 0; i < 1001; ++i)  // With the bug, each time through this loop the containers mistakenly allocate more memory.
		{
			if (i == 100) // Save the allocated volume after 50 iterations.
			{
				allocVolumeX1 = maX.m_alloc_volume;
				allocVolumeY1 = maY.m_alloc_volume;
			}

			for (int32 j = 0; j < 5; ++j)
				x.push_back(0);

			x.swap(y);

			while (!x.empty())
				x.pop_front();
		}

		allocVolumeX2 = maX.m_alloc_volume; // Save the allocated volume after 1001 iterations.
		allocVolumeY2 = maY.m_alloc_volume;

    CHECK(allocVolumeX1 == allocVolumeX2);
    CHECK(allocVolumeX2 < 350);  // Test that the volume has not changed and is below some nominal value.
    CHECK(allocVolumeY1 == allocVolumeY2);
    CHECK(allocVolumeY2 < 350);  // This value is somewhat arbitrary and slightly hardware dependent (e.g. 32 vs. 64 bit). I bumped it up from 300 to 350 when Linux64 showed it to be 320, which was ~still OK.
	}

	{ // Regression to verify that const deque works.
		const rsl::deque<int32> constIntDeque1;
		CHECK(constIntDeque1.empty());

		int32 intArray[3] = { 37, 38, 39 };
		const rsl::deque<int32> constIntDeque2(intArray, intArray + 3);
		CHECK(constIntDeque2.size() == 3);

		const rsl::deque<int32> constIntDeque3(4, 37);
		CHECK(constIntDeque3.size() == 4);

		const rsl::deque<int32> constIntDeque4;
		const rsl::deque<int32> constIntDeque5 = constIntDeque4;
	}

	{
		// test shrink_to_fit 
		rsl::deque<int32, rsl::test::test_allocator> d(4096);
		d.erase(d.begin(), d.end());

		auto prev = d.get_allocator().num_bytes_allocated();
		d.shrink_to_fit();
		CHECK(d.get_allocator().num_bytes_allocated() < prev);
	}


	{ // Test erase / erase_if
		{
			rsl::deque<int32> d = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

			rsl::erase(d, 2);
			CHECK((d == rsl::deque<int32>{1, 3, 4, 5, 6, 7, 8, 9}));

			rsl::erase(d, 7);
			CHECK((d == rsl::deque<int32>{1, 3, 4, 5, 6, 8, 9}));

			rsl::erase(d, 9);
			CHECK((d == rsl::deque<int32>{1, 3, 4, 5, 6, 8}));

			rsl::erase(d, 5);
			CHECK((d == rsl::deque<int32>{1, 3, 4, 6, 8}));

			rsl::erase(d, 3);
			CHECK((d == rsl::deque<int32>{1, 4, 6, 8}));
		}

		{
			rsl::deque<int32> d = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			rsl::erase_if(d, [](auto i) { return i % 2 == 0; });
			CHECK((d == rsl::deque<int32>{1, 3, 5, 7, 9}));
		}
	}
}
