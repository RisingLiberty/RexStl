// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: functional_test.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

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
  rsl::function<int(void)> f  = foo;
  rsl::function<int(void)> f2 = bar;
  rsl::function f3            = foobar;

  CHECK(f() == 0);
  CHECK(f2() == 1);
  CHECK(f3(3) == 3);

  rsl::function<void()> f5;
  CHECK(f.operator bool() == true);
  CHECK(f5.operator bool() == false);
}
TEST_CASE("function assignment")
{
  rsl::function f = foo;
  rsl::function<int(void)> f2;

  f2 = f;
  CHECK(f2() == 0);

  rsl::function<int(void)> f3;
  f2 = f3;

  CHECK(f2.operator bool() == false);
}
TEST_CASE("function swapping")
{
  rsl::function f1 = foo;
  rsl::function f2 = bar;
  f2.swap(f1);
  CHECK(f1() == 1);
  CHECK(f2() == 0);
}
TEST_CASE("reference wrapper")
{
  int i1                            = 1;
  int i2                            = 2;
  rsl::reference_wrapper<int> i1ref = rsl::ref(i1);
  rsl::reference_wrapper<int> i2ref = rsl::ref(i2);

  CHECK(i1ref.get() == i1);
  CHECK(i2ref.get() == i2);

  i1 = 3;

  CHECK(i1ref.get() == 3);
  CHECK(i1 == 3);

  i1 = i2;
  CHECK(i2ref.get() == i1ref.get());
  CHECK(i1ref.get() == 2);
  CHECK(i1 == 2);
}
TEST_CASE("functional plus")
{
  rsl::plus<int> op;

  CHECK(op(1, 1) == 2);
  CHECK(op(1, 2) == 3);
  CHECK(op(1, -2) == -1);
  CHECK(op(-1, -2) == -3);
}
TEST_CASE("functional minus")
{
  rsl::minus<int> op;

  CHECK(op(1, 1) == 0);
  CHECK(op(1, 2) == -1);
  CHECK(op(1, -2) == 3);
  CHECK(op(-1, -2) == 1);
}
TEST_CASE("functional multiplies")
{
  rsl::multiplies<int> op;

  CHECK(op(1, 1) == 1);
  CHECK(op(1, 2) == 2);
  CHECK(op(1, -2) == -2);
  CHECK(op(-1, -2) == 2);
}
TEST_CASE("functional divides")
{
  rsl::divides<int> op;

  CHECK(op(1, 1) == 1);
  CHECK(op(1, 2) == 0);
  CHECK(op(1, -2) == 0);
  CHECK(op(-1, -2) == 0);
  CHECK(op(10, 2) == 5);
  CHECK(op(10, -2) == -5);
}
TEST_CASE("functional modulus")
{
  rsl::modulus<int> op;

  CHECK(op(1, 1) == 0);
  CHECK(op(1, 2) == 1);
  CHECK(op(1, -2) == 1);
  CHECK(op(-1, -2) == -1);
  CHECK(op(10, 2) == 0);
  CHECK(op(10, -2) == 0);
}
TEST_CASE("functional negate")
{
  rsl::negate<int> op;

  CHECK(op(1) == -1);
  CHECK(op(0) == 0);
  CHECK(op(-1) == 1);
}
TEST_CASE("functional less")
{
  rsl::less<int> op;

  CHECK(op(1, 1) == false);
  CHECK(op(0, 1) == true);
  CHECK(op(1, 0) == false);
}
TEST_CASE("functional less equal")
{
  rsl::less_equal<int> op;

  CHECK(op(1, 1) == true);
  CHECK(op(0, 1) == true);
  CHECK(op(1, 0) == false);
}
TEST_CASE("functional equal to")
{
  rsl::equal_to<int> op;

  CHECK(op(1, 1) == true);
  CHECK(op(0, 1) == false);
  CHECK(op(1, 0) == false);
}
TEST_CASE("functional not equal to")
{
  rsl::not_equal_to<int> op;

  CHECK(op(1, 1) == false);
  CHECK(op(0, 1) == true);
  CHECK(op(1, 0) == true);
}
TEST_CASE("functional greater")
{
  rsl::greater<int> op;

  CHECK(op(1, 1) == false);
  CHECK(op(0, 1) == false);
  CHECK(op(1, 0) == true);
}
TEST_CASE("functional greater equal")
{
  rsl::greater_equal<int> op;

  CHECK(op(1, 1) == true);
  CHECK(op(0, 1) == false);
  CHECK(op(1, 0) == true);
}
TEST_CASE("functional logical and")
{
  rsl::logical_and<bool> op;

  CHECK(op(true, true) == true);
  CHECK(op(true, false) == false);
  CHECK(op(false, true) == false);
  CHECK(op(false, false) == false);
}
TEST_CASE("functional logical or")
{
  rsl::logical_or<bool> op;

  CHECK(op(true, true) == true);
  CHECK(op(true, false) == true);
  CHECK(op(false, true) == true);
  CHECK(op(false, false) == false);
}
TEST_CASE("functional logical not")
{
  rsl::logical_not<bool> op;

  CHECK(op(true) == false);
  CHECK(op(false) == true);
}
TEST_CASE("functional bit and")
{
  rsl::bit_and<unsigned int> op;

  CHECK(op(0b1111u, 0b0000u) == 0b0000u);
  CHECK(op(0b1111u, 0b0001u) == 0b0001u);
  CHECK(op(0b1111u, 0b0010u) == 0b0010u);
  CHECK(op(0b1111u, 0b1111u) == 0b1111u);
  CHECK(op(0b1001u, 0b1111u) == 0b1001u);
  CHECK(op(0b1001u, 0b0011u) == 0b0001u);
}
TEST_CASE("functional bit or")
{
  rsl::bit_or<unsigned int> op;

  CHECK(op(0b1111u, 0b0000u) == 0b1111u);
  CHECK(op(0b1111u, 0b0001u) == 0b1111u);
  CHECK(op(0b1111u, 0b0010u) == 0b1111u);
  CHECK(op(0b1111u, 0b1111u) == 0b1111u);
  CHECK(op(0b1001u, 0b1111u) == 0b1111u);
  CHECK(op(0b1001u, 0b0011u) == 0b1011u);
}
TEST_CASE("functional bit xor")
{
  rsl::bit_xor<unsigned int> op;

  CHECK(op(0b1111u, 0b0000u) == 0b1111u);
  CHECK(op(0b1111u, 0b0001u) == 0b1110u);
  CHECK(op(0b1111u, 0b0010u) == 0b1101u);
  CHECK(op(0b1111u, 0b1111u) == 0b0000u);
  CHECK(op(0b1001u, 0b1111u) == 0b0110u);
  CHECK(op(0b1001u, 0b0011u) == 0b1010u);
}
TEST_CASE("functional bit not")
{
  rsl::bit_not<unsigned char> op;

  CHECK(op(0b00001111ui8) == 0b11110000ui8);
  CHECK(op(0b00000000ui8) == 0b11111111ui8);
  CHECK(op(0b00000110ui8) == 0b11111001ui8);
}
TEST_CASE("functional not fn")
{
  auto not_foo    = rsl::not_fn(foo);
  auto not_bar    = rsl::not_fn(bar);
  auto not_foobar = rsl::not_fn(foobar);

  CHECK(not_foo() == true);
  CHECK(not_bar() == false);
  CHECK(not_foobar(1) == false);
  CHECK(not_foobar(2) == false);
  CHECK(not_foobar(0) == true);
}

// NOLINTEND
