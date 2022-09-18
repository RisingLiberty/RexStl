// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: iostream.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/ios.h"
#include "rex_std/streambuf.h"
#include "rex_std/istream.h"
#include "rex_std/ostream.h"

REX_RSL_BEGIN_NAMESPACE

    using iostream = basic_iostream<char8, char_traits<char8>>;
    using wiostream = basic_iostream<tchar, char_traits<tchar>>;

    extern rsl::istream cin;
    // extern rsl::wistream wcin; /// [08/Sep/2022] RSL Comment: Wide character input not supported yet

    extern rsl::ostream cout;
    // extern rsl::wostream wcout; /// [08/Sep/2022] RSL Comment: Wide character output not supported yet

    extern rsl::ostream cerr;
    // extern rsl::wostream wcerr; /// [08/Sep/2022] RSL Comment: Wide character output not supported yet

    extern rsl::ostream clog;
    // extern rsl::wostream wclog; /// [08/Sep/2022] RSL Comment: Wide character output not supported yet

REX_RSL_END_NAMESPACE
