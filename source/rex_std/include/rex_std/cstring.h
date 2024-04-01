// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: cstring.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/type_traits/is_character.h"
#include "rex_std/bonus/types.h"
#include "rex_std/ctype.h"
#include "rex_std/wctype.h"
#include "rex_std/internal/type_traits/enable_if.h"

namespace rsl
{
  inline namespace v1
  {

#define NULL 0 // NOLINT

#if defined(RSL_PLATFORM_X86)
    using size_t = uint32;
#elif defined(RSL_PLATFORM_X64)
    using size_t = uint64;
#else
  #error "No platform specified"
#endif

    // copies one string to another
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strcpy(Char* dest, const Char* src)
    {
      Char* res = dest;

      while(*src) // NOLINT
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
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strncpy(Char* dest, const Char* src, count_t count)
    {
      Char* res = dest;

      while(count > 0 && *src) // NOLINT
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
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strcat(Char* dest, const Char* src)
    {
      Char* res = dest;
      while(*dest) // NOLINT
      {
        ++dest;
      }

      while(*src) // NOLINT
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
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strncat(Char* dest, const Char* src, count_t count)
    {
      Char* res = dest;

      while(*dest) // NOLINT
      {
        ++dest;
      }

      while(count > 0 && *src) // NOLINT(readability-implicit-bool-conversion)
      {
        *dest = *src;
        ++dest;
        ++src;
      }

      *dest = '\0';

      return res;
    }
    // transforms src into a string such that comparing 2 transformed strings
    // with strcmp gives the same result as you'd compare the original strings with strcoll
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    count_t strxfrm(Char* dest, const Char* src, count_t count);
    // returns the lengths of a string
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    constexpr count_t strlen(const Char* str)
    {
      count_t len = 0;
      while(*str) // NOLINT
      {
        ++len;
        ++str;
      }
      return len;
    }
    // compares 2 strings lexicographically
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    int32 strcmp(const Char* lhs, const Char* rhs)
    {
      while(*lhs && *rhs && *lhs == *rhs) // NOLINT
      {
        ++lhs;
        ++rhs;
      }
      return *lhs - *rhs;
    }
    // compares at most count characters lexicographically
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    constexpr int32 strncmp(const Char* lhs, const Char* rhs, count_t count)
    {
      while(count != 0 && *lhs && *rhs && *lhs == *rhs) // NOLINT(readability-implicit-bool-conversion)
      {
        lhs++;
        rhs++;
        count--;
      }
      return count == 0 ? 0 : (*lhs - *rhs);
    }
    // compares 2 strings lexicographically
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    int32 stricmp(const Char* lhs, const Char* rhs)
    {
      while(*lhs && *rhs) // NOLINT
      {
        const Char lhs_lower = rsl::to_lower(*lhs);
        const Char rhs_lower = rsl::to_lower(*rhs);

        if(lhs_lower != rhs_lower)
        {
          break;
        }

        ++lhs;
        ++rhs;
      }

      const Char lhs_lower = rsl::to_lower(*lhs);
      const Char rhs_lower = rsl::to_lower(*rhs);
      return lhs_lower - *rhs_lower;
    }
    // compares at most count characters lexicographically
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    constexpr int32 strincmp(const Char* lhs, const Char* rhs, count_t count)
    {
      while(count != 0 && *lhs && *rhs) // NOLINT(readability-implicit-bool-conversion)
      {
        const Char lhs_lower = rsl::to_lower(*lhs);
        const Char rhs_lower = rsl::to_lower(*rhs);

        if(lhs_lower != rhs_lower)
        {
          break;
        }

        lhs++;
        rhs++;
        count--;
      }

      const Char lhs_lower = rsl::to_lower(*lhs);
      const Char rhs_lower = rsl::to_lower(*rhs);

      return count == 0 ? 0 : lhs_lower - rhs_lower;
    }
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    int32 strcoll(const Char* lhs, const Char* rhs);
    // finds the first occurrence of a character
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    const Char* strchr(const Char* str, Char ch)
    {
      do
      {
        if(*str == ch) // NOLINT
        {
          return str;
        }
      } while(*str++); // NOLINT(readability-implicit-bool-conversion)

      return nullptr;
    }
    // finds the first occurrence of a character
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strchr(Char* str, Char ch)
    {
      do
      {
        if(*str == ch) // NOLINT
        {
          return str;
        }
      } while(*str++); // NOLINT(readability-implicit-bool-conversion)

      return nullptr;
    }
    // finds the last occurrence of a character
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    const Char* strrchr(const Char* str, Char ch)
    {
      const Char* res = nullptr;
      do
      {
        if(*str == ch) // NOLINT
        {
          res = str;
        }
      } while(*str++); // NOLINT(readability-implicit-bool-conversion)
      return res;
    }
    // finds the last occurrence of a character
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strrchr(Char* str, Char ch)
    {
      Char* res = nullptr;
      do
      {
        if(*str == ch) // NOLINT
        {
          res = str;
        }
      } while(*str++); // NOLINT(readability-implicit-bool-conversion)
      return res;
    }
    // calculates the length of the initial segment in "target"
    // that only contains characters from "toFind"
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    count_t strspn(const Char* target, const Char* toFind)
    {
      const Char* s = target;
      const Char* c = nullptr;

      while(*target) // NOLINT
      {
        for(c = toFind; *c; ++c) // NOLINT(readability-implicit-bool-conversion)
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
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    count_t strcspn(const Char* target, const Char* notToFind)
    {
      const Char* s = target;
      const Char* c = nullptr;

      while(*target) // NOLINT
      {
        for(c = notToFind; *c; ++c) // NOLINT
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
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    const Char* strpbrk(const Char* target, const Char* toFind)
    {
      const Char* c = nullptr;

      while(*target) // NOLINT
      {
        for(c = toFind; *c; ++c) // NOLINT
        {
          if(*target == *c)
            return target;
        }
        ++target;
      }

      return nullptr;
    }
    // finds the first location of any character from a set of separators
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strpbrk(Char* target, const Char* toFind)
    {
      const Char* c = nullptr;

      while(*target) // NOLINT
      {
        for(c = toFind; *c; ++c) // NOLINT
        {
          if(*target == *c)
            return target;
        }
        ++target;
      }

      return nullptr;
    }
    // finds the first occurrence of substring of characters
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    const Char* strstr(const Char* str, const Char* substr)
    {
      const Char* s = nullptr;
      const Char* c = nullptr;

      while(*str) // NOLINT
      {
        s = str;
        for(c = substr; *c; ++c) // NOLINT
        {
          if(*c != *str)
          {
            break;
          }
        }
        if(*c == '\0')
        {
          return s;
        }
        ++str;
      }

      return nullptr;
    }
    // finds the first occurrence of substring of characters
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strstr(Char* str, const Char* substr)
    {
      Char* s       = nullptr;
      const Char* c = nullptr;

      while(*str) // NOLINT
      {
        s = str;
        for(c = substr; *c; ++c) // NOLINT(readability-implicit-bool-conversion)
        {
          if(*c != *str)
          {
            break;
          }
        }
        if(*c == '\0')
        {
          return s;
        }
      }

      return nullptr;
    }
    template <typename Char, typename rsl::v1::enable_if_t<is_character_v<Char>, int> = 0>
    Char* strtok(Char* str, const Char* delim);

    /// RSL Comment: Different from ISO C++ Standard at time of writing (09/Aug/2022)
    // Rex doesn't define character array manipulation functions in cstring, but defines them in memory instead.
    // these functions are:
    // memchr
    // memcmp
    // memset
    // memcpy
    // memmove

  } // namespace v1
} // namespace rsl

// #include "rex_std/disable_std_checking.h"
// #include "rex_std/std_alias_defines.h"
//
// #include <cstring>
//
// namespace rsl { inline namespace v1 {
//
//// RSL_FUNC_ALIAS(strxfrm);
//// RSL_FUNC_ALIAS(strcoll);
//// RSL_FUNC_ALIAS(strtok);
//// RSL_FUNC_ALIAS(strerror);
//
// }}
//
// #include "rex_std/enable_std_checking.h"