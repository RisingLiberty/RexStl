// Copyright 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef CRC32C_CRC32C_SSE42_CHECK_H_
#define CRC32C_CRC32C_SSE42_CHECK_H_

// X86-specific code checking the availability of SSE4.2 instructions.

#include "rex_std/bonus/functional/crc/crc32c.h"

#include <cstddef>
#include <cstdint>

#if HAVE_SSE42 && (defined(_M_X64) || defined(__x86_64__))

  // If the compiler supports SSE4.2, it definitely supports X86.

  #if defined(_MSC_VER)
    #include <intrin.h>

namespace rsl
{
  inline namespace v1
  {
    namespace crc32c
    {

#ifdef CRC32_SSE42_RUNTIME_CHECK
      inline bool CanUseSse42()
      {
        int cpu_info[4];
        __cpuid(cpu_info, 1);
        return (cpu_info[2] & (1 << 20)) != 0;
      }
#else
      // Intel introduced Sse support in 2008, AMD introduced it in 2011
      // https://support.schrodinger.com/s/article/243079?#:~:text=2.-,SSE4.,)%20%2F%202011%20(AMD).
      // We can safely assume all target hardware supports it
      constexpr bool CanUseSse42()
      {
        return true;
      }
#endif

    } // namespace crc32c
  }   // namespace v1
} // namespace rsl
  #else // !defined(_MSC_VER)
    #include <cpuid.h>
namespace rsl
{
  inline namespace v1
  {

    namespace crc32c
    {

      inline bool CanUseSse42()
      {
        unsigned int eax, ebx, ecx, edx;
        return __get_cpuid(1, &eax, &ebx, &ecx, &edx) && ((ecx & (1 << 20)) != 0);
      }

    } // namespace crc32c
  }   // namespace v1
} // namespace rsl
  #endif // defined(_MSC_VER)

#endif // HAVE_SSE42 && (defined(_M_X64) || defined(__x86_64__))

#endif // CRC32C_CRC32C_SSE42_CHECK_H_
