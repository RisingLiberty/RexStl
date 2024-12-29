// Copyright 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/bonus/functional/crc/crc32c.h"
#include "rex_std/string.h"
#include "rex_std/string_view.h"

TEST_CASE("Crc32CTest1") 
{
  // From rfc3720 section B.4.
  uint8_t buf[32];

  std::memset(buf, 0, sizeof(buf));
  CHECK(static_cast<uint32_t>(0x484ec20f) == rsl::crc32::compute(buf, sizeof(buf)));

  std::memset(buf, 0xff, sizeof(buf));
  CHECK(static_cast<uint32_t>(0xf91d4e2b) == rsl::crc32::compute(buf, sizeof(buf)));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<uint8_t>(i);
  CHECK(static_cast<uint32_t>(0x378f1b24) == rsl::crc32::compute(buf, sizeof(buf)));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<uint8_t>(31 - i);
  CHECK(static_cast<uint32_t>(0x677bc6cb) == rsl::crc32::compute(buf, sizeof(buf)));

  uint8_t data[48] = {
      0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
      0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x18, 0x28, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };
  CHECK(static_cast<uint32_t>(0xf6441fa0) == rsl::crc32::compute(data, sizeof(data)));
}


TEST_CASE("CRC32CTest2")
{
  char buf[32];

  std::memset(buf, 0, sizeof(buf));
  CHECK(static_cast<uint32_t>(0x484ec20f) == rsl::crc32::compute(buf, sizeof(buf)));

  std::memset(buf, 0xff, sizeof(buf));
  CHECK(static_cast<uint32_t>(0xf91d4e2b) == rsl::crc32::compute(buf, sizeof(buf)));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<char>(i);
  CHECK(static_cast<uint32_t>(0x378f1b24) == rsl::crc32::compute(buf, sizeof(buf)));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<char>(31 - i);
  CHECK(static_cast<uint32_t>(0x677bc6cb) == rsl::crc32::compute(buf, sizeof(buf)));
}

TEST_CASE("CRC32CTest3") 
{
  rsl::string buf;
  buf.resize(32);

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<char>(0x00);
  CHECK(static_cast<uint32_t>(0x484ec20f) == rsl::crc32::compute(buf));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = '\xff';
  CHECK(static_cast<uint32_t>(0xf91d4e2b) == rsl::crc32::compute(buf));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<char>(i);
  CHECK(static_cast<uint32_t>(0x378f1b24) == rsl::crc32::compute(buf));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<char>(31 - i);
  CHECK(static_cast<uint32_t>(0x677bc6cb) == rsl::crc32::compute(buf));
}

TEST_CASE("CRC32CTest4")
{
  uint8_t buf[32];
  rsl::string_view view(reinterpret_cast<const char*>(buf), sizeof(buf));

  std::memset(buf, 0, sizeof(buf));
  CHECK(static_cast<uint32_t>(0x484ec20f) == rsl::crc32::compute(view));

  std::memset(buf, 0xff, sizeof(buf));
  CHECK(static_cast<uint32_t>(0xf91d4e2b) == rsl::crc32::compute(view));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<uint8_t>(i);
  CHECK(static_cast<uint32_t>(0x378f1b24) == rsl::crc32::compute(view));

  for (card32 i = 0; i < 32; ++i)
    buf[i] = static_cast<uint8_t>(31 - i);
  CHECK(static_cast<uint32_t>(0x677bc6cb) == rsl::crc32::compute(view));
}


