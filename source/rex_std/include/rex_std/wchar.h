// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: wchar.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <wchar.h>

namespace rsl
{
  inline namespace v1
  {

    RSL_CLASS_ALIAS(mbstate_t);
    RSL_CLASS_ALIAS(size_t);

    RSL_FUNC_ALIAS(wcscpy);
    RSL_FUNC_ALIAS(wcsncpy);
    RSL_FUNC_ALIAS(wcscat);
    RSL_FUNC_ALIAS(wcsncat);
    RSL_FUNC_ALIAS(wcsxfrm);
    RSL_FUNC_ALIAS(wcslen);
    RSL_FUNC_ALIAS(wcscmp);
    RSL_FUNC_ALIAS(wcscoll);
    RSL_FUNC_ALIAS(wcschr);
    RSL_FUNC_ALIAS(wcsspn);
    RSL_FUNC_ALIAS(wcsspn);
    RSL_FUNC_ALIAS(wcspbrk);
    RSL_FUNC_ALIAS(wcsstr);
    RSL_FUNC_ALIAS(wcstok);
    RSL_FUNC_ALIAS(wmemcpy);
    RSL_FUNC_ALIAS(wmemmove);
    RSL_FUNC_ALIAS(wmemcmp);
    RSL_FUNC_ALIAS(wmemchr);
    RSL_FUNC_ALIAS(wmemset);
    RSL_FUNC_ALIAS(mbsinit);
    RSL_FUNC_ALIAS(btowc);
    RSL_FUNC_ALIAS(wctob);
    RSL_FUNC_ALIAS(mbrlen);
    RSL_FUNC_ALIAS(mbrtowc);
    RSL_FUNC_ALIAS(wcrtomb);
    RSL_FUNC_ALIAS(mbsrtowcs);
    RSL_FUNC_ALIAS(wcsrtombs);
    RSL_FUNC_ALIAS(fgetwc);
    RSL_FUNC_ALIAS(fgetws);
    RSL_FUNC_ALIAS(fputwc);
    RSL_FUNC_ALIAS(fputws);
    RSL_FUNC_ALIAS(getwchar);
    RSL_FUNC_ALIAS(putwchar);
    RSL_FUNC_ALIAS(ungetwc);
    RSL_FUNC_ALIAS(fwide);
    RSL_FUNC_ALIAS(wscanf);
    RSL_FUNC_ALIAS(vwscanf);
    RSL_FUNC_ALIAS(wprintf);
    RSL_FUNC_ALIAS(vwprintf);
    RSL_FUNC_ALIAS(vwprintf);
    RSL_FUNC_ALIAS(wcsftime);
    RSL_FUNC_ALIAS(wcstol);
    RSL_FUNC_ALIAS(wcstoul);
    RSL_FUNC_ALIAS(wcstof);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
