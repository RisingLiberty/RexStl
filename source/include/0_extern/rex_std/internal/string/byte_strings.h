// ============================================ 
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: byte_strings.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

#include "rex_std/bonus/string/string_utils.h"

#include "rex_std/optional.h"

// Character array functions (cstring.h)
#include "rex_std/internal/string/memchr.h"
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/memory/memset.h"
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/memory/memmove.h"
#include "rex_std/internal/memory/memcpy_backward.h" // Not in C++ Standard

namespace rsl
{
    //
    // Character Classification (cctype.h)
    //

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
    REX_NO_DISCARD constexpr bool is_alnum(char8 ch);
    REX_NO_DISCARD constexpr bool is_alpha(char8 ch);
    //REX_NO_DISCARD constexpr bool is_lower(char8 ch);
    //REX_NO_DISCARD constexpr bool is_upper(char8 ch);
    //REX_NO_DISCARD constexpr bool is_digit(char8 ch);
    REX_NO_DISCARD constexpr bool is_xdigit(char8 ch);
    REX_NO_DISCARD constexpr bool is_cntrl(char8 ch);
    REX_NO_DISCARD constexpr bool is_graph(char8 ch);
    REX_NO_DISCARD constexpr bool is_space(char8 ch);
    REX_NO_DISCARD constexpr bool is_blank(char8 ch);
    REX_NO_DISCARD constexpr bool is_print(char8 ch);
    REX_NO_DISCARD constexpr bool is_punct(char8 ch);

    // checks if a character is alphanumeric
    REX_NO_DISCARD constexpr bool is_alnum(char8 ch)
    {
        return is_alpha(ch) || is_digit(ch);
    }
    // checks if a character is alphabetic
    REX_NO_DISCARD constexpr bool is_alpha(char8 ch)
    {
        return is_lower(ch) || is_upper(ch);
    }
    // checks if a character is lowercase
    //REX_NO_DISCARD constexpr bool is_lower(char8 ch)
    //{
    //    return ch >= 'a' && ch <= 'z';
    //}
    // checks if a character is uppercase
    //REX_NO_DISCARD constexpr bool is_upper(char8 ch)
    //{
    //    return ch >= 'A' && ch <= 'Z';
    //}
    // checks if a character is a digit
    //REX_NO_DISCARD constexpr bool is_digit(char8 ch)
    //{
    //    return ch >= '0' && ch <= '9';
    //}
    // checks if a character is a hexadecimal character
    REX_NO_DISCARD constexpr bool is_xdigit(char8 ch)
    {
        return is_digit(ch) ||
            (ch >= 'a' && ch <= 'f') ||
            (ch >= 'A' && ch <= 'F');
    }
    // checks if a character is a control character
    REX_NO_DISCARD constexpr bool is_cntrl(char8 ch)
    {
        return ch >= 0 && ch <= 31 || ch == 127;
    }
    // checks if a character is a graphical character
    REX_NO_DISCARD constexpr bool is_graph(char8 ch)
    {
        return is_print(ch) && ch != 32;
    }
    // checks if a character is a space character
    REX_NO_DISCARD constexpr bool is_space(char8 ch)
    {
        return ch == 32 || (ch >= 9 && ch <= 13);
    }
    // checks if a character is a blank character
    REX_NO_DISCARD constexpr bool is_blank(char8 ch)
    {
        return ch == 9 || ch == 32;
    }
    // checks if a character is a printing character
    REX_NO_DISCARD constexpr bool is_print(char8 ch)
    {
        return !is_cntrl(ch);
    }
    // checks if a character is a punctuation character
    REX_NO_DISCARD constexpr bool is_punct(char8 ch)
    {
        return is_graph(ch) && !is_alnum(ch);
    }

    //
    // Character Manipulation
    //

    // converts a character to lowercase
    REX_NO_DISCARD constexpr char8 to_lower(char8 ch);
    // converts a character to uppercase
    REX_NO_DISCARD constexpr char8 to_upper(char8 ch);

    //
    // Conversion To Numeric Formats (cstdlib.h)
    //
    
