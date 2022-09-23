// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: cstring.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/cstring.h"

// copies one string to another
char8* rsl::strcpy(char8* dest, const char8* src)
{
  char8* res = dest;

  while(*src)
  {
    *dest = *src;
    ++src;
  }

  // the standard says the null termination needs to be copied too
  *dest = *src;

  return res;
}
// copies a at most "count" characters to destination.
// if the null termination char is reached, additional null characters are written.
char8* rsl::strncpy(char8* dest, const char8* src, count_t count)
{
  char8* res = dest;

  while(count > 0 && *src)
  {
    *dest = *src;
    ++dest;
    ++src;
    --count;
  }

  while(count > 0)
  {
    *dest = '\0';
    ++dest;
    --count;
  }

  return res;
}
// appends a copy of src to the end of dest
char8* rsl::strcat(char8* dest, const char8* src)
{
  char8* res = dest;
  while(*dest)
  {
    ++dest;
  }

  while(*src)
  {
    *dest = *src;
    ++dest;
    ++src;
  }

  *dest = '\0';

  return res;
}
// at most count characters are appended from src to dest
// it's possible this function copies count + 1
// if the null termination char needs to be copied over after count characters have been copied
char8* rsl::strncat(char8* dest, const char8* src, count_t count)
{
  char8* res = dest;

  while(*dest)
  {
    ++dest;
  }

  while(count > 0 && *src)
  {
    *dest = *src;
    ++dest;
    ++src;
  }

  *dest = '\0';

  return res;
}
// returns the lengths of a string
count_t rsl::strlen(const char8* str)
{
  count_t len = 0;
  while(*str)
  {
    ++len;
    ++str;
  }
  return len;
}
// compares 2 strings lexicographically
int32 rsl::strcmp(const char8* lhs, const char8* rhs)
{
  while(*lhs && *rhs && *lhs == *rhs)
  {
    ++lhs;
    ++rhs;
  }
  return *lhs - *rhs;
}
// compares at most count characters lexicographically
int32 rsl::strncmp(const char8* lhs, const char8* rhs, count_t count)
{
  while(count != 0 && *lhs && *rhs && *lhs == *rhs)
  {
    lhs++;
    rhs++;
    count--;
  }
  return count == 0 ? 0 : (*lhs - *rhs);
}
// finds the first occurrence of a character
const char8* rsl::strchr(const char8* str, char8 ch)
{
  do
  {
    if(*str == ch)
    {
      return str;
    }
  } while(*str++);

  return nullptr;
}
// finds the first occurrence of a character
char8* rsl::strchr(char8* str, char8 ch)
{
  do
  {
    if(*str == ch)
    {
      return str;
    }
  } while(*str++);

  return nullptr;
}
// finds the last occurrence of a character
const char8* rsl::strrchr(const char8* str, char8 ch)
{
  const char8* res = nullptr;
  do
  {
    if(*str == ch)
    {
      res = str;
    }
  } while(*str++);
  return res;
}
// finds the last occurrence of a character
char8* rsl::strrchr(char8* str, char8 ch)
{
  char8* res = nullptr;
  do
  {
    if(*str == ch)
    {
      res = str;
    }
  } while(*str++);
  return res;
}
// calculates the length of the initial segment in "target"
// that only contains characters from "toFind"
count_t rsl::strspn(const char8* target, const char8* toFind)
{
  const char8* s = target;
  const char8* c;

  while(*target)
  {
    for(c = toFind; *c; ++c)
    {
      if(*target == *c)
        break;
    }
    if(*c == '\0')
      break;
    target++;
  }

  return static_cast<count_t>(target - s);
}
// calculates the length of the initial segment in "target"
// that only contains characters not from "toFind"
count_t rsl::strcspn(const char8* target, const char8* notToFind)
{
  const char8* s = target;
  const char8* c;

  while(*target)
  {
    for(c = notToFind; *c; ++c)
    {
      if(*target != *c)
        break;
    }
    if(*c == '\0')
      break;
    target++;
  }

  return static_cast<count_t>(target - s);
}
// finds the first location of any character from a set of separators
const char8* rsl::strpbrk(const char8* target, const char8* toFind)
{
  const char8* c;

  while(*target)
  {
    for(c = toFind; *c; ++c)
    {
      if(*target == *c)
        return target;
    }
    ++target;
  }

  return nullptr;
}
// finds the first location of any character from a set of separators
char8* rsl::strpbrk(char8* target, const char8* toFind)
{
  const char8* c;

  while(*target)
  {
    for(c = toFind; *c; ++c)
    {
      if(*target == *c)
        return target;
    }
    ++target;
  }

  return nullptr;
}
// finds the first occurrence of substring of characters
const char8* rsl::strstr(const char8* str, const char8* substr)
{
  const char8* s;
  const char8* c;

  while(*str)
  {
    s = str;
    for(c = substr; *c; ++c)
    {
      if(*c != *str)
        break;
    }
    if(*c == '\0')
      return s;
  }

  return nullptr;
}
// finds the first occurrence of substring of characters
char8* rsl::strstr(char8* str, const char8* substr)
{
  char8* s;
  const char8* c;

  while(*str)
  {
    s = str;
    for(c = substr; *c; ++c)
    {
      if(*c != *str)
        break;
    }
    if(*c == '\0')
      return s;
  }

  return nullptr;
}
char8* rsl::strtok(char8* str, const char8* delim);
