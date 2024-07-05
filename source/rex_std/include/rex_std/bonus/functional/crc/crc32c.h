/* Copyright 2017 The CRC32C Authors. All rights reserved.
   Use of this source code is governed by a BSD-style license that can be
   found in the LICENSE file. See the AUTHORS file for names of contributors. */

#ifndef CRC32C_CRC32C_H_
#define CRC32C_CRC32C_H_

/* The API exported by the CRC32C project. */

#if defined(__cplusplus)

  #include <cstddef>
  #include <cstdint>
  #include <string>

#else /* !defined(__cplusplus) */

  #include <stddef.h>
  #include <stdint.h>

#endif /* !defined(__cplusplus) */

/* The C API. */

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

  /* Extends "crc" with the CRC32C of "count" bytes in the buffer pointed by
     "data" */
  uint32_t crc32c_extend(uint32_t crc, const uint8_t* data, size_t count);

  /* Computes the CRC32C of "count" bytes in the buffer pointed by "data". */
  uint32_t crc32c_value(const uint8_t* data, size_t count);

#ifdef __cplusplus
} /* end extern "C" */
#endif /* defined(__cplusplus) */

/* The C++ API. */

#if defined(__cplusplus)

#include "rex_std/bonus/functional/crc/crc32c_arm64.h"
#include "rex_std/bonus/functional/crc/crc32c_arm64_check.h"
#include "rex_std/bonus/functional/crc/crc32c_internal.h"
#include "rex_std/bonus/functional/crc/crc32c_sse42.h"
#include "rex_std/bonus/functional/crc/crc32c_sse42_check.h"

namespace rsl
{
  inline namespace v1
  {

    namespace crc32c
    {

      // Extends "crc" with the CRC32C of "count" bytes in the buffer pointed by
      // "data".
      constexpr uint32_t Extend(uint32_t crc, const uint8_t* data, size_t count)
      {
#if HAVE_SSE42 && (defined(_M_X64) || defined(__x86_64__))
        constexpr bool can_use_sse42 = CanUseSse42();
        if (can_use_sse42)
          return ExtendSse42(crc, data, count);
#elif HAVE_ARM64_CRC32C
        static bool can_use_arm64_crc32 = CanUseArm64Crc32();
        if (can_use_arm64_crc32)
          return ExtendArm64(crc, data, count);
#endif // HAVE_SSE42 && (defined(_M_X64) || defined(__x86_64__))

        return ExtendPortable(crc, data, count);
      }

      // Computes the CRC32C of "count" bytes in the buffer pointed by "data".
      constexpr uint32_t Crc32c(const uint8_t* data, size_t count)
      {
        return Extend(0, data, count);
      }

      // Computes the CRC32C of "count" bytes in the buffer pointed by "data".
      constexpr uint32_t Crc32c(const char* data, size_t count)
      {
        return Extend(0, (const uint8_t*)(const void*)(data), count);
      }

      // Computes the CRC32C of the string's content.
      constexpr uint32_t Crc32c(const std::string& string)
      {
        return Crc32c((const uint8_t*)(string.data()), string.size());
      }

    } // namespace crc32c

  } // namespace v1
} // namespace rsl
  #if __cplusplus > 201402L
    #if __has_include(<string_view>)
      #include <string_view>

namespace rsl
{
  inline namespace v1
  {

    namespace crc32c
    {

      // Computes the CRC32C of the bytes in the string_view.
      inline uint32_t Crc32c(const std::string_view& string_view)
      {
        return Crc32c(reinterpret_cast<const uint8_t*>(string_view.data()), string_view.size());
      }

    } // namespace crc32c

  } // namespace v1
} // namespace rsl
    #endif // __has_include(<string_view>)
  #endif   // __cplusplus > 201402L

#endif /* defined(__cplusplus) */

#endif // CRC32C_CRC32C_H_
