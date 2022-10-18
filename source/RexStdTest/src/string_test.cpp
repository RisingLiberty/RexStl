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
    rsl::string str({'s','o','m','e','t','h','i','n','g'});
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
  //rsl::string str = nullptr;
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
    //rsl::string str;
    //str = nullptr;
  }
  // 5) basic_string& assign(size_type count, value_type ch)
  {
    rsl::string str;
    str.assign(5, 'c');
    REQUIRE(str == "ccccc");
    REQUIRE(str.size() == 5);
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
    str.assign({ 's', 'o', 'm', 'e', 't', 'h', 'i', 'n', 'g'});

    REQUIRE(str.size() == 9);
    REQUIRE(str == "something");
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
  }
  // 2) template <count_t Size> basic_string& insert(size_type index, const value_type (&s)[Size])
  // 3) basic_string& insert(size_type index, const_pointer s, size_type count)
  // 4) basic_string& insert(size_type index, const basic_string& str)
  // 5) basic_string& insert(size_type index, const basic_string& str, size_type indexStr, size_type count = s_npos)
  // 6) iterator insert(const_iterator pos, value_type ch)
  // 7) iterator insert(const_iterator pos, size_type count, value_type ch)
  // 8) template <typename InputIt> iterator insert(const_iterator pos, InputIt first, InputIt last)
  // 9) iterator insert(const_iterator pos, rsl::initializer_list<value_type> ilist)
  // 10) basic_string& insert(size_type pos, const basic_string_view<value_type, traits_type>& sv)
  // 11) basic_string& insert(size_type pos, const basic_string_view<value_type, traits_type>& sv, size_type indexStr, size_type count = s_npos)

  // 12) basic_string& erase(size_type index = 0, size_type count = s_npos)
  // 13) iterator erase(const_iterator position)
  // 14) iterator erase(const_iterator first, const_iterator last)

  // 15) void push_back(value_type ch)
  // 16) void pop_back()

  // 17) basic_string& append(size_type count, value_type ch)
  // 18) basic_string& append(const basic_string& str)
  // 19) basic_string& append(const basic_string& str, size_type pos, size_type count = s_npos)
  // 21) basic_string& append(const_pointer s, size_type count)
  // 22) basic_string& append(const_pointer& s) // NOLINT(modernize-avoid-c-arrays)
  // 23) template <typename InputIt> basic_string& append(InputIt first, InputIt last)
  // 24) basic_string& append(rsl::initializer_list<value_type> ilist)
  // 25) basic_string& append(const basic_string_view<value_type, traits_type> sv)
  // 26) basic_string& append(const basic_string_view<value_type, traits_type>& sv, size_type pos, size_type count = s_npos)

  // 27) basic_string& operator+=(const basic_string& str)
  // 28) basic_string& operator+=(value_type ch)
  // 29) basic_string& operator+=(const value_type (&s)[Size]) // NOLINT(modernize-avoid-c-arrays)
  // 30) basic_string& operator+=(rsl::initializer_list<value_type> ilist)
  // 31) basic_string& operator+=(const basic_string_view<value_type, traits_type>& sv)
}
// NOLINTEND