    namespace internal
    {
        template <typename T>
        constexpr optional<T> strtosigned(const char8* str, char8** str_end, int32 base)
        {

            // skip white space
            while (is_space(*str))
            {
                ++str;
            }

            // determine base
            if ((base == 0 || base == 16) && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) 
            {
		        str += 2;
		        return 16;
	        }
	        if (base == 0)
		    {
                base = *str == '0' ? 8 : 10;
            }

            // determine sign
            int32 sign = 1;
            if (*str == '-')
            {
                sign = -1;
                ++str;
            }
            else if (*str == '+')
            {
                ++str;
            }

            // process string
            optional<T> result = nullopt;
            T value = 0;
            while (*str != '\0')
            {
                char8 c = *str;
                
                if (is_digit(c))
		    	    c -= '0';
		        else if (is_alpha(c))
		        	c -= is_upper(c) ? 'A' - 10 : 'a' - 10;
		        else
		        	break;
		        
                if (c >= base)
		        	break;

		        else 
                {
                    value *= base;
                    value += c;
                }
            }

            // return result
            if (str_end)
            {
                *str_end = const_cast<char8*>(str);
            }
            result = optional<T>(value * sign);

            return result;
        }
    
        template <typename T>
        constexpr optional<T> strtounsigned(const char8* str, char8** str_end, int32 base)
        {
            // skip white space
            while (is_space(*str))
            {
                ++str;
            }

            // determine base
            if ((base == 0 || base == 16) && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) 
            {
		        str += 2;
		        return 16;
	        }
	        if (base == 0)
		    {
                base = *str == '0' ? 8 : 10;
            }

            // process string
            T value = 0;
            optional<T> result = nullopt;
            while (*str != '\0')
            {
                char8 c = *str;
                
                if (is_digit(c))
		    	    c -= '0';
		        else if (is_alpha(c))
		        	c -= is_upper(c) ? 'A' - 10 : 'a' - 10;
		        else
		        	break;
		        
                if (c >= base)
		        	break;

		        else 
                {
                    value *= base;
                    value += c;
                }
            }

            // return result
            if (str_end)
            {
                *str_end = const_cast<char8*>(str);
            }
            result = optional<T>(value);

            return result;
        }

