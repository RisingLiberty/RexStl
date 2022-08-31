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

#include "rex_std/internal/config.h"

#include "rex_std/ios.h"
#include "rex_std/streambuf.h"
#include "rex_std/istream.h"
#include "rex_std/ostream.h"

#include "rex_std/disable_std_checking.h"

#include <iostream>

namespace rsl
{
    auto& cout = std::cout;
    auto& wcout = std::wcout;

    auto& cin = std::cin;
    auto& wcin = std::wcin;

    auto& cerr = std::cerr;
    auto& wcerr = std::wcerr;

    auto& clog = std::clog;
    auto& wclog = std::wclog;
}

#include "rex_std/enable_std_checking.h"