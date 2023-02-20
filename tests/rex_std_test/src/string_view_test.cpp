// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_view_test.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"
#include "rex_std/string_view.h"

// NOLINTBEGIN

TEST_CASE("string view constructor")
{
  // 1) basic_string_view()
  {
    rsl::string_view view;
    CHECK(view.size() == 0);
    CHECK(view.empty());
  }
  // 2) basic_string_view(const basic_string_view&)
  {
    rsl::string_view view  = "Hello";
    rsl::string_view view2 = view;
    CHECK(view == view2);
    CHECK(view == "Hello");
    CHECK(view2 == "Hello");
  }
  // 3) basic_string_view(basic_string_view&&)
  {
    rsl::string_view view  = "Hello";
    rsl::string_view view2 = rsl::move(view);
    CHECK(view == view2);
    CHECK(view == "Hello");
    CHECK(view2 == "Hello");
  }
  // 4) basic_string_view(const_pointer s, size_type count)
  {
    rsl::string_view view("Hello", 5);
    CHECK(view == "Hello");
  }
  // 5) basic_string_view(const_pointer& s)
  {
    const char8* ptr = "Hello";
    rsl::string_view view(ptr);
    CHECK(view == "Hello");
  }
  // 6) basic_string_view(It1 first, It2 last)
  {
    rsl::string_view view = "Hello";
    rsl::string_view view2(view.cbegin(), view.cend());
    CHECK(view == view2);
    CHECK(view == "Hello");
    CHECK(view2 == "Hello");
  }
  // 7) basic_string_view(const value_type (&s)[Size])
  {
    rsl::string_view view = "Hello";
    CHECK(view == "Hello");
  }
}
TEST_CASE("string view assignment")
{
  {
    rsl::string_view str  = "Hello";
    rsl::string_view str2 = "World";
    str                   = str2;
    CHECK(str == str2);
    CHECK(str == "World");
    CHECK(str2 == "World");
  }
  {
    rsl::string_view str  = "Hello";
    rsl::string_view str2 = "World";
    str                   = rsl::move(str2);
    CHECK(str == str2);
    CHECK(str == "World");
    CHECK(str2 == "World");
  }
}
TEST_CASE("string view iterators")
{
  rsl::string_view str = "Hello";
  CHECK(*str.begin() == 'H');
  CHECK(*str.cbegin() == 'H');
  CHECK(*(str.end() - 1) == 'o');
  CHECK(*(str.cend() - 1) == 'o');
  CHECK(*str.rbegin() == 'o');
  CHECK(*str.crbegin() == 'o');
  CHECK(*(str.rend() - 1) == 'H');
  CHECK(*(str.crend() - 1) == 'H');
}
TEST_CASE("string view access")
{
  rsl::string_view str = "Hello";
  CHECK(str.at(0) == 'H');
  CHECK(str.at(1) == 'e');
  CHECK(str.at(2) == 'l');
  CHECK(str.at(3) == 'l');
  CHECK(str.at(4) == 'o');

  CHECK(str[0] == 'H');
  CHECK(str[1] == 'e');
  CHECK(str[2] == 'l');
  CHECK(str[3] == 'l');
  CHECK(str[4] == 'o');

  CHECK(str.front() == 'H');
  CHECK(str.back() == 'o');
}
TEST_CASE("string view size and capacity")
{
  {
    rsl::string_view str = "Hello";
    CHECK(str.size() == 5);
    CHECK(str.empty() == false);
    CHECK(str.length() == 5);
  }
  {
    rsl::string_view str;
    CHECK(str.size() == 0);
    CHECK(str.empty() == true);
    CHECK(str.length() == 0);
  }
}
TEST_CASE("string view remove prefix")
{
  {
    rsl::string_view str = "Hello World";
    str.remove_prefix(6);
    CHECK(str == "World");
  }
}
TEST_CASE("string view remove suffix")
{
  {
    rsl::string_view str = "Hello World";
    str.remove_suffix(6);
    CHECK(str == "Hello");
  }
}
TEST_CASE("string view swap")
{
  rsl::string_view str  = "Hello";
  rsl::string_view str2 = "View";
  str.swap(str2);
  CHECK(str == "View");
  CHECK(str2 == "Hello");
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
  CHECK(str2 == "Hel");
}
TEST_CASE("string view compare")
{
  // 1) compare(basic_string_view sv)
  {
    rsl::string_view str("Hello World");
    CHECK(str.compare(rsl::string_view("Hello")) > 0);
    CHECK(str.compare(rsl::string_view("Hello World")) == 0);
    CHECK(str.compare(rsl::string_view("Hello World Again")) < 0);
  }
  // 2) compare(size_type pos1, size_type count1, basic_string_view v)
  {
    rsl::string_view str("Hello World");
    CHECK(str.compare(0, 5, rsl::string_view("Hello Again")) < 0);
    CHECK(str.compare(0, 11, rsl::string_view("Hello World")) == 0);
    CHECK(str.compare(0, 5, rsl::string_view("Hello World")) < 0);
    CHECK(str.compare(6, 5, rsl::string_view("Hello World")) > 0);
  }
  // 3) compare(size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2)
  {
    rsl::string_view str("Hello World");
    CHECK(str.compare(0, 5, rsl::string_view("Hello Again"), 6, 5) > 0);
    CHECK(str.compare(0, 5, rsl::string_view("Hello Again"), 0, 5) == 0);
    CHECK(str.compare(0, 12, rsl::string_view("Hello World"), 6, 5) < 0);
  }
  // 4) compare(const value_type (&s)[Size])
  {
    rsl::string_view str("Hello World");
    CHECK(str.compare("Hello Again") > 0);
    CHECK(str.compare("Hello World") == 0);
    CHECK(str.compare("Hello World Again") < 0);
  }
  // 5) compare(size_type pos1, size_type count1, const value_type (&s)[Size])
  {
    rsl::string_view str("Hello World");
    CHECK(str.compare(0, 5, "Hello Again") < 0);
    CHECK(str.compare(0, 11, "Hello World") == 0);
    CHECK(str.compare(0, 5, "Hello World") < 0);
    CHECK(str.compare(6, 5, "Hello World") > 0);
  }
  // 6) compare(size_type pos1, size_type count1, const_pointer s, size_type count2)
  {
    rsl::string_view str("Hello World");
    CHECK(str.compare(0, 5, "Hello Again", 11) < 0);
    CHECK(str.compare(0, 5, "Hello World", 11) < 0);
    CHECK(str.compare(0, 11, "Hello World", 11) == 0);
  }
}
TEST_CASE("string view starts with")
{
  rsl::string_view str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  CHECK(str.starts_with("Hello") == true);
  CHECK(str.starts_with(hello) == true);
  CHECK(str.starts_with('H') == true);

  CHECK(str.starts_with("World") == false);
  CHECK(str.starts_with(world) == false);
  CHECK(str.starts_with('W') == false);
}
TEST_CASE("string view ends with")
{
  rsl::string_view str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  CHECK(str.ends_with("Hello") == false);
  CHECK(str.ends_with(hello) == false);
  CHECK(str.ends_with('H') == false);

  CHECK(str.ends_with("World") == true);
  CHECK(str.ends_with(world) == true);
  CHECK(str.ends_with('d') == true);
}
TEST_CASE("string view contains")
{
  {  
    rsl::string_view str("Hello World");
    const char8* hello = "Hello";
    const char8* world = "World";
    CHECK(str.contains("Hello") == true);
    CHECK(str.contains(hello) == true);
    CHECK(str.contains('H') == true);

    CHECK(str.contains("World") == true);
    CHECK(str.contains(world) == true);
    CHECK(str.contains('W') == true);

    CHECK(str.contains("Again") == false);
  }

  {
    rsl::string_view str      = "class rsl::v1::basic_string_view<char,class rsl::v1::char_traits<char> > __cdecl rsl::v1::internal::msvc_class_type_name<class rex::app_entry::MyClass>(void)";
    rsl::string_view to_find  = "class rsl::v1::basic_string_view<char,class rsl::v1::char_traits<char> > __cdecl rsl::v1::internal::type_name<class ";

    CHECK(str.contains(to_find) == true);
  }
}
TEST_CASE("string view find")
{
  rsl::string_view str("Hello Hello World");
  CHECK(str.find("Hello") == 0);
  CHECK(str.find("Hello", 1) == 6);
  CHECK(str.find("World") == 12);
  CHECK(str.find("asdfghj") == rsl::string_view::npos());

  CHECK(str.find(rsl::string_view("Hello")) == 0);
  CHECK(str.find(rsl::string_view("Hello"), 1) == 6);
  CHECK(str.find(rsl::string_view("World")) == 12);
  CHECK(str.find(rsl::string_view("asdfghj")) == rsl::string_view::npos());

  CHECK(str.find('H') == 0);
  CHECK(str.find('d') == 16);
  CHECK(str.find('y') == rsl::string_view::npos());
}
TEST_CASE("string view rfind")
{
  rsl::string_view str("Hello Hello World");
  CHECK(str.rfind("Hello") == 6);
  CHECK(str.rfind("Hello", 7) == 0);
  CHECK(str.rfind("World") == 12);
  CHECK(str.rfind("asdfghj") == rsl::string_view::npos());

  CHECK(str.rfind(rsl::string_view("Hello")) == 6);
  CHECK(str.rfind(rsl::string_view("Hello"), 7) == 0);
  CHECK(str.rfind(rsl::string_view("World")) == 12);
  CHECK(str.rfind(rsl::string_view("asdfghj")) == rsl::string_view::npos());

  CHECK(str.rfind('H') == 6);
  CHECK(str.rfind('d') == 16);
  CHECK(str.rfind('y') == rsl::string_view::npos());
}
TEST_CASE("string view find first of")
{
  rsl::string_view str("Hello Hello World");
  CHECK(str.find_first_of("he") == 1);
  CHECK(str.find_first_of("He") == 0);
  CHECK(str.find_first_of("ll") == 2);
  CHECK(str.find_first_of("W") == 12);
  CHECK(str.find_first_of("w") == str.npos());

  CHECK(str.find_first_of(rsl::string_view("he")) == 1);
  CHECK(str.find_first_of(rsl::string_view("He")) == 0);
  CHECK(str.find_first_of(rsl::string_view("ll")) == 2);
  CHECK(str.find_first_of(rsl::string_view("W")) == 12);
  CHECK(str.find_first_of(rsl::string_view("w")) == str.npos());

  CHECK(str.find_first_of('H') == 0);
  CHECK(str.find_first_of('d') == 16);
  CHECK(str.find_first_of('y') == rsl::string_view::npos());
}
TEST_CASE("string view find_last of")
{
  rsl::string_view str("Hello Hello World");
  CHECK(str.find_first_not_of("he") == 0);
  CHECK(str.find_first_not_of("He") == 2);
  CHECK(str.find_first_not_of("ll") == 0);
  CHECK(str.find_first_not_of("W") == 0);
  CHECK(str.find_first_not_of("w") == 0);

  CHECK(str.find_first_not_of(rsl::string_view("he")) == 0);
  CHECK(str.find_first_not_of(rsl::string_view("He")) == 2);
  CHECK(str.find_first_not_of(rsl::string_view("ll")) == 0);
  CHECK(str.find_first_not_of(rsl::string_view("W")) == 0);
  CHECK(str.find_first_not_of(rsl::string_view("w")) == 0);

  CHECK(str.find_first_not_of('H') == 1);
  CHECK(str.find_first_not_of('d') == 0);
  CHECK(str.find_first_not_of('y') == 0);
}
TEST_CASE("string view first not of")
{
  rsl::string_view str("Hello Hello World");
  CHECK(str.find_last_of("he") == 7);
  CHECK(str.find_last_of("He") == 7);
  CHECK(str.find_last_of("ll") == 15);
  CHECK(str.find_last_of("W") == 12);
  CHECK(str.find_last_of("w") == str.npos());

  CHECK(str.find_last_of(rsl::string_view("he")) == 7);
  CHECK(str.find_last_of(rsl::string_view("He")) == 7);
  CHECK(str.find_last_of(rsl::string_view("ll")) == 15);
  CHECK(str.find_last_of(rsl::string_view("W")) == 12);
  CHECK(str.find_last_of(rsl::string_view("w")) == str.npos());

  CHECK(str.find_last_of('H') == 6);
  CHECK(str.find_last_of('d') == 16);
  CHECK(str.find_last_of('y') == rsl::string_view::npos());
}
TEST_CASE("string view last not of")
{
  rsl::string_view str("Hello Hello World");
  CHECK(str.find_last_not_of("he") == 17);
  CHECK(str.find_last_not_of("He") == 17);
  CHECK(str.find_last_not_of("ll") == 17);
  CHECK(str.find_last_not_of("W") == 17);
  CHECK(str.find_last_not_of("w") == 17);

  CHECK(str.find_last_not_of(rsl::string_view("he")) == 17);
  CHECK(str.find_last_not_of(rsl::string_view("He")) == 17);
  CHECK(str.find_last_not_of(rsl::string_view("ll")) == 17);
  CHECK(str.find_last_not_of(rsl::string_view("W")) == 17);
  CHECK(str.find_last_not_of(rsl::string_view("w")) == 17);

  CHECK(str.find_last_not_of('H') == 17);
  CHECK(str.find_last_not_of('d') == 17);
  CHECK(str.find_last_not_of('y') == 17);
}
TEST_CASE("string view literals")
{
  using namespace rsl::string_view_literals;
  auto view1 = "hello"s;
  auto view2 = u"hello"s;
  auto view3 = U"hello"s;
  auto view4 = L"hello"s;

  CHECK(view1 == "hello");
  CHECK(view2 == u"hello");
  CHECK(view3 == U"hello");
  CHECK(view4 == L"hello");
}
// NOLINTEND