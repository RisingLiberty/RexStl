// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_forward_list.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std/bonus/types.h"

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std_test/test_allocator.h"
#include "rex_std_test/test_rex_std.h"
#include "rex_std_test/test_object.h"

#include "rex_std/forward_list.h"
#include "rex_std/algorithm.h"

TEST_CASE("Test Forward List")
{
		// rsl::forward_list();
		{
			rsl::forward_list<int32> list;
			CHECK(list.empty());
		}

		// rsl::forward_list(const allocator_type& allocator);
		{
			rsl::test::malloc_allocator::reset_all();

			CHECK(rsl::test::malloc_allocator::s_alloc_count_all == 0);
			rsl::forward_list<int32, rsl::test::malloc_allocator> list;
			list.resize(100, 42);
			CHECK(rsl::test::malloc_allocator::s_alloc_count_all == 100);
		}

		// explicit rsl::forward_list(size_type n, const allocator_type& allocator = EASTL_rsl::forward_list_DEFAULT_ALLOCATOR);
		{
			rsl::forward_list<int32> list(100);
			CHECK(!list.empty());
		}

		// rsl::forward_list(size_type n, const value_type& value, const allocator_type& allocator = EASTL_rsl::forward_list_DEFAULT_ALLOCATOR);
		{
			rsl::forward_list<int32> list(32, 42);
			CHECK(list.front() == 42);
			CHECK(!list.empty());
		}

		// rsl::forward_list(const this_type& x);
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);

			CHECK(!list1.empty());
			rsl::forward_list<int32> list2(list1);
			CHECK(!list2.empty());
			CHECK(list1 == list2);
		}

		// rsl::forward_list(std::initializer_list<value_type> ilist, const allocator_type& allocator = EASTL_rsl::forward_list_DEFAULT_ALLOCATOR);
		{
			rsl::forward_list<int32> list1({ 1,2,3,4,5,6,7,8 });
			CHECK(!list1.empty());
		}

		// rsl::forward_list(this_type&& x);
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);

			rsl::forward_list<int32> list2(rsl::move(list1));

			CHECK(list1.empty());
			CHECK(!list2.empty());
			CHECK(list1 != list2);
		}

		// rsl::forward_list(this_type&& x, const allocator_type& allocator);
		{ }

		// rsl::forward_list(InputIterator first, InputIterator last); 
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);
			CHECK(!list1.empty());

			rsl::forward_list<int32> list2(list1.begin(), list1.end());
			CHECK(!list2.empty());
			CHECK(list1 == list2);
		}

		// this_type& operator=(const this_type& x);
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);
			CHECK(!list1.empty());

			rsl::forward_list<int32> list2 = list1;
			CHECK(!list2.empty());
			CHECK(list1 == list2);
		}

		// this_type& operator=(std::initializer_list<value_type>);
		{
			rsl::forward_list<int32> list1 = { 1,2,3,4,5,6,7,8 };
			CHECK(!list1.empty());
		}

		// this_type& operator=(this_type&& x);
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);
			rsl::forward_list<int32> list2 = rsl::move(list1);

			CHECK(list1.empty());
			CHECK(!list2.empty());
			CHECK(list1 != list2);
		}

		// void swap(this_type& x);
		{
			rsl::forward_list<int32> list1;
			list1.resize(8, 37);

			rsl::forward_list<int32> list2;
			CHECK(!list1.empty());
			CHECK(list2.empty());

			list2.swap(list1);

			CHECK(list1.empty());
			CHECK(!list2.empty());
		}

		// void assign(size_type n, const value_type& value);
		{
			rsl::forward_list<int32> list1;
			list1.assign(100, 42);

			CHECK(!list1.empty());

			for (auto& e : list1)
			{
				CHECK(e == 42);
			}
		}

		// void assign(std::initializer_list<value_type> ilist);
		{
#if !defined(EA_COMPILER_NO_INITIALIZER_LISTS)
			rsl::forward_list<int32> list1;
			list1.assign({ 1,2,3,4,5,6,7,8 });

			CHECK(!list1.empty());

			auto i = rsl::begin(list1);
			CHECK(*i == 1); i++;
			CHECK(*i == 2); i++;
			CHECK(*i == 3); i++;
			CHECK(*i == 4); i++;
			CHECK(*i == 5); i++;
			CHECK(*i == 6); i++;
			CHECK(*i == 7); i++;
			CHECK(*i == 8); i++;
			CHECK(i == rsl::end(list1));
#endif
		}

		// void assign(InputIterator first, InputIterator last);
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);
			CHECK(!list1.empty());

			rsl::forward_list<int32> list2;
			list2.assign(list1.begin(), list1.end());
			CHECK(!list2.empty());
			CHECK(list1 == list2);
		}

		// iterator       begin() EA_NOEXCEPT;
		// const_iterator begin() const EA_NOEXCEPT;
		// const_iterator cbegin() const EA_NOEXCEPT;
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 1);
			CHECK(!list1.empty());

			const auto ci = list1.begin();
			auto i = list1.begin();
			auto ci2 = list1.cbegin();

			CHECK(*i == 1);
			CHECK(*ci == 1);
			CHECK(*ci2 == 1);
		}

		// iterator       end() EA_NOEXCEPT;
		// const_iterator end() const EA_NOEXCEPT;
		// const_iterator cend() const EA_NOEXCEPT;
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);
			CHECK(!list1.empty());

			const auto ci = list1.end();
			auto i = list1.end();
			auto ci2 = list1.cend();

			CHECK(i == rsl::end(list1));
			CHECK(ci == rsl::end(list1));
			CHECK(ci2 == rsl::end(list1));
		}

		// reference       front();
		// const_reference front() const;
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 1);

			CHECK(list1.begin() == rsl::begin(list1));
			CHECK(list1.front() == 1);

			const rsl::forward_list<int32> clist1(list1);
			CHECK(clist1.front() == 1);
		}


		//     void emplace_front(Args&&... args);
		//     void emplace_front(value_type&& value);
		//     void emplace_front(const value_type& value);
		{
			rsl::forward_list<rsl::test::test_object> list1;
			list1.emplace_front(42);
			CHECK(list1.front().x() == 42);
			CHECK(list1.front().num_copy_ctor_calls() == 0);
			CHECK(list1.front().num_move_ctor_calls() == 0);

			list1.emplace_front(1, 2, 3);
			CHECK(list1.front().num_copy_ctor_calls() == 0);
			CHECK(list1.front().num_move_ctor_calls() == 0);
			CHECK(list1.front().x() == (1 + 2 + 3));
		}

		// void      push_front(const value_type& value);
		// reference push_front();
		// void      push_front(value_type&& value);
		{
			rsl::forward_list<rsl::test::test_object> list1;
			list1.push_front(rsl::test::test_object(42));
			CHECK(list1.front().x() == 42);
			CHECK(list1.front().num_copy_ctor_calls() == 0);
			CHECK(list1.front().num_move_ctor_calls() == 1);

			list1.push_front(rsl::test::test_object());
			CHECK(list1.front().num_copy_ctor_calls() == 0);
			CHECK(list1.front().num_move_ctor_calls() == 0);
			CHECK(list1.front().x() == 0);

			list1.push_front(rsl::test::test_object());
			CHECK(list1.front().x() == 1492);
		}

		// void pop_front();
		{
			rsl::forward_list<int32> list1;
			list1.push_front(4);
			list1.push_front(3);
			list1.push_front(2);
			list1.push_front(1);

			list1.pop_front();
			CHECK(list1.front() == 2);

			list1.pop_front();
			CHECK(list1.front() == 3);

			list1.pop_front();
			CHECK(list1.front() == 4);
		}

		// bool empty() const EA_NOEXCEPT;
		// size_type size() const EA_NOEXCEPT;
		{
			rsl::forward_list<int32> list1;
			CHECK(list1.empty());

			list1.push_front(42);
			CHECK(!list1.empty());

			list1.pop_front();
			CHECK(list1.empty());
		}


		// void resize(size_type n, const value_type& value);
		// void resize(size_type n);
		{
			rsl::forward_list<int32> list1;
			CHECK(list1.empty());
			list1.resize(100, 42);
			CHECK(list1.front() == 42);
			CHECK(!list1.empty());

			rsl::forward_list<int32> list2;
			CHECK(list2.empty());
			list2.resize(100);
			CHECK(!list2.empty());
		}

		// iterator insert(const_iterator position);
		// iterator insert(const_iterator position, const value_type& value);
		// void     insert(const_iterator position, size_type n, const value_type& value);
		{
			static const int32 MAGIC_VALUE = 42;
			struct TestVal
			{
				TestVal() : mV(MAGIC_VALUE) {}
				TestVal(int32 v) : mV(v) {}
				operator int32() { return mV; }
				int32 mV;
			};

			rsl::forward_list<TestVal> list1;
			CHECK(list1.empty());

			auto insert_iter = rsl::begin(list1);

			list1.insert_after(insert_iter, TestVal(42));
			CHECK(!list1.empty());
			CHECK(list1.front() == MAGIC_VALUE);


			list1.insert_after(insert_iter, TestVal(43));
			CHECK(!list1.empty());
			CHECK(list1.front() == MAGIC_VALUE);
		}

		// template <typename InputIterator>
		// void insert(const_iterator position, InputIterator first, InputIterator last);
		{
			rsl::forward_list<int32> list1;
			CHECK(list1.empty());
			list1.resize(100, 42);
			CHECK(!list1.empty());

			rsl::forward_list<int32> list2;
			list2.resize(400, 24);
			CHECK(!list2.empty());

			list1.insert_after(rsl::end(list1), rsl::begin(list2), rsl::end(list2)); // [42,42,42,...,42, | 24,24,24,24...]
			CHECK(!list1.empty());
			CHECK(list1.front() == 42);

			auto boundary_iter = list1.begin();
			rsl::advance(boundary_iter, 100); // move to insertation point
			CHECK(*boundary_iter == 24);
		}


		// Returns an iterator pointing to the last inserted element, or position if insertion count is zero.
		// iterator insert_after(const_iterator position);
		// iterator insert_after(const_iterator position, const value_type& value);
		// iterator insert_after(const_iterator position, size_type n, const value_type& value);
		// iterator insert_after(const_iterator position, std::initializer_list<value_type> ilist);
		{
			rsl::forward_list<int32> list1;
			CHECK(list1.empty());
			list1.push_front(0);

			list1.insert_after(list1.begin(), 0);
			CHECK(!list1.empty());

			list1.insert_after(list1.begin(), 43);

			list1.insert_after(list1.begin(), 10, 42);
			CHECK(rsl::count_if(list1.begin(), list1.end(), [](int32 i) { return i == 42; }) == 10);

			list1.insert_after(list1.begin(), { 1,2,3,4,5,6,7,8,9,0 });
		}

		// iterator insert_after(const_iterator position, value_type&& value);
		{
			rsl::forward_list<rsl::test::test_object> list1;
			CHECK(list1.empty());
			list1.push_front(0);

			list1.insert_after(list1.begin(), rsl::test::test_object(42));
			CHECK(!list1.empty());
			CHECK(rsl::test::test_object::num_copy_ctor_calls() == 0);
			CHECK(rsl::test::test_object::num_move_ctor_calls() == 1);
		}

		// iterator insert_after(const_iterator position, InputIterator first, InputIterator last);
		{
			rsl::forward_list<int32> list1 = { 0,1,2,3,4 };
			rsl::forward_list<int32> list2 = { 9,8,7,6,5 };
			list1.insert_after(list1.begin(), list2.begin(), list2.end());
			CHECK(list1 == rsl::forward_list<int32>({ 0,9,8,7,6,5,1,2,3,4 }));
		}

		// iterator emplace_after(const_iterator position, Args&&... args);
		// iterator emplace_after(const_iterator position, value_type&& value);
		// iterator emplace_after(const_iterator position, const value_type& value);
		{
			rsl::forward_list<rsl::test::test_object> list1;
			list1.emplace_after(list1.before_begin(), 42);
			CHECK(list1.front().x() == 42);
			CHECK(list1.front().num_copy_ctor_calls() == 0);
			CHECK(list1.front().num_move_ctor_calls() == 0);

			list1.emplace_after(list1.before_begin(), 1, 2, 3, 4);
			CHECK(list1.front().num_copy_ctor_calls() == 0);
			CHECK(list1.front().num_move_ctor_calls() == 0);
			CHECK(list1.front().x() == (1 + 2 + 3 + 4));
		}

		// iterator erase_after(const_iterator position);
		// iterator erase_after(const_iterator first, const_iterator last);
		{
			rsl::forward_list<int32> list1 = { 0,1,2,3,4,5,6,7 };

			auto p = list1.begin();
			p++; p++; p++;

			list1.erase_after(p);
			CHECK(list1 == rsl::forward_list<int32>({ 0,1,2,4,5,6,7 }));

			list1.erase_after(list1.begin(), list1.end());
			CHECK(list1 == rsl::forward_list<int32>({}));
			CHECK(list1.empty());
		}

		// iterator erase_after(const_iterator position);
		// iterator erase_after(const_iterator before_first, const_iterator last);
		{
			rsl::forward_list<int32> list1 = { 0,1,2,3,4,5,6,7 };
			auto p = list1.begin();

			list1.erase_after(p);
			CHECK(list1 == rsl::forward_list<int32>({ 0,2,3,4,5,6,7 }));

			list1.erase_after(p);
			CHECK(list1 == rsl::forward_list<int32>({ 0,3,4,5,6,7 }));

			list1.erase_after(p);
			CHECK(list1 == rsl::forward_list<int32>({ 0,4,5,6,7 }));

			list1.erase_after(p, list1.end());
			CHECK(list1 == rsl::forward_list<int32>({ 0 }));
		}

		// void clear();
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);
			CHECK(!list1.empty());

			list1.clear();
			CHECK(list1.empty());
		}

		// void remove(const value_type& value);
		{
			rsl::forward_list<int32> list1 = { 0,1,2,3,4 };
			rsl::forward_list<int32> list2 = { 0,1,3,4 };

			list1.remove(2);

			CHECK(list1 == list2);
		}

		// void remove_if(Predicate predicate);
		{
			rsl::forward_list<int32> list1;
			list1.resize(100, 42);

			list1.remove_if([](int32 i) { return i == 1234; }); // intentionally remove nothing.

			list1.remove_if([](int32 i) { return i == 42; });
		}

		// void reverse() EA_NOEXCEPT;
		{
			rsl::forward_list<int32> list1 = { 0,1,2,3,4 };
			rsl::forward_list<int32> list2 = { 4,3,2,1,0 };
			CHECK(list1 != list2);

			list1.reverse();
			CHECK(list1 == list2);
		}

		// void splice_after(const_iterator position, this_type& x);
		// void splice_after(const_iterator position, this_type& x, const_iterator i);
		// void splice_after(const_iterator position, this_type& x, const_iterator first, const_iterator last);
		{
			rsl::forward_list<int32> valid = { 0,1,2,3,4,5,6,7 };
			{
				rsl::forward_list<int32> list1 = { 0,1,2,3 };
				rsl::forward_list<int32> list2 = { 4,5,6,7 };
				list1.splice_after(list1.end(), list2);

				CHECK(list1 == valid);
			}
			{
				rsl::forward_list<int32> list1 = { 0,1,2,3 };
				rsl::forward_list<int32> list2 = { 4,5,6,7 };

				list1.splice_after(list1.begin(), list2, list2.begin());
				CHECK(list1 == rsl::forward_list<int32>({ 4,0,1,2,3 }));
				CHECK(list2 == rsl::forward_list<int32>({ 5,6,7 }));

				list1.splice_after(list1.begin(), list2, list2.begin());
				CHECK(list1 == rsl::forward_list<int32>({ 5,4,0,1,2,3 }));
				CHECK(list2 == rsl::forward_list<int32>({ 6,7 }));

				list1.splice_after(list1.begin(), list2, list2.begin());
				CHECK(list1 == rsl::forward_list<int32>({ 6,5,4,0,1,2,3 }));
				CHECK(list2 == rsl::forward_list<int32>({ 7 }));

				list1.splice_after(list1.begin(), list2, list2.begin());
				CHECK(list1 == rsl::forward_list<int32>({ 7,6,5,4,0,1,2,3 }));
				CHECK(list2 == rsl::forward_list<int32>({}));
			}
		}

		// void splice_after(const_iterator position, this_type&& x);
		// void splice_after(const_iterator position, this_type&& x, const_iterator i);
		// void splice_after(const_iterator position, this_type&& x, const_iterator first, const_iterator last);
		{
			{
				rsl::forward_list<int32> list1 = { 0,1,2,3 };
				rsl::forward_list<int32> list2 = { 4,5,6,7 };

				list1.splice_after(list1.begin(), rsl::move(list2));
				CHECK(list1 == rsl::forward_list<int32>({ 4,5,6,7,0,1,2,3 }));
			}
			{
				rsl::forward_list<int32> list1 = { 0,1,2,3 };
				rsl::forward_list<int32> list2 = { 4,5,6,7 };

				list1.splice_after(list1.begin(), rsl::move(list2), list2.begin());
				CHECK(list1 == rsl::forward_list<int32>({ 4,0,1,2,3 }));
			}
			{
				rsl::forward_list<int32> list1 = { 0,1,2,3 };
				rsl::forward_list<int32> list2 = { 4,5,6,7 };

				auto b = list2.begin();
				auto e = list2.end();
				e = list2.previous(e);
				e = list2.previous(e);

				list1.splice_after(list1.begin(), rsl::move(list2), b, e);
				CHECK(list1 == rsl::forward_list<int32>({ 4,5,0,1,2,3 }));
			}
		}

		// void splice_after(const_iterator position, this_type& x);
		// void splice_after(const_iterator position, this_type& x, const_iterator i);
		// void splice_after(const_iterator position, this_type& x, const_iterator first, const_iterator last);
		{
			rsl::forward_list<int32> list1 = { 0,1,2,3 };
			rsl::forward_list<int32> list2 = { 4,5,6,7 };

			list1.splice_after(list1.begin(), list2);
			CHECK(list1 == rsl::forward_list<int32>({ 0,4,5,6,7,1,2,3 }));
		}

		// void splice_after(const_iterator position, this_type&& x);
		// void splice_after(const_iterator position, this_type&& x, const_iterator i);
		// void splice_after(const_iterator position, this_type&& x, const_iterator first, const_iterator last);
		{
			{
				rsl::forward_list<int32> list1 = { 0,1,2,3 };
				rsl::forward_list<int32> list2 = { 4,5,6,7 };

				list1.splice_after(list1.begin(), rsl::move(list2));
				CHECK(list1 == rsl::forward_list<int32>({ 0,4,5,6,7,1,2,3 }));
			}
			{
				rsl::forward_list<int32> list1 = { 0,1,2,3 };
				rsl::forward_list<int32> list2 = { 4,5,6,7 };

				list1.splice_after(list1.begin(), rsl::move(list2), list2.begin());
				CHECK(list1 == rsl::forward_list<int32>({ 0,5,6,7,1,2,3 }));
			}
			{
				rsl::forward_list<int32> list1 = { 0,1,2,3 };
				rsl::forward_list<int32> list2 = { 4,5,6,7 };

				auto b = list2.begin();
				auto e = list2.end();
				e = list2.previous(e);
				e = list2.previous(e);

				list1.splice_after(list1.begin(), rsl::move(list2), b, e);
				CHECK(list1 == rsl::forward_list<int32>({ 0,5,6,1,2,3 }));
			}
		}

		// void sort();
		{
			rsl::forward_list<int32> list1 = { 0, 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 2, 2, 1, 0 };
			CHECK(!rsl::is_sorted(rsl::begin(list1), rsl::end(list1)));

			list1.sort();

			CHECK(rsl::is_sorted(rsl::begin(list1), rsl::end(list1)));
		}

		// template <class Compare>
		// void sort(Compare compare);
		{
			auto compare = [](int32 a, int32 b) { return a > b; };

			rsl::forward_list<int32> list1 = { 0, 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 2, 2, 1, 0 };
			CHECK(!rsl::is_sorted(rsl::begin(list1), rsl::end(list1), compare));
			list1.sort(compare);
			CHECK(rsl::is_sorted(rsl::begin(list1), rsl::end(list1), compare));
		}

			using list1 = rsl::forward_list<int32, rsl::allocator>;
			using list2 = rsl::forward_list<int32, rsl::test::dummy_non_empty_allocator>;

			CHECK(sizeof(list1) < sizeof(list2));
		

		{ // Test erase_after / erase_if
			{
				rsl::forward_list<int32> l = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

				auto numErased = rsl::erase(l, 5);
				CHECK((l == rsl::forward_list<int32>{0, 1, 2, 3, 4, 6, 7, 8, 9}));
				CHECK(numErased == 1);

				numErased = rsl::erase(l, 7);
				CHECK((l == rsl::forward_list<int32>{0, 1, 2, 3, 4, 6, 8, 9}));
				CHECK(numErased == 1);

				numErased = rsl::erase(l, 2);
				CHECK((l == rsl::forward_list<int32>{0, 1, 3, 4, 6, 8, 9}));
				CHECK(numErased == 1);

				numErased = rsl::erase(l, 0);
				CHECK((l == rsl::forward_list<int32>{1, 3, 4, 6, 8, 9}));
				CHECK(numErased == 1);

				numErased = rsl::erase(l, 4);
				CHECK((l == rsl::forward_list<int32>{1, 3, 6, 8, 9}));
				CHECK(numErased == 1);
			}

			{
				rsl::forward_list<int32> l = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

				auto numErased = rsl::erase_if(l, [](auto e) { return e % 2 == 0; });
				CHECK((l == rsl::forward_list<int32>{1, 3, 5, 7, 9}));
				CHECK(numErased == 5);

				numErased = rsl::erase_if(l, [](auto e) { return e == 5; });
				CHECK((l == rsl::forward_list<int32>{1, 3, 7, 9}));
				CHECK(numErased == 1);

				numErased = rsl::erase_if(l, [](auto e) { return e % 3 == 0; });
				CHECK((l == rsl::forward_list<int32>{1, 7}));
				CHECK(numErased == 2);
			}
		}

		{ // Test global operators
			{
				rsl::forward_list<int32> list1 = { 0, 1, 2, 3, 4, 5 };
				rsl::forward_list<int32> list2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
				rsl::forward_list<int32> list3 = { 5, 6, 7, 8 };

				CHECK(list1 == list1);
				CHECK(!(list1 != list1));

				CHECK(list1 != list2);
				CHECK(list2 != list3);
				CHECK(list1 != list3);

				CHECK(list1 < list2);
				CHECK(list1 <= list2);

				CHECK(list2 > list1);
				CHECK(list2 >= list1);

				CHECK(list3 > list1);
				CHECK(list3 > list2);
			}

#if defined(EA_COMPILER_HAS_THREE_WAY_COMPARISON)
			{
				rsl::forward_list<int32> list1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
				rsl::forward_list<int32> list2 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
				rsl::forward_list<int32> list3 = { -1, 0, 1, 2, 3, 4, 5 };

				// CHECK equality between list1 and list2
				CHECK((list1 <=> list2) == 0);
				CHECK(!((list1 <=> list2) != 0));
				CHECK((list1 <=> list2) <= 0);
				CHECK((list1 <=> list2) >= 0);
				CHECK(!((list1 <=> list2) < 0));
				CHECK(!((list1 <=> list2) > 0));

				list1.push_front(-2); // Make list1 less than list2.
				list2.push_front(-1);

				// CHECK list1 < list2
				CHECK(!((list1 <=> list2) == 0));
				CHECK((list1 <=> list2) != 0);
				CHECK((list1 <=> list2) <= 0);
				CHECK(!((list1 <=> list2) >= 0));
				CHECK(((list1 <=> list2) < 0));
				CHECK(!((list1 <=> list2) > 0));


				// CHECK list3.size() < list2.size() and list3 is a subset of list2
				CHECK(!((list3 <=> list2) == 0));
				CHECK((list3 <=> list2) != 0);
				CHECK((list3 <=> list2) <= 0);
				CHECK(!((list3 <=> list2) >= 0));
				CHECK(((list3 <=> list2) < 0));
				CHECK(!((list3 <=> list2) > 0));
			}

			{
				rsl::forward_list<int32> list1 = { 1, 2, 3, 4, 5, 6, 7 };
				rsl::forward_list<int32> list2 = { 7, 6, 5, 4, 3, 2, 1 };
				rsl::forward_list<int32> list3 = { 1, 2, 3, 4 };

				struct weak_ordering_rsl::forward_list
				{
					rsl::forward_list<int32> rsl::forward_list;
					inline std::weak_ordering operator<=>(const weak_ordering_rsl::forward_list& b) const { return rsl::forward_list <=> b.rsl::forward_list; }
				};

				CHECK(synth_three_way{}(weak_ordering_rsl::forward_list{ list1 }, weak_ordering_rsl::forward_list{ list2 }) == std::weak_ordering::less);
				CHECK(synth_three_way{}(weak_ordering_rsl::forward_list{ list3 }, weak_ordering_rsl::forward_list{ list1 }) == std::weak_ordering::less);
				CHECK(synth_three_way{}(weak_ordering_rsl::forward_list{ list2 }, weak_ordering_rsl::forward_list{ list1 }) == std::weak_ordering::greater);
				CHECK(synth_three_way{}(weak_ordering_rsl::forward_list{ list2 }, weak_ordering_rsl::forward_list{ list3 }) == std::weak_ordering::greater);
				CHECK(synth_three_way{}(weak_ordering_rsl::forward_list{ list1 }, weak_ordering_rsl::forward_list{ list1 }) == std::weak_ordering::equivalent);

				struct strong_ordering_rsl::forward_list
				{
					rsl::forward_list<int32> rsl::forward_list;
					inline std::strong_ordering operator<=>(const strong_ordering_rsl::forward_list& b) const { return rsl::forward_list <=> b.rsl::forward_list; }
				};

				CHECK(synth_three_way{}(strong_ordering_rsl::forward_list{ list1 }, strong_ordering_rsl::forward_list{ list2 }) == std::strong_ordering::less);
				CHECK(synth_three_way{}(strong_ordering_rsl::forward_list{ list3 }, strong_ordering_rsl::forward_list{ list1 }) == std::strong_ordering::less);
				CHECK(synth_three_way{}(strong_ordering_rsl::forward_list{ list2 }, strong_ordering_rsl::forward_list{ list1 }) == std::strong_ordering::greater);
				CHECK(synth_three_way{}(strong_ordering_rsl::forward_list{ list2 }, strong_ordering_rsl::forward_list{ list3 }) == std::strong_ordering::greater);
				CHECK(synth_three_way{}(strong_ordering_rsl::forward_list{ list1 }, strong_ordering_rsl::forward_list{ list1 }) == std::strong_ordering::equal);
			}
#endif
		}

}