// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: functional_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "catch2/catch.hpp"

//NOLINTBEGIN

#include "rex_std/functional.h"

int foo()
{
  return 0;
}
int bar()
{
  return 1;
}
int foobar(int x)
{
  return x;
}

TEST_CASE("function creation")
{
  rsl::function<int(void)> f = foo;
  rsl::function<int(void)> f2 = bar;
  rsl::function f3 = foobar;

  REQUIRE(f() == 0);
  REQUIRE(f2() == 1);
  REQUIRE(f3(3) == 3);

  rsl::function<void()> f5;
  REQUIRE(f.operator bool() == true);
  REQUIRE(f5.operator bool() == false);
}
TEST_CASE("function assignment")
{
  rsl::function f = foo;
  rsl::function<int(void)> f2;

  f2 = f;
  REQUIRE(f2() == 0);

  rsl::function<int(void)> f3;
  f2 = f3;

  REQUIRE(f2.operator bool() == false);
}
TEST_CASE("function swapping")
{
  rsl::function f1 = foo;
  rsl::function f2 = bar;
  f2.swap(f1);
  REQUIRE(f1() == 1);
  REQUIRE(f2() == 0);
}
TEST_CASE("reference wrapper")
{
  int i1 = 1;
  int i2 = 2;
  rsl::reference_wrapper<int> i1ref = rsl::ref(i1);
  rsl::reference_wrapper<int> i2ref = rsl::ref(i2);

  REQUIRE(i1ref.get() == i1);
  REQUIRE(i2ref.get() == i2);

  i1 = 3;

  REQUIRE(i1ref.get() == 3);
  REQUIRE(i1 == 3);
  
  i1 = i2;
  REQUIRE(i2ref.get() == i1ref.get());
  REQUIRE(i1ref.get() == 2);
  REQUIRE(i1 == 2);
}
TEST_CASE("functional plus")
{
  rsl::plus<int> op;

  REQUIRE(op(1, 1) == 2);
  REQUIRE(op(1, 2) == 3);
  REQUIRE(op(1, -2) == -1);
  REQUIRE(op(-1, -2) == -3);
}
TEST_CASE("functional minus")
{
  rsl::minus<int> op;

  REQUIRE(op(1, 1) == 0);
  REQUIRE(op(1, 2) == -1);
  REQUIRE(op(1, -2) == 3);
  REQUIRE(op(-1, -2) == 1);
}
TEST_CASE("functional multiplies")
{
  rsl::multiplies<int> op;

  REQUIRE(op(1, 1) == 1);
  REQUIRE(op(1, 2) == 2);
  REQUIRE(op(1, -2) == -2);
  REQUIRE(op(-1, -2) == 2);
}
TEST_CASE("functional divides")
{
  rsl::divides<int> op;

  REQUIRE(op(1, 1) == 1);
  REQUIRE(op(1, 2) == 0);
  REQUIRE(op(1, -2) == 0);
  REQUIRE(op(-1, -2) == 0);
  REQUIRE(op(10, 2) == 5);
  REQUIRE(op(10, -2) == -5);
}
TEST_CASE("functional modulus")
{
  rsl::modulus<int> op;

  REQUIRE(op(1, 1) == 0);
  REQUIRE(op(1, 2) == 1);
  REQUIRE(op(1, -2) == 1);
  REQUIRE(op(-1, -2) == -1);
  REQUIRE(op(10, 2) == 0);
  REQUIRE(op(10, -2) == 0);
}
TEST_CASE("functional negate")
{
  rsl::negate<int> op;

  REQUIRE(op(1) == -1);
  REQUIRE(op(0) == 0);
  REQUIRE(op(-1) == 1);
}
TEST_CASE("functional less")
{
  rsl::less<int> op;

  REQUIRE(op(1, 1) == false);
  REQUIRE(op(0, 1) == true);
  REQUIRE(op(1, 0) == false);
}
TEST_CASE("functional less equal")
{
  rsl::less_equal<int> op;

  REQUIRE(op(1, 1) == true);
  REQUIRE(op(0, 1) == true);
  REQUIRE(op(1, 0) == false);
}
TEST_CASE("functional equal to")
{
  rsl::equal_to<int> op;

  REQUIRE(op(1, 1) == true);
  REQUIRE(op(0, 1) == false);
  REQUIRE(op(1, 0) == false);
}
TEST_CASE("functional not equal to")
{
  rsl::not_equal_to<int> op;

  REQUIRE(op(1, 1) == false);
  REQUIRE(op(0, 1) == true);
  REQUIRE(op(1, 0) == true);
}
TEST_CASE("functional greater")
{
  rsl::greater<int> op;

  REQUIRE(op(1, 1) == false);
  REQUIRE(op(0, 1) == false);
  REQUIRE(op(1, 0) == true);
}
TEST_CASE("functional greater equal")
{
  rsl::greater_equal<int> op;

  REQUIRE(op(1, 1) == true);
  REQUIRE(op(0, 1) == false);
  REQUIRE(op(1, 0) == true);
}
TEST_CASE("functional logical and")
{
  rsl::logical_and<bool> op;

  REQUIRE(op(true, true) == true);
  REQUIRE(op(true, false) == false);
  REQUIRE(op(false, true) == false);
  REQUIRE(op(false, false) == false);
}
TEST_CASE("functional logical or")
{
  rsl::logical_or<bool> op;

  REQUIRE(op(true, true) == true);
  REQUIRE(op(true, false) == true);
  REQUIRE(op(false, true) == true);
  REQUIRE(op(false, false) == false);
}
TEST_CASE("functional logical not")
{
  rsl::logical_not<bool> op;

  REQUIRE(op(true) == false);
  REQUIRE(op(false) == true);
}
TEST_CASE("functional bit and")
{
  rsl::bit_and<unsigned int> op;

  REQUIRE(op(0b1111u, 0b0000u) == 0b0000u);
  REQUIRE(op(0b1111u, 0b0001u) == 0b0001u);
  REQUIRE(op(0b1111u, 0b0010u) == 0b0010u);
  REQUIRE(op(0b1111u, 0b1111u) == 0b1111u);
  REQUIRE(op(0b1001u, 0b1111u) == 0b1001u);
  REQUIRE(op(0b1001u, 0b0011u) == 0b0001u);

}
TEST_CASE("functional bit or")
{
  rsl::bit_or<unsigned int> op;

  REQUIRE(op(0b1111u, 0b0000u) == 0b1111u);
  REQUIRE(op(0b1111u, 0b0001u) == 0b1111u);
  REQUIRE(op(0b1111u, 0b0010u) == 0b1111u);
  REQUIRE(op(0b1111u, 0b1111u) == 0b1111u);
  REQUIRE(op(0b1001u, 0b1111u) == 0b1111u);
  REQUIRE(op(0b1001u, 0b0011u) == 0b1011u);
}
TEST_CASE("functional bit xor")
{
  rsl::bit_xor<unsigned int> op;

  REQUIRE(op(0b1111u, 0b0000u) == 0b1111u);
  REQUIRE(op(0b1111u, 0b0001u) == 0b1110u);
  REQUIRE(op(0b1111u, 0b0010u) == 0b1101u);
  REQUIRE(op(0b1111u, 0b1111u) == 0b0000u);
  REQUIRE(op(0b1001u, 0b1111u) == 0b0110u);
  REQUIRE(op(0b1001u, 0b0011u) == 0b1010u);
}
TEST_CASE("functional bit not")
{
  rsl::bit_not<unsigned int> op;

  REQUIRE(op(0b00001111u) == 0b11110000ui8);
  REQUIRE(op(0b00000000u) == 0b11111111ui8);
  REQUIRE(op(0b00000110u) == 0b11111001ui8);
}
TEST_CASE("functional not fn")
{
  auto not_foo = rsl::not_fn(foo);
  auto not_bar = rsl::not_fn(bar);
  auto not_foobar = rsl::not_fn(foobar);

  REQUIRE(not_foo() == true);
  REQUIRE(not_bar() == false);
  REQUIRE(not_foobar(1) == false);
  REQUIRE(not_foobar(2) == false);
  REQUIRE(not_foobar(0) == true);
}

//NOLINTEND
