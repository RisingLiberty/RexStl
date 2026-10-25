// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_stack_string.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/bonus/string/stack_string.h"
#include "rex_std/string_view.h"

TEST_CASE("stack string construction")
{
  // stack_string()
  {
    rsl::tiny_stack_string str;
    CHECK(str.empty());
    CHECK(str.length() == 0);
    CHECK(str.size() == 0);
    CHECK(str.c_str()[0] == '\0');
    CHECK(str.max_size() == 32);
  }

  // stack_string(const char*)
  {
    rsl::tiny_stack_string str("hello");
    CHECK(!str.empty());
    CHECK(str.length() == 5);
    CHECK(str.to_view() == "hello");
    CHECK(str.c_str()[5] == '\0');
  }

  // stack_string(const char*, count)
  {
    rsl::tiny_stack_string str("hello world", 5);
    CHECK(str.length() == 5);
    CHECK(str.to_view() == "hello");
  }

  // stack_string(string_view)
  {
    rsl::string_view view = "hello world";
    rsl::small_stack_string str(view);
    CHECK(str.length() == 11);
    CHECK(str.to_view() == view);
  }

  // stack_string(initializer_list)
  {
    rsl::tiny_stack_string str = {'a', 'b', 'c'};
    CHECK(str.length() == 3);
    CHECK(str.to_view() == "abc");
  }

  // construction from a stack string with a different size
  {
    rsl::tiny_stack_string tiny("hello");
    rsl::big_stack_string big(tiny);
    CHECK(big.length() == 5);
    CHECK(big.to_view() == "hello");
  }

  // copy construction
  {
    rsl::tiny_stack_string str("hello");
    rsl::tiny_stack_string copy(str);
    CHECK(copy.to_view() == "hello");
    copy[0] = 'j';
    CHECK(str.to_view() == "hello");
  }

  // strings longer than the buffer get truncated, leaving room for the null terminator
  {
    rsl::tiny_stack_string str("this string is a lot longer than thirty two characters");
    CHECK(str.length() < str.max_size());
  }
}

TEST_CASE("stack string assignment")
{
  rsl::tiny_stack_string str("hello");

  str = "world";
  CHECK(str.length() == 5);
  CHECK(str.to_view() == "world");

  str = "hi";
  CHECK(str.length() == 2);
  CHECK(str.to_view() == "hi");
  CHECK(str.c_str()[2] == '\0');

  str = rsl::string_view("view");
  CHECK(str.to_view() == "view");

  str.assign("assigned", 6);
  CHECK(str.to_view() == "assign");

  const char* text = "first last";
  str.assign(text, text + 5);
  CHECK(str.to_view() == "first");

  str.assign(rsl::string_view("from view"));
  CHECK(str.to_view() == "from view");
}

TEST_CASE("stack string element access")
{
  rsl::tiny_stack_string str("hello");

  CHECK(str[0] == 'h');
  CHECK(str[4] == 'o');
  CHECK(str.at(1) == 'e');
  CHECK(str.front() == 'h');
  CHECK(str.back() == 'o');

  str[0] = 'j';
  CHECK(str.to_view() == "jello");

  const rsl::tiny_stack_string& const_str = str;
  CHECK(const_str[1] == 'e');
  CHECK(const_str.at(2) == 'l');
  CHECK(const_str.front() == 'j');
  CHECK(const_str.back() == 'o');
}

TEST_CASE("stack string iterators")
{
  rsl::tiny_stack_string str("abc");

  CHECK(str.end() - str.begin() == 3);
  CHECK(str.cend() - str.cbegin() == 3);

  rsl::tiny_stack_string copy;
  for(char c : str)
  {
    copy.push_back(c);
  }
  CHECK(copy.to_view() == "abc");

  // reverse iteration
  rsl::tiny_stack_string reversed;
  for(auto it = str.rbegin(); it != str.rend(); ++it)
  {
    reversed.push_back(*it);
  }
  CHECK(reversed.to_view() == "cba");
}

