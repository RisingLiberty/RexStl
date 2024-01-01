// Copyright 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/bonus/functional/crc/crc32c_round_up.h"

#include <cstddef>
#include <cstdint>

TEST_CASE("CRC32Crsl::crc32c::RoundUpTest")
{
  uintptr_t zero = 0;

  CHECK(zero == rsl::crc32c::RoundUp<1>(zero));
  CHECK(1U == rsl::crc32c::RoundUp<1>(1U));
  CHECK(2U == rsl::crc32c::RoundUp<1>(2U));
  CHECK(3U == rsl::crc32c::RoundUp<1>(3U));
  CHECK(~static_cast<uintptr_t>(0) == rsl::crc32c::RoundUp<1>(~static_cast<uintptr_t>(0)));
  CHECK(~static_cast<uintptr_t>(1) == rsl::crc32c::RoundUp<1>(~static_cast<uintptr_t>(1)));
  CHECK(~static_cast<uintptr_t>(2) == rsl::crc32c::RoundUp<1>(~static_cast<uintptr_t>(2)));
  CHECK(~static_cast<uintptr_t>(3) == rsl::crc32c::RoundUp<1>(~static_cast<uintptr_t>(3)));

  CHECK(zero == rsl::crc32c::RoundUp<2>(zero));
  CHECK(2U == rsl::crc32c::RoundUp<2>(1U));
  CHECK(2U == rsl::crc32c::RoundUp<2>(2U));
  CHECK(4U == rsl::crc32c::RoundUp<2>(3U));
  CHECK(4U == rsl::crc32c::RoundUp<2>(4U));
  CHECK(6U == rsl::crc32c::RoundUp<2>(5U));
  CHECK(6U == rsl::crc32c::RoundUp<2>(6U));
  CHECK(8U == rsl::crc32c::RoundUp<2>(7U));
  CHECK(8U == rsl::crc32c::RoundUp<2>(8U));
  CHECK(~static_cast<uintptr_t>(1) == rsl::crc32c::RoundUp<2>(~static_cast<uintptr_t>(1)));
  CHECK(~static_cast<uintptr_t>(1) == rsl::crc32c::RoundUp<2>(~static_cast<uintptr_t>(2)));
  CHECK(~static_cast<uintptr_t>(3) == rsl::crc32c::RoundUp<2>(~static_cast<uintptr_t>(3)));
  CHECK(~static_cast<uintptr_t>(3) == rsl::crc32c::RoundUp<2>(~static_cast<uintptr_t>(4)));

  CHECK(zero == rsl::crc32c::RoundUp<4>(zero));
  CHECK(4U == rsl::crc32c::RoundUp<4>(1U));
  CHECK(4U == rsl::crc32c::RoundUp<4>(2U));
  CHECK(4U == rsl::crc32c::RoundUp<4>(3U));
  CHECK(4U == rsl::crc32c::RoundUp<4>(4U));
  CHECK(8U == rsl::crc32c::RoundUp<4>(5U));
  CHECK(8U == rsl::crc32c::RoundUp<4>(6U));
  CHECK(8U == rsl::crc32c::RoundUp<4>(7U));
  CHECK(8U == rsl::crc32c::RoundUp<4>(8U));
  CHECK(~static_cast<uintptr_t>(3) == rsl::crc32c::RoundUp<4>(~static_cast<uintptr_t>(3)));
  CHECK(~static_cast<uintptr_t>(3) == rsl::crc32c::RoundUp<4>(~static_cast<uintptr_t>(4)));
  CHECK(~static_cast<uintptr_t>(3) == rsl::crc32c::RoundUp<4>(~static_cast<uintptr_t>(5)));
  CHECK(~static_cast<uintptr_t>(3) == rsl::crc32c::RoundUp<4>(~static_cast<uintptr_t>(6)));
  CHECK(~static_cast<uintptr_t>(7) == rsl::crc32c::RoundUp<4>(~static_cast<uintptr_t>(7)));
  CHECK(~static_cast<uintptr_t>(7) == rsl::crc32c::RoundUp<4>(~static_cast<uintptr_t>(8)));
  CHECK(~static_cast<uintptr_t>(7) == rsl::crc32c::RoundUp<4>(~static_cast<uintptr_t>(9)));
}

TEST_CASE("CRC32Crsl::crc32c::RoundUpTest")
{
  uintptr_t zero = 0, three = 3, four = 4, seven = 7, eight = 8;

  const uint8_t* zero_ptr = reinterpret_cast<const uint8_t*>(zero);
  const uint8_t* three_ptr = reinterpret_cast<const uint8_t*>(three);
  const uint8_t* four_ptr = reinterpret_cast<const uint8_t*>(four);
  const uint8_t* seven_ptr = reinterpret_cast<const uint8_t*>(seven);
  const uint8_t* eight_ptr = reinterpret_cast<uint8_t*>(eight);

  CHECK(zero_ptr == rsl::crc32c::RoundUp<1>(zero_ptr));
  CHECK(zero_ptr == rsl::crc32c::RoundUp<4>(zero_ptr));
  CHECK(zero_ptr == rsl::crc32c::RoundUp<8>(zero_ptr));

  CHECK(three_ptr == rsl::crc32c::RoundUp<1>(three_ptr));
  CHECK(four_ptr == rsl::crc32c::RoundUp<4>(three_ptr));
  CHECK(eight_ptr == rsl::crc32c::RoundUp<8>(three_ptr));

  CHECK(four_ptr == rsl::crc32c::RoundUp<1>(four_ptr));
  CHECK(four_ptr == rsl::crc32c::RoundUp<4>(four_ptr));
  CHECK(eight_ptr == rsl::crc32c::RoundUp<8>(four_ptr));

  CHECK(seven_ptr == rsl::crc32c::RoundUp<1>(seven_ptr));
  CHECK(eight_ptr == rsl::crc32c::RoundUp<4>(seven_ptr));
  CHECK(eight_ptr == rsl::crc32c::RoundUp<8>(four_ptr));
}
