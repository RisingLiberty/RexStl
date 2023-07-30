// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: string_test.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/string.h"

#include "rex_std_test/test_allocator.h"

namespace rsl::test
{
  inline namespace v1
  {
    using test_string = rsl::basic_string<char, rsl::char_traits<char>, rsl::test::test_allocator>;
    using test_string_view = rsl::basic_string_view<char, rsl::char_traits<char>>;
  }
}

TEST_CASE("string creation")
{
  using namespace rsl::test;

  // string has 16 constructors

  // 1) basic_string()
  {
    rsl::test::test_string str;
    CHECK(str.empty());
    CHECK(str.size() == 0);
    CHECK(str.capacity() == str.sso_buff_size());
    CHECK(str.get_allocator().num_allocs() == 0);
    CHECK(str.get_allocator().num_bytes_allocated() == 0);
    CHECK(str.get_allocator().num_frees() == 0);
  }
  // 2) basic_string(const allocator& alloc)
  {
    rsl::test::test_string str = rsl::test::test_string(test_allocator());
    CHECK(str.empty());
    CHECK(str.size() == 0);
    CHECK(str.capacity() == str.sso_buff_size());
    CHECK(str.get_allocator().num_allocs() == 0);
    CHECK(str.get_allocator().num_bytes_allocated() == 0);
    CHECK(str.get_allocator().num_frees() == 0);
  }
  // 3) basic_string(size_type count, value_type ch, const allocator& alloc = allocator())
  {
    {
      // string size that'd trigger sso
      rsl::test::test_string str(5, 'c');
      CHECK(str.size() == 5);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str[0] == 'c');
      CHECK(str[1] == 'c');
      CHECK(str[2] == 'c');
      CHECK(str[3] == 'c');
      CHECK(str[4] == 'c');
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }

    {
      // string size that's on the boundary of sso, all characters in the sso will be filled with this
      const auto sso_buff_size = rsl::test::test_string::sso_buff_size();
      rsl::test::test_string str(sso_buff_size - 1, 'c');
      CHECK(str.size() == sso_buff_size - 1);
      CHECK(str.capacity() == sso_buff_size);
      for (count_t i = 0; i < sso_buff_size - 1; ++i)
      {
        CHECK(str[i] == 'c');
      }
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }

    {
      // string that'll heap allocate
      const auto sso_buff_size = rsl::test::test_string::sso_buff_size() + 1;
      rsl::test::test_string str(sso_buff_size, 'c');
      CHECK(str.size() == sso_buff_size);
      CHECK(str.capacity() == str.size() + 1);
      for (count_t i = 0; i < str.size(); ++i)
      {
        CHECK(str[i] == 'c');
      }
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
  }
  // 4) basic_string(const basic_string& other, size_type pos, const allocator& alloc = allocator())
  {
    {
      // string that'd trigger sso

      rsl::test::test_string str("small string");
      rsl::test::test_string str2(str, 4);
      CHECK(str2.size() == 8);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "l string");
      CHECK(str2[0] == 'l');
      CHECK(str2[1] == ' ');
      CHECK(str2[2] == 's');
      CHECK(str2[3] == 't');
      CHECK(str2[4] == 'r');
      CHECK(str2[5] == 'i');
      CHECK(str2[6] == 'n');
      CHECK(str2[7] == 'g');
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }

    {
      // string size that's on the boundary of sso, all characters in the sso will be filled with this

      rsl::test::test_string str("the sso string xxxx");
      rsl::test::test_string str2(str, 4);
      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == 16);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "sso string xxxx");
      CHECK(str2[0] == 's');
      CHECK(str2[1] == 's');
      CHECK(str2[2] == 'o');
      CHECK(str2[3] == ' ');
      CHECK(str2[4] == 's');
      CHECK(str2[5] == 't');
      CHECK(str2[6] == 'r');
      CHECK(str2[7] == 'i');
      CHECK(str2[8] == 'n');
      CHECK(str2[9] == 'g');
      CHECK(str2[10] == ' ');
      CHECK(str2[11] == 'x');
      CHECK(str2[12] == 'x');
      CHECK(str2[13] == 'x');
      CHECK(str2[14] == 'x');
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }

    {
      // string that'll heap allocate

      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2(str, 4);
      CHECK(str2.size() == 21);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2 == " is a very big string");
      CHECK(str2[0] == ' ');
      CHECK(str2[1] == 'i');
      CHECK(str2[2] == 's');
      CHECK(str2[3] == ' ');
      CHECK(str2[4] == 'a');
      CHECK(str2[5] == ' ');
      CHECK(str2[6] == 'v');
      CHECK(str2[7] == 'e');
      CHECK(str2[8] == 'r');
      CHECK(str2[9] == 'y');
      CHECK(str2[10] == ' ');
      CHECK(str2[11] == 'b');
      CHECK(str2[12] == 'i');
      CHECK(str2[13] == 'g');
      CHECK(str2[14] == ' ');
      CHECK(str2[15] == 's');
      CHECK(str2[16] == 't');
      CHECK(str2[17] == 'r');
      CHECK(str2[18] == 'i');
      CHECK(str2[19] == 'n');
      CHECK(str2[20] == 'g');
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 5) basic_string(const basic_string& other, size_type pos, size_type count, const allocator& alloc = allocator())
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str("small string");
      rsl::test::test_string str2(str, 2, 3);
      CHECK(str2.size() == 3);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "all");
      CHECK(str2[0] == 'a');
      CHECK(str2[1] == 'l');
      CHECK(str2[2] == 'l');
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str("the sso string xxxx");
      rsl::test::test_string str2(str, 2, 15);
      CHECK(str2.size() == str2.sso_buff_size() - 1);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "e sso string xx");
      CHECK(str2[0] == 'e');
      CHECK(str2[1] == ' ');
      CHECK(str2[2] == 's');
      CHECK(str2[3] == 's');
      CHECK(str2[4] == 'o');
      CHECK(str2[5] == ' ');
      CHECK(str2[6] == 's');
      CHECK(str2[7] == 't');
      CHECK(str2[8] == 'r');
      CHECK(str2[9] == 'i');
      CHECK(str2[10] == 'n');
      CHECK(str2[11] == 'g');
      CHECK(str2[12] == ' ');
      CHECK(str2[13] == 'x');
      CHECK(str2[14] == 'x');
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2(str, 2, 20);
      CHECK(str2.size() == 20);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2[0] == 'i');
      CHECK(str2[1] == 's');
      CHECK(str2[2] == ' ');
      CHECK(str2[3] == 'i');
      CHECK(str2[4] == 's');
      CHECK(str2[5] == ' ');
      CHECK(str2[6] == 'a');
      CHECK(str2[7] == ' ');
      CHECK(str2[8] == 'v');
      CHECK(str2[9] == 'e');
      CHECK(str2[10] == 'r');
      CHECK(str2[11] == 'y');
      CHECK(str2[12] == ' ');
      CHECK(str2[13] == 'b');
      CHECK(str2[14] == 'i');
      CHECK(str2[15] == 'g');
      CHECK(str2[16] == ' ');
      CHECK(str2[17] == 's');
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 6) explicit basic_string(const_pointer& s, const allocator& alloc = allocator())
  {
    // string that'd trigger sso
    {
      const char8* p = "small string";
      rsl::test::test_string str(p);
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "small string");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      const char8* p = "the sso string!";
      rsl::test::test_string str(p);
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "the sso string!");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      const char8* p = "this is a very big string";
      rsl::test::test_string str(p);
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str == "this is a very big string");
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
  }
  // 7) basic_string(const_pointer s, size_type count, const allocator& alloc = allocator())
  {
    // string that'd trigger sso
    {
      const char8* p = "small string";
      rsl::test::test_string str(p, 4);
      CHECK(str.size() == 4);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str[0] == 's');
      CHECK(str[1] == 'm');
      CHECK(str[2] == 'a');
      CHECK(str[3] == 'l');
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      const char8* p = "the sso string! xxxx";
      rsl::test::test_string str(p, 15);
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "the sso string!");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      const char8* p = "this is a very big string";
      rsl::test::test_string str(p, 20);
      CHECK(str.size() == 20);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str == "this is a very big s");
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
  }
  // 9) template <typename InputIt> basic_string(InputIt first, InputIt last, const allocator & alloc = allocator())
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str("small string");
      rsl::test::test_string str2(str.cbegin(), str.cend());
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str.sso_buff_size());
      CHECK(str2 == "small string");
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str("the sso string!");
      rsl::test::test_string str2(str.cbegin(), str.cend());
      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "the sso string!");
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2(str.cbegin(), str.cend());
      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2 == "this is a very big string");
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str2)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 10) basic_string(const basic_string& other)
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str("small string");
      rsl::test::test_string str2(str);
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "small string");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str == str2);

      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "small string");
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str("the sso string!");
      rsl::test::test_string str2(str);
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "the sso string!");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str == str2);

      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "the sso string!");
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2(str);
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str == "this is a very big string");
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str == str2);

      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2 == "this is a very big string");
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str2)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }

  }
  // 11) basic_string(const basic_string& other, const allocator& alloc)
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str("small string");
      rsl::test::test_string str2(str, test_allocator());
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "small string");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str == str2);

      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "small string");
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str("the sso string!");
      rsl::test::test_string str2(str, test_allocator());
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "the sso string!");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str == str2);

      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2 == "the sso string!");
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2(str, test_allocator());
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str == "this is a very big string");
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str == str2);

      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2 == "this is a very big string");
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }

  }
  // 12) basic_string(basic_string&& other)
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str("small string");
      rsl::test::test_string str2(rsl::move(str));

      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str("the sso string!");
      rsl::test::test_string str2(rsl::move(str));

      CHECK(str2 == "the sso string!");
      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2(rsl::move(str));
      CHECK(str == "");
      CHECK(str.empty() == true);
      CHECK(str.size() == 0);
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2 == "this is a very big string");
      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 13) basic_string(basic_string&& other, const allocator& alloc)
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str("small string");
      rsl::test::test_string str2(rsl::move(str), test_allocator());

      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str("the sso string!");
      rsl::test::test_string str2(rsl::move(str), test_allocator());

      CHECK(str2 == "the sso string!");
      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2(rsl::move(str), test_allocator());

      CHECK(str2 == "this is a very big string");
      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 14) basic_string(rsl::initializer_list<value_type> ilist, const allocator& alloc = allocator())
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str({ 's', 'm', 'a', 'l', 'l', ' ', 's', 't', 'r', 'i', 'n', 'g' });
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str({ 't', 'h', 'e', ' ', 's', 's', 'o', ' ', 's', 't', 'r', 'i', 'n', 'g', '!' });
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str({ 't', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 'v', 'e', 'r', 'y', ' ', 'b', 'i', 'g', ' ', 's', 't', 'r', 'i', 'n', 'g' });
      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }

  }
  // 15) explicit basic_string(const basic_string_view<CharType>& sv, const allocator& alloc = allocator())
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str(rsl::string_view("small string"));
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "small string");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str(rsl::string_view("the sso string!"));
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "the sso string!");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str(rsl::string_view("this is a very big string"));
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str == "this is a very big string");
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
  }
  // 16) explicit basic_string(const basic_string_view<value_type, traits_type> sv, size_type pos, size_type n, const allocator& alloc = allocator())
  {
    // string that'd trigger sso
    {
      rsl::test::test_string str(rsl::string_view("small string"), test_allocator());
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "small string");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str(rsl::string_view("the sso string!"), test_allocator());
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "the sso string!");
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str(rsl::string_view("this is a very big string"), test_allocator());
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str == "this is a very big string");
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
  }
  // 17) basic_string(rsl::nullptr_t)
  // the following should not compile
  // rsl::test::test_string str = nullptr;
}
TEST_CASE("string assignment")
{
  using namespace rsl::test;

  // Rex Standard Library has "defined" behavior for string post move.
  // was there's only 1 RSL, it's possible for us to test for this.
  // However, if we would have checks for content post move assignment
  // this makes it easier to use string after move which is not allowed
  // therefore we don't implement checks for strings after they've been
  // move assigned from. using such a string is undefined, they should be cleared first.
  // we only check no additional allocations are performed on it

  // 1) basic_string& operator=(const basic_string& other)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("small string");

      str = str2;
      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("the sso string!");

      str = str2;
      CHECK(str == str2);
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "the sso string!");
      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("this is a very big string");

      str = str2;
      CHECK(str == str2);
      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "this is a very big string");
      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str2)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("small string");

      str = str2;
      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is a heap string");

      str = str2;
      CHECK(str == str2);
      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "this is a heap string");
      CHECK(str2.size() == 21);
      CHECK(str2.capacity() == 22);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == 22 * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is an even bigger string");

      str = str2;
      CHECK(str == str2);
      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
      CHECK(str2 == "this is an even bigger string");
      CHECK(str2.size() == 29);
      CHECK(str2.capacity() == 30);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 2) basic_string& operator=(basic_string&& other)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("small string");

      str = rsl::move(str2);

      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("the sso string!");

      str = rsl::move(str2);

      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("this is a very big string");

      str = rsl::move(str2);

      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("small string");

      str = rsl::move(str2);

      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is a heap string");

      card32 old_allocs = str2.get_allocator().num_allocs();
      card32 old_frees = str2.get_allocator().num_frees();

      str = rsl::move(str2);

      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 22);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 22 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() <= old_allocs);
      CHECK(str2.get_allocator().num_frees() >= old_frees);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is an even bigger string");

      card32 old_allocs = str2.get_allocator().num_allocs();
      card32 old_frees = str2.get_allocator().num_frees();

      str = rsl::move(str2);

      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() <= old_allocs);
      CHECK(str2.get_allocator().num_frees() >= old_frees);
    }
  }

  // 3) basic_string& operator=(value_type ch)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str("small string");
      str = 'c';

      CHECK(str == "c");
      CHECK(str.size() == 1);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation
    {
      rsl::test::test_string str("this is a very big string");
      str = 'c';

      CHECK(str == "c");
      CHECK(str.size() == 1);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
  }
  // 4) basic_string& operator=(rsl::nullptr_t) = delete
  {
    // this should not compile;
    // rsl::test::test_string str;
    // str = nullptr;
  }

  // 5) basic_string& assign(size_type count, value_type ch)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      str.assign(5, 'c');
      CHECK(str == "ccccc");
      CHECK(str.size() == 5);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      str.assign(15, 'c');
      CHECK(str == "ccccccccccccccc");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      str.assign(20, 'c');
      CHECK(str == "cccccccccccccccccccc");
      CHECK(str.size() == 20);
      CHECK(str.capacity() == 21);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 21 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      str.assign(10, 'c');
      CHECK(str == "cccccccccc");
      CHECK(str.size() == 10);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      str.assign(20, 'c');
      CHECK(str == "cccccccccccccccccccc");
      CHECK(str.size() == 20);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      str.assign(30, 'c');
      CHECK(str == "cccccccccccccccccccccccccccccc");
      CHECK(str.size() == 30);
      CHECK(str.capacity() == 31);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 31 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
    }
  }
  // 6) basic_string& assign(const basic_string& other)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("small string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("the sso string!");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "the sso string!");
      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("this is a very big string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "this is a very big string");
      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str2)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("small string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is a heap string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "this is a heap string");
      CHECK(str2.size() == 21);
      CHECK(str2.capacity() == 22);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == 22 * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is an even bigger string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
      CHECK(str2 == "this is an even bigger string");
      CHECK(str2.size() == 29);
      CHECK(str2.capacity() == 30);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 7) basic_string& assign(const basic_string& other, size_type pos, size_type count = s_npos)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("small string");

      str.assign(str2, 0, 5);
      CHECK(str == "small");
      CHECK(str.size() == 5);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("the sso string!");

      str.assign(str2, 0, 15);
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "the sso string!");
      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("this is a very big string");

      str.assign(str2, 0, 20);
      CHECK(str == "this is a very big s");
      CHECK(str.size() == 20);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2 == "this is a very big string");
      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str2)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("small string");

      str.assign(str2, 0, 5);
      CHECK(str == "small");
      CHECK(str.size() == 5);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is a heap string");

      str.assign(str2, 0, 20);
      CHECK(str == "this is a heap strin");
      CHECK(str.size() == 20);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "this is a heap string");
      CHECK(str2.size() == 21);
      CHECK(str2.capacity() == 22);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == 22 * sizeof(decltype(str2)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is an even bigger string");

      str.assign(str2, 0, 27);
      CHECK(str == "this is an even bigger stri");
      CHECK(str.size() == 27);
      CHECK(str.capacity() == 28);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 28 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
      CHECK(str2 == "this is an even bigger string");
      CHECK(str2.size() == 29);
      CHECK(str2.capacity() == 30);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str2)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 8) basic_string& assign(basic_string&& other)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("small string");

      str.assign(rsl::move(str2));

      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("the sso string!");

      str.assign(rsl::move(str2));

      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("this is a very big string");

      str.assign(rsl::move(str2));

      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("small string");

      str.assign(rsl::move(str2));

      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is a heap string");

      card32 old_allocs = str2.get_allocator().num_allocs();
      card32 old_frees = str2.get_allocator().num_frees();

      str.assign(rsl::move(str2));

      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 22);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 22 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() <= old_allocs);
      CHECK(str2.get_allocator().num_frees() >= old_frees);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is an even bigger string");

      card32 old_allocs = str2.get_allocator().num_allocs();
      card32 old_frees = str2.get_allocator().num_frees();

      str.assign(rsl::move(str2));

      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);

      CHECK(str2.get_allocator().num_allocs() <= old_allocs);
      CHECK(str2.get_allocator().num_frees() >= old_frees);
    }

  }
  // 9) basic_string& assign(const_pointer str, size_type count)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;

      str.assign("small string", 12);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;

      str.assign("the sso string!", 15);
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;

      str.assign("this is a very big string", 25);
      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");

      str.assign("small string", 12);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");

      str.assign("this is a heap string", 21);
      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");

      str.assign("this is an even bigger string", 29);
      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
    }
  }
  // 10) basic_string& assign(const_pointer& s)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;

      str.assign("small string");
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;

      str.assign("the sso string!");
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;

      str.assign("this is a very big string");
      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");

      str.assign("small string");
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");

      str.assign("this is a heap string");
      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");

      str.assign("this is an even bigger string");
      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
    }
  }
  // 11) template <typename InputIt> basic_string& assign(InputIt first, InputIt last)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("small string");

      str.assign(str2.cbegin(), str2.cend());
      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("the sso string!");

      str.assign(str2.cbegin(), str2.cend());
      CHECK(str == str2);
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "the sso string!");
      CHECK(str2.size() == 15);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      rsl::test::test_string str2("this is a very big string");

      str.assign(str2.cbegin(), str2.cend());
      CHECK(str == str2);
      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "this is a very big string");
      CHECK(str2.size() == 25);
      CHECK(str2.capacity() == str2.size() + 1);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == str2.capacity() * sizeof(decltype(str2)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("small string");

      str.assign(str2.cbegin(), str2.cend());
      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "small string");
      CHECK(str2.size() == 12);
      CHECK(str2.capacity() == str2.sso_buff_size());
      CHECK(str2.get_allocator().num_allocs() == 0);
      CHECK(str2.get_allocator().num_bytes_allocated() == 0);
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is a heap string");

      str.assign(str2.cbegin(), str2.cend());
      CHECK(str == str2);
      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
      CHECK(str2 == "this is a heap string");
      CHECK(str2.size() == 21);
      CHECK(str2.capacity() == 22);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == 22 * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string str2("this is an even bigger string");

      str.assign(str2.cbegin(), str2.cend());
      CHECK(str == str2);
      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
      CHECK(str2 == "this is an even bigger string");
      CHECK(str2.size() == 29);
      CHECK(str2.capacity() == 30);
      CHECK(str2.get_allocator().num_allocs() == 1);
      CHECK(str2.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str2.get_allocator().num_frees() == 0);
    }
  }
  // 12) basic_string& assign(rsl::initializer_list<value_type> ilist)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;

      str.assign({'s','m','a','l','l',' ','s','t','r','i','n','g'});
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;

      str.assign({'t','h','e',' ','s','s','o',' ','s','t','r','i','n','g','!'});
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;

      str.assign({'t','h','i','s',' ', 'i','s',' ','a',' ','v','e','r','y',' ','b','i','g',' ','s','t','r','i','n','g'});
      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");

      str.assign({ 's','m','a','l','l',' ','s','t','r','i','n','g' });
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");

      str.assign({'t','h','i','s',' ','i','s',' ','a',' ','h','e','a','p',' ','s','t','r','i','n','g'});
      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");

      str.assign({'t','h','i','s',' ','i','s',' ','a','n',' ','e','v','e','n',' ','b','i','g','g','e','r',' ','s','t','r','i','n','g'});
      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
    }
  }
  // 13) basic_string& assign(basic_string_view<value_type, traits_type> sv)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      rsl::test::test_string_view str2("small string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      rsl::test::test_string_view str2("the sso string!");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      rsl::test::test_string_view str2("this is a very big string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "this is a very big string");
      CHECK(str.size() == 25);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string_view str2("small string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "small string");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string_view str2("this is a heap string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "this is a heap string");
      CHECK(str.size() == 21);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string_view str2("this is an even bigger string");

      str.assign(str2);
      CHECK(str == str2);
      CHECK(str == "this is an even bigger string");
      CHECK(str.size() == 29);
      CHECK(str.capacity() == 30);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 30 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
    }
  }
  // 14) basic_string& assign(basic_string_view<value_type, traits_type> sv, size_type pos, size_type count = s_npos)
  {
    // string size that'd trigger sso
    {
      rsl::test::test_string str;
      rsl::test::test_string_view str2("small string");

      str.assign(str2, 0, 5);
      CHECK(str == "small");
      CHECK(str.size() == 5);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string size that's on the boundary of sso, all characters in the sso will be filled with this
    {
      rsl::test::test_string str;
      rsl::test::test_string_view str2("the sso string!");

      str.assign(str2, 0, 15);
      CHECK(str == "the sso string!");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str.get_allocator().num_allocs() == 0);
      CHECK(str.get_allocator().num_bytes_allocated() == 0);
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string that'll heap allocate
    {
      rsl::test::test_string str;
      rsl::test::test_string_view str2("this is a very big string");

      str.assign(str2, 0, 20);
      CHECK(str == "this is a very big s");
      CHECK(str.size() == 20);
      CHECK(str.capacity() == str.size() + 1);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size < sso
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string_view str2("small string");

      str.assign(str2, 0, 5);
      CHECK(str == "small");
      CHECK(str.size() == 5);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with sso < size < old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string_view str2("this is a heap string");

      str.assign(str2, 0, 20);
      CHECK(str == "this is a heap strin");
      CHECK(str.size() == 20);
      CHECK(str.capacity() == 26);
      CHECK(str.get_allocator().num_allocs() == 1);
      CHECK(str.get_allocator().num_bytes_allocated() == 26 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 0);
    }
    // string will keep the heap allocation with size > old_size
    {
      rsl::test::test_string str("this is a very big string");
      rsl::test::test_string_view str2("this is an even bigger string");

      str.assign(str2, 0, 27);
      CHECK(str == "this is an even bigger stri");
      CHECK(str.size() == 27);
      CHECK(str.capacity() == 28);
      CHECK(str.get_allocator().num_allocs() == 2);
      CHECK(str.get_allocator().num_bytes_allocated() == 28 * sizeof(decltype(str)::value_type));
      CHECK(str.get_allocator().num_frees() == 1);
    }
  }
}
TEST_CASE("string swap")
{
  using namespace rsl::test;

  rsl::test::test_string heap_string("this is a very long string that'll for sure get allocated on the heap");
  rsl::test::test_string stack_string;

  {
    rsl::test::test_string str(heap_string);
    rsl::test::test_string str2(stack_string);

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.swap(str2);

    CHECK(str == stack_string);
    CHECK(str2 == heap_string);
    CHECK(str.size() == stack_string.size());
    CHECK(str2.size() == heap_string.size());

    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }

  {
    rsl::test::test_string str3(stack_string);
    rsl::test::test_string str4(heap_string);

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str3.swap(str4);

    CHECK(str4 == stack_string);
    CHECK(str3 == heap_string);
    CHECK(str3.size() == heap_string.size());
    CHECK(str4.size() == stack_string.size());

    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }

  {
    rsl::test::test_string str5(stack_string);
    rsl::test::test_string str6(stack_string);

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str5.swap(str6);

    CHECK(str5 == stack_string);
    CHECK(str6 == stack_string);
    CHECK(str5.size() == stack_string.size());
    CHECK(str6.size() == stack_string.size());

    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }

  {
    rsl::test::test_string str7(heap_string);
    rsl::test::test_string str8(heap_string);

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str7.swap(str8);

    CHECK(str7 == heap_string);
    CHECK(str8 == heap_string);
    CHECK(str7.size() == heap_string.size());
    CHECK(str8.size() == heap_string.size());

    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
}
TEST_CASE("string element access")
{
  using namespace rsl::test;

  const rsl::test::test_string str("small string");

  CHECK(str.at(0) == 's');
  CHECK(str.at(1) == 'm');
  CHECK(str.at(2) == 'a');

  CHECK(str[0] == 's');
  CHECK(str[1] == 'm');
  CHECK(str[2] == 'a');

  CHECK(str.front() == 's');
  CHECK(*str.begin() == 's');
  CHECK(str.back() == 'g');
  CHECK(*--str.cend() == 'g');

  CHECK(*str.crbegin() == 'g');
  CHECK(*--str.crend() == 's');
}
TEST_CASE("string capacity")
{
  using namespace rsl::test;

  rsl::test::test_string str("small string");

  CHECK(str.size() == 12);
  CHECK(str.empty() == false);

  str.clear();
  CHECK(str.size() == 0);
  CHECK(str.empty() == true);

  rsl::test::test_string str2;
  str2.reserve(20); // make sure this is bigger than the sso buffer size

  CHECK(str2.size() == 0);
  CHECK(str2.empty() == true);
  CHECK(str2.capacity() == 20);
}
TEST_CASE("string insertion and erasion")
{
  using namespace rsl::test;

  // 1) insert(size_type index, size_type count, value_type ch)
  {
    {
      rsl::test::test_string str("hello world");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.insert(6, 2, 'c');

      CHECK(str == "hello ccworld");
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("hello world");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.insert(6, 5, 'c');

      CHECK(str == "hello cccccworld");
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }

  // 2) template <count_t Size> basic_string& insert(size_type index, const value_type (&s)[Size])
  {
    rsl::test::test_string str("Hello world");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(6, "new");
    CHECK(str == "Hello newworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(9, " !");

    CHECK(str == "Hello new !world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
  // 3) basic_string& insert(size_type index, const_pointer s, size_type count)
  {
    rsl::test::test_string str("Hello world");
    const char8* ptr = "new ";
    const char8* ptr2 = " !";

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(6, ptr, 3);
    CHECK(str == "Hello newworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(9, ptr2, 2);

    CHECK(str == "Hello new !world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
  // 4) basic_string& insert(size_type index, const basic_string& str)
  {
    rsl::test::test_string str("Hello world");
    rsl::test::test_string str2("new");
    rsl::test::test_string str3(" !");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(6, str2);
    CHECK(str == "Hello newworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(9, str3);

    CHECK(str == "Hello new !world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
  // 5) basic_string& insert(size_type index, const basic_string& str, size_type indexStr, size_type count = s_npos)
  {
    rsl::test::test_string str("Hello world");
    rsl::test::test_string str2("new !");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(6, str2, 0, 3);
    CHECK(str == "Hello newworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(9, str2, 3, 2);

    CHECK(str == "Hello new !world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
  // 6) iterator insert(const_iterator pos, value_type ch)
  {
    rsl::test::test_string str("Hello world");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(str.cbegin() + 6, 'n');
    CHECK(str == "Hello nworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(str.cbegin() + 7, 'e');
    str.insert(str.cbegin() + 8, 'w');
    str.insert(str.cbegin() + 9, ' ');
    str.insert(str.cbegin() + 10, '!');
    CHECK(str == "Hello new !world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
  // 7) iterator insert(const_iterator pos, size_type count, value_type ch)
  {
    rsl::test::test_string str("Hello world");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(str.cbegin() + 6, 3, 'c');
    CHECK(str == "Hello cccworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(str.cbegin() + 6, 2, 'c');
    CHECK(str == "Hello cccccworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
  // 8) template <typename InputIt> iterator insert(const_iterator pos, InputIt first, InputIt last)
  {
    rsl::test::test_string str("Hello world");
    rsl::test::test_string str2("new !");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(str.cbegin() + 6, str2.cbegin(), str2.cend() - 2);
    CHECK(str == "Hello newworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(str.cbegin() + 9, str2.cend() - 2, str2.cend());
    CHECK(str == "Hello new !world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

  }
  // 9) iterator insert(const_iterator pos, rsl::initializer_list<value_type> ilist)
  {
    rsl::test::test_string str("Hello world");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(str.cbegin() + 6, { 'n', 'e', 'w' });
    CHECK(str == "Hello newworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(str.cbegin() + 9, { ' ','!'});
    CHECK(str == "Hello new !world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
  // 10) basic_string& insert(size_type pos, const basic_string_view<value_type, traits_type>& sv)
  {
    rsl::test::test_string str("Hello world");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(6, rsl::string_view("new"));
    CHECK(str == "Hello newworld");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(9, rsl::string_view(" !"));
    CHECK(str == "Hello new !world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }
  // 11) basic_string& insert(size_type pos, const basic_string_view<value_type, traits_type>& sv, size_type indexStr, size_type count = s_npos)
  {
    rsl::test::test_string str("Hello world");

    card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
    card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
    card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

    str.insert(6, rsl::string_view("new "), 0, 4);
    CHECK(str == "Hello new world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    str.insert(10, rsl::string_view("new! "), 3, 2);
    CHECK(str == "Hello new ! world");
    CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
    CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
    CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
  }

  // 12) basic_string& erase(size_type index = 0, size_type count = s_npos)
  {
    {
      rsl::test::test_string str("Hello world");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.erase(5, 6);
      CHECK(str == "Hello");
      CHECK(str.size() == 5);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello world Freddy");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.erase(5, 6);
      CHECK(str == "Hello Freddy");
      CHECK(str.size() == 12);
      CHECK(str.capacity() == 19);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 13) iterator erase(const_iterator position)
  {
    {
      rsl::test::test_string str("Hello world");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.erase(str.cbegin());
      CHECK(str == "ello world");
      CHECK(str.size() == 10);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      {
        rsl::test::test_string str("Hello world Freddy");

        card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
        card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
        card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

        str.erase(str.cbegin());
        CHECK(str == "ello world Freddy");
        CHECK(str.size() == 17);
        CHECK(str.capacity() == 19);
        CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
        CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
        CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
      }
    }
  }
  // 14) iterator erase(const_iterator first, const_iterator last)
  {
    {
      rsl::test::test_string str("Hello world");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.erase(str.cbegin(), str.cend());
      CHECK(str == "");
      CHECK(str.empty());
      CHECK(str.size() == 0);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello world Freddy");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.erase(str.cbegin(), str.cend());;
      CHECK(str == "");
      CHECK(str.empty());
      CHECK(str.size() == 0);
      CHECK(str.capacity() == 19);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

  }
  // 15) void push_back(value_type ch)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.push_back('c');
      CHECK(str == "Hello worldc");
      CHECK(str.size() == old_size + 1);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello my world");

      const auto old_size = str.size();

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.push_back('c');
      str.push_back('c');
      CHECK(str == "Hello my worldcc");
      CHECK(str.size() == old_size + 2);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

  }
  // 16) void pop_back()
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.pop_back();

      CHECK(str == "Hello worl");
      CHECK(str.size() == old_size - 1);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello new world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.pop_back();

      CHECK(str == "Hello new worl");
      CHECK(str.size() == old_size - 1);
      CHECK(str.capacity() == 16);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }

  // 17) basic_string& append(size_type count, value_type ch)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(2, 'c');
      CHECK(str == "Hello worldcc");
      CHECK(str.size() == old_size + 2);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello my world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(5, 'c');
      CHECK(str == "Hello my worldccccc");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 18) basic_string& append(const basic_string& str)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(rsl::test::test_string("new"));
      CHECK(str == "Hello worldnew");
      CHECK(str.size() == old_size + 3);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello my world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(rsl::test::test_string(" again"));
      CHECK(str == "Hello my world again");
      CHECK(str.size() == old_size + 6);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

  }
  // 19) basic_string& append(const basic_string& str, size_type pos, size_type count = s_npos)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(rsl::test::test_string(" my "), 1);
      CHECK(str == "Hello worldmy ");
      CHECK(str.size() == old_size + 3);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(rsl::test::test_string(" again"), 1);
      CHECK(str == "Hello worldagain");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

  }
  // 21) basic_string& append(const_pointer s, size_type count)
  {
    {
      rsl::test::test_string str("Hello world");
      const char8* ptr = "new";

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(ptr, 3);
      CHECK(str == "Hello worldnew");
      CHECK(str.size() == old_size + 3);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello world");
      const char8* ptr = "new !";

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(ptr, 5);
      CHECK(str == "Hello worldnew !");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 22) basic_string& append(const_pointer& s) // NOLINT(modernize-avoid-c-arrays)
  {
    {
      rsl::test::test_string str("Hello world");
      const char8* ptr = "my ";

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(ptr);
      CHECK(str == "Hello worldmy ");
      CHECK(str.size() == old_size + 3);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    }

    {
      rsl::test::test_string str("Hello world");
      const char8* ptr = "new !";

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(ptr);
      CHECK(str == "Hello worldnew !");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    }
  }
  // 23) template <typename InputIt> basic_string& append(InputIt first, InputIt last)
  {
    {
      rsl::test::test_string str("Hello world");
      rsl::test::test_string str2("my ");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(str2.cbegin(), str2.cend());
      CHECK(str == "Hello worldmy ");
      CHECK(str.size() == old_size + 3);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello world");
      rsl::test::test_string str2("new !");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(str2.cbegin(), str2.cend());
      CHECK(str == "Hello worldnew !");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 24) basic_string& append(rsl::initializer_list<value_type> ilist)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append({ ' ', 'm', 'y' });
      CHECK(str == "Hello world my");
      CHECK(str.size() == old_size + 3);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append({ 'n', 'e', 'w', ' ', '!'});
      CHECK(str == "Hello worldnew !");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 25) basic_string& append(const basic_string_view<value_type, traits_type> sv)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(rsl::string_view("my "));
      CHECK(str == "Hello worldmy ");
      CHECK(str.size() == old_size + 3);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(rsl::string_view("new !"));
      CHECK(str == "Hello worldnew !");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 26) basic_string& append(const basic_string_view<value_type, traits_type>& sv, size_type pos, size_type count = s_npos)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(rsl::string_view("new "), 0, 3);
      CHECK(str == "Hello worldnew");
      CHECK(str.size() == old_size + 3);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.append(rsl::string_view("new !"), 0, 5);
      CHECK(str == "Hello worldnew !");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }

  // 27) basic_string& operator+=(const basic_string& str)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += rsl::test::test_string("new ");
      CHECK(str == "Hello worldnew ");
      CHECK(str.size() == old_size + 4);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += rsl::test::test_string("again");
      CHECK(str == "Hello worldagain");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

    }
  }
  // 28) basic_string& operator+=(value_type ch)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += 'c';
      CHECK(str == "Hello worldc");
      CHECK(str.size() == old_size + 1);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += 'c';
      str += 'c';
      str += 'c';
      str += 'c';
      str += 'c';
      CHECK(str == "Hello worldccccc");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 29) basic_string& operator+=(const value_type (&s)[Size]) // NOLINT(modernize-avoid-c-arrays)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += "new ";
      CHECK(str == "Hello worldnew ");
      CHECK(str.size() == old_size + 4);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += "again";
      CHECK(str == "Hello worldagain");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 30) basic_string& operator+=(rsl::initializer_list<value_type> ilist)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += {'n', 'e', 'w', ' '};
      CHECK(str == "Hello worldnew ");
      CHECK(str.size() == old_size + 4);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += {'a', 'g', 'a', 'i', 'n'};
      CHECK(str == "Hello worldagain");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 31) basic_string& operator+=(const basic_string_view<value_type, traits_type>& sv)
  {
    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += rsl::string_view("new ");
      CHECK(str == "Hello worldnew ");
      CHECK(str.size() == old_size + 4);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }

    {
      rsl::test::test_string str("Hello world");

      const auto old_size = str.size();
      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str += rsl::string_view("again");
      CHECK(str == "Hello worldagain");
      CHECK(str.size() == old_size + 5);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
}
TEST_CASE("string compare")
{
  using namespace rsl::test;

  // 1) compare(const basic_string& str)
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare(rsl::test::test_string("Hello")) > 0);
    CHECK(str.compare(rsl::test::test_string("Hello World")) == 0);
    CHECK(str.compare(rsl::test::test_string("Hello World Again")) < 0);
  }
  // 2) compare(size_type pos1, size_type count1, const basic_string& str)
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare(0, 5, rsl::test::test_string("Hello Again")) < 0);
    CHECK(str.compare(0, 11, rsl::test::test_string("Hello World")) == 0);
    CHECK(str.compare(0, 5, rsl::test::test_string("Hello World")) < 0);
    CHECK(str.compare(6, 5, rsl::test::test_string("Hello World")) > 0);
  }
  // 3) compare(size_type pos1, size_type count1, const basic_string& str, size_type pos2, size_type count2)
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare(0, 5, rsl::test::test_string("Hello Again"), 6, 5) > 0);
    CHECK(str.compare(0, 5, rsl::test::test_string("Hello Again"), 0, 5) == 0);
    CHECK(str.compare(0, 12, rsl::test::test_string("Hello World"), 6, 5) < 0);
  }
  // 4) compare(const_pointer (&s)[Size])
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare("Hello Again") > 0);
    CHECK(str.compare("Hello World") == 0);
    CHECK(str.compare("Hello World Again") < 0);
  }
  // 5) compare(size_type pos1, size_type count1, const_pointer (&s)[Size])
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare(0, 5, "Hello Again") < 0);
    CHECK(str.compare(0, 11, "Hello World") == 0);
    CHECK(str.compare(0, 5, "Hello World") < 0);
    CHECK(str.compare(6, 5, "Hello World") > 0);
  }
  // 6) compare(size_type pos1, size_type count1, const_pointer s, size_type count2)
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare(0, 5, "Hello Again", 11) < 0);
    CHECK(str.compare(0, 5, "Hello World", 11) < 0);
    CHECK(str.compare(0, 11, "Hello World", 11) == 0);
  }
  // 7) compare(const basic_string_view<value_type, traits_type>& sv)
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare(rsl::string_view("Hello")) > 0);
    CHECK(str.compare(rsl::string_view("Hello World")) == 0);
    CHECK(str.compare(rsl::string_view("Hello World Again")) < 0);
  }
  // 8) compare(size_type pos1, size_type count1, const basic_string_view<value_type, traits_type> sv)
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare(0, 5, rsl::string_view("Hello Again")) < 0);
    CHECK(str.compare(0, 11, rsl::string_view("Hello World")) == 0);
    CHECK(str.compare(0, 5, rsl::string_view("Hello World")) < 0);
    CHECK(str.compare(6, 5, rsl::string_view("Hello World")) > 0);
  }
  // 9) compare(size_type pos1, size_type count1, const basic_string_view<value_type, traits_type> sv, size_type pos2, size_type count2 = s_npos)
  {
    rsl::test::test_string str("Hello World");
    CHECK(str.compare(0, 5, rsl::string_view("Hello Again"), 6, 5) > 0);
    CHECK(str.compare(0, 5, rsl::string_view("Hello Again"), 0, 5) == 0);
    CHECK(str.compare(0, 11, rsl::string_view("Hello World"), 6, 5) < 0);
  }

  // operator==
  {
    rsl::test::test_string str("Hello");
    rsl::test::test_string str2("Something");

    REQUIRE_FALSE(str == str2);
    REQUIRE_FALSE(str == "Something");
  }
}
TEST_CASE("string starts with")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  CHECK(str.starts_with("Hello") == true);
  CHECK(str.starts_with(hello) == true);
  CHECK(str.starts_with('H') == true);

  CHECK(str.starts_with("World") == false);
  CHECK(str.starts_with(world) == false);
  CHECK(str.starts_with('W') == false);
}
TEST_CASE("string ends with")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello World");
  const char8* hello = "Hello";
  const char8* world = "World";
  CHECK(str.ends_with("Hello") == false);
  CHECK(str.ends_with(hello) == false);
  CHECK(str.ends_with('H') == false);

  CHECK(str.ends_with("World") == true);
  CHECK(str.ends_with(world) == true);
  CHECK(str.ends_with('d') == true);
}
TEST_CASE("string contains")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello World");
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
TEST_CASE("string replace")
{
  using namespace rsl::test;

  // 1) replace(size_type pos, size_type count, const basic_string& str)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, rsl::test::test_string("Something"));
      CHECK(str == "Something World");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, rsl::test::test_string("Something nice"));
      CHECK(str == "Something nice World");
      CHECK(str.size() == 20);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 2) replace(const_iterator first, const_iterator last, const basic_string& str)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, rsl::test::test_string("Something"));
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "Something World");
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, rsl::test::test_string("Something nice"));
      CHECK(str == "Something nice World");
      CHECK(str.size() == 20);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 3) replace(size_type pos1, size_type count1, const basic_string& str, size_type pos2, size_type count2)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, rsl::test::test_string("Something"), 0, 4);
      CHECK(str.size() == 10);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(str == "Some World");
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, rsl::test::test_string("Something very!"), 0, 14);
      CHECK(str.size() == 20);
      CHECK(str == "Something very World");
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 4) replace(const_iterator first, const_iterator last, InputIt first2, InputIt last2)
  {
    {
      rsl::test::test_string str("Hello World");
      rsl::test::test_string str2("Something");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, str2.cbegin(), str2.cend());
      CHECK(str == "Something World");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");
      rsl::test::test_string str2("Something nice");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, str2.cbegin(), str2.cend());
      CHECK(str == "Something nice World");
      CHECK(str.size() == 20);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 5) replace(size_type pos, size_type count, const value_type (&s)[Size])
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, "Something");
      CHECK(str == "Something World");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, "Something nice");
      CHECK(str == "Something nice World");
      CHECK(str.size() == 20);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 6) replace(const_iterator first, const_iterator last, const value_type (&s)[Size])
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, "Something");
      CHECK(str == "Something World");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, "Something nice");
      CHECK(str == "Something nice World");
      CHECK(str.size() == 20);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 7) replace(size_type pos, size_type count, size_type count2, value_type ch)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, 5, 'c');
      CHECK(str == "ccccc World");
      CHECK(str.size() == 11);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, 10, 'c');

      CHECK(str == "cccccccccc World");
      CHECK(str.size() == 16);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 8) replace(const_iterator first, const_iterator last, size_type count2, value_type ch)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, 5, 'c');
      CHECK(str == "ccccc World");
      CHECK(str.size() == 11);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, 10, 'c');
      CHECK(str == "cccccccccc World");
      CHECK(str.size() == 16);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 9) replace(const_iterator first, const_iterator last, rsl::initializer_list<value_type> ilist)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, { 'S', 'o', 'm', 'e' });
      CHECK(str == "Some World");
      CHECK(str.size() == 10);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, { 'S', 'o', 'm', 'e', ' ', 'v', 'e', 'r', 'y', ' ', 'b', 'i', 'g'});
      CHECK(str == "Some very big World");
      CHECK(str.size() == 19);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 10) replace(size_type pos, size_type count, const basic_string_view<value_type, traits_type>& sv)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, rsl::string_view("Something"));
      CHECK(str == "Something World");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, rsl::string_view("Something nice"));
      CHECK(str == "Something nice World");
      CHECK(str.size() == 20);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 11) replace(const_iterator first, const_iterator last, const basic_string_view<value_type, traits_type>& sv)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, rsl::string_view("Something"));
      CHECK(str == "Something World");
      CHECK(str.size() == 15);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(str.cbegin(), str.cbegin() + 5, rsl::string_view("Something nice"));
      CHECK(str == "Something nice World");
      CHECK(str.size() == 20);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
  // 12) replace(size_type pos, size_type count, const basic_string_view<value_type, traits_type>& sv, size_type pos2, size_type count2 = s_npos)
  {
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, rsl::string_view("Something"), 0, 4);
      CHECK(str == "Some World");
      CHECK(str.size() == 10);
      CHECK(str.capacity() == str.sso_buff_size());
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
    {
      rsl::test::test_string str("Hello World");

      card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
      card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
      card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

      str.replace(0, 5, rsl::string_view("Something very nice"), 0, 14);
      CHECK(str == "Something very World");
      CHECK(str.size() == 20);
      CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
      CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
      CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
    }
  }
}
TEST_CASE("string subtr")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello World");
  rsl::test::test_string str2(str.substr());
  CHECK(str == str2);

  rsl::string_view str3 = str2.substr(0, 5);
  CHECK(str3 == "Hello");

  rsl::string_view str4 = str.substr(6);
  CHECK(str4 == "World");
}
TEST_CASE("string copy")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello World");
  char8 buffer[20] = {};

  str.copy(buffer, sizeof(buffer), 0);
  CHECK(rsl::strcmp(buffer, "Hello World") == 0);

  rsl::memset(buffer, 0, sizeof(buffer));
  str.copy(buffer, sizeof(buffer), 6);
  CHECK(rsl::strcmp(buffer, "World") == 0);
}
TEST_CASE("string resize")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello World");

  card32 pre_num_allocs = rsl::test::test_allocator::all_num_allocs();
  card32 pre_num_bytes_allocated = rsl::test::test_allocator::all_num_bytes_allocated();
  card32 pre_num_frees = rsl::test::test_allocator::all_num_frees();

  str.resize(5);
  CHECK(str == "Hello");
  CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
  CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
  CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

  str.resize(10);
  CHECK(str == "Hello\0\0\0\0\0");
  CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs);
  CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated);
  CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

  str.resize(20);
  CHECK(str == "Hello\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
  CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
  CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
  CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);

  str.resize(10);
  CHECK(str == "Hello\0\0\0\0\0");
  CHECK(rsl::test::test_allocator::all_num_allocs() == pre_num_allocs + 1);
  CHECK(rsl::test::test_allocator::all_num_bytes_allocated() == pre_num_bytes_allocated + str.capacity() * sizeof(decltype(str)::value_type));
  CHECK(rsl::test::test_allocator::all_num_frees() == pre_num_frees);
}
TEST_CASE("string find")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello Hello World");
  CHECK(str.find("Hello") == 0);
  CHECK(str.find("Hello", 1) == 6);
  CHECK(str.find("World") == 12);
  CHECK(str.find("asdfghj") == rsl::test::test_string::npos());

  CHECK(str.find(rsl::test::test_string("Hello")) == 0);
  CHECK(str.find(rsl::test::test_string("Hello"), 1) == 6);
  CHECK(str.find(rsl::test::test_string("World")) == 12);
  CHECK(str.find(rsl::test::test_string("asdfghj")) == rsl::test::test_string::npos());

  CHECK(str.find(rsl::string_view("Hello")) == 0);
  CHECK(str.find(rsl::string_view("Hello"), 1) == 6);
  CHECK(str.find(rsl::string_view("World")) == 12);
  CHECK(str.find(rsl::string_view("asdfghj")) == rsl::test::test_string::npos());

  CHECK(str.find('H') == 0);
  CHECK(str.find('d') == 16);
  CHECK(str.find('y') == rsl::test::test_string::npos());
}
TEST_CASE("string rfind")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello Hello World");
  CHECK(str.rfind("Hello") == 6);
  CHECK(str.rfind("Hello", 7) == 0);
  CHECK(str.rfind("World") == 12);
  CHECK(str.rfind("asdfghj") == rsl::test::test_string::npos());

  CHECK(str.rfind(rsl::test::test_string("Hello")) == 6);
  CHECK(str.rfind(rsl::test::test_string("Hello"), 7) == 0);
  CHECK(str.rfind(rsl::test::test_string("World")) == 12);
  CHECK(str.rfind(rsl::test::test_string("asdfghj")) == rsl::test::test_string::npos());

  CHECK(str.rfind(rsl::string_view("Hello")) == 6);
  CHECK(str.rfind(rsl::string_view("Hello"), 7) == 0);
  CHECK(str.rfind(rsl::string_view("World")) == 12);
  CHECK(str.rfind(rsl::string_view("asdfghj")) == rsl::test::test_string::npos());

  CHECK(str.rfind('H') == 6);
  CHECK(str.rfind('d') == 16);
  CHECK(str.rfind('y') == rsl::test::test_string::npos());
}
TEST_CASE("string find first of")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello Hello World");
  CHECK(str.find_first_of("he") == 1);
  CHECK(str.find_first_of("He") == 0);
  CHECK(str.find_first_of("ll") == 2);
  CHECK(str.find_first_of("W") == 12);
  CHECK(str.find_first_of("w") == str.npos());

  CHECK(str.find_first_of(rsl::test::test_string("he")) == 1);
  CHECK(str.find_first_of(rsl::test::test_string("He")) == 0);
  CHECK(str.find_first_of(rsl::test::test_string("ll")) == 2);
  CHECK(str.find_first_of(rsl::test::test_string("W")) == 12);
  CHECK(str.find_first_of(rsl::test::test_string("w")) == str.npos());

  CHECK(str.find_first_of(rsl::string_view("he")) == 1);
  CHECK(str.find_first_of(rsl::string_view("He")) == 0);
  CHECK(str.find_first_of(rsl::string_view("ll")) == 2);
  CHECK(str.find_first_of(rsl::string_view("W")) == 12);
  CHECK(str.find_first_of(rsl::string_view("w")) == str.npos());

  CHECK(str.find_first_of('H') == 0);
  CHECK(str.find_first_of('d') == 16);
  CHECK(str.find_first_of('y') == rsl::test::test_string::npos());
}
TEST_CASE("string find first not of")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello Hello World");
  CHECK(str.find_first_not_of("he") == 0);
  CHECK(str.find_first_not_of("He") == 2);
  CHECK(str.find_first_not_of("ll") == 0);
  CHECK(str.find_first_not_of("W") == 0);
  CHECK(str.find_first_not_of("w") == 0);

  CHECK(str.find_first_not_of(rsl::test::test_string("he")) == 0);
  CHECK(str.find_first_not_of(rsl::test::test_string("He")) == 2);
  CHECK(str.find_first_not_of(rsl::test::test_string("ll")) == 0);
  CHECK(str.find_first_not_of(rsl::test::test_string("W")) == 0);
  CHECK(str.find_first_not_of(rsl::test::test_string("w")) == 0);

  CHECK(str.find_first_not_of(rsl::string_view("he")) == 0);
  CHECK(str.find_first_not_of(rsl::string_view("He")) == 2);
  CHECK(str.find_first_not_of(rsl::string_view("ll")) == 0);
  CHECK(str.find_first_not_of(rsl::string_view("W")) == 0);
  CHECK(str.find_first_not_of(rsl::string_view("w")) == 0);

  CHECK(str.find_first_not_of('H') == 1);
  CHECK(str.find_first_not_of('d') == 0);
  CHECK(str.find_first_not_of('y') == 0);
}
TEST_CASE("string find last of")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello Hello World");
  CHECK(str.find_last_of("he") == 7);
  CHECK(str.find_last_of("He") == 7);
  CHECK(str.find_last_of("ll") == 15);
  CHECK(str.find_last_of("W") == 12);
  CHECK(str.find_last_of("w") == str.npos());

  CHECK(str.find_last_of(rsl::test::test_string("he")) == 7);
  CHECK(str.find_last_of(rsl::test::test_string("He")) == 7);
  CHECK(str.find_last_of(rsl::test::test_string("ll")) == 15);
  CHECK(str.find_last_of(rsl::test::test_string("W")) == 12);
  CHECK(str.find_last_of(rsl::test::test_string("w")) == str.npos());

  CHECK(str.find_last_of(rsl::string_view("he")) == 7);
  CHECK(str.find_last_of(rsl::string_view("He")) == 7);
  CHECK(str.find_last_of(rsl::string_view("ll")) == 15);
  CHECK(str.find_last_of(rsl::string_view("W")) == 12);
  CHECK(str.find_last_of(rsl::string_view("w")) == str.npos());

  CHECK(str.find_last_of('H') == 6);
  CHECK(str.find_last_of('d') == 16);
  CHECK(str.find_last_of('y') == rsl::test::test_string::npos());
}
TEST_CASE("string find last not of")
{
  using namespace rsl::test;

  rsl::test::test_string str("Hello Hello World");
  CHECK(str.find_last_not_of("he") == 17);
  CHECK(str.find_last_not_of("He") == 17);
  CHECK(str.find_last_not_of("ll") == 17);
  CHECK(str.find_last_not_of("W") == 17);
  CHECK(str.find_last_not_of("w") == 17);

  CHECK(str.find_last_not_of(rsl::test::test_string("he")) == 17);
  CHECK(str.find_last_not_of(rsl::test::test_string("He")) == 17);
  CHECK(str.find_last_not_of(rsl::test::test_string("ll")) == 17);
  CHECK(str.find_last_not_of(rsl::test::test_string("W")) == 17);
  CHECK(str.find_last_not_of(rsl::test::test_string("w")) == 17);

  CHECK(str.find_last_not_of(rsl::string_view("he")) == 17);
  CHECK(str.find_last_not_of(rsl::string_view("He")) == 17);
  CHECK(str.find_last_not_of(rsl::string_view("ll")) == 17);
  CHECK(str.find_last_not_of(rsl::string_view("W")) == 17);
  CHECK(str.find_last_not_of(rsl::string_view("w")) == 17);

  CHECK(str.find_last_not_of('H') == 17);
  CHECK(str.find_last_not_of('d') == 17);
  CHECK(str.find_last_not_of('y') == 17);
}
TEST_CASE("string integer conversions")
{
  using namespace rsl::test;

  {
    rsl::test::test_string intstr("123");
    CHECK(intstr.to_int().value() == 123);
    CHECK(intstr.to_uint().value() == 123);
  }

  {
    rsl::test::test_string nointstr("hello");
    CHECK(nointstr.to_int().has_value() == false);
    CHECK(nointstr.to_uint().has_value() == false);
  }

  {
    rsl::test::test_string floatstr("1.23");
    CHECK(floatstr.to_float().value() == 1.23f);
    CHECK(floatstr.to_int().has_value() == true);
    CHECK(floatstr.to_uint().has_value() == true);
  }
}
TEST_CASE("wide string test")
{
  using namespace rsl::test;

  {
    rsl::wstring str(L"small string");
    rsl::wstring str2(L"");
    str.swap(str2);

    CHECK(str.size() == 0);
    CHECK(str2.size() == 12);
    CHECK(str.length() == 0);
    CHECK(str2.length() == 12);
    CHECK(str.capacity() > 0);
    CHECK(str2.capacity() > 0);

    str.resize(20);
    CHECK(str.size() == 20);

    str.assign(L"this is a very long string that should be assigned on the heap");
    CHECK(str == L"this is a very long string that should be assigned on the heap");

  }
}
// NOLINTEND
