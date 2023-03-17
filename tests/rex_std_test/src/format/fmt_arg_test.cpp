// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fmt_arg_test.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/format.h"
#include "rex_std/internal/format/args.h"
#include "rex_std/internal/functional/reference_wrapper.h"
#include "rex_std/bonus/type_traits/is_char_array.h"

TEST_CASE("arg test, basic")
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  store.push_back(42);
  store.push_back("abc1");
  store.push_back(1.5f);

  REQUIRE(rsl::fmt_stack_string("42 and abc1 and 1.5") == rsl::vformat("{} and {} and {}", store));
}

TEST_CASE("arg test, strings and refs")
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  char str[] = "1234567890";
  store.push_back(str);
  store.push_back(rsl::cref(str));
  store.push_back(rsl::string_view{ str });
  str[0] = 'X';

  auto result = rsl::vformat("{} and {} and {}", store);
  REQUIRE(rsl::fmt_stack_string("1234567890 and X234567890 and X234567890") == result);
}

struct custom_type 
{
  int i = 0;
};

FMT_BEGIN_NAMESPACE
template <> struct formatter<custom_type> 
{
  auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) 
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const custom_type& p, FormatContext& ctx) -> decltype(ctx.out()) 
  {
    return format_to(ctx.out(), "cust={}", p.i);
  }
};
FMT_END_NAMESPACE

TEST_CASE("args_test, custom_format") 
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  auto c = custom_type();
  store.push_back(c);
  ++c.i;
  store.push_back(c);
  ++c.i;
  store.push_back(rsl::cref(c));
  ++c.i;
  auto result = rsl::vformat("{} and {} and {}", store);
  REQUIRE(rsl::fmt_stack_string("cust=0 and cust=1 and cust=3") == result);
}

struct to_stringable 
{
  friend rsl::string_view to_string_view(to_stringable) 
  { 
    return {}; 
  }
};

FMT_BEGIN_NAMESPACE
template <> struct formatter<to_stringable> 
{
  auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) 
  {
    return ctx.begin();
  }

  auto format(to_stringable, format_context& ctx) -> decltype(ctx.out()) 
  {
    return ctx.out();
  }
};
FMT_END_NAMESPACE

TEST_CASE("args_test, to_string_and_formatter") 
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  auto s = to_stringable();
  store.push_back(s);
  store.push_back(rsl::cref(s));
  rsl::vformat("", store);
}

TEST_CASE("args_test, named_int") 
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  store.push_back(rsl::arg("a1", 42));
  REQUIRE(rsl::fmt_stack_string("42") == rsl::vformat("{a1}", store));
}

TEST_CASE("args_test, named_strings") 
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  char str[] = "1234567890";
  store.push_back(rsl::arg("a1", str));
  store.push_back(rsl::arg("a2", rsl::cref(str)));
  str[0] = 'X';
  REQUIRE(rsl::fmt_stack_string("1234567890 and X234567890") == rsl::vformat("{a1} and {a2}", store));
}

TEST_CASE("args_test, named_arg_by_ref") 
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  char band[] = "Rolling Stones";
  store.push_back(rsl::arg("band", rsl::cref(band)));
  band[9] = 'c';  // Changing band affects the output.
  REQUIRE(rsl::vformat("{band}", store) == rsl::fmt_stack_string("Rolling Scones"));
}

TEST_CASE("args_test, named_custom_format") 
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  auto c = custom_type();
  store.push_back(rsl::arg("c1", c));
  ++c.i;
  store.push_back(rsl::arg("c2", c));
  ++c.i;
  store.push_back(rsl::arg("c_ref", rsl::cref(c)));
  ++c.i;
  auto result = rsl::vformat("{c1} and {c2} and {c_ref}", store);
  REQUIRE(rsl::fmt_stack_string("cust=0 and cust=1 and cust=3") == result);
}

TEST_CASE("args_test, clear") 
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  store.push_back(42);

  auto result = rsl::vformat("{}", store);
  REQUIRE(rsl::fmt_stack_string("42") == result);

  store.push_back(43);
  result = rsl::vformat("{} and {}", store);
  REQUIRE(rsl::fmt_stack_string("42 and 43") == result);

  store.clear();
  store.push_back(44);
  result = rsl::vformat("{}", store);
  REQUIRE(rsl::fmt_stack_string("44") == result);
}

TEST_CASE("args_test, reserve") 
{
  rsl::dynamic_format_arg_store<rsl::format_context> store;
  store.reserve(2, 1);
  store.push_back(1.5f);
  store.push_back(rsl::arg("a1", 42));
  auto result = rsl::vformat("{a1} and {}", store);
  REQUIRE(rsl::fmt_stack_string("42 and 1.5") == result);
}

TEST_CASE("args_test, move_constructor") {
  using store_type = rsl::dynamic_format_arg_store<rsl::format_context>;
  auto store = rsl::unique_ptr<store_type>(new store_type());
  store->push_back(42);
  store->push_back(rsl::fmt_stack_string("foo"));
  store->push_back(rsl::arg("a1", "foo"));
  auto moved_store = rsl::move(*store);
  store.reset();
  REQUIRE(rsl::vformat("{} {} {a1}", moved_store) == rsl::fmt_stack_string("42 foo foo"));
}

