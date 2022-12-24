// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_view_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "catch2/catch.hpp"
#include "rex_std/string_view.h"

// NOLINTBEGIN

TEST_CASE("string view constructor")
{
  // 1) basic_string_view()
  {
    rsl::string_view view;
    REQUIRE(view.size() == 0);
    REQUIRE(view.empty());
  }
  // 2) basic_string_view(const basic_string_view&)
  {
    rsl::string_view view  = "Hello";
    rsl::string_view view2 = view;
    REQUIRE(view == view2);
    REQUIRE(view == "Hello");
    REQUIRE(view2 == "Hello");
  }
  // 3) basic_string_view(basic_string_view&&)
  {
    rsl::string_view view  = "Hello";
    rsl::string_view view2 = rsl::move(view);
    REQUIRE(view == view2);
    REQUIRE(view == "Hello");
    REQUIRE(view2 == "Hello");
  }
  // 4) basic_string_view(const_pointer s, size_type count)
  {
    rsl::string_view view("Hello", 5);
    REQUIRE(view == "Hello");
  }
  // 5) basic_string_view(const_pointer& s)
  {
    const char8* ptr = "Hello";
    rsl::string_view view(ptr);
    REQUIRE(view == "Hello");
  }
  // 6) basic_string_view(It1 first, It2 last)
  {
    rsl::string_view view = "Hello";
    rsl::string_view view2(view.cbegin(), view.cend());
    REQUIRE(view == view2);
    REQUIRE(view == "Hello");
    REQUIRE(view2 == "Hello");
  }
  // 7) basic_string_view(const value_type (&s)[Size])
  {
    rsl::string_view view = "Hello";
    REQUIRE(view == "Hello");
  }
}
TEST_CASE("string view assignment")
{
  {
    rsl::string_view str  = "Hello";
    rsl::string_view str2 = "World";
    str                   = str2;
    REQUIRE(str == str2);
    REQUIRE(str == "World");
    REQUIRE(str2 == "World");
  }
  {
    rsl::string_view str  = "Hello";
    rsl::string_view str2 = "World";
    str                   = rsl::move(str2);
    REQUIRE(str == str2);
    REQUIRE(str == "World");
    REQUIRE(str2 == "World");
  }
}
TEST_CASE("string view iterators")
{
  rsl::string_view str = "Hello";
  REQUIRE(*str.begin() == 'H');
  REQUIRE(*str.cbegin() == 'H');
  REQUIRE(*(str.end() - 1) == 'o');
  REQUIRE(*(str.cend() - 1) == 'o');
  REQUIRE(*str.rbegin() == 'o');
  REQUIRE(*str.crbegin() == 'o');
  REQUIRE(*(str.rend() - 1) == 'H');
  REQUIRE(*(str.crend() - 1) == 'H');
}
TEST_CASE("string view access")
{
  rsl::string_view str = "Hello";
  REQUIRE(str.at(0) == 'H');
  REQUIRE(str.at(1) == 'e');
  REQUIRE(str.at(2) == 'l');
  REQUIRE(str.at(3) == 'l');
  REQUIRE(str.at(4) == 'o');

  REQUIRE(str[0] == 'H');
  REQUIRE(str[1] == 'e');
  REQUIRE(str[2] == 'l');
  REQUIRE(str[3] == 'l');
  REQUIRE(str[4] == 'o');

  REQUIRE(str.front() == 'H');
  REQUIRE(str.back() == 'o');
}
TEST_CASE("string view size and capacity")
{
  {
    rsl::string_view str = "Hello";
    REQUIRE(str.size() == 5);
    REQUIRE(str.empty() == false);
    REQUIRE(str.length() == 5);
  }
  {
    rsl::string_view str;
    REQUIRE(str.size() == 0);
    REQUIRE(str.empty() == true);
    REQUIRE(str.length() == 0);
  }
}
TEST_CASE("string view remove prefix")
{
  {
    rsl::string_view str = "Hello World";
    str.remove_prefix(6);
    REQUIRE(str == "World");
  }
}
TEST_CASE("string view remove suffix")
{
  {
    rsl::string_view str = "Hello World";
    str.remove_suffix(6);
    REQUIRE(str == "Hello");
  }
}
TEST_CASE("string view swap")
{
  rsl::string_view str  = "Hello";
  rsl::string_view str2 = "View";
  str.swap(str2);
  REQUIRE(str == "View");
  REQUIRE(str2 == "Hello");
}
TEST_CASE("string view copy")
{
  char8 buffer[20];
  rsl::string_view str = "Hello";
  str.copy(buffer, sizeof(buffer));
}
TEST_CASE("string view substr")
{
  rsl::string_view str  = "Hello";
  rsl::string_view str2 = str.substr(0, 3);
  REQUIRE(str2 == "Hel");
}
TEST_CASE("string view compare")
{
  // 1) compare(basic_string_view sv)
  {
    rsl::string_view str("Hello World");
    REQUIRE(str.compare(rsl::string_view("Hello")) > 0);
    REQUIRE(str.compare(rsl::string_view("Hello World")) == 0);
    REQUIRE(str.compare(rsl::string_view("Hello World Again")) < 0);
  }
  // 2) compare(size_type pos1, size_type count1, basic_string_view v)
  {
    rsl::string_view str("Hello World");
    REQUIRE(str.compare(0, 5, rsl::string_view("Hello Again")) < 0);
    REQUIRE(str.compare(0, 11, rsl::string_view("Hello World")) == 0);
    REQUIRE(str.compare(0, 5, rsl::string_view("Hello World")) < 0);
    REQUIRE(str.compare(6, 5, rsl::string_view("Hello World")) > 0);
  }
  // 3) compare(size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2)
  {
    rsl::string_view str("Hello World");
    REQUIRE(str.compare(0, 5, rsl::string_view("Hello Again"), 6, 5) > 0);
    REQUIRE(str.compare(0, 5, rsl::string_view("Hello Again"), 0, 5) == 0);
    REQUIRE(str.compare(0, 12, rsl::string_view("Hello World"), 6, 5) < 0);
  }
  // 4) compare(const value_type (&s)[Size])
  {
    rsl::string_view str("Hello World");
    REQUIRE(str.compare("Hello Again") > 0);
    REQUIRE(str.compare("Hello World") == 0);
    REQUIRE(str.compare("Hello World Again") < 0);
  }
  // 5) compare(size_type pos1, size_type count1, const value_type (&s)[Size])
  {
    rsl::string_view str("Hello World");
    REQUIRE(str.compare(0, 5, "Hello Again") < 0);
    REQUIRE(str.compare(0, 11, "Hello World") == 0);
    REQUIRE(str.compare(0, 5, "Hello World") < 0);
    REQUIRE(str.compare(6, 5, "Hello World") > 0);
  }
  // 6) compare(size_type pos1, size_type count1, const_pointer s, size_type count2)
  {
    rsl::string_view str("Hello World");
    REQUIRE(str.compare(0, 5, "Hello Again", 11) < 0);
    REQUIRE(str.compare(0, 5, "Hello World", 11) < 0);
    REQUIRE(str.compare(0, 11, "Hello World", 11) == 0);
  }
}
TEST_CASE("string view starts with")
{
  rsl::string_view str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  REQUIRE(str.starts_with("Hello") == true);
  REQUIRE(str.starts_with(hello) == true);
  REQUIRE(str.starts_with('H') == true);

  REQUIRE(str.starts_with("World") == false);
  REQUIRE(str.starts_with(world) == false);
  REQUIRE(str.starts_with('W') == false);
}
TEST_CASE("string view ends with")
{
  rsl::string_view str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  REQUIRE(str.ends_with("Hello") == false);
  REQUIRE(str.ends_with(hello) == false);
  REQUIRE(str.ends_with('H') == false);

  REQUIRE(str.ends_with("World") == true);
  REQUIRE(str.ends_with(world) == true);
  REQUIRE(str.ends_with('d') == true);
}
TEST_CASE("string view contains")
{
  rsl::string_view str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  REQUIRE(str.contains("Hello") == true);
  REQUIRE(str.contains(hello) == true);
  REQUIRE(str.contains('H') == true);

  REQUIRE(str.contains("World") == true);
  REQUIRE(str.contains(world) == true);
  REQUIRE(str.contains('W') == true);

  REQUIRE(str.contains("Again") == false);
}
TEST_CASE("string view find")
{
  rsl::string_view str("Hello Hello World");
  REQUIRE(str.find("Hello") == 0);
  REQUIRE(str.find("Hello", 1) == 6);
  REQUIRE(str.find("World") == 12);
  REQUIRE(str.find("asdfghj") == rsl::string_view::npos());

  REQUIRE(str.find(rsl::string_view("Hello")) == 0);
  REQUIRE(str.find(rsl::string_view("Hello"), 1) == 6);
  REQUIRE(str.find(rsl::string_view("World")) == 12);
  REQUIRE(str.find(rsl::string_view("asdfghj")) == rsl::string_view::npos());

  REQUIRE(str.find('H') == 0);
  REQUIRE(str.find('d') == 16);
  REQUIRE(str.find('y') == rsl::string_view::npos());
}
TEST_CASE("string view rfind")
{
  rsl::string_view str("Hello Hello World");
  REQUIRE(str.rfind("Hello") == 6);
  REQUIRE(str.rfind("Hello", 7) == 0);
  REQUIRE(str.rfind("World") == 12);
  REQUIRE(str.rfind("asdfghj") == rsl::string_view::npos());

  REQUIRE(str.rfind(rsl::string_view("Hello")) == 6);
  REQUIRE(str.rfind(rsl::string_view("Hello"), 7) == 0);
  REQUIRE(str.rfind(rsl::string_view("World")) == 12);
  REQUIRE(str.rfind(rsl::string_view("asdfghj")) == rsl::string_view::npos());

  REQUIRE(str.rfind('H') == 6);
  REQUIRE(str.rfind('d') == 16);
  REQUIRE(str.rfind('y') == rsl::string_view::npos());
}
TEST_CASE("string view find first of")
{
  rsl::string_view str("Hello Hello World");
  REQUIRE(str.find_first_of("he") == 1);
  REQUIRE(str.find_first_of("He") == 0);
  REQUIRE(str.find_first_of("ll") == 2);
  REQUIRE(str.find_first_of("W") == 12);
  REQUIRE(str.find_first_of("w") == str.npos());

  REQUIRE(str.find_first_of(rsl::string_view("he")) == 1);
  REQUIRE(str.find_first_of(rsl::string_view("He")) == 0);
  REQUIRE(str.find_first_of(rsl::string_view("ll")) == 2);
  REQUIRE(str.find_first_of(rsl::string_view("W")) == 12);
  REQUIRE(str.find_first_of(rsl::string_view("w")) == str.npos());

  REQUIRE(str.find_first_of('H') == 0);
  REQUIRE(str.find_first_of('d') == 16);
  REQUIRE(str.find_first_of('y') == rsl::string_view::npos());
}
TEST_CASE("string view find_last of")
{
  rsl::string_view str("Hello Hello World");
  REQUIRE(str.find_first_not_of("he") == 0);
  REQUIRE(str.find_first_not_of("He") == 2);
  REQUIRE(str.find_first_not_of("ll") == 0);
  REQUIRE(str.find_first_not_of("W") == 0);
  REQUIRE(str.find_first_not_of("w") == 0);

  REQUIRE(str.find_first_not_of(rsl::string_view("he")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string_view("He")) == 2);
  REQUIRE(str.find_first_not_of(rsl::string_view("ll")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string_view("W")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string_view("w")) == 0);

  REQUIRE(str.find_first_not_of('H') == 1);
  REQUIRE(str.find_first_not_of('d') == 0);
  REQUIRE(str.find_first_not_of('y') == 0);
}
TEST_CASE("string view first not of")
{
  rsl::string_view str("Hello Hello World");
  REQUIRE(str.find_last_of("he") == 7);
  REQUIRE(str.find_last_of("He") == 7);
  REQUIRE(str.find_last_of("ll") == 15);
  REQUIRE(str.find_last_of("W") == 12);
  REQUIRE(str.find_last_of("w") == str.npos());

  REQUIRE(str.find_last_of(rsl::string_view("he")) == 7);
  REQUIRE(str.find_last_of(rsl::string_view("He")) == 7);
  REQUIRE(str.find_last_of(rsl::string_view("ll")) == 15);
  REQUIRE(str.find_last_of(rsl::string_view("W")) == 12);
  REQUIRE(str.find_last_of(rsl::string_view("w")) == str.npos());

  REQUIRE(str.find_last_of('H') == 6);
  REQUIRE(str.find_last_of('d') == 16);
  REQUIRE(str.find_last_of('y') == rsl::string_view::npos());
}
TEST_CASE("string view last not of")
{
  rsl::string_view str("Hello Hello World");
  REQUIRE(str.find_last_not_of("he") == 17);
  REQUIRE(str.find_last_not_of("He") == 17);
  REQUIRE(str.find_last_not_of("ll") == 17);
  REQUIRE(str.find_last_not_of("W") == 17);
  REQUIRE(str.find_last_not_of("w") == 17);

  REQUIRE(str.find_last_not_of(rsl::string_view("he")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string_view("He")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string_view("ll")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string_view("W")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string_view("w")) == 17);

  REQUIRE(str.find_last_not_of('H') == 17);
  REQUIRE(str.find_last_not_of('d') == 17);
  REQUIRE(str.find_last_not_of('y') == 17);
}
TEST_CASE("string view literals")
{
  using namespace rsl::string_view_literals;
  auto view1 = "hello"s;
  auto view2 = u"hello"s;
  auto view3 = U"hello"s;
  auto view4 = L"hello"s;

  REQUIRE(view1 == "hello");
  REQUIRE(view2 == u"hello");
  REQUIRE(view3 == U"hello");
  REQUIRE(view4 == L"hello");
}
// NOLINTEND