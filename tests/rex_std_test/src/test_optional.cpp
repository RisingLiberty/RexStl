// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_optional.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/optional.h"
#include "rex_std/functional.h"
#include "rex_std/type_traits.h"

#include "rex_std_test/test_object.h"

TEST_CASE("optional creation")
{
  rsl::optional<int> opt;

  CHECK(opt.has_value() == false);
  CHECK(opt.value_or(2) == 2);

  rsl::optional<int> opt2 = 1;
  CHECK(opt2.has_value() == true);
  CHECK(opt2.value_or(2) == 1);
  CHECK(*opt2 == 1);

  rsl::optional<int> opt3 = opt2;
  CHECK(opt2.has_value() == true);
  CHECK(opt2.value_or(2) == 1);
  CHECK(opt2.value() == 1);
  CHECK(*opt2 == 1);
  CHECK(opt3.has_value() == true);
  CHECK(opt3.value_or(2) == 1);
  CHECK(opt3.value() == 1);
  CHECK(*opt3 == 1);

  rsl::optional<int> opt4 = rsl::move(opt3);
  CHECK(opt3.has_value() == true);
  CHECK(opt3.value_or(2) == 1);
  CHECK(opt4.has_value() == true);
  CHECK(opt4.value_or(2) == 1);
  CHECK(*opt4 == 1);

  rsl::optional<bool> opt5(opt4);
  CHECK(opt5.has_value() == true);
  CHECK(opt5.value() == true);
  CHECK(opt5.value_or(false) == true);

  rsl::optional<int> opt6 = rsl::nullopt_t{};

  CHECK(opt6.has_value() == false);
  CHECK(opt6.value_or(2) == 2);

}

TEST_CASE("optional modifiers")
{
  rsl::optional<int> opt  = 3;
  rsl::optional<int> opt2 = 4;

  opt.swap(opt2);
  CHECK(opt.value() == 4);
  CHECK(opt2.value() == 3);

  opt.reset();
  CHECK(opt.has_value() == false);
  CHECK(opt.value_or(2) == 2);
  opt.swap(opt2);
  CHECK(opt.has_value() == true);
  CHECK(opt.value_or(2) == 3);
  CHECK(opt2.has_value() == false);
  CHECK(opt2.value_or(2) == 2);
  opt.swap(opt2);
  CHECK(opt.has_value() == false);
  CHECK(opt.value_or(2) == 2);
  CHECK(opt2.has_value() == true);
  CHECK(opt2.value_or(2) == 3);

  opt.emplace(10);
  CHECK(opt.has_value() == true);
  CHECK(opt.value_or(2) == 10);
  CHECK(opt.value() == 10);
  CHECK(*opt == 10);

  opt.emplace(20);
  CHECK(opt.has_value() == true);
  CHECK(opt.value_or(2) == 20);
  CHECK(opt.value() == 20);
  CHECK(*opt == 20);

}

TEST_CASE("coverage tests")
{
  rsl::optional<uint64> opt = 3ui64;
  CHECK(opt.has_value() == true);
  CHECK(opt.value() == 3);
  CHECK(*opt == 3);

  rsl::optional<uint32> opt2 = 3;
  CHECK(opt2.has_value() == true);
}

TEST_CASE("optional in place construction")
{
  using namespace rsl::test;
  test_object::reset();

  {
    rsl::optional<test_object> opt(rsl::in_place, 1, 2, 3);
    CHECK(opt.has_value());
    CHECK(opt->x() == 6);
    CHECK(test_object::num_ctor_calls() == 1);
    CHECK(test_object::num_copy_ctor_calls() == 0);
    CHECK(test_object::num_move_ctor_calls() == 0);
  }

  CHECK(test_object::is_clear());
  test_object::reset();
}

TEST_CASE("optional bool conversion")
{
  rsl::optional<int> empty;
  rsl::optional<int> filled = 5;
  rsl::optional<int> zero   = 0;

  CHECK(!empty);
  CHECK(static_cast<bool>(filled));
  CHECK(static_cast<bool>(zero)); // holding a value of 0 still means it has a value

  static_assert(!rsl::is_convertible_v<rsl::optional<int>, bool>);
}

TEST_CASE("optional access")
{
  struct point
  {
    int x;
    int y;
  };

  rsl::optional<point> opt = point {1, 2};
  CHECK(opt->x == 1);
  CHECK((*opt).y == 2);

  opt->x = 10;
  CHECK(opt.value().x == 10);

  const rsl::optional<point>& const_opt = opt;
  CHECK(const_opt->x == 10);
  CHECK((*const_opt).y == 2);
  CHECK(const_opt.value().y == 2);

  // value_or on an rvalue optional
  CHECK(rsl::optional<int>(5).value_or(3) == 5);
  CHECK(rsl::optional<int>().value_or(3) == 3);

  // moving the value out of an optional
  rsl::optional<int> moved_from = 7;
  int moved                     = rsl::move(moved_from).value();
  CHECK(moved == 7);
}