TEST_CASE("stack string modifiers")
{
  // push_back and pop_back
  {
    rsl::tiny_stack_string str;
    str.push_back('a');
    str.push_back('b');
    CHECK(str.length() == 2);
    CHECK(str.to_view() == "ab");

    str.pop_back();
    CHECK(str.length() == 1);
    CHECK(str.to_view() == "a");
    CHECK(str.c_str()[1] == '\0');
  }

  // clear
  {
    rsl::tiny_stack_string str("hello");
    str.clear();
    CHECK(str.empty());
    CHECK(str.c_str()[0] == '\0');
  }

  // resize
  {
    rsl::tiny_stack_string str("hello");
    str.resize(2);
    CHECK(str.length() == 2);
    CHECK(str.to_view() == "he");
    CHECK(str.c_str()[2] == '\0');

    str.resize(4);
    CHECK(str.length() == 4);
    CHECK(str[2] == '\0');
    CHECK(str[3] == '\0');

    // resizing beyond the max size clamps
    str.resize(100);
    CHECK(str.length() == str.max_size() - 1);
  }

  // remove prefix and suffix
  {
    rsl::tiny_stack_string str("hello world");
    str.remove_prefix(6);
    CHECK(str.to_view() == "world");

    rsl::tiny_stack_string str2("hello world");
    str2.remove_suffix(6);
    CHECK(str2.to_view() == "hello");

    rsl::tiny_stack_string str3("prefix_value");
    str3.remove_prefix(rsl::string_view("prefix_"));
    CHECK(str3.to_view() == "value");
    str3.remove_prefix(rsl::string_view("other"));
    CHECK(str3.to_view() == "value");
  }

  // note: insert doesn't compile at the moment, prepare_for_new_insert uses an undeclared type 's32'

  // erase
  {
    rsl::tiny_stack_string str("hello world");
    str.erase(5, 6);
    CHECK(str.to_view() == "hello");
    CHECK(str.length() == 5);
  }
}

TEST_CASE("stack string operations")
{
  rsl::small_stack_string str("hello world");

  // find
  CHECK(str.find('o') == 4);
  CHECK(str.find('o', 5) == 7);
  CHECK(str.find(rsl::string_view("world")) == 6);
  CHECK(str.find("xyz", 0) == rsl::string_view::npos());
  CHECK(str.rfind('o') == 7);
  CHECK(str.rfind(rsl::string_view("o")) == 7);
  CHECK(str.find_first_of(rsl::string_view("ol")) == 2);
  CHECK(str.find_last_of(rsl::string_view("ol")) == 9);

  // starts_with and ends_with
  CHECK(str.starts_with("hello"));
  CHECK(str.starts_with('h'));
  CHECK(!str.starts_with("world"));
  CHECK(str.ends_with("world"));
  CHECK(str.ends_with('d'));
  CHECK(!str.ends_with("hello"));

  // substr
  CHECK(str.substr(6).to_view() == "world");
  CHECK(str.substr(0, 5).to_view() == "hello");

  // compare
  // note: compare(const char*) doesn't compile at the moment
  CHECK(str.compare(rsl::small_stack_string("hello world")) == 0);
  CHECK(str.compare(rsl::small_stack_string("hello")) > 0);
  CHECK(str.compare(rsl::small_stack_string("hello worlds")) < 0);

  // copy
  char buffer[6] = {};
  str.copy(buffer, 5);
  CHECK(rsl::string_view(buffer) == "hello");
}

TEST_CASE("stack string concatenation")
{
  rsl::small_stack_string str("hello");

  str += ' ';
  str += "world";
  CHECK(str.to_view() == "hello world");

  str += rsl::string_view("!");
  CHECK(str.to_view() == "hello world!");

  rsl::small_stack_string a("foo");
  CHECK((a + 'x').to_view() == "foox");
  CHECK((a + rsl::string_view("bar")).to_view() == "foobar");
  CHECK((a + rsl::small_stack_string("baz")).to_view() == "foobaz");
  CHECK(("pre" + a).to_view() == "prefoo");
}

TEST_CASE("stack string comparison")
{
  rsl::tiny_stack_string a("abc");
  rsl::tiny_stack_string b("abd");

  CHECK(a == rsl::string_view("abc"));
  CHECK(a != rsl::string_view("abd"));
  CHECK(rsl::string_view("abc") == a);
  CHECK(a != b);

  // note: operator!=(string_view, stack_string) doesn't compile at the moment, it's missing a semicolon

  // note: operator<, <=, > and >= don't compile at the moment, they call a compare(const char*, card32) overload that doesn't exist
}

TEST_CASE("stack string hash")
{
  rsl::tiny_stack_string a("hello");
  rsl::tiny_stack_string b("hello");
  rsl::tiny_stack_string c("world");

  CHECK(rsl::hash<rsl::tiny_stack_string>()(a) == rsl::hash<rsl::tiny_stack_string>()(b));
  CHECK(rsl::hash<rsl::tiny_stack_string>()(a) != rsl::hash<rsl::tiny_stack_string>()(c));

  // hashing a stack string gives the same result as hashing a view of the same characters
  CHECK(rsl::hash<rsl::tiny_stack_string>()(a) == rsl::hash<rsl::string_view>()(rsl::string_view("hello")));
}

// NOLINTEND
