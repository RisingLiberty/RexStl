// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stdio.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/disable_std_checking.h"
#include "rex_std/std_alias_defines.h"

#include <cstdio>

namespace rsl
{
  inline namespace v1
  {

    RSL_CLASS_ALIAS(FILE);
    RSL_CLASS_ALIAS(fpos_t);
    RSL_CLASS_ALIAS(size_t);

    RSL_FUNC_ALIAS(fopen);
    RSL_FUNC_ALIAS(freopen);
    RSL_FUNC_ALIAS(fclose);
    RSL_FUNC_ALIAS(fflush);
    RSL_FUNC_ALIAS(setbuf);
    RSL_FUNC_ALIAS(setvbuf);
    RSL_FUNC_ALIAS(fread);
    RSL_FUNC_ALIAS(fwrite);
    RSL_FUNC_ALIAS(fgetc);
    RSL_FUNC_ALIAS(fgets);
    RSL_FUNC_ALIAS(fputc);
    RSL_FUNC_ALIAS(putc);
    RSL_FUNC_ALIAS(fputs);
    RSL_FUNC_ALIAS(getchar);
    RSL_FUNC_ALIAS(putchar);
    RSL_FUNC_ALIAS(puts);
    RSL_FUNC_ALIAS(ungetc);
    RSL_FUNC_ALIAS(scanf);
    RSL_FUNC_ALIAS(fscanf);
    RSL_FUNC_ALIAS(sscanf);
    RSL_FUNC_ALIAS(vscanf);
    RSL_FUNC_ALIAS(vfscanf);
    RSL_FUNC_ALIAS(vsscanf);
    RSL_FUNC_ALIAS(printf);
    RSL_FUNC_ALIAS(fprintf);
    RSL_FUNC_ALIAS(sprintf);
    RSL_FUNC_ALIAS(snprintf);
    RSL_FUNC_ALIAS(vprintf);
    RSL_FUNC_ALIAS(vfprintf);
    RSL_FUNC_ALIAS(vsprintf);
    RSL_FUNC_ALIAS(vsprintf);
    RSL_FUNC_ALIAS(vsnprintf);
    RSL_FUNC_ALIAS(ftell);
    RSL_FUNC_ALIAS(fgetpos);
    RSL_FUNC_ALIAS(fseek);
    RSL_FUNC_ALIAS(fsetpos);
    RSL_FUNC_ALIAS(rewind);
    RSL_FUNC_ALIAS(clearerr);
    RSL_FUNC_ALIAS(feof);
    RSL_FUNC_ALIAS(ferror);
    RSL_FUNC_ALIAS(perror);
    RSL_FUNC_ALIAS(remove);
    RSL_FUNC_ALIAS(rename);
    RSL_FUNC_ALIAS(tmpfile);
    RSL_FUNC_ALIAS(tmpnam);

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
