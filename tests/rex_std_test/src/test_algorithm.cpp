// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_algorithm.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"
#include "rex_std/algorithm.h"
#include "rex_std_test/test_object.h"
#include "rex_std_test/test_allocator.h"
#include "rex_std_test/test_rand.h"
#include "rex_std_test/rex_std_test.h"
#include "rex_std/vector.h"
#include "rex_std/functional.h"
#include "rex_std/forward_list.h"
#include "rex_std/list.h"
#include "rex_std/bonus/memory/mem_check.h"
#include "rex_std/deque.h"
#include "rex_std/internal/utility/pair.h"

namespace rsl
{
  struct A {
    A(int n) : a(n) {}
    int a;
  };
  struct LessStruct { bool operator()(const A& a1, const A& a2) { return a1.a < a2.a; } };


  struct B {
    B(int n) : b(n) {}
    int b;
  };
  inline bool LessFunction(const B& b1, const B& b2) { return b1.b < b2.b; }
}

enum TestMinMaxEnum
{
  teX = 0,
  teY = 3
};


///////////////////////////////////////////////////////////////////////////////
// Greater
//
// A version of greater that uses operator < instead of operator >.
//
template <typename T>
struct Greater
{
  bool operator()(const T& a, const T& b) const
  {
    return (b < a);
  }
};


///////////////////////////////////////////////////////////////////////////////
// DivisibleBy
//
struct DivisibleBy
{
  int d;
  DivisibleBy(int n = 1) : d(n) {}
  bool operator()(int n) const { return ((n % d) == 0); }
};


///////////////////////////////////////////////////////////////////////////////
// TestObjectNegate
//
struct TestObjectNegate
{
  rsl::test::test_object operator()(const rsl::test::test_object& a) const
  {
    return rsl::test::test_object(-a.x());
  }
};

