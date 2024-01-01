// Copyright 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

// ARM-specific code

#ifndef CRC32C_CRC32C_ARM_H_
#define CRC32C_CRC32C_ARM_H_

#include "rex_std/bonus/functional/crc/crc32c_config.h"

#include <cstddef>
#include <cstdint>

#if HAVE_ARM64_CRC32C

namespace rsl
{
  inline namespace v1
  {
    namespace crc32c
    {

      uint32_t ExtendArm64(uint32_t crc, const uint8_t* data, size_t count);

    } // namespace crc32c
  }   // namespace v1
} // namespace rsl
#endif // HAVE_ARM64_CRC32C

#endif // CRC32C_CRC32C_ARM_H_
