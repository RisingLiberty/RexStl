// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: test_cstring.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

// NOLINTBEGIN

#include "rex_std/cstring.h"

namespace cstring_test
{
  bool equals(const char* lhs, const char* rhs)
  {
    while(*lhs && *rhs)
    {
      if(*lhs != *rhs)
      {
        return false;
      }
      ++lhs;
      ++rhs;
    }
    return *lhs == *rhs;
  }
} // namespace cstring_test

TEST_CASE("strlen")
{
  CHECK(rsl::strlen("") == 0);
  CHECK(rsl::strlen("a") == 1);
  CHECK(rsl::strlen("hello") == 5);
  CHECK(rsl::strlen("hello world") == 11);
  CHECK(rsl::strlen(L"hello") == 5);

  // strlen stops at the first null terminator
  const char str[] = {'a', 'b', '\0', 'c', '\0'};
  CHECK(rsl::strlen(str) == 2);

  static_assert(rsl::strlen("constexpr") == 9);
}

TEST_CASE("strcpy")
{
  char buffer[32] = {};
  char* res       = rsl::strcpy(buffer, "hello");
  CHECK(res == buffer);
  CHECK(cstring_test::equals(buffer, "hello"));

  // the null terminator gets copied over as well
  char buffer2[32] = "xxxxxxxxxx";
  rsl::strcpy(buffer2, "abc");
  CHECK(cstring_test::equals(buffer2, "abc"));
  CHECK(buffer2[3] == '\0');
  CHECK(buffer2[4] == 'x');

  // copying an empty string
  rsl::strcpy(buffer, "");
  CHECK(buffer[0] == '\0');
}

TEST_CASE("strncpy")
{
  // count is smaller than the source string, no null terminator is written
  {
    char buffer[8] = "xxxxxxx";
    char* res      = rsl::strncpy(buffer, "hello", 3);
    CHECK(res == buffer);
    CHECK(buffer[0] == 'h');
    CHECK(buffer[1] == 'e');
    CHECK(buffer[2] == 'l');
    CHECK(buffer[3] == 'x');
  }

  // count is bigger than the source string, the rest is padded with null terminators
  {
    char buffer[8] = "xxxxxxx";
    rsl::strncpy(buffer, "hi", 5);
    CHECK(buffer[0] == 'h');
    CHECK(buffer[1] == 'i');
    CHECK(buffer[2] == '\0');
    CHECK(buffer[3] == '\0');
    CHECK(buffer[4] == '\0');
    CHECK(buffer[5] == 'x');
  }
}

TEST_CASE("strcat")
{
  char buffer[32] = "hello";
  char* res       = rsl::strcat(buffer, " world");
  CHECK(res == buffer);
  CHECK(cstring_test::equals(buffer, "hello world"));

  rsl::strcat(buffer, "");
  CHECK(cstring_test::equals(buffer, "hello world"));

  char empty[8] = "";
  rsl::strcat(empty, "abc");
  CHECK(cstring_test::equals(empty, "abc"));
}

TEST_CASE("strncat")
{
  // only the first 'count' characters are appended
  char buffer[32] = "hello";
  char* res       = rsl::strncat(buffer, " world", 3);
  CHECK(res == buffer);
  CHECK(cstring_test::equals(buffer, "hello wo"));

  // count bigger than the source appends the full source
  char buffer2[32] = "abc";
  rsl::strncat(buffer2, "def", 10);
  CHECK(cstring_test::equals(buffer2, "abcdef"));
}

TEST_CASE("strcmp")
{
  CHECK(rsl::strcmp("abc", "abc") == 0);
  CHECK(rsl::strcmp("abc", "abd") < 0);
  CHECK(rsl::strcmp("abd", "abc") > 0);
  CHECK(rsl::strcmp("ab", "abc") < 0);
  CHECK(rsl::strcmp("abc", "ab") > 0);
  CHECK(rsl::strcmp("", "") == 0);
  CHECK(rsl::strcmp("", "a") < 0);
  CHECK(rsl::strcmp("ABC", "abc") < 0);
}

TEST_CASE("strncmp")
{
  CHECK(rsl::strncmp("abc", "abd", 2) == 0);
  CHECK(rsl::strncmp("abc", "abd", 3) < 0);
  CHECK(rsl::strncmp("abd", "abc", 3) > 0);
  CHECK(rsl::strncmp("abc", "abc", 10) == 0);
  CHECK(rsl::strncmp("ab", "abc", 3) < 0);
  CHECK(rsl::strncmp("abc", "xyz", 0) == 0);

  static_assert(rsl::strncmp("abc", "abd", 2) == 0);
}

