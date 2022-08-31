// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: iosfwd.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

#include "rex_std/internal/string/char_traits.h"

#include "rex_std/bonus/memory/typed_allocator.h"

#include "rex_std/std_alias_defines.h"
#include "rex_std/disable_std_checking.h"

#include <iosfwd>

namespace rsl
{
    class allocator;

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ios, CharT, Traits);
    
    template <typename State>
    REX_STD_TEMPLATED_CLASS_ALIAS(fpos, State);
    
    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_streambuf, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_istream, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ostream, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_iostream, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ifstream, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ofstream, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_fstream, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_stringbuf, CharT, Traits, Allocator);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_istringstream, CharT, Traits, Allocator);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ostringstream, CharT, Traits, Allocator);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_stringstream, CharT, Traits, Allocator);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_syncbuf, CharT, Traits, Allocator);

    template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_osyncstream, CharT, Traits, Allocator);

#ifdef REX_ENABLE_WITH_CPP20
    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_spanbuf, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ispanstream, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_ospanstream, CharT, Traits);

    template <typename CharT, typename Traits = char_traits<CharT>>
    REX_STD_TEMPLATED_CLASS_ALIAS(basic_spanstream, CharT, Traits);
#endif // REX_ENABLE_WITH_CPP20

    //template <typename T>
    //class char_traits;

    //template<>
    //class char_traits<char8>;
    //template<>
    //class char_traits<tchar>;
    //template<>
    //class char_traits<char16_t>;
    //template<>
    //class char_traits<char32_t>;

    //class allocator;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_ios;

    //template <typename State>
    //class fpos;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_streambuf;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_ostream;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_istream;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_iostream;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_filebuf;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_ifstream;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_ofstream;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_fstream;

    //template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<T>>
    //class basic_stringbuf;

    //template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<T>>
    //class basic_istringstream;

    //template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<T>>
    //class basic_ostringstream;

    //template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<T>>
    //class basic_stringstream;

    //template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<T>>
    //class basic_syncbuf;

    //template <typename CharT, typename Traits = char_traits<CharT>, typename Allocator = typed_allocator<T>>
    //class basic_osyncstream;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_spanbuf;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_ispanstream;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_ospanstream;

    //template <typename CharT, typename Traits = char_traits<CharT>>
    //class basic_spanstream;
}

#include "rex_std/enable_std_checking.h"