TEST_CASE("TestMinMax")
{
  using namespace rsl;

  {
    // const T& min(const T& a, const T& b);
    // const T& min(const T& a, const T& b, Compare compare)
    // const T& max(const T& a, const T& b);
    // const T& max(const T& a, const T& b, Compare compare)

    A a1(1), a2(2), a3(3);
    a3 = min(a1, a2, LessStruct());
    CHECK(a3.a == 1);
    a3 = max(a1, a2, LessStruct());
    CHECK(a3.a == 2);

    B b1(1), b2(2), b3(3);
    b3 = min(b2, b1, LessFunction);
    CHECK(b3.b == 1);
    b3 = max(b2, b1, LessFunction);
    CHECK(b3.b == 2);


    rsl::test::test_object t1(1), t2(2), t3(3);
    t3 = min(t2, t1);
    CHECK(t3.x() == 1);
    t3 = max(t2, t1);
    CHECK(t3.x() == 2);


    int i1, i2(-1), i3(1);
    i1 = min(i2, i3);
    CHECK(i1 == -1);
    i1 = min(i3, i2);
    CHECK(i1 == -1);
    i1 = max(i2, i3);
    CHECK(i1 == 1);
    i1 = max(i3, i2);
    CHECK(i1 == 1);

    const volatile int i2cv(-1), i3cv(1);
    i1 = min(i2cv, i3cv);
    CHECK(i1 == -1);
    i1 = min(i3cv, i2cv);
    CHECK(i1 == -1);
    i1 = max(i2cv, i3cv);
    CHECK(i1 == 1);
    i1 = max(i3cv, i2cv);
    CHECK(i1 == 1);

    float f1, f2(-1), f3(1);
    f1 = min(f2, f3);
    CHECK(f1 == -1);
    f1 = min(f3, f2);
    CHECK(f1 == -1);
    f1 = max(f2, f3);
    CHECK(f1 == 1);
    f1 = max(f3, f2);
    CHECK(f1 == 1);

    double d1, d2(-1), d3(1);
    d1 = min(d2, d3);
    CHECK(d1 == -1);
    d1 = min(d3, d2);
    CHECK(d1 == -1);
    d1 = max(d2, d3);
    CHECK(d1 == 1);
    d1 = max(d3, d2);
    CHECK(d1 == 1);

    void* p1, * p2 = &d2, * p3 = &d3;
    p1 = min(p2, p3);
    CHECK((uintptr_t)p1 == min((uintptr_t)p2, (uintptr_t)p3));

    double* pd1, * pd2 = &d2, * pd3 = &d3;
    pd1 = min(pd2, pd3);
    CHECK((uintptr_t)pd1 == min((uintptr_t)pd2, (uintptr_t)pd3));

    CHECK(min<int>({ 3, 1, 2 }) == 1);
    CHECK(max<int>({ 3, 1, 2 }) == 3);

    // Test scalar specializations
    CHECK(min((char)1, (char)1) == 1);
    CHECK(min((char)1, (char)2) == 1);
    CHECK(min((char)2, (char)1) == 1);

    CHECK(min((signed char)1, (signed char)1) == 1);
    CHECK(min((signed char)1, (signed char)2) == 1);
    CHECK(min((signed char)2, (signed char)1) == 1);

    CHECK(min((unsigned char)1, (unsigned char)1) == 1);
    CHECK(min((unsigned char)1, (unsigned char)2) == 1);
    CHECK(min((unsigned char)2, (unsigned char)1) == 1);

    CHECK(min((signed short)1, (signed short)1) == 1);
    CHECK(min((signed short)1, (signed short)2) == 1);
    CHECK(min((signed short)2, (signed short)1) == 1);

    CHECK(min((unsigned short)1, (unsigned short)1) == 1);
    CHECK(min((unsigned short)1, (unsigned short)2) == 1);
    CHECK(min((unsigned short)2, (unsigned short)1) == 1);

    CHECK(min((signed int)1, (signed int)1) == 1);
    CHECK(min((signed int)1, (signed int)2) == 1);
    CHECK(min((signed int)2, (signed int)1) == 1);

    CHECK(min((unsigned int)1, (unsigned int)1) == 1);
    CHECK(min((unsigned int)1, (unsigned int)2) == 1);
    CHECK(min((unsigned int)2, (unsigned int)1) == 1);

    CHECK(min((signed long)1, (signed long)1) == 1);
    CHECK(min((signed long)1, (signed long)2) == 1);
    CHECK(min((signed long)2, (signed long)1) == 1);

    CHECK(min((unsigned long)1, (unsigned long)1) == 1);
    CHECK(min((unsigned long)1, (unsigned long)2) == 1);
    CHECK(min((unsigned long)2, (unsigned long)1) == 1);

    CHECK(min((signed long long)1, (signed long long)1) == 1);
    CHECK(min((signed long long)1, (signed long long)2) == 1);
    CHECK(min((signed long long)2, (signed long long)1) == 1);

    CHECK(min((unsigned long long)1, (unsigned long long)1) == 1);
    CHECK(min((unsigned long long)1, (unsigned long long)2) == 1);
    CHECK(min((unsigned long long)2, (unsigned long long)1) == 1);

    CHECK(min((float)1, (float)1) == 1);
    CHECK(min((float)1, (float)2) == 1);
    CHECK(min((float)2, (float)1) == 1);

    CHECK(min((double)1, (double)1) == 1);
    CHECK(min((double)1, (double)2) == 1);
    CHECK(min((double)2, (double)1) == 1);

    CHECK(min((long double)1, (long double)1) == 1);
    CHECK(min((long double)1, (long double)2) == 1);
    CHECK(min((long double)2, (long double)1) == 1);


    // Test max specializations
    CHECK(max((char)1, (char)1) == 1);
    CHECK(max((char)1, (char)2) == 2);
    CHECK(max((char)2, (char)1) == 2);

    CHECK(max((signed char)1, (signed char)1) == 1);
    CHECK(max((signed char)1, (signed char)2) == 2);
    CHECK(max((signed char)2, (signed char)1) == 2);

    CHECK(max((unsigned char)1, (unsigned char)1) == 1);
    CHECK(max((unsigned char)1, (unsigned char)2) == 2);
    CHECK(max((unsigned char)2, (unsigned char)1) == 2);

    CHECK(max((signed short)1, (signed short)1) == 1);
    CHECK(max((signed short)1, (signed short)2) == 2);
    CHECK(max((signed short)2, (signed short)1) == 2);

    CHECK(max((unsigned short)1, (unsigned short)1) == 1);
    CHECK(max((unsigned short)1, (unsigned short)2) == 2);
    CHECK(max((unsigned short)2, (unsigned short)1) == 2);

    CHECK(max((signed int)1, (signed int)1) == 1);
    CHECK(max((signed int)1, (signed int)2) == 2);
    CHECK(max((signed int)2, (signed int)1) == 2);

    CHECK(max((unsigned int)1, (unsigned int)1) == 1);
    CHECK(max((unsigned int)1, (unsigned int)2) == 2);
    CHECK(max((unsigned int)2, (unsigned int)1) == 2);

    CHECK(max((signed long)1, (signed long)1) == 1);
    CHECK(max((signed long)1, (signed long)2) == 2);
    CHECK(max((signed long)2, (signed long)1) == 2);

    CHECK(max((unsigned long)1, (unsigned long)1) == 1);
    CHECK(max((unsigned long)1, (unsigned long)2) == 2);
    CHECK(max((unsigned long)2, (unsigned long)1) == 2);

    CHECK(max((signed long long)1, (signed long long)1) == 1);
    CHECK(max((signed long long)1, (signed long long)2) == 2);
    CHECK(max((signed long long)2, (signed long long)1) == 2);

    CHECK(max((unsigned long long)1, (unsigned long long)1) == 1);
    CHECK(max((unsigned long long)1, (unsigned long long)2) == 2);
    CHECK(max((unsigned long long)2, (unsigned long long)1) == 2);

    CHECK(max((float)1, (float)1) == 1);
    CHECK(max((float)1, (float)2) == 2);
    CHECK(max((float)2, (float)1) == 2);

    CHECK(max((double)1, (double)1) == 1);
    CHECK(max((double)1, (double)2) == 2);
    CHECK(max((double)2, (double)1) == 2);

    CHECK(max((long double)1, (long double)1) == 1);
    CHECK(max((long double)1, (long double)2) == 2);
    CHECK(max((long double)2, (long double)1) == 2);
  }

  {
    // const T& min(const T& a, const T& b);
    // const T& min(const T& a, const T& b, Compare compare)
    // const T& max(const T& a, const T& b);
    // const T& max(const T& a, const T& b, Compare compare)

    A a1(1), a2(2), a3(3);
    a3 = min(a1, a2, LessStruct());
    CHECK(a3.a == 1);
    a3 = max(a1, a2, LessStruct());
    CHECK(a3.a == 2);

    B b1(1), b2(2), b3(3);
    b3 = min(b2, b1, LessFunction);
    CHECK(b3.b == 1);
    b3 = max(b2, b1, LessFunction);
    CHECK(b3.b == 2);


    rsl::test::test_object t1(1), t2(2), t3(3);
    t3 = min(t2, t1);
    CHECK(t3.x() == 1);
    t3 = max(t2, t1);
    CHECK(t3.x() == 2);


    int i1, i2(-1), i3(1);
    i1 = min(i2, i3);
    CHECK(i1 == -1);
    i1 = min(i3, i2);
    CHECK(i1 == -1);
    i1 = max(i2, i3);
    CHECK(i1 == 1);
    i1 = max(i3, i2);
    CHECK(i1 == 1);

    float f1, f2(-1), f3(1);
    f1 = min(f2, f3);
    CHECK(f1 == -1);
    f1 = min(f3, f2);
    CHECK(f1 == -1);
    f1 = max(f2, f3);
    CHECK(f1 == 1);
    f1 = max(f3, f2);
    CHECK(f1 == 1);

    double d1, d2(-1), d3(1);
    d1 = min(d2, d3);
    CHECK(d1 == -1);
    d1 = min(d3, d2);
    CHECK(d1 == -1);
    d1 = max(d2, d3);
    CHECK(d1 == 1);
    d1 = max(d3, d2);
    CHECK(d1 == 1);

    // Make sure enums work
    static_assert(rsl::is_enum<TestMinMaxEnum>::value, "is_enum failure");
    CHECK(rsl::min(teX, teY) == teX);

    // Make sure pointers work
    rsl::test::test_object testObjectArray[2];
    CHECK(rsl::min(&testObjectArray[0], &testObjectArray[1]) == &testObjectArray[0]);

    rsl::test::rand rng(rsl::test::rand_seed());
    int32_t value = rng.rand_range(17, 18);
    int32_t result = rsl::max<int32_t>(0, value); // warning C4347: behavior change: 'const T &rsl::max<int32_t>(const T &,const T &)' is called instead of 'int rsl::max(int,int)'
    CHECK(result == 17);

    // Regression for Microsoft error C2666 (http://msdn.microsoft.com/en-us/library/dyafzty4%28v=vs.110%29.aspx)
    uint32_t value2a = 17;
    uint32_t value2b = 2;
    uint32_t result2 = rsl::min<uint32_t>(value2a - value2b, 4); // error C2666: 'rsl::min' : 12 overloads have similar conversions
    CHECK(result2 == 4);

    // Regression for volatile arguments + literals
    // This test is disabled until we come up with a solution for this. std::min gives the same result as below, so we aren't necessarily obligated to resolve this.
    // volatile uint32_t value3  = 17;
    // uint32_t result3 = rsl::min<uint32_t>(value3, 4); // error C2664: 'const T &rsl::min<unsigned int>(const T &,const T &)' : cannot convert parameter 1 from 'volatile uint32_t' to 'const unsigned int &'
    // CHECK(result3 == 4);
  }


  {
    // ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
    // ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare compare)

    int intArray[] = { -5, 2, 1, 5, 4, 5 };
    int* pInt = min_element(intArray, intArray + 6);
    CHECK((pInt && (*pInt == -5)));

    pInt = min_element(intArray, intArray + 6, Greater<int>());
    CHECK((pInt && (*pInt == 5)));


    rsl::test::test_object toArray[] = { rsl::test::test_object(7), rsl::test::test_object(2), rsl::test::test_object(8), rsl::test::test_object(5), rsl::test::test_object(4), rsl::test::test_object(-12) };
    rsl::test::test_object* pTO = min_element(toArray, toArray + 6);
    CHECK((pTO && (*pTO == rsl::test::test_object(-12))));

    pTO = min_element(toArray, toArray + 6, Greater<rsl::test::test_object>());
    CHECK((pTO && (*pTO == rsl::test::test_object(8))));
  }


  {
    // ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
    // ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare compare)

    int intArray[] = { -5, 2, 1, 5, 4, 5 };
    int* pInt = max_element(intArray, intArray + 6);
    CHECK((pInt && (*pInt == 5)));

    pInt = max_element(intArray, intArray + 6, less<int>());
    CHECK((pInt && (*pInt == 5)));


    rsl::test::test_object toArray[] = { rsl::test::test_object(7), rsl::test::test_object(2), rsl::test::test_object(8), rsl::test::test_object(5), rsl::test::test_object(4), rsl::test::test_object(-12) };
    rsl::test::test_object* pTO = max_element(toArray, toArray + 6);
    CHECK((pTO && (*pTO == rsl::test::test_object(8))));

    pTO = max_element(toArray, toArray + 6, less<rsl::test::test_object>());
    CHECK((pTO && (*pTO == rsl::test::test_object(8))));
  }

  {
    // template <class ForwardIterator, class Compare>
    // rsl::pair<ForwardIterator, ForwardIterator>
    // minmax_element(ForwardIterator first, ForwardIterator last)
    //
    // template <class ForwardIterator, class Compare>
    // rsl::pair<ForwardIterator, ForwardIterator>
    // minmax_element(ForwardIterator first, ForwardIterator last, Compare compare)

    int intArray[] = { 5, -2, 1, 5, 6, 5 };

    min_max_element_result<int*> result = rsl::minmax_element(intArray, intArray + 6);
    CHECK(((*result.min == -2) && (*result.max == 6)));
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestClamp")
{
  using namespace rsl;

  CHECK(rsl::clamp(42, 1, 100) == 42);
  CHECK(rsl::clamp(-42, 1, 100) == 1);
  CHECK(rsl::clamp(420, 1, 100) == 100);
  CHECK(rsl::clamp(1, 1, 100) == 1);
  CHECK(rsl::clamp(100, 1, 100) == 100);

  CHECK(rsl::clamp(42.0f, 1.0f, 100.0f, less<float>()) == 42.0f);
  CHECK(rsl::clamp(-42.0f, 1.0f, 100.0f, less<float>()) == 1.0f);
  CHECK(rsl::clamp(420.0f, 1.0f, 100.0f, less<float>()) == 100.0f);
  CHECK(rsl::clamp(1.0f, 1.0f, 100.0f, less<float>()) == 1.0f);
  CHECK(rsl::clamp(100.0f, 1.0f, 100.0f, less<float>()) == 100.0f);

  CHECK(rsl::clamp(42., 1., 100., less<double>()) == 42.0);
  CHECK(rsl::clamp(-42., 1., 100., less<double>()) == 1.0);
  CHECK(rsl::clamp(420., 1., 100., less<double>()) == 100.0);
  CHECK(rsl::clamp(1., 1., 100., less<double>()) == 1.0);
  CHECK(rsl::clamp(100., 1., 100., less<double>()) == 100.0);

  CHECK(rsl::clamp(A(42), A(1), A(100), LessStruct()).a == A(42).a);
  CHECK(rsl::clamp(A(-42), A(1), A(100), LessStruct()).a == A(1).a);
  CHECK(rsl::clamp(A(420), A(1), A(100), LessStruct()).a == A(100).a);
  CHECK(rsl::clamp(A(1), A(1), A(100), LessStruct()).a == A(1).a);
  CHECK(rsl::clamp(A(100), A(1), A(100), LessStruct()).a == A(100).a);

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestAllAnyNoneOf")
{
  rsl::test::test_object::reset();

  // bool all_of (InputIterator first, InputIterator last, Predicate p);
  // bool any_of (InputIterator first, InputIterator last, Predicate p);
  // bool none_of(InputIterator first, InputIterator last, Predicate p);
  {

    rsl::vector<int> v;
    v.push_back(2);
    v.push_back(4);
    v.push_back(6);
    v.push_back(8);

    CHECK(rsl::all_of(v.begin(), v.end(), DivisibleBy(2)));
    CHECK(rsl::any_of(v.begin(), v.end(), DivisibleBy(3)));
    CHECK(rsl::none_of(v.begin(), v.end(), DivisibleBy(5)));
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestMismatch")
{
  // pair mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
  // pair mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Predicate predicate)

  int intArray1[] = { -5, 2, 1, 5, 4, 8888 };
  int intArray2[] = { -5, 2, 1, 5, 4, 9999 };
  int intArray3[] = { -5, 2, 1, 5, 4, 9999 };

  rsl::mismatch_result pairInt = rsl::mismatch(intArray1, intArray1, intArray2);
  CHECK(pairInt.lhs_it == intArray1 + 0);
  CHECK(pairInt.rhs_it == intArray2 + 0);

  pairInt = rsl::mismatch(intArray1, intArray1 + 6, intArray2);
  CHECK(pairInt.lhs_it == intArray1 + 5);
  CHECK(pairInt.rhs_it == intArray2 + 5);
  pairInt = rsl::mismatch(intArray2, intArray2 + 6, intArray3);

  CHECK(pairInt.lhs_it == intArray2 + 6);
  CHECK(pairInt.rhs_it == intArray3 + 6);


  pairInt = rsl::mismatch(intArray1, intArray1, intArray2, rsl::equal_to<int>());
  CHECK(pairInt.lhs_it == intArray1 + 0);
  CHECK(pairInt.rhs_it == intArray2 + 0);

  pairInt = rsl::mismatch(intArray1, intArray1 + 6, intArray2, rsl::equal_to<int>());
  CHECK(pairInt.lhs_it == intArray1 + 5);
  CHECK(pairInt.rhs_it == intArray2 + 5);

  pairInt = rsl::mismatch(intArray2, intArray2 + 6, intArray3, rsl::equal_to<int>());
  CHECK(pairInt.lhs_it == intArray2 + 6);
  CHECK(pairInt.rhs_it == intArray3 + 6);

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestSwap")
{
  // void swap(T& a, T& b)
  // void iter_swap(ForwardIterator1 a, ForwardIterator2 b)

  {
    rsl::array intArray = { -5, 2, 1, 5, 4, 5 };

    rsl::swap(intArray[0], intArray[4]);
    CHECK(intArray == rsl::array{ 4, 2, 1, 5, -5, 5 });

    iter_swap(intArray.begin() + 2, intArray.begin() + 3);
    CHECK(intArray == rsl::array{ 4, 2, 5, 1, -5, 5 });

    rsl::test::test_object toArray[] = { rsl::test::test_object(-5), rsl::test::test_object(2), rsl::test::test_object(1), rsl::test::test_object(5), rsl::test::test_object(4), rsl::test::test_object(5) };

    rsl::swap(toArray[0], toArray[4]);
    CHECK(toArray[0] == rsl::test::test_object(4));
    CHECK(toArray[4] == rsl::test::test_object(-5));

    rsl::iter_swap(toArray + 2, toArray + 3);
    CHECK(toArray[2] == rsl::test::test_object(5));
    CHECK(toArray[3] == rsl::test::test_object(1));

    // ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)

    rsl::array intArray1 = { 3, 2, 6, 5, 4, 1 };
    rsl::array intArray2 = { 0, 0, 0, 0, 0, 0 };

    swap_ranges(intArray1.begin(), intArray1.begin() + 6, intArray2.begin());
    CHECK(intArray1 == rsl::array{ 0, 0, 0, 0, 0, 0 });
    CHECK(intArray2 == rsl::array{ 3, 2, 6, 5, 4, 1 });


    rsl::test::test_object toArray1[] = { rsl::test::test_object(3), rsl::test::test_object(2), rsl::test::test_object(6), rsl::test::test_object(5), rsl::test::test_object(4), rsl::test::test_object(1) };
    rsl::test::test_object toArray2[] = { rsl::test::test_object(0), rsl::test::test_object(0), rsl::test::test_object(0), rsl::test::test_object(0), rsl::test::test_object(0), rsl::test::test_object(0) };

    rsl::swap_ranges(toArray1, toArray1 + 6, toArray2);
    CHECK(toArray1[0] == rsl::test::test_object(0));
    CHECK(toArray1[5] == rsl::test::test_object(0));
    CHECK(toArray2[0] == rsl::test::test_object(3));
    CHECK(toArray2[5] == rsl::test::test_object(1));
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestAdjacentFind")
{
  // ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
  // ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate predicate)

  {
    int intArray[] = { 3, 2, 5, 5, 4, 1 };

    int* pInt = rsl::adjacent_find(intArray + 0, intArray + 6);
    CHECK(pInt == (intArray + 2));

    pInt = rsl::adjacent_find(intArray + 3, intArray + 6);
    CHECK(pInt == (intArray + 6)); // Verify not found


    rsl::test::test_object toArray[] = { rsl::test::test_object(3), rsl::test::test_object(2), rsl::test::test_object(5), rsl::test::test_object(5), rsl::test::test_object(4), rsl::test::test_object(1) };

    rsl::test::test_object* pTO = rsl::adjacent_find(toArray + 0, toArray + 6);
    CHECK(pTO == (toArray + 2));

    pTO = rsl::adjacent_find(toArray + 3, toArray + 6);
    CHECK(pTO == (toArray + 6)); // Verify not found
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestMove")
{
  {
    // OutputIterator move(InputIterator first, InputIterator last, OutputIterator result)
    rsl::array intArray1 = { 3, 2, 6, 5, 4, 1 };
    rsl::array intArray2 = { 0, 0, 0, 0, 0, 0 };

    move(intArray1.begin(), intArray1.begin() + 0, intArray2.begin());
    CHECK(intArray2 == rsl::array{ 0, 0, 0, 0, 0, 0 });

    move(intArray1.begin(), intArray1.begin() + 6, intArray2.begin());
    CHECK(intArray2 == rsl::array{ 3, 2, 6, 5, 4, 1 });

    move(intArray1.begin() + 1, intArray1.begin() + 6, intArray1.begin() + 0); // Copy over self.
    CHECK(intArray1 == rsl::array{ 2, 6, 5, 4, 1, 1 });
  }

  {
    // OutputIterator move(InputIterator first, InputIterator last, OutputIterator result)
    rsl::vector<rsl::string> src;
    for (card32 i = 0; i < 4; i++)
    {
       src.push_back(rsl::string(1, (char8)('0' + i)));
    }
    rsl::vector<rsl::string> dest(rsl::Size(src.size()));

    rsl::move(src.begin(), src.end(), dest.begin());
    CHECK(((dest[0] == "0") && (dest[3] == "3")));
  }

  {
    // BidirectionalIterator2 move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
    rsl::vector<rsl::string> src;
    for (card32 i = 0; i < 4; i++)
    {
      src.push_back(rsl::string(1, (char8)('0' + i)));
    }
    rsl::vector<rsl::string> dest(rsl::Size(src.size()));

    rsl::move_backward(src.begin(), src.end(), dest.end());
    CHECK(((dest[0] == "0") && (dest[3] == "3")));
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestCopy")
{
  {
    // OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)

    rsl::array intArray1 = { 3, 2, 6, 5, 4, 1 };
    rsl::array intArray2 = { 0, 0, 0, 0, 0, 0 };

    copy(intArray1.begin(), intArray1.begin() + 0, intArray2.begin());
    CHECK(intArray2 == rsl::array{ 0, 0, 0, 0, 0, 0 });

    copy(intArray1.begin(), intArray1.begin() + 6, intArray2.begin());
    CHECK(intArray1 == rsl::array{ 3, 2, 6, 5, 4, 1 });

    copy(intArray1.begin() + 1, intArray1.begin() + 6, intArray1.begin() + 0); // Copy over self.
    CHECK(intArray1 == rsl::array{ 2, 6, 5, 4, 1, 1 });
  }
  {
    // OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate predicate)

    rsl::array intArray1 = { 9, 1, 9, 9, 9, 9, 1, 1, 9, 9 };
    rsl::array intArray2 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    auto equal_to_1 = [](int i) { return i == 1; };
    copy_if(intArray1.begin(), intArray1.begin() + 0, intArray2.begin(), equal_to_1);
    CHECK(intArray2 == rsl::array{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });

    copy_if(intArray1.begin(), intArray1.begin() + 9, intArray2.begin(), equal_to_1);
    CHECK(intArray2 == rsl::array{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 });

    copy_if(intArray1.begin() + 1, intArray1.begin() + 9, intArray1.begin() + 0, equal_to_1); // Copy over self.
    CHECK(intArray1 == rsl::array{ 1, 1, 1, 9, 9, 9, 1, 1, 9, 9 });
  }
  {
    // OutputIterator copy_n(InputIterator first, Size count, OutputIterator result)

    rsl::string in("123456");
    rsl::string out;

    rsl::copy_n(in.begin(), 4, rsl::back_inserter(out));
    CHECK(out == "1234");
  }
  {
    // BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)

    rsl::array intArray1 = { 3, 2, 6, 5, 4, 1 };
    rsl::array intArray2 = { 0, 0, 0, 0, 0, 0 };

    copy_backward(intArray1.begin(), intArray1.begin() + 0, (int*) nullptr);
    CHECK(intArray2 == rsl::array{ 0, 0, 0, 0, 0, 0 });

    copy_backward(intArray1.begin(), intArray1.begin() + 0, intArray2.begin() + 0);
    CHECK(intArray2 == rsl::array{ 0, 0, 0, 0, 0, 0 });

    copy_backward(intArray1.begin(), intArray1.begin() + 6, intArray2.begin() + 6);
    CHECK(intArray2 == rsl::array{ 3, 2, 6, 5, 4, 1 });

    copy_backward(intArray1.begin(), intArray1.begin() + 5, intArray1.begin() + 6); // Copy over self.
    CHECK(intArray1 == rsl::array{ 3, 3, 2, 6, 5, 4 });
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestCount")
{
  {
    // difference_type count(InputIterator first, InputIterator last, const T& value)

    rsl::array intArray = { 1, 2, 1, 5, 4, 1 };
    ptrdiff_t n = count(intArray.begin(), intArray.begin() + 6, 1);
    CHECK(n == 3);

    rsl::array toArray = { rsl::test::test_object(1), rsl::test::test_object(2), rsl::test::test_object(1), rsl::test::test_object(5), rsl::test::test_object(4), rsl::test::test_object(1) };
    n = count(toArray.begin(), toArray.begin() + 6, rsl::test::test_object(1));
    CHECK(n == 3);
  }


  {
    // difference_type count_if(InputIterator first, InputIterator last, Predicate predicate)

    rsl::array intArray = { 3, 2, 6, 5, 4, 1, 2, 4, 5, 4, 1, 2 };

    // Count all items whose value is less than three.
    auto less_than_3 = [](int i) { return i < 3; };
    ptrdiff_t n = count_if(intArray.begin(), intArray.begin(), less_than_3); // No-op
    CHECK(n == 0);
    n = count_if(intArray.begin(), intArray.begin() + 12, less_than_3);
    CHECK(n == 5);


    // Count all items whose value is less than three.
    rsl::array toArray = { rsl::test::test_object(1), rsl::test::test_object(3), rsl::test::test_object(1), rsl::test::test_object(4), rsl::test::test_object(2), rsl::test::test_object(5) };

    auto less_than_testobject_3 = [](const rsl::test::test_object& lhs) { return lhs < rsl::test::test_object(3); };
    n = count_if(toArray.begin(), toArray.begin(), less_than_testobject_3); // No-op
    CHECK(n == 0);
    n = count_if(toArray.begin(), toArray.begin() + 6, less_than_testobject_3);
    CHECK(n == 3);


    // Count all items whose value is less than three.
    rsl::forward_list<int> intList;
    intList.push_front(1);
    intList.push_front(3);
    intList.push_front(1);
    intList.push_front(4);
    intList.push_front(2);
    intList.push_front(5);

    n = count_if(intList.begin(), intList.begin(), less_than_3); // No-op
    CHECK(n == 0);
    n = count_if(intList.begin(), intList.end(), less_than_3);
    CHECK(n == 3);
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestFill")
{
  {
    // void fill(ForwardIterator first, ForwardIterator last, const T& value)

    rsl::vector<int> intArray(rsl::Size(10));

    CHECK(intArray == rsl::vector{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    rsl::fill(intArray.begin() + 3, intArray.begin() + 7, 4);
    CHECK(intArray == rsl::vector{ 0, 0, 0, 4, 4, 4, 4, 0, 0, 0 });


    rsl::forward_list<int> intList(10);
    rsl::forward_list<int>::iterator first = intList.begin();
    rsl::forward_list<int>::iterator last = intList.begin();

    rsl::advance(first, 3);
    rsl::advance(last, 7);
    CHECK(intList == rsl::forward_list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    rsl::fill(first, last, 4);
    CHECK(intList == rsl::forward_list{ 0, 0, 0, 4, 4, 4, 4, 0, 0, 0 });


    // Exercise specializations we have for some platform/compiler combinations
    // void fill(uint64_t* first, uint64_t* last, uint64_t c);
    // void fill( int64_t* first,  int64_t* last,  int64_t c);
    // void fill(uint32_t* first, uint32_t* last, uint32_t c);
    // void fill( int32_t* first,  int32_t* last,  int32_t c);
    // void fill(uint16_t* first, uint16_t* last, uint16_t c);
    // void fill( int16_t* first,  int16_t* last,  int16_t c);
    const card32 kMaxSize = 300;
    rsl::vector<uint64_t> vU64(rsl::Size(kMaxSize), 0);
    rsl::vector< int64_t> vI64(rsl::Size(kMaxSize), 0);
    rsl::vector<uint32_t> vU32(rsl::Size(kMaxSize), 0);
    rsl::vector< int32_t> vI32(rsl::Size(kMaxSize), 0);
    rsl::vector<uint16_t> vU16(rsl::Size(kMaxSize), 0);
    rsl::vector< int16_t> vI16(rsl::Size(kMaxSize), 0);

    for (card32 i = 0; i < kMaxSize; ++i)
    {
      rsl::fill(vU64.begin(), vU64.begin() + i, 0x0123456789abcdef);
      CHECK(rsl::memcheck(&vU64[0], 0x0123456789abcdef, i) == NULL);
      rsl::memset(&vU64[0], 0, i);

      rsl::fill(vI64.begin(), vI64.begin() + i, 0x0123456789abcdef);
      CHECK(rsl::memcheck(&vI64[0], 0x0123456789abcdef, i) == NULL);
      rsl::memset(&vI64[0], 0, i);

      rsl::fill(vU32.begin(), vU32.begin() + i, 0x01234567);
      CHECK(rsl::memcheck(&vU32[0], 0x01234567, i) == NULL);
      rsl::memset(&vU32[0], 0, i);

      rsl::fill(vI32.begin(), vI32.begin() + i, 0x01234567);
      CHECK(rsl::memcheck(&vI32[0], 0x01234567, i) == NULL);
      rsl::memset(&vI32[0], 0, i);

      rsl::fill(vU16.begin(), vU16.begin() + i, 0x0123ui16);
      CHECK(rsl::memcheck(&vU16[0], 0x0123ui16, i) == NULL);
      rsl::memset(&vU16[0], 0, i);

      rsl::fill(vI16.begin(), vI16.begin() + i, 0x0123ui16);
      CHECK(rsl::memcheck(&vI16[0], 0x0123ui16, i) == NULL);
      rsl::memset(&vI16[0], 0, i);
    }

    {   // Regression for user-reported compile failure.
      enum TestEnum { eTestValue = -1 };
      rsl::vector<int32_t> intArrayEnum;

      rsl::fill<rsl::vector<int32_t>::iterator, int32_t>(intArrayEnum.begin(), intArrayEnum.end(), eTestValue);
      CHECK(intArrayEnum.size() == 0);
    }
  }

  {
    // OutputIterator fill_n(OutputIterator first, Size n, const T& value)

    rsl::vector<int> intArray(rsl::Size(10));

    CHECK(intArray == rsl::vector{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    rsl::fill_n(intArray.begin() + 3, 4, 4);
    CHECK(intArray == rsl::vector{ 0, 0, 0, 4, 4, 4, 4, 0, 0, 0 });


    rsl::list<int> intList(10);
    rsl::list<int>::iterator first = intList.begin();

    rsl::advance(first, 3);
    CHECK(intList == rsl::list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    rsl::fill_n(first, 4, 4);
    CHECK(intList == rsl::list{ 0, 0, 0, 4, 4, 4, 4, 0, 0, 0 });

    // Exercise specializations we have for some platform/compiler combinations
    // template<typename Size>
    // uint64_t* fill_n(uint64_t* first, Size n, uint64_t c);
    //  int64_t* fill_n( int64_t* first, Size n,  int64_t c);
    // uint32_t* fill_n(uint32_t* first, Size n, uint32_t c);
    //  int32_t* fill_n( int32_t* first, Size n,  int32_t c);
    // uint16_t* fill_n(uint16_t* first, Size n, uint16_t c);
    //  int16_t* fill_n( int16_t* first, Size n,  int16_t c);

    const card32 kMaxSize = 17;
    rsl::vector<uint64_t> vU64(rsl::Size(kMaxSize), 0);
    rsl::vector< int64_t> vI64(rsl::Size(kMaxSize), 0);
    rsl::vector<uint32_t> vU32(rsl::Size(kMaxSize), 0);
    rsl::vector< int32_t> vI32(rsl::Size(kMaxSize), 0);
    rsl::vector<uint16_t> vU16(rsl::Size(kMaxSize), 0);
    rsl::vector< int16_t> vI16(rsl::Size(kMaxSize), 0);

    rsl::vector<uint64_t>::iterator itU64 = rsl::fill_n(vU64.begin(), kMaxSize, UINT64_C(0x0123456789abcdef));
    CHECK(rsl::memcheck(&vU64[0], 0x0123456789abcdefui64, kMaxSize) == NULL);
    CHECK(itU64 == (vU64.begin() + kMaxSize));
    rsl::memset(&vU64[0], 0, kMaxSize);

    rsl::vector<int64_t>::iterator itI64 = rsl::fill_n(vI64.begin(), kMaxSize, UINT64_C(0x0123456789abcdef));
    CHECK(rsl::memcheck(&vI64[0], 0x0123456789abcdefui64, kMaxSize) == NULL);
    CHECK(itI64 == (vI64.begin() + kMaxSize));
    rsl::memset(&vI64[0], 0, kMaxSize);

    rsl::vector<uint32_t>::iterator itU32 = rsl::fill_n(vU32.begin(), kMaxSize, UINT32_C(0x01234567));
    CHECK(rsl::memcheck(&vU32[0], 0x01234567u, kMaxSize) == NULL);
    CHECK(itU32 == (vU32.begin() + kMaxSize));
    rsl::memset(&vU32[0], 0, kMaxSize);

    rsl::vector<int32_t>::iterator itI32 = rsl::fill_n(vI32.begin(), kMaxSize, UINT32_C(0x01234567));
    CHECK(rsl::memcheck(&vI32[0], 0x01234567u, kMaxSize) == NULL);
    CHECK(itI32 == (vI32.begin() + kMaxSize));
    rsl::memset(&vI32[0], 0, kMaxSize);

    rsl::vector<uint16_t>::iterator itU16 = rsl::fill_n(vU16.begin(), kMaxSize, UINT16_C(0x0123));
    CHECK(rsl::memcheck(&vU16[0], 0x0123ui16, kMaxSize) == NULL);
    CHECK(itU16 == (vU16.begin() + kMaxSize));
    rsl::memset(&vU16[0], 0, kMaxSize);

    rsl::vector<int16_t>::iterator itI16 = rsl::fill_n(vI16.begin(), kMaxSize, UINT16_C(0x0123));
    CHECK(rsl::memcheck(&vI16[0], 0x0123ui16, kMaxSize) == NULL);
    CHECK(itI16 == (vI16.begin() + kMaxSize));
    rsl::memset(&vI16[0], 0, kMaxSize);
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestFind")
{
  {
    // InputIterator find(InputIterator first, InputIterator last, const T& value)
    rsl::vector<int> intArray;
    intArray.push_back(0);
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);

    rsl::vector<int>::iterator it = find(intArray.begin(), intArray.end(), 2);
    CHECK(it == (intArray.begin() + 2));
    CHECK(*it == 2);

    it = find(intArray.begin(), intArray.end(), 7);
    CHECK(it == intArray.end());
  }


  {
    // InputIterator find_if(InputIterator first, InputIterator last, Predicate predicate)
    // InputIterator find_if_not(InputIterator first, InputIterator last, Predicate predicate)

    int intArray[] = { 3, 2, 6, 5, 4, 1, 2, 4, 5, 4, 1, 2 };

    // Find an item which is equal to 1.
    int* pInt = rsl::find_if(intArray, intArray, [](int i) { return i == 1; }); // No-op
    CHECK(pInt == (intArray));
    pInt = rsl::find_if(intArray, intArray + 12, [](int i) { return i == 1; });
    CHECK(pInt == (intArray + 5));
    pInt = rsl::find_if(intArray, intArray + 12, [](int i) { return i == 99; });
    CHECK(pInt == (intArray + 12));

    pInt = rsl::find_if_not(intArray, intArray + 12, [](int i) { return i == 3; });
    CHECK(pInt == (intArray + 1));

    // Find an item which is equal to 1.
    rsl::test::test_object toArray[] = { rsl::test::test_object(4), rsl::test::test_object(3), rsl::test::test_object(2), rsl::test::test_object(1), rsl::test::test_object(2), rsl::test::test_object(5) };

    rsl::test::test_object* pTO = rsl::find_if(toArray, toArray, [](const rsl::test::test_object& lhs) { return lhs == rsl::test::test_object(1); }); // No-op
    CHECK(pTO == (toArray));
    pTO = rsl::find_if(toArray, toArray + 6, [](const rsl::test::test_object& lhs) { return lhs == rsl::test::test_object(1); });
    CHECK(pTO == (toArray + 3));
    pTO = rsl::find_if(toArray, toArray + 6, [](const rsl::test::test_object& lhs) { return lhs == rsl::test::test_object(99); });
    CHECK(pTO == (toArray + 6));

    pTO = rsl::find_if_not(toArray, toArray + 6, [](const rsl::test::test_object& lhs) { return lhs == rsl::test::test_object(4); });
    CHECK(pTO == (toArray + 1));

    // Find an item which is equal to 1.
    rsl::forward_list<int> intList;
    intList.push_front(4);
    intList.push_front(3);
    intList.push_front(2);
    intList.push_front(1);
    intList.push_front(2);
    intList.push_front(5);

    // The list is now: { 5, 2, 1, 2, 3, 4 }
    rsl::forward_list<int>::iterator it = find_if(intList.begin(), intList.begin(), [](int i) { return i == 1; }); // No-op
    CHECK(it == intList.begin());
    it = find_if(intList.begin(), intList.end(), [](int i) { return i == 1; });
    CHECK(*it == 1);
    it = find_if(intList.begin(), intList.end(), [](int i) { return i == 99; });
    CHECK(it == intList.end());

    it = find_if_not(intList.begin(), intList.end(), [](int i) { return i == 5; });
    CHECK(*it == 2);
  }


  {
    // ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
    // ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate)

    int intArray1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int intArray2[3] = { 7, 6, 5 };

    int* pInt = rsl::find_first_of(intArray1, intArray1, intArray2, intArray2 + 3);
    CHECK(pInt == intArray1);
    pInt = rsl::find_first_of(intArray1, intArray1 + 10, intArray2, intArray2);
    CHECK(pInt == intArray1 + 10);
    pInt = rsl::find_first_of(intArray1, intArray1 + 10, intArray2, intArray2 + 3);
    CHECK(pInt == intArray1 + 5);

    pInt = rsl::find_first_of(intArray1, intArray1, intArray2, intArray2 + 3, rsl::equal_to<int>());
    CHECK(pInt == intArray1);
    pInt = rsl::find_first_of(intArray1, intArray1 + 10, intArray2, intArray2, rsl::equal_to<int>());
    CHECK(pInt == intArray1 + 10);
    pInt = rsl::find_first_of(intArray1, intArray1 + 10, intArray2, intArray2 + 3, rsl::equal_to<int>());
    CHECK(pInt == intArray1 + 5);
  }


  {
    // ForwardIterator1 find_first_not_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
    // ForwardIterator1 find_first_not_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2), BinaryPredicate predicate)

    int intArray1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int intArray2[3] = { 0, 1, 2 };

    int* pInt = rsl::find_first_not_of(intArray1, intArray1, intArray2, intArray2 + 3);
    CHECK(pInt == intArray1);
    pInt = rsl::find_first_not_of(intArray1, intArray1 + 10, intArray2, intArray2);
    CHECK(pInt == intArray1);
    pInt = rsl::find_first_not_of(intArray1, intArray1 + 10, intArray2, intArray2 + 3);
    CHECK(pInt == intArray1 + 3);

    pInt = rsl::find_first_not_of(intArray1, intArray1, intArray2, intArray2 + 3, rsl::equal_to<int>());
    CHECK(pInt == intArray1);
    pInt = rsl::find_first_not_of(intArray1, intArray1 + 10, intArray2, intArray2, rsl::equal_to<int>());
    CHECK(pInt == intArray1 + 0);
    pInt = rsl::find_first_not_of(intArray1, intArray1 + 10, intArray2, intArray2 + 3, rsl::equal_to<int>());
    CHECK(pInt == intArray1 + 3);
  }


  {
    // ForwardIterator1 find_last_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
    // ForwardIterator1 find_last_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate)

    int intArray1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int intArray2[3] = { 3, 4, 5 };

    int* pInt = rsl::find_last_of(intArray1, intArray1, intArray2, intArray2 + 3);
    CHECK(pInt == intArray1);
    pInt = rsl::find_last_of(intArray1, intArray1 + 10, intArray2, intArray2);
    CHECK(pInt == intArray1 + 10);
    pInt = rsl::find_last_of(intArray1, intArray1 + 10, intArray2, intArray2 + 3);
    CHECK(pInt == intArray1 + 5);

    pInt = rsl::find_last_of(intArray1, intArray1, intArray2, intArray2 + 3, rsl::equal_to<int>());
    CHECK(pInt == intArray1);
    pInt = rsl::find_last_of(intArray1, intArray1 + 10, intArray2, intArray2, rsl::equal_to<int>());
    CHECK(pInt == intArray1 + 10);
    pInt = rsl::find_last_of(intArray1, intArray1 + 10, intArray2, intArray2 + 3, rsl::equal_to<int>());
    CHECK(pInt == intArray1 + 5);
  }


  {
    // ForwardIterator1 find_last_not_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
    // ForwardIterator1 find_last_not_of(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2), BinaryPredicate predicate)

    int intArray1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int intArray2[3] = { 7, 8, 9 };

    int* pInt = rsl::find_last_not_of(intArray1, intArray1, intArray2, intArray2 + 3);
    CHECK(pInt == intArray1);
    pInt = rsl::find_last_not_of(intArray1, intArray1 + 10, intArray2, intArray2);
    CHECK(pInt == intArray1 + 10);
    pInt = rsl::find_last_not_of(intArray1, intArray1 + 10, intArray2, intArray2 + 3);
    CHECK(pInt == intArray1 + 6);

    pInt = rsl::find_last_not_of(intArray1, intArray1, intArray2, intArray2 + 3, rsl::equal_to<int>());
    CHECK(pInt == intArray1);
    pInt = rsl::find_last_not_of(intArray1, intArray1 + 10, intArray2, intArray2, rsl::equal_to<int>());
    CHECK(pInt == intArray1 + 10);
    pInt = rsl::find_last_not_of(intArray1, intArray1 + 10, intArray2, intArray2 + 3, rsl::equal_to<int>());
    CHECK(pInt == intArray1 + 6);
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestForEach")
{
  {
    // Function for_each(InputIterator first, InputIterator last, Function function)

    rsl::deque<int> intDeque(1000);
    rsl::test::set_incremental_integers<int> sii; // We define this class at the top of this file.
    card32 i;

    sii = rsl::for_each(intDeque.begin(), intDeque.end(), sii);
    CHECK(sii.x() == 1000);
    for (i = 0; i < 1000; i++)
    {
      if (intDeque[i] != (int)i)
      {
        break;
      }
    }
    CHECK(i == 1000);


    rsl::array<int, 1000> intArray;
    sii.reset();

    sii = for_each(intArray.begin(), intArray.end(), sii);
    CHECK(sii.x() == 1000);
    for (i = 0; i < 1000; i++)
    {
      if (intArray[i] != (int)i)
      {
        break;
      }
    }
    CHECK(i == 1000);
  }

  // for_each_n
  {
    {
      rsl::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      for_each_n(v.begin(), 5, [](auto& e) { e += 10; });

      rsl::vector<int> expected = { 10, 11, 12, 13, 14, 5, 6, 7, 8, 9 };
      CHECK(v == expected);
    }

    // verify lambda can return a result that is ignored.
    {
      rsl::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      for_each_n(v.begin(), 5, [](auto& e) { e += 10; return 42; });

      rsl::vector<int> expected = { 10, 11, 12, 13, 14, 5, 6, 7, 8, 9 };
      CHECK(v == expected);
    }
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestGenerate")
{
  {
    // void generate(ForwardIterator first, ForwardIterator last, Generator generator)
    // OutputIterator generate_n(OutputIterator first, Size n, Generator generator)
    rsl::test::rand rng(rsl::test::rand_seed());

    rsl::deque<int> intDeque((card32)rng.rand_range(100, 1000));
    rsl::test::generate_incremental_integers<int> gii(0); // We define this class at the top of this file.
    int i, iEnd;

    rsl::generate(intDeque.begin(), intDeque.end(), gii);
    for (i = 0, iEnd = (int)intDeque.size(); i < iEnd; i++)
    {
      if (intDeque[(card32)i] != i)
      {
        break;
      }
    }
    CHECK(i == iEnd);


    rsl::array<int, 1000> intArray;
    gii.reset(0);

    rsl::generate(intArray.begin(), intArray.end(), gii);
    for (i = 0; i < 1000; i++)
    {
      if (intArray[(card32)i] != i)
        break;
    }
    CHECK(i == 1000);
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestTransform")
{
  {
    // OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperation unaryOperation)
    rsl::test::rand rng(rsl::test::rand_seed());

    rsl::deque<int> intDeque((card32)rng.rand_range(1, 1000));
    int i, iEnd;

    for (i = 0, iEnd = (int)intDeque.size(); i < iEnd; i++)
    {
      intDeque[(card32)i] = 1;
    }
    rsl::transform(intDeque.begin(), intDeque.begin(), intDeque.begin(), rsl::negate<int>()); // No-op
    CHECK(intDeque[0] == 1); // Verify nothing happened
    rsl::transform(intDeque.begin(), intDeque.end(), intDeque.begin(), rsl::negate<int>());
    for (i = 0, iEnd = (int)intDeque.size(); i < iEnd; i++)
    {
      if (intDeque[(card32)i] != -1)
      {
        break;
      }
    }
    CHECK(i == iEnd);


    rsl::forward_list<rsl::test::test_object> sList;
    for (i = 0, iEnd = rng.rand_range(1, 100); i < iEnd; i++)
    {
      sList.push_front(rsl::test::test_object(1));
    }
    rsl::transform(sList.begin(), sList.begin(), sList.begin(), TestObjectNegate()); // No-op
    CHECK(sList.front() == rsl::test::test_object(1));
    rsl::transform(sList.begin(), sList.end(), sList.begin(), TestObjectNegate()); // TestObjectNegate is a custom function we define for this test.
    rsl::forward_list<rsl::test::test_object>::iterator it = sList.begin();
    for (; it != sList.end(); it++)
    {
      if (!(*it == rsl::test::test_object(-1)))
      {
        break;
      }
    }
    CHECK(it == sList.end());
  }

  {
    // OutputIterator transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result, BinaryOperation binaryOperation)

    rsl::array intArray1 = { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 };
    rsl::array intArray2 = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

    auto pInt = transform(intArray1.cbegin(), intArray1.cbegin(), intArray2.cbegin(), intArray2.begin(), rsl::plus<int>());
    CHECK(pInt == intArray2.cbegin());
    CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
    CHECK(intArray2 == rsl::array{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 });

    pInt = transform(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin(), intArray2.begin(), rsl::plus<int>());
    CHECK(pInt == intArray2.cbegin() + 12);
    CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
    CHECK(intArray2 == rsl::array{ 3, 3, 4, 4, 3, 3, 4, 4, 3, 3, 4, 4 });
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestEqual")
{
  // bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
  // bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate predicate)
  rsl::test::rand rng(rsl::test::rand_seed());

  rsl::vector<card32> intArray(100_size);
  rsl::list<card32>   intList(100);
  rsl::generate(intArray.begin(), intArray.end(), rng);
  rsl::copy(intArray.begin(), intArray.end(), intList.begin());

  bool b = equal(intArray.begin(), intArray.begin(), (card32*)NULL);
  CHECK(b);
  b = equal(intArray.begin(), intArray.end(), intList.begin());
  CHECK(b);
  intArray[50] += 1;
  b = equal(intArray.begin(), intArray.end(), intList.begin());
  CHECK(!b);

  intArray[50] -= 1; // resulttore its original value so the containers are equal again.
  b = equal(intArray.begin(), intArray.begin(), (card32*)NULL, rsl::equal_to<card32>());
  CHECK(b);
  b = equal(intArray.begin(), intArray.end(), intList.begin(), rsl::equal_to<card32>());
  CHECK(b);
  intArray[50] += 1;
  b = equal(intArray.begin(), intArray.end(), intList.begin(), rsl::equal_to<card32>());
  CHECK(!b);

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestIdentical")
{
  // bool identical(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
  // bool identical(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryPredicate predicate)
  rsl::test::rand rng(rsl::test::rand_seed());

  rsl::vector<card32> intArray(100_size);
  rsl::list<card32>   intList(100);
  rsl::generate(intArray.begin(), intArray.end(), rng);
  rsl::copy(intArray.begin(), intArray.end(), intList.begin());


  bool b = equal_range(intArray.begin(), intArray.begin(), (card32*)NULL, (card32*)NULL);
  CHECK(b);
  b = equal_range(intArray.begin(), intArray.end(), intList.begin(), intList.end());
  CHECK(b);
  b = equal_range(intArray.begin(), intArray.end() - 10, intList.begin(), intList.end());
  CHECK(!b);
  b = equal_range(intList.begin(), intList.end(), intArray.begin() + 10, intArray.end());
  CHECK(!b);
  intArray[50] += 1;
  b = equal_range(intArray.begin(), intArray.end(), intList.begin(), intList.end());
  CHECK(!b);


  intArray[50] -= 1; // resulttore its original value so the containers are equal again.
  b = equal_range(intArray.begin(), intArray.begin(), (card32*)NULL, (card32*)NULL, rsl::equal_to<card32>());
  CHECK(b);
  b = equal_range(intArray.begin(), intArray.end(), intList.begin(), intList.end(), rsl::equal_to<card32>());
  CHECK(b);
  b = equal_range(intArray.begin(), intArray.end() - 10, intList.begin(), intList.end(), rsl::equal_to<card32>());
  CHECK(!b);
  b = equal_range(intList.begin(), intList.end(), intArray.begin() + 10, intArray.end(), rsl::equal_to<card32>());
  CHECK(!b);
  intArray[50] += 1;
  b = equal_range(intArray.begin(), intArray.end(), intList.begin(), intList.end(), rsl::equal_to<card32>());
  CHECK(!b);

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestLexicographicalCompare")
{
  {
    // bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    // bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare compare)

    int intArray1[6] = { 0, 1, 2, 3, 4, 5 };
    int intArray2[6] = { 0, 1, 2, 3, 4, 6 };
    int intArray3[5] = { 0, 1, 2, 3, 4 };

    bool b = rsl::lexicographical_compare(intArray1, intArray1, intArray2, intArray2); // Test empty range.
    CHECK(!b);
    b = rsl::lexicographical_compare(intArray1, intArray1 + 6, intArray2, intArray2 + 6);
    CHECK(b);
    b = rsl::lexicographical_compare(intArray2, intArray2 + 6, intArray1, intArray1 + 6);
    CHECK(!b);
    b = rsl::lexicographical_compare(intArray1, intArray1 + 6, intArray3, intArray3 + 5);
    CHECK(!b);

    b = rsl::lexicographical_compare(intArray1, intArray1, intArray2, intArray2, rsl::greater<int>()); // Test empty range.
    CHECK(!b);
    b = rsl::lexicographical_compare(intArray1, intArray1 + 6, intArray2, intArray2 + 6, rsl::greater<int>());
    CHECK(!b);
    b = rsl::lexicographical_compare(intArray2, intArray2 + 6, intArray1, intArray1 + 6, rsl::greater<int>());
    CHECK(b);
    b = rsl::lexicographical_compare(intArray3, intArray3 + 5, intArray1, intArray1 + 6, rsl::less<int>());
    CHECK(b);
  }

  {
    // bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    // bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare compare)

    char* cstr = nullptr;

    bool b = rsl::lexicographical_compare(cstr, cstr, cstr, cstr);
    CHECK(!b);
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestLowerBound")
{
  // ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value)
  // ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
  rsl::test::rand rng(rsl::test::rand_seed());

  int i;

  int* pInt = rsl::lower_bound((int*)NULL, (int*)NULL, 100);
  CHECK(pInt == NULL);

  constexpr card32 max_tries = 50;
  for (i = 0; i < max_tries; i++)
  {
    rsl::deque<int> intDeque((card32)rng.rand_range(1, 500));

    for (int j = 0, jEnd = (int)intDeque.size(); j < jEnd; j++)
      intDeque[(card32)j] = (int)rng.rand_limit(jEnd / 2); // This will result in both gaps and duplications.

    for (int k = 0, kEnd = (int)intDeque.size(); k < kEnd; k++)
    {
      rsl::deque<int>::iterator it = rsl::lower_bound(intDeque.begin(), intDeque.end(), k);

      if (it != intDeque.begin())
        CHECK(*(it - 1) < k);

      if (it != intDeque.end())
        CHECK(((k < *it) || !(*it < k))); // Verify tha k <= *it by using only operator<
    }
  }

  for (i = 0; i < max_tries; i++)
  {
    rsl::list<rsl::test::test_object> toList;
    int              nSize = (int)rng.rand_range(1, 500);

    for (int j = 0, jEnd = nSize; j < jEnd; j++)
      toList.push_back(rsl::test::test_object((int)rng.rand_limit(jEnd / 2))); // This will result in both gaps and duplications.

    for (int k = 0; k < nSize; k++)
    {
      rsl::test::test_object toK(k);
      rsl::list<rsl::test::test_object>::iterator it = lower_bound(toList.begin(), toList.end(), toK);

      if (it != toList.begin())
      {
        --it;
        CHECK(*it < toK);
        ++it;
      }

      if (it != toList.end())
        CHECK(((toK < *it) || !(*it < toK))); // Verify tha k <= *it by using only operator<
    }
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestUpperBound")
{
  // ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value)
  // ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
  rsl::test::rand rng(rsl::test::rand_seed());

  int i;

  int* pInt = rsl::upper_bound((int*)NULL, (int*)NULL, 100);
  CHECK(pInt == NULL);

  constexpr card32 max_tries = 50;
  for (i = 0; i < max_tries; i++)
  {
    rsl::deque<int> intDeque((card32)rng.rand_range(1, 500));

    for (card32 j = 0, jEnd = intDeque.size(); j < jEnd; j++)
      intDeque[j] = (int)rng.rand_limit((uint32_t)jEnd / 2); // This will result in both gaps and duplications.

    for (int k = 0, kEnd = (int)intDeque.size(); k < kEnd; k++)
    {
      rsl::deque<int>::iterator it = rsl::upper_bound(intDeque.begin(), intDeque.end(), k);

      if (it != intDeque.begin())
        CHECK(((*(it - 1) < k) || !(k < *(it - 1)))); // Verify tha *it <= k by using only operator<

      if (it != intDeque.end())
        CHECK(k < *it);
    }
  }

  for (i = 0; i < max_tries; i++)
  {
    rsl::list<rsl::test::test_object> toList;
    int              nSize = (int)rng.rand_range(1, 500);

    for (int j = 0, jEnd = nSize; j < jEnd; j++)
      toList.push_back(rsl::test::test_object((int)rng.rand_limit(jEnd / 2))); // This will result in both gaps and duplications.

    for (int k = 0; k < nSize; k++)
    {
      rsl::test::test_object toK(k);
      rsl::list<rsl::test::test_object>::iterator it = upper_bound(toList.begin(), toList.end(), toK);

      if (it != toList.begin())
      {
        --it;
        CHECK(((*it < toK) || !(toK < *it))); // Verify tha *it <= k by using only operator<
        ++it;
      }

      if (it != toList.end())
        CHECK(toK < *it);
    }
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestEqualRange")
{
  {
    // pair<ForwardIterator, ForwardIterator> equal_range(ForwardIterator first, ForwardIterator last, const T& value)
    // pair<ForwardIterator, ForwardIterator> equal_range(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
    rsl::test::rand rng(rsl::test::rand_seed());

    int i;

    rsl::equal_range_result<int*> pInt = rsl::equal_range((int*)NULL, (int*)NULL, 100);
    CHECK(pInt.first_it == NULL);
    CHECK(pInt.second_it == NULL);

    constexpr card32 max_tries = 50;
    for (i = 0; i < max_tries; i++)
    {
      rsl::deque<int> intDeque((card32)rng.rand_range(1, 500));

      for (int j = 0, jEnd = (int)intDeque.size(); j < jEnd; j++)
        intDeque[(card32)j] = (int)rng.rand_limit(jEnd / 2); // This will result in both gaps and duplications.

      for (int k = 0, kEnd = (int)intDeque.size(); k < kEnd; k++)
      {
        rsl::equal_range_result<rsl::deque<int>::iterator> res = rsl::equal_range(intDeque.begin(), intDeque.end(), k);

        // Test it.first as lower_bound.
        if (res.first_it != intDeque.begin())
          CHECK(*(res.first_it - 1) < k);

        if (res.first_it != intDeque.end())
          CHECK(((k < *res.first_it) || !(*res.first_it < k))); // Verify tha k <= *it by using only operator<

        // Test it.second as upper_bound.
        if (res.second_it != intDeque.begin())
          CHECK(((*(res.second_it - 1) < k) || !(k < *(res.second_it - 1)))); // Verify tha *it <= k by using only operator<

        if (res.second_it != intDeque.end())
          CHECK(k < *res.second_it);
      }
    }


    for (i = 0; i < max_tries; i++)
    {
      rsl::list<rsl::test::test_object> toList;
      int              nSize = (int)rng.rand_range(1, 500);

      for (int j = 0, jEnd = nSize; j < jEnd; j++)
        toList.push_back(rsl::test::test_object((int)rng.rand_limit(jEnd / 2))); // This will result in both gaps and duplications.

      for (int k = 0; k < nSize; k++)
      {
        rsl::test::test_object toK(k);
        rsl::equal_range_result it = equal_range(toList.begin(), toList.end(), toK);

        // Test it.first as lower_bound
        if (it.first_it != toList.begin())
        {
          --it.first_it;
          CHECK(*it.first_it < toK);
          ++it.first_it;
        }

        if (it.first_it != toList.end())
          CHECK(((toK < *it.first_it) || !(*it.first_it < toK))); // Verify tha k <= *it by using only operator<

        // Test it.second as upper_bound
        if (it.second_it != toList.begin())
        {
          --it.second_it;
          CHECK(((*it.second_it < toK) || !(toK < *it.second_it))); // Verify tha *it <= k by using only operator<
          ++it.second_it;
        }

        if (it.second_it != toList.end())
          CHECK(toK < *it.second_it);
      }
    }
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestReplace")
{
  // void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
  // void replace_if(ForwardIterator first, ForwardIterator last, Predicate predicate, const T& new_value)

  {
    int intArray[8] = { 0, 3, 2, 7, 5, 4, 5, 3, };

    // Convert 3s to 99s.
    rsl::replace(intArray, intArray, 3, 99); // No-op
    CHECK(((intArray[1] == 3) && (intArray[7] == 3)));
    rsl::replace(intArray, intArray + 8, 3, 99); // No-op
    CHECK(((intArray[1] == 99) && (intArray[7] == 99)));

    // Convert 99s to 88s.
    rsl::replace_if(intArray, intArray, [](int i) { return i == 99; }, 88); // No-op
    CHECK(((intArray[1] == 99) && (intArray[7] == 99)));
    rsl::replace_if(intArray, intArray + 8, [](int i) { return i == 99; }, 88);
    CHECK(((intArray[1] == 88) && (intArray[7] == 88)));


    rsl::forward_list<rsl::test::test_object> toList;
    rsl::forward_list<rsl::test::test_object>::iterator it;
    toList.push_front(rsl::test::test_object(3));
    toList.push_front(rsl::test::test_object(5));
    toList.push_front(rsl::test::test_object(4));
    toList.push_front(rsl::test::test_object(5));
    toList.push_front(rsl::test::test_object(7));
    toList.push_front(rsl::test::test_object(2));
    toList.push_front(rsl::test::test_object(3));
    toList.push_front(rsl::test::test_object(0));

    // Convert 3s to 99s.
    replace(toList.begin(), toList.begin(), rsl::test::test_object(3), rsl::test::test_object(99)); // No-op
    it = toList.begin();
    advance(it, 1);
    CHECK(*it == rsl::test::test_object(3));
    advance(it, 6);
    CHECK(*it == rsl::test::test_object(3));
    replace(toList.begin(), toList.end(), rsl::test::test_object(3), rsl::test::test_object(99));
    it = toList.begin();
    advance(it, 1);
    CHECK(*it == rsl::test::test_object(99));
    advance(it, 6);
    CHECK(*it == rsl::test::test_object(99));

    // Convert 99s to 88s.
    replace_if(toList.begin(), toList.begin(), [](const rsl::test::test_object& lhs) { return lhs == rsl::test::test_object(99); }, rsl::test::test_object(88)); // No-op
    it = toList.begin();
    advance(it, 1);
    CHECK(*it == rsl::test::test_object(99));
    advance(it, 6);
    CHECK(*it == rsl::test::test_object(99));
    replace_if(toList.begin(), toList.end(), [](const rsl::test::test_object& lhs) { return lhs == rsl::test::test_object(99); }, rsl::test::test_object(88));
    it = toList.begin();
    advance(it, 1);
    CHECK(*it == rsl::test::test_object(88));
    advance(it, 6);
    CHECK(*it == rsl::test::test_object(88));
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestRemoveCopy")
{
  {
    // OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value)
    // OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate predicate)

    rsl::array intArray1 = { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 };
    rsl::array intArray2 = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

    auto pInt = remove_copy(intArray1.cbegin(), intArray1.cbegin(), intArray2.begin(), 1); // No-op
    CHECK(pInt == intArray2.cbegin());
    CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
    CHECK(intArray2 == rsl::array{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 });

    pInt = remove_copy(intArray1.cbegin(), intArray1.cbegin() + 12, intArray2.begin(), 1);
    CHECK(pInt == intArray2.cbegin() + 6);
    CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
    CHECK(intArray2 == rsl::array{ 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3 });

    pInt = remove_copy_if(intArray1.cbegin(), intArray1.cbegin(), intArray2.begin(), [](int i) { return i == 0; }); // No-op
    CHECK(pInt == intArray2.cbegin());
    CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
    CHECK(intArray2 == rsl::array{ 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3 });

    pInt = remove_copy_if(intArray1.cbegin(), intArray1.cbegin() + 12, intArray2.begin(), [](int i) { return i == 0; });
    CHECK(pInt == intArray2.cbegin() + 6);
    CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
    CHECK(intArray2 == rsl::array{ 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3 });
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestRemove")
{
  // ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value)
  // ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate predicate)

  rsl::array intArray1 = { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 };
  rsl::array intArray2 = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

  auto pInt = remove(intArray1.begin(), intArray1.begin(), 1);
  CHECK(pInt == intArray1.begin());
  CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
  pInt = remove(intArray1.begin(), intArray1.begin() + 12, 1);
  CHECK(pInt == intArray1.begin() + 6);
  CHECK(intArray1 == rsl::array{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 });

  pInt = remove(intArray2.begin(), intArray2.begin(), 1);
  CHECK(pInt == intArray2.begin());
  CHECK(intArray2 == rsl::array{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 });
  pInt = remove(intArray2.begin(), intArray2.begin() + 12, 1);
  CHECK(pInt == intArray2.begin() + 12);
  CHECK(intArray2 == rsl::array{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 });

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestReplaceCopy")
{
  // OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_value, const T& new_value)
  // OutputIterator replace_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate predicate, const T& new_value)

  rsl::array intArray1 = { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 };
  rsl::array intArray2 = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

  auto pInt = replace_copy(intArray1.cbegin(), intArray1.cbegin(), intArray2.begin(), 1, 4);
  CHECK(pInt == intArray2.cbegin());
  CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
  CHECK(intArray2 == rsl::array{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 });

  pInt = replace_copy(intArray1.cbegin(), intArray1.cbegin() + 12, intArray2.begin(), 1, 4);
  CHECK(pInt == intArray2.cbegin() + 12);
  CHECK(intArray1 == rsl::array{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 });
  CHECK(intArray2 == rsl::array{ 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4 });

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestReverse")
{
  {
    // void reverse(BidirectionalIterator first, BidirectionalIterator last)

    rsl::vector<int> intArray;
    for (int i = 0; i < 10; i++)
      intArray.push_back(i);

    rsl::reverse(intArray.begin(), intArray.begin()); // No-op
    CHECK(intArray == rsl::vector{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    reverse(intArray.begin(), intArray.end());
    CHECK(intArray == rsl::vector{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 });


    rsl::list<rsl::test::test_object> toList;
    for (int j = 0; j < 10; j++)
    {
      toList.push_back(rsl::test::test_object(j));
    }

    reverse(toList.begin(), toList.begin()); // No-op
    CHECK(toList.front() == rsl::test::test_object(0));
    CHECK(toList.back() == rsl::test::test_object(9));

    reverse(toList.begin(), toList.end());
    CHECK(toList.front() == rsl::test::test_object(9));
    CHECK(toList.back() == rsl::test::test_object(0));

    // Verify that reversing an empty range executes without exception.
    reverse(toList.begin(), toList.begin());
  }


  {
    // reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result)

    rsl::vector<int> intArray1;
    rsl::array         intArray2 = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };

    for (int i = 0; i < 10; i++)
      intArray1.push_back(i);

    auto pInt = reverse_copy(intArray1.cbegin(), intArray1.cbegin(), intArray2.begin()); // No-op
    CHECK(pInt == intArray2.cbegin());
    CHECK(intArray2 == rsl::array{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 });

    pInt = reverse_copy(intArray1.cbegin(), intArray1.cend(), intArray2.begin());
    CHECK(pInt == intArray2.cbegin() + intArray1.size());
    CHECK(intArray2 == rsl::array{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 });


    rsl::list<rsl::test::test_object> toList;
    rsl::test::test_object       toArray2[10];

    for (int j = 0; j < 10; j++)
    {
      toList.push_back(rsl::test::test_object(j));
      toArray2[j] = rsl::test::test_object(5);
    }

    rsl::test::test_object* pTO = reverse_copy(toList.begin(), toList.begin(), toArray2); // No-op
    CHECK(pTO == toArray2);
    CHECK(toArray2[0] == rsl::test::test_object(5));
    CHECK(toArray2[9] == rsl::test::test_object(5));

    pTO = reverse_copy(toList.begin(), toList.end(), toArray2);
    CHECK(pTO == toArray2 + 10);
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestSearch")
{
  {
    // ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
    // ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate)

    // Test via bidirectional/random_access iterator.
    rsl::basic_string<char> sTest("abcdefg abcdefg abcdefg");
    const char* pSubstring1 = " abcd";
    const char* pSubstring2 = "1234";

    rsl::basic_string<char>::iterator iString = search(sTest.begin(), sTest.end(), pSubstring1, pSubstring1 + strlen(pSubstring1));
    CHECK(&*iString == &sTest[7]);

    iString = search(sTest.begin(), sTest.end(), pSubstring1, pSubstring1 + 1); // Search for sequence of 1.
    CHECK(&*iString == &sTest[7]);

    iString = search(sTest.begin(), sTest.end(), pSubstring2, pSubstring2 + strlen(pSubstring2));
    CHECK(&*iString == rsl::iterator_to_pointer(sTest.end()));

    iString = search(sTest.begin(), sTest.end(), pSubstring2, pSubstring2); // Search with empty search pattern.
    CHECK(&*iString == rsl::iterator_to_pointer(sTest.begin()));

    // Test via forward iterator.
    rsl::forward_list<char> sListTest;
    for (rsl::forward_list<char>::size_type i = sTest.size(); i > 0; --i)
      sListTest.push_front(sTest[i - 1]);

    rsl::forward_list<char>::iterator iSlist = search(sListTest.begin(), sListTest.end(), pSubstring1, pSubstring1 + 5);
    rsl::forward_list<char>::iterator i7 = sListTest.begin();
    advance(i7, 7);
    CHECK(iSlist == i7);

    iSlist = search(sListTest.begin(), sListTest.end(), pSubstring2, pSubstring2 + strlen(pSubstring2));
    CHECK(iSlist == sListTest.end());

    iSlist = search(sListTest.begin(), sListTest.end(), pSubstring2, pSubstring2); // Search with empty search pattern.
    CHECK(iSlist == sListTest.begin());
  }


  {
    // ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size count, const T& value)

    const char* pString1 = "Hello wwworld";
    const char* presultult = rsl::search_n(pString1, pString1 + strlen(pString1), 1, 'w');
    CHECK(presultult == pString1 + 6);
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestBinarySearch")
{
  {
    // bool binary_search(ForwardIterator first, ForwardIterator last, const T& value)
    // bool binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)

    // ForwardIterator binary_search_i(ForwardIterator first, ForwardIterator last, const T& value)
    // ForwardIterator binary_search_i(ForwardIterator first, ForwardIterator last, const T& value, Compare compare)

    rsl::vector<int> intArray;
    for (int i = 0; i < 1000; i++)
      intArray.push_back(i);

    bool b = binary_search(intArray.begin(), intArray.begin(), 0);
    CHECK(b == false);

    b = binary_search(intArray.begin(), intArray.begin() + 1, 0);
    CHECK(b == true);

    b = binary_search(intArray.begin(), intArray.end(), 733, rsl::less<int>());
    CHECK(b == true);


    rsl::vector<int>::iterator it = binary_search_it(intArray.begin(), intArray.begin(), 0);
    CHECK(it == intArray.begin());

    it = binary_search_it(intArray.begin(), intArray.begin() + 1, 0, rsl::less<int>());
    CHECK(it == intArray.begin());

    it = binary_search_it(intArray.begin(), intArray.end(), 733);
    CHECK(it == intArray.begin() + 733);


    rsl::list<rsl::test::test_object> toList;
    rsl::list<rsl::test::test_object>::iterator toI;
    for (int j = 0; j < 1000; j++)
    {
      toList.push_back(rsl::test::test_object(j));
    }

    b = rsl::binary_search(toList.begin(), toList.begin(), rsl::test::test_object(0), rsl::less<rsl::test::test_object>());
    CHECK(b == false);

    toI = toList.begin();
    toI++;
    b = binary_search(toList.begin(), toI, rsl::test::test_object(0));
    CHECK(b == true);

    b = binary_search(toList.begin(), toList.end(), rsl::test::test_object(733));
    CHECK(b == true);


    toI = binary_search_it(toList.begin(), toList.begin(), rsl::test::test_object(0), rsl::less<rsl::test::test_object>()); // No-op
    CHECK(toI == toList.begin());

    toI = toList.begin();
    toI++;
    toI = binary_search_it(toList.begin(), toI, rsl::test::test_object(0));
    CHECK(*toI == rsl::test::test_object(0));

    toI = binary_search_it(toList.begin(), toList.end(), rsl::test::test_object(733));
    CHECK(*toI == rsl::test::test_object(733));
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestUnique")
{
  {
    // ForwardIterator unique(ForwardIterator first, ForwardIterator last)
    // ForwardIterator unique(ForwardIterator first, ForwardIterator last, BinaryPredicate predicate)

    rsl::array intArray = { 1, 2, 3, 3, 4, 4 };

    auto pInt = unique(intArray.begin(), intArray.begin() + 0);
    CHECK(pInt == intArray.begin());
    CHECK(intArray == rsl::array{ 1, 2, 3, 3, 4, 4 });

    pInt = unique(intArray.begin(), intArray.begin() + 6, rsl::equal_to<int>());
    CHECK(pInt == intArray.begin() + 4);
    CHECK(intArray == rsl::array{ 1, 2, 3, 4, 4, 4 });


    rsl::test::test_object toArray[] = { rsl::test::test_object(1), rsl::test::test_object(2), rsl::test::test_object(3), rsl::test::test_object(3), rsl::test::test_object(4), rsl::test::test_object(4) };

    rsl::test::test_object* pTO = rsl::unique(toArray, toArray + 6);
    CHECK(pTO == toArray + 4);
    CHECK(toArray[3] == rsl::test::test_object(4));
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestFindEnd")
{
  {
    // ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
    // ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate)

    // Test via bidirectional/random_access iterator.
    rsl::basic_string<char> sTest("abcdefg abcdefg abcdefg");
    const char* pSubstring1 = "abcd";
    const char* pSubstring2 = "1234";

    rsl::basic_string<char>::iterator iString = find_end(sTest.begin(), sTest.end(), pSubstring1, pSubstring1 + 4);
    CHECK(&*iString == &sTest[16]);

    iString = find_end(sTest.begin(), sTest.end(), pSubstring1, pSubstring1 + 4, rsl::equal_to<char>());
    CHECK(&*iString == &sTest[16]);

    iString = find_end(sTest.begin(), sTest.end(), pSubstring2, pSubstring2 + strlen(pSubstring2));
    CHECK(iString == sTest.end());

    iString = find_end(sTest.begin(), sTest.end(), pSubstring2, pSubstring2 + strlen(pSubstring2), rsl::equal_to<char>());
    CHECK(iString == sTest.end());

    // Test via forward iterator.
    rsl::forward_list<char> sListTest;
    for (rsl::forward_list<char>::size_type i = sTest.size(); i > 0; --i)
      sListTest.push_front(sTest[i - 1]);

    rsl::forward_list<char>::iterator iSlist = find_end(sListTest.begin(), sListTest.end(), pSubstring1, pSubstring1 + strlen(pSubstring1));
    rsl::forward_list<char>::iterator i16 = sListTest.begin();
    advance(i16, 16);
    CHECK(iSlist == i16);

    iSlist = find_end(sListTest.begin(), sListTest.end(), pSubstring1, pSubstring1 + strlen(pSubstring1), rsl::equal_to<char>());
    i16 = sListTest.begin();
    advance(i16, 16);
    CHECK(iSlist == i16);

    iSlist = find_end(sListTest.begin(), sListTest.end(), pSubstring2, pSubstring2 + strlen(pSubstring2));
    CHECK(iSlist == sListTest.end());

    iSlist = find_end(sListTest.begin(), sListTest.end(), pSubstring2, pSubstring2 + strlen(pSubstring2), rsl::equal_to<char>());
    CHECK(iSlist == sListTest.end());
  }
 
  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestSetDifference")
{
  // OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  // OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,  OutputIterator result, Compare compare)

  rsl::array intArray1 = { 0, 0, 2, 5, 8, 8, 12, 24, 26, 43 };
  rsl::array intArray2 = { 0, 0, 0, 5, 7, 8, 11, 24, 25, 43 };
  rsl::array intArray3 = { 9, 9, 9, 9, 9, 9,  9,  9,  9,  9 };

  set_difference(intArray1.cbegin(), intArray1.cbegin() + 0, intArray2.cbegin(), intArray2.cbegin() + 0, intArray3.begin());
  CHECK(intArray3 == rsl::array{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 });

  set_difference(intArray1.cbegin(), intArray1.cbegin() + 10, intArray2.cbegin(), intArray2.cbegin() + 10, intArray3.begin());
  CHECK(intArray3 == rsl::array{ 2, 8, 12, 26, 9, 9, 9, 9, 9, 9 });

  intArray3[0] = intArray3[1] = intArray3[2] = 9;

  set_difference(intArray1.cbegin(), intArray1.cbegin() + 10, intArray2.cbegin(), intArray2.cbegin() + 10, intArray3.begin(), rsl::less<int>());
  CHECK(intArray3 == rsl::array{ 2, 8, 12, 26, 9, 9, 9, 9, 9, 9 });

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestSetSymmetricDifference")
{
  // OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  // OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,  OutputIterator result, Compare compare)

  rsl::array intArray1 = { 0, 0, 2, 5, 8, 8, 12, 24, 26, 43 };
  rsl::array intArray2 = { 0, 0, 0, 5, 7, 8, 11, 24, 25, 43 };
  rsl::array intArray3 = { 9, 9, 9, 9, 9, 9,  9,  9,  9,  9 };

  set_symmetric_difference(intArray1.cbegin(), intArray1.cbegin() + 0, intArray2.cbegin(), intArray2.cbegin() + 0, intArray3.begin());
  CHECK(intArray3 == rsl::array{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 });

  set_symmetric_difference(intArray1.cbegin(), intArray1.cbegin() + 10, intArray2.cbegin(), intArray2.cbegin() + 10, intArray3.begin());
  CHECK(intArray3 == rsl::array{ 0, 2, 7, 8, 11, 12, 25, 26, 9, 9 });

  intArray3[0] = intArray3[1] = intArray3[2] = intArray3[4] = intArray3[5] = intArray3[6] = 9;

  set_symmetric_difference(intArray1.cbegin(), intArray1.cbegin() + 10, intArray2.cbegin(), intArray2.cbegin() + 10, intArray3.begin(), rsl::less<int>());
  CHECK(intArray3 == rsl::array{ 0, 2, 7, 8, 11, 12, 25, 26, 9, 9 });

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestSetIntersection")
{
  // OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  // OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare)

  rsl::array intArray1 = { 0, 0, 2, 5, 8, 8, 12, 24, 26, 43 };
  rsl::array intArray2 = { 0, 0, 0, 5, 7, 8, 11, 24, 25, 43 };
  rsl::array intArray3 = { 9, 9, 9, 9, 9, 9,  9,  9,  9,  9 };

  set_intersection(intArray1.cbegin(), intArray1.cbegin() + 0, intArray2.cbegin(), intArray2.cbegin() + 0, intArray3.begin());
  CHECK(intArray3 == rsl::array{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 });

  set_intersection(intArray1.cbegin(), intArray1.cbegin() + 10, intArray2.cbegin(), intArray2.cbegin() + 10, intArray3.begin());
  CHECK(intArray3 == rsl::array{ 0, 0, 5, 8, 24, 43, 9, 9, 9, 9 });

  intArray3[0] = intArray3[1] = intArray3[2] = intArray3[4] = intArray3[5] = intArray3[6] = 9;

  set_intersection(intArray1.cbegin(), intArray1.cbegin() + 10, intArray2.cbegin(), intArray2.cbegin() + 10, intArray3.begin(), rsl::less<int>());
  CHECK(intArray3 == rsl::array{ 0, 0, 5, 8, 24, 43, 9, 9, 9, 9 });

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestSetUnion")
{
  // OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
  // OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare)

  rsl::array intArray1 = { 0, 0, 2, 5, 8, 8, 12, 24, 26, 43 };
  rsl::array intArray2 = { 0, 0, 0, 5, 7, 8, 11, 24, 25, 43 };
  rsl::array intArray3 = { 9, 9, 9, 9, 9, 9,  9,  9,  9,  9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 };

  set_union(intArray1.cbegin(), intArray1.cbegin() + 0, intArray2.cbegin(), intArray2.cbegin() + 0, intArray3.begin());
  CHECK(intArray3 == rsl::array{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 });

  set_union(intArray1.cbegin(), intArray1.cbegin() + 10, intArray2.cbegin(), intArray2.cbegin() + 10, intArray3.begin());
  CHECK(intArray3 == rsl::array{ 0, 0, 0, 2, 5, 7, 8, 8, 11, 12, 24, 25, 26, 43, 9, 9, 9, 9, 9, 9 });

  intArray3[0] = intArray3[1] = intArray3[2] = intArray3[3] = intArray3[4] = intArray3[5] = intArray3[6] = intArray3[7] = intArray3[8] = intArray3[9] = intArray3[10] = intArray3[11] = 9;

  set_union(intArray1.cbegin(), intArray1.cbegin() + 10, intArray2.cbegin(), intArray2.cbegin() + 10, intArray3.begin(), rsl::less<int>());
  CHECK(intArray3 == rsl::array{ 0, 0, 0, 2, 5, 7, 8, 8, 11, 12, 24, 25, 26, 43, 9, 9, 9, 9, 9, 9 });

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestIsPermutation")
{
  // template<typename ForwardIterator1, typename ForwardIterator2>
  // bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)

  // template<typename ForwardIterator1, typename ForwardIterator2, class BinaryPredicate>
  // bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate predicate)
  rsl::test::rand rng(rsl::test::rand_seed());

  {

    rsl::array intArray1 = { 0, 1, 2, 3, 4 };
    rsl::array intArray2 = { 0, 1, 2, 3, 4 };

    // Test an empty set.
    CHECK(rsl::is_permutation(intArray1.cbegin(), intArray1.cbegin() + 0, intArray2.cbegin()));

    // Test two identical sets.
    CHECK(rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin()));
    rsl::random_shuffle(intArray1.begin(), intArray1.end(), rng);

    // Test order randomization.
    CHECK(rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin()));
    rsl::random_shuffle(intArray2.begin(), intArray2.end(), rng);
    CHECK(rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin()));

    // Test the case where there's a difference.
    intArray2[4] = intArray2[3]; // This change guarantees is_permutation will return false.
    CHECK(!rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin()));
  }

  {

    rsl::array intArray1 = { 0, 0, 0, 1, 1 };
    rsl::array intArray2 = { 0, 0, 0, 1, 1 };

    // Test two identical sets.
    CHECK(rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin()));
    rsl::random_shuffle(intArray1.begin(), intArray1.end(), rng);

    // Test order randomization.
    CHECK(rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin()));
    rsl::random_shuffle(intArray2.begin(), intArray2.end(), rng);
    CHECK(rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin()));

    // Test the case where there's a difference.
    intArray2[4] = (intArray2[4] == 0) ? 1 : 0;
    CHECK(!rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin()));
  }

  for (int n = 0; n < 100000; n++)
  {
    rsl::array<card32, 6> intArray1;
    rsl::array<card32, 6> intArray2;

    for (count_t i = 0; i < intArray1.size(); i++)
    {
      intArray1[i] = rng.rand_limit(6);
      intArray2[i] = rng.rand_limit(6);
    }

    bool isPermutation = rsl::is_permutation(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin());

    // If is_permutation returned true, then sorted versions of the two arrays should be identical.
    rsl::sort(intArray1.begin(), intArray1.end());
    rsl::sort(intArray2.begin(), intArray2.end());

    rsl::mismatch_result mismatchResult = rsl::mismatch(intArray1.cbegin(), intArray1.cend(), intArray2.cbegin());
    bool isIdentical = (mismatchResult.lhs_it == (intArray1.cend()));

    CHECK(isPermutation == isIdentical); // With an array size of 6, isPermutation ends up being true about 1 in 400 times here.
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestNextPermutation")
{
  //template<typename BidirectionalIterator>
  //bool next_permutation(BidirectionalIterator first, BidirectionalIterator last);

  //template<typename BidirectionalIterator, typename Compare>
  //bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare compare);

  uint64_t    count;
  rsl::vector<int> intArray;
  for (int i = 0; i < 8; i++)
  {
    intArray.push_back(i);
  }

  count = 0;
  do {
    ++count;
  } while (next_permutation(intArray.begin(), intArray.end()));
  CHECK(count == 40320); // count = n!
  CHECK(is_sorted(intArray.begin(), intArray.end()));

  count = 0;
  do {
    ++count;
  } while (next_permutation(intArray.begin(), intArray.end(), rsl::less<int>()));
  CHECK(count == 40320); // count = n!
  CHECK(is_sorted(intArray.begin(), intArray.end()));

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}


TEST_CASE("TestRotate")
{
  // template <typename ForwardIterator>
  // ForwardIterator rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last);
  rsl::test::rand rng(rsl::test::rand_seed());

  // rsl::array (ContiguousIterator/Pointer)
  const card32 kRotateArraySize = 10;
  typedef rsl::array<int, kRotateArraySize> IntArray;

  {   // This type is templated, so we can't run a loop over various sizes.
    IntArray intArray;

    for (card32 i = 0; i < kRotateArraySize; i++)
    {
      rsl::generate_n(intArray.begin(), kRotateArraySize, rsl::test::generate_incremental_integers<int>());
      IntArray::iterator intArrayItMiddle = rsl::next(intArray.begin(), i);
      IntArray::iterator intArrayIt = rsl::rotate(intArray.begin(), intArrayItMiddle, intArray.end());

      for (card32 j = 0; j < kRotateArraySize; j++)
      {
        if (intArrayIt == intArray.end())
          intArrayIt = intArray.begin();
        CHECK(*intArrayIt++ == (int)j);
      }
    }
  }

  // rsl::vector (ContiguousIterator)
  typedef rsl::vector<int> IntVector;

  for (card32 s = 10; s < 500; s += (card32)rng.rand_range(50, 100))
  {
    IntVector intVector(rsl::Size(s), 0);

    for (card32 i = 0; i < s; i++)
    {
      rsl::generate_n(intVector.begin(), s, rsl::test::generate_incremental_integers<int>());
      IntVector::iterator intVectorItMiddle = rsl::next(intVector.begin(), i);
      IntVector::iterator intVectorIt = rsl::rotate(intVector.begin(), intVectorItMiddle, intVector.end());

      for (card32 j = 0; j < s; j++)
      {
        if (intVectorIt == intVector.end())
          intVectorIt = intVector.begin();
        CHECK(*intVectorIt++ == (int)j);
      }
    }
  }

  // rsl::deque (RandomAccessIterator)
  typedef rsl::deque<int> IntDeque;

  for (card32 s = 10; s < 500; s += (card32)rng.rand_range(50, 100))
  {
    IntDeque intDeque(s, 0);

    for (card32 i = 0; i < s; i++)
    {
      rsl::generate_n(intDeque.begin(), s, rsl::test::generate_incremental_integers<int>());
      IntDeque::iterator intDequeItMiddle = rsl::next(intDeque.begin(), i);
      IntDeque::iterator intDequeIt = rsl::rotate(intDeque.begin(), intDequeItMiddle, intDeque.end());

      for (card32 j = 0; j < s; j++)
      {
        if (intDequeIt == intDeque.end())
          intDequeIt = intDeque.begin();
        CHECK(*intDequeIt++ == (int)j);
      }
    }
  }

  // rsl::list (BidirectionalIterator)
  typedef rsl::list<int> IntList;

  for (card32 s = 10; s < 500; s += (card32)rng.rand_range(50, 100))
  {
    IntList intList(s, 0);

    for (card32 i = 0; i < s; i++)
    {
      rsl::generate_n(intList.begin(), s, rsl::test::generate_incremental_integers<int>());
      IntList::iterator intListItMiddle = rsl::next(intList.begin(), i);
      IntList::iterator intListIt = rsl::rotate(intList.begin(), intListItMiddle, intList.end());

      for (card32 j = 0; j < s; j++)
      {
        if (intListIt == intList.end())
          intListIt = intList.begin();
        CHECK(*intListIt++ == (int)j);
      }
    }
  }

  // rsl::forward_list (ForwardIterator)
  typedef rsl::forward_list<int> IntSlist;

  for (card32 s = 10; s < 500; s += (card32)rng.rand_range(50, 100))
  {
    IntSlist intSlist(s, 0);

    for (card32 i = 0; i < s; i++)
    {
      rsl::generate_n(intSlist.begin(), s, rsl::test::generate_incremental_integers<int>());
      IntSlist::iterator intSlistItMiddle = rsl::next(intSlist.begin(), i);
      IntSlist::iterator intSlistIt = rsl::rotate(intSlist.begin(), intSlistItMiddle, intSlist.end());

      for (card32 j = 0; j < s; j++)
      {
        if (intSlistIt == intSlist.end())
          intSlistIt = intSlist.begin();
        CHECK(*intSlistIt++ == (int)j);
      }
    }
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

TEST_CASE("TestSort")
{
  // test rsl::sort with move-only type
  {
    rsl::vector<rsl::unique_ptr<int>> vec;
    rsl::sort(vec.begin(), vec.end(), [](const rsl::unique_ptr<int>& lhs, const rsl::unique_ptr<int>& rhs) { return *lhs < *rhs; });
  }
  {
    rsl::vector<rsl::unique_ptr<int>> vec;
    rsl::sort(vec.begin(), vec.end());
  }
  {
    rsl::vector<rsl::test::missing_move_constructor> vec;
    rsl::sort(vec.begin(), vec.end(), [](const rsl::test::missing_move_constructor& lhs, const rsl::test::missing_move_constructor& rhs) { return lhs < rhs; });
  }
  {
    rsl::vector<rsl::test::missing_move_constructor> vec;
    rsl::sort(vec.begin(), vec.end());
  }
  {
    rsl::vector<rsl::test::missing_move_assignable> vec;
    rsl::sort(vec.begin(), vec.end(), [](const rsl::test::missing_move_assignable& lhs, const rsl::test::missing_move_assignable& rhs) { return lhs < rhs; });
  }
  {
    rsl::vector<rsl::test::missing_move_assignable> vec;
    rsl::sort(vec.begin(), vec.end());
  }
  {
    rsl::vector<rsl::unique_ptr<int>> vec;
    vec.emplace_back(new int(7));
    vec.emplace_back(new int(-42));
    vec.emplace_back(new int(5));
    rsl::sort(vec.begin(), vec.end(), [](const rsl::unique_ptr<int>& lhs, const rsl::unique_ptr<int>& rhs) { return *lhs < *rhs; });
    CHECK(*vec[0] == -42);
    CHECK(*vec[1] == 5);
    CHECK(*vec[2] == 7);
  }
  {
    rsl::test::rand rng(rsl::test::rand_seed());

    for (unsigned tests = 0; tests < 50; ++tests)
    {
      rsl::vector<rsl::unique_ptr<int>> vec1;

      for (int i = 0; i < 100; ++i)
      {
        int randomNumber = rng();
        vec1.emplace_back(new int(randomNumber));
      }

      auto vec1Cmp = [](const rsl::unique_ptr<int>& lhs, const rsl::unique_ptr<int>& rhs) { return *lhs < *rhs; };
      rsl::sort(vec1.begin(), vec1.end(), vec1Cmp);
      CHECK(rsl::is_sorted(vec1.begin(), vec1.end(), vec1Cmp));
    }
  }

  CHECK(rsl::test::test_object::is_clear());
  rsl::test::test_object::reset();
}

