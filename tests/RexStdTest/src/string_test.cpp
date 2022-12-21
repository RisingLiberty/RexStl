// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/string.h"

TEST_CASE("string creation")
{
  // string has 16 constructors

  // 1) basic_string()
  {
    rsl::string str;
    REQUIRE(str.empty());
    REQUIRE(str.size() == 0);
  }
  // 2) basic_string(const allocator& alloc)
  {
    rsl::string str = rsl::string(rsl::allocator());
    REQUIRE(str.empty());
    REQUIRE(str.size() == 0);
  }
  // 3) basic_string(size_type count, value_type ch, const allocator& alloc = allocator())
  {
    rsl::string str(5, 'c');
    REQUIRE(str.size() == 5);
    REQUIRE(str[0] == 'c');
    REQUIRE(str[1] == 'c');
    REQUIRE(str[2] == 'c');
    REQUIRE(str[3] == 'c');
    REQUIRE(str[4] == 'c');
  }
  // 4) basic_string(const basic_string& other, size_type pos, const allocator& alloc = allocator())
  {
    rsl::string str("something");
    rsl::string str2(str, 4);
    REQUIRE(str2.size() == 5);
    REQUIRE(str2[0] == 't');
    REQUIRE(str2[1] == 'h');
    REQUIRE(str2[2] == 'i');
    REQUIRE(str2[3] == 'n');
    REQUIRE(str2[4] == 'g');
  }
  // 5) basic_string(const basic_string& other, size_type pos, size_type count, const allocator& alloc = allocator())
  {
    rsl::string str("something");
    rsl::string str2(str, 2, 3);
    REQUIRE(str2.size() == 3);
    REQUIRE(str2[0] == 'm');
    REQUIRE(str2[1] == 'e');
    REQUIRE(str2[2] == 't');
  }
  // 6) explicit basic_string(const_pointer& s, const allocator& alloc = allocator())
  {
    const char8* p = "something";
    rsl::string str(p);
    REQUIRE(str.size() == 9);
    REQUIRE(str == "something");
  }
  // 7) basic_string(const_pointer s, size_type count, const allocator& alloc = allocator())
  {
    const char8* p = "something";
    rsl::string str(p, 4);
    REQUIRE(str.size() == 4);
    REQUIRE(str[0] == 's');
    REQUIRE(str[1] == 'o');
    REQUIRE(str[2] == 'm');
    REQUIRE(str[3] == 'e');
  }
  // 9) template <typename InputIt> basic_string(InputIt first, InputIt last, const allocator & alloc = allocator())
  {
    rsl::string str("something");
    rsl::string str2(str.cbegin(), str.cend());
    REQUIRE(str2.size() == 9);
    REQUIRE(str2 == "something");
  }
  // 10) basic_string(const basic_string& other)
  {
    rsl::string str("something");
    rsl::string str2(str);
    REQUIRE(str == str2);
    REQUIRE(str == "something");
    REQUIRE(str2 == "something");
  }
  // 11) basic_string(const basic_string& other, const allocator& alloc)
  {
    rsl::string str("something");
    rsl::string str2(str, rsl::allocator());
    REQUIRE(str == str2);
    REQUIRE(str == "something");
    REQUIRE(str2 == "something");
  }
  // 12) basic_string(basic_string&& other)
  {
    rsl::string str("something");
    rsl::string str2(rsl::move(str));
    REQUIRE(str2 == "something");
  }
  // 13) basic_string(basic_string&& other, const allocator& alloc)
  {
    rsl::string str("something");
    rsl::string str2(rsl::move(str), rsl::allocator());
    REQUIRE(str2 == "something");
  }
  // 14) basic_string(rsl::initializer_list<value_type> ilist, const allocator& alloc = allocator())
  {
    rsl::string str({'s', 'o', 'm', 'e', 't', 'h', 'i', 'n', 'g'});
    REQUIRE(str == "something");
  }
  // 15) explicit basic_string(const basic_string_view<CharType>& sv, const allocator& alloc = allocator())
  {
    rsl::string str(rsl::string_view("something"));
    REQUIRE(str == "something");
  }
  // 16) explicit basic_string(const basic_string_view<value_type, traits_type> sv, size_type pos, size_type n, const allocator& alloc = allocator())
  {
    rsl::string str(rsl::string_view("something"), 4, 5);
    REQUIRE(str == "thing");
  }
  // 17) basic_string(rsl::nullptr_t)
  // the following should not compile
  // rsl::string str = nullptr;
}
TEST_CASE("string assignment")
{
  // string has 16 assignment functions

  // 1) basic_string& operator=(const basic_string& other)
  {
    rsl::string str;
    rsl::string str2("something");

    str = str2;
    REQUIRE(str == str2);
    REQUIRE(str == "something");
    REQUIRE(str2 == "something");
    REQUIRE(str.size() == 9);
    REQUIRE(str2.size() == 9);
  }
  // 2) basic_string& operator=(basic_string&& other)
  {
    rsl::string str;
    rsl::string str2("something");

    str = rsl::move(str2);
    REQUIRE(str == "something");
    REQUIRE(str.size() == 9);
  }
  // 3) basic_string& operator=(value_type ch)
  {
    rsl::string str("something");
    str = 'c';

    REQUIRE(str == "c");
    REQUIRE(str.size() == 1);
  }
  // 4) basic_string& operator=(rsl::nullptr_t) = delete
  {
      // this should not compile;
      // rsl::string str;
      // str = nullptr;
  } // 5) basic_string& assign(size_type count, value_type ch)
  {
    rsl::string str;
    str.assign(5, 'c');
    REQUIRE(str == "ccccc");
    REQUIRE(str.size() == 5);


    str.assign(20, 'c');
    REQUIRE(str == "cccccccccccccccccccc");
    REQUIRE(str.size() == 20);
  }
  // 6) basic_string& assign(const basic_string& other)
  {
    rsl::string str;
    rsl::string str2("something");

    str.assign(str2);
  }
  // 7) basic_string& assign(const basic_string& other, size_type pos, size_type count = s_npos)
  {
    rsl::string str;
    rsl::string str2("something");

    str.assign(str2, 4, 5);
    REQUIRE(str.size() == 5);
    REQUIRE(str == "thing");
  }
  // 8) basic_string& assign(basic_string&& other)
  {
    rsl::string str;
    rsl::string str2("something");

    str.assign(rsl::move(str2));
    REQUIRE(str == "something");
    REQUIRE(str.size() == 9);

    str2.assign("a very big string to make sure we get heap allocation");
    str.assign(rsl::move(str2));
  }
  // 9) basic_string& assign(const_pointer str, size_type count)
  {
    rsl::string str;
    str.assign("something", 4);

    REQUIRE(str == "some");
    REQUIRE(str.size() == 4);

    str.assign("something", 9);
    REQUIRE(str == "something");
    REQUIRE(str.size() == 9);
  }
  // 10) basic_string& assign(const_pointer& s)
  {
    rsl::string str;

    str.assign("something");

    REQUIRE(str.size() == 9);
    REQUIRE(str == "something");
  }
  // 11) template <typename InputIt> basic_string& assign(InputIt first, InputIt last)
  {
    rsl::string str("something");
    rsl::string str2;

    str2.assign(str.cbegin(), str.cend());

    REQUIRE(str.size() == 9);
    REQUIRE(str == "something");
  }
  // 12) basic_string& assign(rsl::initializer_list<value_type> ilist)
  {
    rsl::string str;
    str.assign({'s', 'o', 'm', 'e', 't', 'h', 'i', 'n', 'g'});

    REQUIRE(str.size() == 9);
    REQUIRE(str == "something");

    str.assign({ 's', 'o', 'm', 'e', 't', 'h', 'i', 'n', 'g', ' ', 'e', 'l', 's', 'e', ' ', 'a','n','d',' ','t','h','e','n',' ','s','o','m','e','t','h','i','n','g'});
    REQUIRE(str.size() == 33);
    REQUIRE(str == "something else and then something");
  }
  // 13) basic_string& assign(basic_string_view<value_type, traits_type> sv)
  {
    rsl::string str;
    rsl::string_view view = "something";
    str.assign(view);

    REQUIRE(str == "something");
    REQUIRE(str.size() == 9);
  }
  // 14) basic_string& assign(basic_string_view<value_type, traits_type> sv, size_type pos, size_type count = s_npos)
  {
    rsl::string str;
    rsl::string_view view = "something";

    str.assign(view, 4);
    REQUIRE(str == "thing");
    REQUIRE(str.size() == 5);

    str.assign(view, 0, 4);
    REQUIRE(str == "some");
    REQUIRE(str.size() == 4);
  }
}
TEST_CASE("string swap")
{
  rsl::string heap_string("this is a very long string that'll for sure get allocated on the heap");
  rsl::string stack_string;

  {
    rsl::string str(heap_string);
    rsl::string str2(stack_string);
    str.swap(str2);

    REQUIRE(str.size() == stack_string.size());
    REQUIRE(str2.size() == heap_string.size());
  }

  {
    rsl::string str3(stack_string);
    rsl::string str4(heap_string);
    str3.swap(str4);

    REQUIRE(str3.size() == heap_string.size());
    REQUIRE(str4.size() == stack_string.size());
  }

  {
    rsl::string str5(stack_string);
    rsl::string str6(stack_string);
    str5.swap(str6);

    REQUIRE(str5.size() == stack_string.size());
    REQUIRE(str6.size() == stack_string.size());
  }

  {
    rsl::string str7(heap_string);
    rsl::string str8(heap_string);
    str7.swap(str8);

    REQUIRE(str7.size() == heap_string.size());
    REQUIRE(str8.size() == heap_string.size());
  }
}
TEST_CASE("string element access")
{
  const rsl::string str("something");

  REQUIRE(str.at(0) == 's');
  REQUIRE(str.at(1) == 'o');
  REQUIRE(str.at(2) == 'm');

  REQUIRE(str[0] == 's');
  REQUIRE(str[1] == 'o');
  REQUIRE(str[2] == 'm');

  REQUIRE(str.front() == 's');
  REQUIRE(*str.begin() == 's');
  REQUIRE(str.back() == 'g');
  REQUIRE(*--str.cend() == 'g');

  REQUIRE(*str.crbegin() == 'g');
  REQUIRE(*--str.crend() == 's');
}
TEST_CASE("string capacity")
{
  rsl::string str("something");

  REQUIRE(str.size() == 9);
  REQUIRE(str.empty() == false);

  str.clear();
  REQUIRE(str.size() == 0);
  REQUIRE(str.empty() == true);

  rsl::string str2;
  str2.reserve(20); // make sure this is bigger than the sso buffer size

  REQUIRE(str2.size() == 0);
  REQUIRE(str2.empty() == true);
  REQUIRE(str2.capacity() == 20);
}
TEST_CASE("string insertion and erasion")
{
  // 1) insert(size_type index, size_type count, value_type ch)
  {
    rsl::string str("hello world");
    str.insert(6, 5, 'c');

    REQUIRE(str == "hello cccccworld");

    rsl::string str2("hello world");
    str2.insert(6, 2, 'c');
    REQUIRE(str2 == "hello ccworld");
  }

  // 2) template <count_t Size> basic_string& insert(size_type index, const value_type (&s)[Size])
  {
    rsl::string str("Hello world");
    str.insert(6, "new ");
    REQUIRE(str == "Hello new world");
  }
  // 3) basic_string& insert(size_type index, const_pointer s, size_type count)
  {
    rsl::string str("Hello world");
    const char8* ptr = "new ";
    str.insert(6, ptr, 4);
    REQUIRE(str == "Hello new world");
  }
  // 4) basic_string& insert(size_type index, const basic_string& str)
  {
    rsl::string str("Hello world");
    rsl::string str2("new ");
    str.insert(6, str2);
    REQUIRE(str == "Hello new world");
  }
  // 5) basic_string& insert(size_type index, const basic_string& str, size_type indexStr, size_type count = s_npos)
  {
    rsl::string str("Hello world");
    rsl::string str2("new ");
    str.insert(6, str2, 0, 1);
    REQUIRE(str == "Hello nworld");
  }
  // 6) iterator insert(const_iterator pos, value_type ch)
  {
    rsl::string str("Hello world");
    str.insert(str.cbegin() + 6, 'n');
    REQUIRE(str == "Hello nworld");
  }
  // 7) iterator insert(const_iterator pos, size_type count, value_type ch)
  {
    rsl::string str("Hello world");
    str.insert(str.cbegin() + 6, 5, 'c');
    REQUIRE(str == "Hello cccccworld");
  }
  // 8) template <typename InputIt> iterator insert(const_iterator pos, InputIt first, InputIt last)
  {
    rsl::string str("Hello world");
    rsl::string str2("new ");
    str.insert(str.cbegin() + 6, str2.cbegin(), str2.cend());
    REQUIRE(str == "Hello new world");
  }
  // 9) iterator insert(const_iterator pos, rsl::initializer_list<value_type> ilist)
  {
    rsl::string str("Hello world");
    str.insert(str.cbegin() + 6, {'n', 'e', 'w', ' '});
    REQUIRE(str == "Hello new world");
  }
  // 10) basic_string& insert(size_type pos, const basic_string_view<value_type, traits_type>& sv)
  {
    rsl::string str("Hello world");
    str.insert(6, rsl::string_view("new "));
    REQUIRE(str == "Hello new world");
  }
  // 11) basic_string& insert(size_type pos, const basic_string_view<value_type, traits_type>& sv, size_type indexStr, size_type count = s_npos)
  {
    rsl::string str("Hello world");
    str.insert(6, rsl::string_view("new "), 0, 1);
    REQUIRE(str == "Hello nworld");
  }

  // 12) basic_string& erase(size_type index = 0, size_type count = s_npos)
  {
    rsl::string str("Hello world");
    str.erase(5, 6);
    REQUIRE(str == "Hello");
  }
  // 13) iterator erase(const_iterator position)
  {
    rsl::string str("Hello world");
    str.erase(str.cbegin());
    REQUIRE(str == "ello world");
  }
  // 14) iterator erase(const_iterator first, const_iterator last)
  {
    rsl::string str("Hello world");
    str.erase(str.cbegin(), str.cend());
    REQUIRE(str == "");
    REQUIRE(str.empty());
    REQUIRE(str.size() == 0);
  }
  // 15) void push_back(value_type ch)
  {
    rsl::string str("Hello world");

    const auto old_size = str.size();

    str.push_back('c');
    REQUIRE(str == "Hello worldc");
    REQUIRE(str.size() == old_size + 1);
  }
  // 16) void pop_back()
  {
    rsl::string str("Hello world");

    const auto old_size = str.size();

    str.pop_back();

    REQUIRE(str == "Hello worl");
    REQUIRE(str.size() == old_size - 1);
  }

  // 17) basic_string& append(size_type count, value_type ch)
  {
    rsl::string str("Hello world");
    str.append(5, 'c');
    REQUIRE(str == "Hello worldccccc");
  }
  // 18) basic_string& append(const basic_string& str)
  {
    rsl::string str("Hello world");
    str.append(rsl::string(" again"));
    REQUIRE(str == "Hello world again");
  }
  // 19) basic_string& append(const basic_string& str, size_type pos, size_type count = s_npos)
  {
    rsl::string str("Hello world");
    str.append(rsl::string(" again"), 1);
    REQUIRE(str == "Hello worldagain");
  }
  // 21) basic_string& append(const_pointer s, size_type count)
  {
    rsl::string str("Hello world");
    const char8* ptr = "new ";
    str.append(ptr, 4);
    REQUIRE(str == "Hello worldnew ");
  }
  // 22) basic_string& append(const_pointer& s) // NOLINT(modernize-avoid-c-arrays)
  {
    rsl::string str("Hello world");
    const char8* ptr = "new ";
    str.append(ptr);
    REQUIRE(str == "Hello worldnew ");
  }
  // 23) template <typename InputIt> basic_string& append(InputIt first, InputIt last)
  {
    rsl::string str("Hello world");
    rsl::string str2("again");
    str.append(str2.cbegin(), str2.cend());
    REQUIRE(str == "Hello worldagain");
  }
  // 24) basic_string& append(rsl::initializer_list<value_type> ilist)
  {
    rsl::string str("Hello world");
    str.append({'a', 'g', 'a', 'i', 'n'});
    REQUIRE(str == "Hello worldagain");
  }
  // 25) basic_string& append(const basic_string_view<value_type, traits_type> sv)
  {
    rsl::string str("Hello world");
    str.append(rsl::string_view("again"));
    REQUIRE(str == "Hello worldagain");
  }
  // 26) basic_string& append(const basic_string_view<value_type, traits_type>& sv, size_type pos, size_type count = s_npos)
  {
    rsl::string str("Hello world");
    str.append(rsl::string_view("again"), 0, 1);
    REQUIRE(str == "Hello worlda");
  }

  // 27) basic_string& operator+=(const basic_string& str)
  {
    rsl::string str("Hello world");
    str += rsl::string("again");
    REQUIRE(str == "Hello worldagain");
  }
  // 28) basic_string& operator+=(value_type ch)
  {
    rsl::string str("Hello world");
    str += 'c';
    REQUIRE(str == "Hello worldc");
  }
  // 29) basic_string& operator+=(const value_type (&s)[Size]) // NOLINT(modernize-avoid-c-arrays)
  {
    rsl::string str("Hello world");
    str += "again";
    REQUIRE(str == "Hello worldagain");
  }
  // 30) basic_string& operator+=(rsl::initializer_list<value_type> ilist)
  {
    rsl::string str("Hello world");
    str += {'a', 'g', 'a', 'i', 'n'};
    REQUIRE(str == "Hello worldagain");
  }
  // 31) basic_string& operator+=(const basic_string_view<value_type, traits_type>& sv)
  {
    rsl::string str("Hello world");
    str += rsl::string_view("again");
    REQUIRE(str == "Hello worldagain");
  }
}
TEST_CASE("string compare")
{
  // 1) compare(const basic_string& str)
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare(rsl::string("Hello")) > 0);
    REQUIRE(str.compare(rsl::string("Hello World")) == 0);
    REQUIRE(str.compare(rsl::string("Hello World Again")) < 0);
  }
  // 2) compare(size_type pos1, size_type count1, const basic_string& str)
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare(0, 5, rsl::string("Hello Again")) < 0);
    REQUIRE(str.compare(0, 11, rsl::string("Hello World")) == 0);
    REQUIRE(str.compare(0, 5, rsl::string("Hello World")) < 0);
    REQUIRE(str.compare(6, 5, rsl::string("Hello World")) > 0);
  }
  // 3) compare(size_type pos1, size_type count1, const basic_string& str, size_type pos2, size_type count2)
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare(0, 5, rsl::string("Hello Again"), 6, 5) > 0);
    REQUIRE(str.compare(0, 5, rsl::string("Hello Again"), 0, 5) == 0);
    REQUIRE(str.compare(0, 12, rsl::string("Hello World"), 6, 5) < 0);
  }
  // 4) compare(const_pointer (&s)[Size])
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare("Hello Again") > 0);
    REQUIRE(str.compare("Hello World") == 0);
    REQUIRE(str.compare("Hello World Again") < 0);
  }
  // 5) compare(size_type pos1, size_type count1, const_pointer (&s)[Size])
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare(0, 5, "Hello Again") < 0);
    REQUIRE(str.compare(0, 11, "Hello World") == 0);
    REQUIRE(str.compare(0, 5, "Hello World") < 0);
    REQUIRE(str.compare(6, 5, "Hello World") > 0);
  }
  // 6) compare(size_type pos1, size_type count1, const_pointer s, size_type count2)
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare(0, 5, "Hello Again", 11) < 0);
    REQUIRE(str.compare(0, 5, "Hello World", 11) < 0);
    REQUIRE(str.compare(0, 11, "Hello World", 11) == 0);
  }
  // 7) compare(const basic_string_view<value_type, traits_type>& sv)
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare(rsl::string_view("Hello")) > 0);
    REQUIRE(str.compare(rsl::string_view("Hello World")) == 0);
    REQUIRE(str.compare(rsl::string_view("Hello World Again")) < 0);
  }
  // 8) compare(size_type pos1, size_type count1, const basic_string_view<value_type, traits_type> sv)
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare(0, 5, rsl::string_view("Hello Again")) < 0);
    REQUIRE(str.compare(0, 11, rsl::string_view("Hello World")) == 0);
    REQUIRE(str.compare(0, 5, rsl::string_view("Hello World")) < 0);
    REQUIRE(str.compare(6, 5, rsl::string_view("Hello World")) > 0);
  }
  // 9) compare(size_type pos1, size_type count1, const basic_string_view<value_type, traits_type> sv, size_type pos2, size_type count2 = s_npos)
  {
    rsl::string str("Hello World");
    REQUIRE(str.compare(0, 5, rsl::string_view("Hello Again"), 6, 5) > 0);
    REQUIRE(str.compare(0, 5, rsl::string_view("Hello Again"), 0, 5) == 0);
    REQUIRE(str.compare(0, 11, rsl::string_view("Hello World"), 6, 5) < 0);
  }

  // operator==
  {
    rsl::string str("Hello");
    rsl::string str2("Something");

    REQUIRE_FALSE(str == str2);
    REQUIRE_FALSE(str == "Something");
  }
}
TEST_CASE("string starts with")
{
  rsl::string str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  REQUIRE(str.starts_with("Hello") == true);
  REQUIRE(str.starts_with(hello) == true);
  REQUIRE(str.starts_with('H') == true);

  REQUIRE(str.starts_with("World") == false);
  REQUIRE(str.starts_with(world) == false);
  REQUIRE(str.starts_with('W') == false);
}
TEST_CASE("string ends with")
{
  rsl::string str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  REQUIRE(str.ends_with("Hello") == false);
  REQUIRE(str.ends_with(hello) == false);
  REQUIRE(str.ends_with('H') == false);

  REQUIRE(str.ends_with("World") == true);
  REQUIRE(str.ends_with(world) == true);
  REQUIRE(str.ends_with('d') == true);
}
TEST_CASE("string contains")
{
  rsl::string str("Hello World");
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
TEST_CASE("string replace")
{
  // 1) replace(size_type pos, size_type count, const basic_string& str)
  {
    rsl::string str("Hello World");
    str.replace(0, 5, rsl::string("Something"));
    REQUIRE(str == "Something World");
  }
  // 2) replace(const_iterator first, const_iterator last, const basic_string& str)
  {
    rsl::string str("Hello World");
    str.replace(str.cbegin(), str.cbegin() + 5, rsl::string("Something"));
    REQUIRE(str == "Something World");
  }
  // 3) replace(size_type pos1, size_type count1, const basic_string& str, size_type pos2, size_type count2)
  {
    rsl::string str("Hello World");
    str.replace(0, 5, rsl::string("Something"), 0, 4);
    REQUIRE(str == "Some World");
  }
  // 4) replace(const_iterator first, const_iterator last, InputIt first2, InputIt last2)
  {
    rsl::string str("Hello World");
    rsl::string str2("Something");
    str.replace(str.cbegin(), str.cbegin() + 5, str2.cbegin(), str2.cend());
    REQUIRE(str == "Something World");
  }
  // 5) replace(size_type pos, size_type count, const value_type (&s)[Size])
  {
    rsl::string str("Hello World");
    str.replace(0, 5, "Something");
    REQUIRE(str == "Something World");
  }
  // 6) replace(const_iterator first, const_iterator last, const value_type (&s)[Size])
  {
    rsl::string str("Hello World");
    str.replace(str.cbegin(), str.cbegin() + 5, "Something");
    REQUIRE(str == "Something World");
  }
  // 7) replace(size_type pos, size_type count, size_type count2, value_type ch)
  {
    rsl::string str("Hello World");
    str.replace(0, 5, 5, 'c');
    REQUIRE(str == "ccccc World");

    str.assign("Hello World");
    str.replace(0, 5, 10, 'c');
    REQUIRE(str == "cccccccccc World");
  }
  // 8) replace(const_iterator first, const_iterator last, size_type count2, value_type ch)
  {
    rsl::string str("Hello World");
    str.replace(str.cbegin(), str.cbegin() + 5, 5, 'c');
    REQUIRE(str == "ccccc World");
  }
  // 9) replace(const_iterator first, const_iterator last, rsl::initializer_list<value_type> ilist)
  {
    rsl::string str("Hello World");
    str.replace(str.cbegin(), str.cbegin() + 5, {'S', 'o', 'm', 'e'});
    REQUIRE(str == "Some World");
  }
  // 10) replace(size_type pos, size_type count, const basic_string_view<value_type, traits_type>& sv)
  {
    rsl::string str("Hello World");
    str.replace(0, 5, rsl::string_view("Something"));
    REQUIRE(str == "Something World");
  }
  // 11) replace(const_iterator first, const_iterator last, const basic_string_view<value_type, traits_type>& sv)
  {
    rsl::string str("Hello World");
    str.replace(str.cbegin(), str.cbegin() + 5, rsl::string_view("Something"));
    REQUIRE(str == "Something World");
  }
  // 12) replace(size_type pos, size_type count, const basic_string_view<value_type, traits_type>& sv, size_type pos2, size_type count2 = s_npos)
  {
    rsl::string str("Hello World");
    str.replace(0, 5, rsl::string_view("Something"), 0, 4);
    REQUIRE(str == "Some World");
  }
}
TEST_CASE("string subtr")
{
  rsl::string str("Hello World");
  rsl::string str2(str.substr());
  REQUIRE(str == str2);

  rsl::string_view str3 = str2.substr(0, 5);
  REQUIRE(str3 == "Hello");

  rsl::string_view str4 = str.substr(6);
  REQUIRE(str4 == "World");
}
TEST_CASE("string copy")
{
  rsl::string str("Hello World");
  char8 buffer[20] = {};

  str.copy(buffer, sizeof(buffer), 0);
  REQUIRE(rsl::strcmp(buffer, "Hello World") == 0);

  rsl::memset(buffer, 0, sizeof(buffer));
  str.copy(buffer, sizeof(buffer), 6);
  REQUIRE(rsl::strcmp(buffer, "World") == 0);
}
TEST_CASE("string resize")
{
  rsl::string str("Hello World");

  str.resize(5);
  REQUIRE(str == "Hello");
  str.resize(10);
  REQUIRE(str == "Hello\0\0\0\0\0");
}
TEST_CASE("string find")
{
  rsl::string str("Hello Hello World");
  REQUIRE(str.find("Hello") == 0);
  REQUIRE(str.find("Hello", 1) == 6);
  REQUIRE(str.find("World") == 12);
  REQUIRE(str.find("asdfghj") == rsl::string::npos());

  REQUIRE(str.find(rsl::string("Hello")) == 0);
  REQUIRE(str.find(rsl::string("Hello"), 1) == 6);
  REQUIRE(str.find(rsl::string("World")) == 12);
  REQUIRE(str.find(rsl::string("asdfghj")) == rsl::string::npos());

  REQUIRE(str.find(rsl::string_view("Hello")) == 0);
  REQUIRE(str.find(rsl::string_view("Hello"), 1) == 6);
  REQUIRE(str.find(rsl::string_view("World")) == 12);
  REQUIRE(str.find(rsl::string_view("asdfghj")) == rsl::string::npos());

  REQUIRE(str.find('H') == 0);
  REQUIRE(str.find('d') == 16);
  REQUIRE(str.find('y') == rsl::string::npos());
}
TEST_CASE("string rfind")
{
  rsl::string str("Hello Hello World");
  REQUIRE(str.rfind("Hello") == 6);
  REQUIRE(str.rfind("Hello", 7) == 0);
  REQUIRE(str.rfind("World") == 12);
  REQUIRE(str.rfind("asdfghj") == rsl::string::npos());

  REQUIRE(str.rfind(rsl::string("Hello")) == 6);
  REQUIRE(str.rfind(rsl::string("Hello"), 7) == 0);
  REQUIRE(str.rfind(rsl::string("World")) == 12);
  REQUIRE(str.rfind(rsl::string("asdfghj")) == rsl::string::npos());

  REQUIRE(str.rfind(rsl::string_view("Hello")) == 6);
  REQUIRE(str.rfind(rsl::string_view("Hello"), 7) == 0);
  REQUIRE(str.rfind(rsl::string_view("World")) == 12);
  REQUIRE(str.rfind(rsl::string_view("asdfghj")) == rsl::string::npos());

  REQUIRE(str.rfind('H') == 6);
  REQUIRE(str.rfind('d') == 16);
  REQUIRE(str.rfind('y') == rsl::string::npos());
}
TEST_CASE("string find first of")
{
  rsl::string str("Hello Hello World");
  REQUIRE(str.find_first_of("he") == 1);
  REQUIRE(str.find_first_of("He") == 0);
  REQUIRE(str.find_first_of("ll") == 2);
  REQUIRE(str.find_first_of("W") == 12);
  REQUIRE(str.find_first_of("w") == str.npos());

  REQUIRE(str.find_first_of(rsl::string("he")) == 1);
  REQUIRE(str.find_first_of(rsl::string("He")) == 0);
  REQUIRE(str.find_first_of(rsl::string("ll")) == 2);
  REQUIRE(str.find_first_of(rsl::string("W")) == 12);
  REQUIRE(str.find_first_of(rsl::string("w")) == str.npos());

  REQUIRE(str.find_first_of(rsl::string_view("he")) == 1);
  REQUIRE(str.find_first_of(rsl::string_view("He")) == 0);
  REQUIRE(str.find_first_of(rsl::string_view("ll")) == 2);
  REQUIRE(str.find_first_of(rsl::string_view("W")) == 12);
  REQUIRE(str.find_first_of(rsl::string_view("w")) == str.npos());

  REQUIRE(str.find_first_of('H') == 0);
  REQUIRE(str.find_first_of('d') == 16);
  REQUIRE(str.find_first_of('y') == rsl::string::npos());
}
TEST_CASE("string find first not of")
{
  rsl::string str("Hello Hello World");
  REQUIRE(str.find_first_not_of("he") == 0);
  REQUIRE(str.find_first_not_of("He") == 2);
  REQUIRE(str.find_first_not_of("ll") == 0);
  REQUIRE(str.find_first_not_of("W") == 0);
  REQUIRE(str.find_first_not_of("w") == 0);

  REQUIRE(str.find_first_not_of(rsl::string("he")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string("He")) == 2);
  REQUIRE(str.find_first_not_of(rsl::string("ll")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string("W")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string("w")) == 0);

  REQUIRE(str.find_first_not_of(rsl::string_view("he")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string_view("He")) == 2);
  REQUIRE(str.find_first_not_of(rsl::string_view("ll")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string_view("W")) == 0);
  REQUIRE(str.find_first_not_of(rsl::string_view("w")) == 0);

  REQUIRE(str.find_first_not_of('H') == 1);
  REQUIRE(str.find_first_not_of('d') == 0);
  REQUIRE(str.find_first_not_of('y') == 0);
}
TEST_CASE("string find last of")
{
  rsl::string str("Hello Hello World");
  REQUIRE(str.find_last_of("he") == 7);
  REQUIRE(str.find_last_of("He") == 7);
  REQUIRE(str.find_last_of("ll") == 15);
  REQUIRE(str.find_last_of("W") == 12);
  REQUIRE(str.find_last_of("w") == str.npos());

  REQUIRE(str.find_last_of(rsl::string("he")) == 7);
  REQUIRE(str.find_last_of(rsl::string("He")) == 7);
  REQUIRE(str.find_last_of(rsl::string("ll")) == 15);
  REQUIRE(str.find_last_of(rsl::string("W")) == 12);
  REQUIRE(str.find_last_of(rsl::string("w")) == str.npos());

  REQUIRE(str.find_last_of(rsl::string_view("he")) == 7);
  REQUIRE(str.find_last_of(rsl::string_view("He")) == 7);
  REQUIRE(str.find_last_of(rsl::string_view("ll")) == 15);
  REQUIRE(str.find_last_of(rsl::string_view("W")) == 12);
  REQUIRE(str.find_last_of(rsl::string_view("w")) == str.npos());

  REQUIRE(str.find_last_of('H') == 6);
  REQUIRE(str.find_last_of('d') == 16);
  REQUIRE(str.find_last_of('y') == rsl::string::npos());
}
TEST_CASE("string find last not of")
{
  rsl::string str("Hello Hello World");
  REQUIRE(str.find_last_not_of("he") == 17);
  REQUIRE(str.find_last_not_of("He") == 17);
  REQUIRE(str.find_last_not_of("ll") == 17);
  REQUIRE(str.find_last_not_of("W") == 17);
  REQUIRE(str.find_last_not_of("w") == 17);

  REQUIRE(str.find_last_not_of(rsl::string("he")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string("He")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string("ll")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string("W")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string("w")) == 17);

  REQUIRE(str.find_last_not_of(rsl::string_view("he")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string_view("He")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string_view("ll")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string_view("W")) == 17);
  REQUIRE(str.find_last_not_of(rsl::string_view("w")) == 17);

  REQUIRE(str.find_last_not_of('H') == 17);
  REQUIRE(str.find_last_not_of('d') == 17);
  REQUIRE(str.find_last_not_of('y') == 17);
}
TEST_CASE("string integer conversions")
{
  {
    rsl::string intstr("123");
    REQUIRE(intstr.to_int().value() == 123);
    REQUIRE(intstr.to_uint().value() == 123);
  }

  {
    rsl::string nointstr("hello");
    REQUIRE(nointstr.to_int().has_value() == false);
    REQUIRE(nointstr.to_uint().has_value() == false);
  }

  {
    rsl::string floatstr("1.23");
    REQUIRE(floatstr.to_float().value() == 1.23f);
    REQUIRE(floatstr.to_int().has_value() == true);
    REQUIRE(floatstr.to_uint().has_value() == true);
  }
}
TEST_CASE("wide string test")
{
  {
    rsl::wstring str(L"something");
    rsl::wstring str2(L"");
    str.swap(str2);

    REQUIRE(str.size() == 0);
    REQUIRE(str2.size() == 9);
    REQUIRE(str.length() == 0);
    REQUIRE(str2.length() == 9);
    REQUIRE(str.capacity() > 0);
    REQUIRE(str2.capacity() > 0);

    str.resize(20);
    REQUIRE(str.size() == 20);

    str.assign(L"this is a very long string that should be assigned on the heap");
    REQUIRE(str == L"this is a very long string that should be assigned on the heap");

  }
}
// NOLINTEND