        template <typename T>
        constexpr optional<T> strtofloatingpoint(const char8* str, char8** str_end)
        {
            int32 sign = 1;

            const char8* c = str;

            if (*c == '-')
            {
                sign = -1;
                ++c;
            }
            else if (*c == '+')
            {
                ++c;
            }

            T before_radix_value = 0.0f;
            T after_radix_value = 0.0f;
            card32 num_digits_after_radix = 0;
            bool assigning_before_radix = true;
            optional<T> result = nullopt;

            while (*c != '\0')
            {
                if (!is_digitf(*c))
                {
                    break;
                }

                if (*c == '.')
                {
                    assigning_before_radix = false;
                    continue;
                }

                if (assigning_before_radix)
                {
                    before_radix_value = ctoi(*c) + before_radix_value * 10.0f;
                }
                else
                {
                    after_radix_value = ctoi(*c) + after_radix_value * 10.0f;
                    ++num_digits_after_radix;
                }
            }

            if (str_end)
            {
                *str_end = const_cast<char8*>(str);
            }            
            return optional<T>(sign * before_radix_value + (after_radix_value / (max(1.0f, pow(10.0f, num_digits_after_radix)))));
        }
    }

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // returns an optional instead of a basic type
    // converts a byte string to a floating point value
    REX_NO_DISCARD constexpr optional<float64> atof(const char8* str)
    {
        return internal::strtofloatingpoint<float64>(str, nullptr);
    }    

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<int32> atoi(const char8* str)
    {
        // this is the same function as strtoi, but is less flexible
        return internal::strtosigned<int32>(str, nullptr, 10);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<long> atol(const char8* str)
    {
        // this is the same function as strtol, but is less flexible
        return internal::strtosigned<long>(str, nullptr, 10);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<int64> atoll(const char8* str)
    {
        // this is the same function as strtoll, but is less flexible
        return internal::strtosigned<int64>(str, nullptr, 10);
    }

    /// RSL Comment: Not in ISO C++ Standard at time of writing (10/Jul/2022)
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<int32> strtoi(const char8* str, char8** str_end, int32 base)
    {
        return internal::strtosigned<int32>(str, str_end, base);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an integer value
    REX_NO_DISCARD constexpr optional<long> strtol(const char8* str, char8** str_end, int32 base)
    {
        return internal::strtosigned<long>(str, str_end, base);
    }
    // converts a byte string to an integer value
    // this returns an optional instead of a basic type
    REX_NO_DISCARD constexpr optional<int64> strtoll(const char8* str, char8** str_end, int32 base)
    {
        return internal::strtosigned<int64>(str, str_end, base);
    }

    /// RSL Comment: Not in ISO C++ Standard at time of writing (10/Jul/2022)
    // converts a byte string to an unsigned integer value
    REX_NO_DISCARD constexpr optional<uint32> strtoui(const char8* str, char8** str_end, int32 base)
    {
        return internal::strtounsigned<uint32>(str, str_end, base);
    }
    // converts a byte string to an unsigned integer value
    REX_NO_DISCARD constexpr optional<ulong> strtoul(const char8* str, char8** str_end, int32 base)
    {
        return internal::strtounsigned<ulong>(str, str_end, base);
    }
    // converts a byte string to an unsigned integer value
    REX_NO_DISCARD constexpr optional<uint64> strtoull(const char8* str, char8** str_end, int32 base)
    {
        return internal::strtounsigned<uint64>(str, str_end, base);
    }

    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    REX_NO_DISCARD constexpr optional<float32> strtof(const char8* str, char8** str_end)
    {
        return internal::strtofloatingpoint<float32>(str, str_end);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    REX_NO_DISCARD constexpr optional<float64> strtod(const char8* str, char8** str_end)
    {
        return internal::strtofloatingpoint<float64>(str, str_end);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to an floating point value
    REX_NO_DISCARD constexpr optional<lfloat64> strtold(const char8* str, char8** str_end)
    {
        return internal::strtofloatingpoint<lfloat64>(str, str_end);
    }

    // (cinttypes.h)

    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to intmax
    REX_NO_DISCARD constexpr optional<intmax> strtoimax(const char8* str, char8** str_end, int32 base)
    {
        return internal::strtosigned<intmax>(str, str_end, base);
    }
    /// RSL Comment: Different from ISO C++ Standard at time of writing (27/Aug/2022)
    // this returns an optional instead of a basic type
    // converts a byte string to uintmax
    REX_NO_DISCARD constexpr optional<uintmax> strtoumax(const char8* str, char8** str_end, int32 base)
    {
        return internal::strtounsigned<uintmax>(str, str_end, base);
    }

    //
    // string Manipulation (cstring.h)
    //

    // copies one string to another
    char8* strcpy(char8* dest, const char8* src);
    // copies a certain amount of characters from one string to another
    char8* strncpy(char8* dest, const char8* src, count_t count);
    // concatenates two strings
    char8* strcat(char8* dest, const char8* src);
    // concatenates a certain amount of characters of two strings
    char8* strncat(char8* dest, const char8* src, count_t count);
    // transform a string so that strcmp would produce the same result as strcoll
    //count_t strxfrm(char8* dest, const char8* src, count_t count);

    //
    // string Examination (cstring.h)
    //

    // returns the lengths of a given string
    REX_NO_DISCARD count_t strlen(const char8* str);
    // compares two strings
    REX_NO_DISCARD int32 strcmp(const char8* lhs, const char8* rhs);
    // compares a certain number of characters from two strings
    REX_NO_DISCARD int32 strncmp(const char8* lhs, const char8* rhs, count_t count);
    // compares two strings in accordance to the current locale
    //REX_NO_DISCARD int32 strcoll(const char8* lhs, const char8* rhs);
    // finds the first occurrence of a character
    REX_NO_DISCARD const char8* strchr(const char8* str, char8 ch);
    // finds the last occurrence of a character
    REX_NO_DISCARD const char8* strrchr(const char8* str, char8 ch);
    // returns the length of the maximum initial segment that consists
    // of only the characters found in another byte string
    REX_NO_DISCARD count_t strspn(const char8* dest, const char8* src);
    // returns the length of the maximum initial segment that consists
    // of only the characters not found in another byte string
    REX_NO_DISCARD count_t strcspn(const char8* dest, const char8* src);
    // finds the first location of any character from a set of separators
    REX_NO_DISCARD const char8* strpbrk(const char8* dest, const char8* breakset);
    // finds the first occurrence of a substring of characters
    REX_NO_DISCARD const char8* strstr(const char8* str, const char8* substring);
    // finds the next token in a byte string
    //REX_NO_DISCARD char8* strtok(char8* str, const char8* delim);

    //
    // Miscellaneous (cstring.h)
    //

    // returns a text version of a given error code
    //REX_NO_DISCARD const char8* strerror(int32 errnum); 
}