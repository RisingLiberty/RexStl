// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: wctype.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/bonus/defines.h"
#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <cwctype>

namespace rsl
{
  inline namespace v1
  {
    REX_STD_CLASS_ALIAS(wctrans_t);
    REX_STD_CLASS_ALIAS(wctype_t);

    // all of these functions are similar to the standards, except for 2 differences.
    // first, the "is" is separated with an underscore for readability.
    // second, these functions returns bools instead of ints.

    // I know these functions end up calling each other a lot.
    // However, they're very simple functions so should be inlined by the compiler

    // CONTROL CODES
    // 00 | NULL | null char
    // 01 | STX  | start of header
    // 02 | SOT  | start of text
    // 03 | ETX  | end of text
    // 04 | EOT  | end of transmision
    // 05 | ENQ  | enquiry
    // 06 | ACK  | acknowledge
    // 07 | ACK  | bell
    // 08 | BS   | backspace
    // 09 | HT   | horizontal tabulation
    // 0A | LF   | line feed
    // 0B | VT   | vrtial tabulation
    // 0C | FF   | form feed
    // 0D | CR   | carriage return
    // 0E | S0   | shift out
    // 0F | SI   | shift in
    // 10 | DLE  | data link escape
    // 11 | DC1  | device control 1
    // 12 | DC2  | device control 2
    // 13 | DC3  | device control 3
    // 14 | DC4  | device control 4
    // 15 | NAK  | negative acknowledge
    // 16 | SYN  | synchornous idle
    // 17 | ETB  | end of transmission
    // 18 | CAN  | cancel
    // 19 | EM   | end of medium
    // 1A | SUB  | substitute
    // 1B | ESC  | escape
    // 1C | FS   | file separator
    // 1D | GS   | group separator
    // 1E | RS   | record separator
    // 1F | US   | unit separator
    // 7F | DEL  | delete

    // Forward declarations
    // checks if a character is alphanumeric
    REX_NO_DISCARD constexpr bool is_alnum(tchar ch);
    REX_NO_DISCARD constexpr bool is_alpha(tchar ch);
    // REX_NO_DISCARD constexpr bool is_lower(tchar ch);
    // REX_NO_DISCARD constexpr bool is_upper(tchar ch);
    // REX_NO_DISCARD constexpr bool is_digit(tchar ch);
    REX_NO_DISCARD constexpr bool is_xdigit(tchar ch);
    REX_NO_DISCARD constexpr bool is_cntrl(tchar ch);
    REX_NO_DISCARD constexpr bool is_graph(tchar ch);
    REX_NO_DISCARD constexpr bool is_space(tchar ch);
    REX_NO_DISCARD constexpr bool is_blank(tchar ch);
    REX_NO_DISCARD constexpr bool is_print(tchar ch);
    REX_NO_DISCARD constexpr bool is_punct(tchar ch);

    REX_NO_DISCARD constexpr bool is_digit(tchar digit);
    REX_NO_DISCARD constexpr bool is_upper(tchar letter);
    REX_NO_DISCARD constexpr bool is_lower(tchar letter);

    // checks if a character is alphanumeric
    REX_NO_DISCARD constexpr bool is_alnum(tchar ch)
    {
      return is_alpha(ch) || is_digit(ch);
    }
    // checks if a character is alphabetic
    REX_NO_DISCARD constexpr bool is_alpha(tchar ch)
    {
      return is_lower(ch) || is_upper(ch);
    }

    REX_NO_DISCARD constexpr bool is_upper(tchar letter)
    {
      return letter >= L'A' && letter <= L'Z';
    }
    REX_NO_DISCARD constexpr bool is_lower(tchar letter)
    {
      return letter >= L'a' && letter <= L'z';
    }

    REX_NO_DISCARD constexpr bool is_digit(tchar digit)
    {
      return digit >= L'0' && digit <= L'9';
    }
    REX_NO_DISCARD constexpr bool is_digitf(tchar digit)
    {
      return is_digit(digit) || digit == L'.';
    }

    // checks if a character is a hexadecimal character
    REX_NO_DISCARD constexpr bool is_xdigit(tchar ch)
    {
      return is_digit(ch) || (ch >= L'a' && ch <= L'f') || (ch >= L'A' && ch <= L'F');
    }
    // checks if a character is a control character
    REX_NO_DISCARD constexpr bool is_cntrl(tchar ch)
    {
      return (ch >= 0 && ch <= 31) || ch == 127; // NOLINT(readability-magic-numbers)
    }
    // checks if a character is a graphical character
    REX_NO_DISCARD constexpr bool is_graph(tchar ch)
    {
      return is_print(ch) && ch != ' ';
    }
    // checks if a character is a space character
    REX_NO_DISCARD constexpr bool is_space(tchar ch)
    {
      return ch == ' ' || (ch >= L'\t' && ch <= L'\r');
    }
    // checks if a character is a blank character
    REX_NO_DISCARD constexpr bool is_blank(tchar ch)
    {
      return ch == L'\t' || ch == L' ';
    }
    // checks if a character is a printing character
    REX_NO_DISCARD constexpr bool is_print(tchar ch)
    {
      return !is_cntrl(ch);
    }
    // checks if a character is a punctuation character
    REX_NO_DISCARD constexpr bool is_punct(tchar ch)
    {
      return is_graph(ch) && !is_alnum(ch);
    }


    REX_NO_DISCARD constexpr tchar to_upper(tchar letter)
    {
      return is_lower(letter) ? letter - (L'z' - L'Z') : letter; // NOLINT(cppcoreguidelines-narrowing-conversions)
    }
    REX_NO_DISCARD constexpr tchar to_lower(tchar letter)
    {
      return is_upper(letter) ? letter - (L'Z' - L'z') : letter; // NOLINT(cppcoreguidelines-narrowing-conversions)
    }

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
