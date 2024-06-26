// Copyright 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/bonus/functional/crc/crc32c_read_le.h"

#include <cstddef>
#include <cstdint>

#include "rex_std/bonus/functional/crc/crc32c_round_up.h"

TEST_CASE("Crc32CReadLETest4Bytes")
{
  // little-endian 0x12345678
  alignas(4) uint8_t bytes[] = {0x78, 0x56, 0x34, 0x12};

  CHECK(rsl::crc32c::RoundUp<4>(bytes) == bytes);
  CHECK(static_cast<uint32_t>(0x12345678) == rsl::crc32c::ReadUint32LE(bytes));
}

TEST_CASE("Crc32CReadLETest8Bytes")
{
  // little-endian 0x123456789ABCDEF0
  alignas(8) uint8_t bytes[] = {0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12};

  CHECK(rsl::crc32c::RoundUp<8>(bytes) == bytes);
  CHECK(static_cast<uint64_t>(0x123456789ABCDEF0) == rsl::crc32c::ReadUint64LE(bytes));
}