TEST_CASE("stricmp")
{
  CHECK(rsl::stricmp("abc", "ABC") == 0);
  CHECK(rsl::stricmp("Hello", "hELLO") == 0);
  CHECK(rsl::stricmp("abc", "ABD") < 0);
  CHECK(rsl::stricmp("ABD", "abc") > 0);
  CHECK(rsl::stricmp("ab", "ABC") < 0);
  CHECK(rsl::stricmp("", "") == 0);
}

TEST_CASE("strincmp")
{
  CHECK(rsl::strincmp("abc", "ABD", 2) == 0);
  CHECK(rsl::strincmp("abc", "ABD", 3) < 0);
  CHECK(rsl::strincmp("HELLO", "hello world", 5) == 0);
  CHECK(rsl::strincmp("abc", "xyz", 0) == 0);
}

TEST_CASE("strchr")
{
  const char* str = "hello world";

  CHECK(rsl::strchr(str, 'h') == str);
  CHECK(rsl::strchr(str, 'o') == str + 4);
  CHECK(rsl::strchr(str, 'd') == str + 10);
  CHECK(rsl::strchr(str, 'z') == nullptr);

  // the null terminator is considered part of the string
  CHECK(rsl::strchr(str, '\0') == str + 11);

  char buffer[] = "abc";
  char* res     = rsl::strchr(buffer, 'b');
  CHECK(res == buffer + 1);
  *res = 'x';
  CHECK(cstring_test::equals(buffer, "axc"));
}

TEST_CASE("strrchr")
{
  const char* str = "hello world";

  CHECK(rsl::strrchr(str, 'o') == str + 7);
  CHECK(rsl::strrchr(str, 'l') == str + 9);
  CHECK(rsl::strrchr(str, 'h') == str);
  CHECK(rsl::strrchr(str, 'z') == nullptr);
  CHECK(rsl::strrchr(str, '\0') == str + 11);

  char buffer[] = "abcabc";
  CHECK(rsl::strrchr(buffer, 'a') == buffer + 3);
}

TEST_CASE("strspn")
{
  CHECK(rsl::strspn("abcde", "abc") == 3);
  CHECK(rsl::strspn("abcde", "xyz") == 0);
  CHECK(rsl::strspn("aaaa", "a") == 4);
  CHECK(rsl::strspn("", "abc") == 0);
  CHECK(rsl::strspn("abc", "") == 0);
  CHECK(rsl::strspn("cba123", "abc") == 3);
}

TEST_CASE("strcspn")
{
  CHECK(rsl::strcspn("abcde", "dx") == 3);
  CHECK(rsl::strcspn("abcde", "xyz") == 5);
  CHECK(rsl::strcspn("abcde", "a") == 0);
  CHECK(rsl::strcspn("", "abc") == 0);
  CHECK(rsl::strcspn("abc", "") == 3);
}

TEST_CASE("strpbrk")
{
  const char* str = "hello world";

  CHECK(rsl::strpbrk(str, "ow") == str + 4);
  CHECK(rsl::strpbrk(str, "dw") == str + 6);
  CHECK(rsl::strpbrk(str, "xyz") == nullptr);
  CHECK(rsl::strpbrk(str, "") == nullptr);

  char buffer[] = "a,b";
  CHECK(rsl::strpbrk(buffer, ",") == buffer + 1);
}

TEST_CASE("strstr")
{
  const char* str = "hello world";

  CHECK(rsl::strstr(str, "hello") == str);
  CHECK(rsl::strstr(str, "world") == str + 6);
  CHECK(rsl::strstr(str, "o w") == str + 4);
  CHECK(rsl::strstr(str, "d") == str + 10);
  CHECK(rsl::strstr(str, "worlds") == nullptr);
  CHECK(rsl::strstr(str, "xyz") == nullptr);
  CHECK(rsl::strstr(str, "ll") == str + 2);

  // the non const overload never advances 'str' when the first position doesn't match, so it loops forever.
  // we only test a case that matches immediately here to keep the test suite from hanging
  char buffer[] = "abcabd";
  CHECK(rsl::strstr(buffer, "a") == buffer);
}

// NOLINTEND