TEST_CASE("optional assignment")
{
  // assigning nullopt resets the optional
  {
    rsl::optional<int> opt = 1;
    opt                    = rsl::nullopt;
    CHECK(!opt.has_value());
  }

  // assigning a value
  {
    rsl::optional<int> opt;
    opt = 5;
    CHECK(opt.has_value());
    CHECK(*opt == 5);

    opt = 6;
    CHECK(*opt == 6);
  }

  // note: copy assignment from another optional doesn't compile at the moment, it refers to a non existing member 'val'

  // move assignment
  {
    rsl::optional<int> opt;
    opt = rsl::optional<int>(3);
    CHECK(*opt == 3);

    // note: move assigning an empty optional to a filled optional asserts at the moment (bad optional access),
    // as the move assignment calls value() on the empty optional
  }
}

TEST_CASE("optional lifetime")
{
  using namespace rsl::test;
  test_object::reset();

  // note: emplace (and assigning a value) doesn't compile at the moment for types that aren't trivially destructible,
  // the storage calls m_val.get() without specifying the template argument

  // an empty optional doesn't construct anything
  {
    rsl::optional<test_object> opt;
    CHECK(test_object::num_ctor_calls() == 0);
  }
  CHECK(test_object::num_dtor_calls() == 0);

  {
    rsl::optional<test_object> opt(rsl::in_place, 1);
    CHECK(test_object::num_ctor_calls() == 1);

    opt.reset();
    CHECK(!opt.has_value());
    CHECK(test_object::num_dtor_calls() == 1);

    // resetting an empty optional doesn't call the destructor again
    opt.reset();
    CHECK(test_object::num_dtor_calls() == 1);
  }
  CHECK(test_object::num_dtor_calls() == 1);

  // the value gets destroyed when the optional goes out of scope
  {
    rsl::optional<test_object> opt(rsl::in_place, 2);
  }
  CHECK(test_object::num_dtor_calls() == 2);

  CHECK(test_object::is_clear());
  test_object::reset();
}

TEST_CASE("optional comparison")
{
  rsl::optional<int> empty;
  rsl::optional<int> one   = 1;
  rsl::optional<int> two   = 2;
  rsl::optional<int> other = 1;

  // optional vs optional
  CHECK(one == other);
  CHECK(one != two);
  CHECK(empty != one);
  CHECK(empty == rsl::optional<int>());
  CHECK(one < two);
  CHECK(empty < one);
  CHECK(!(one < empty));
  CHECK(one <= other);
  CHECK(two > one);
  CHECK(one > empty);
  CHECK(two >= one);
  CHECK(empty >= empty);

  // optional vs nullopt
  CHECK(empty == rsl::nullopt);
  CHECK(rsl::nullopt == empty);
  CHECK(one != rsl::nullopt);
  CHECK(rsl::nullopt != one);
  CHECK(!(one < rsl::nullopt));
  CHECK(rsl::nullopt < one);
  CHECK(!(rsl::nullopt < empty));
  CHECK(one > rsl::nullopt);
  CHECK(rsl::nullopt <= empty);
  CHECK(empty >= rsl::nullopt);

  // optional vs value
  CHECK(one == 1);
  CHECK(1 == one);
  CHECK(one != 2);
  CHECK(2 != one);
  CHECK(empty != 1);
  CHECK(one < 2);
  CHECK(0 < one);
  CHECK(empty < 1);
  CHECK(two > 1);
  CHECK(3 > two);
  CHECK(one <= 1);
  CHECK(one >= 1);
}

TEST_CASE("make optional")
{
  auto opt = rsl::make_optional(5);
  static_assert(rsl::is_same_v<decltype(opt), rsl::optional<int>>);
  CHECK(*opt == 5);

  // note: make_optional<T>(args...) doesn't compile at the moment, it calls rsl::forward<Args>(args...) instead of rsl::forward<Args>(args)...
}

TEST_CASE("optional swap free function")
{
  rsl::optional<int> a = 1;
  rsl::optional<int> b;

  rsl::swap(a, b);
  CHECK(!a.has_value());
  CHECK(*b == 1);

  rsl::swap(a, b);
  CHECK(*a == 1);
  CHECK(!b.has_value());
}

TEST_CASE("optional hash")
{
  rsl::optional<int> a = 5;
  rsl::optional<int> b = 5;
  rsl::optional<int> c = 6;

  CHECK(rsl::hash<rsl::optional<int>>()(a) == rsl::hash<rsl::optional<int>>()(b));
  CHECK(rsl::hash<rsl::optional<int>>()(a) != rsl::hash<rsl::optional<int>>()(c));
  CHECK(rsl::hash<rsl::optional<int>>()(a) == rsl::hash<int>()(5));
}

// NOLINTEND
