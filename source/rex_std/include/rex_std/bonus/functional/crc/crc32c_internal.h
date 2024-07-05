// Copyright 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef CRC32C_CRC32C_INTERNAL_H_
#define CRC32C_CRC32C_INTERNAL_H_

// Internal functions that may change between releases.

#include <cstddef>
#include <cstdint>

namespace rsl
{
  inline namespace v1
  {
    namespace crc32c
    {

      // Un-accelerated implementation that works on all CPUs.
      constexpr uint32_t ExtendPortable(uint32_t crc, const uint8_t* data, size_t count);

      // CRCs are pre- and post- conditioned by xoring with all ones.
      static constexpr const uint32_t kCRC32Xor = static_cast<uint32_t>(0xffffffffU);

    } // namespace crc32c
  }   // namespace v1
} // namespace rsl

// Copyright 2008 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "rex_std/bonus/functional/crc/crc32c_prefetch.h"
#include "rex_std/bonus/functional/crc/crc32c_read_le.h"
#include "rex_std/bonus/functional/crc/crc32c_round_up.h"
#include "rex_std/bonus/functional/crc/crc32c_constants.h"

#include <cstddef>
#include <cstdint>

namespace rsl
{
  inline namespace v1
  {
    namespace crc32c
    {
      constexpr uint32_t ExtendPortable(uint32_t crc, const uint8_t* data, size_t size)
      {
        const uint8_t* p = data;
        const uint8_t* e = p + size;
        uint32_t l = crc ^ kCRC32Xor;

        // Process one byte at a time.
#define STEP1                                                                                                                                                                                                                                            \
  do                                                                                                                                                                                                                                                     \
  {                                                                                                                                                                                                                                                      \
    int c = (l & 0xff) ^ *p++;                                                                                                                                                                                                                           \
    l     = kByteExtensionTable[c] ^ (l >> 8);                                                                                                                                                                                                           \
  } while(0)

// Process one of the 4 strides of 4-byte data.
#define STEP4(s)                                                                                                                                                                                                                                         \
  do                                                                                                                                                                                                                                                     \
  {                                                                                                                                                                                                                                                      \
    crc##s = ReadUint32LE(p + s * 4) ^ kStrideExtensionTable3[crc##s & 0xff] ^ kStrideExtensionTable2[(crc##s >> 8) & 0xff] ^ kStrideExtensionTable1[(crc##s >> 16) & 0xff] ^ kStrideExtensionTable0[crc##s >> 24];                                      \
  } while(0)

// Process a 16-byte swath of 4 strides, each of which has 4 bytes of data.
#define STEP16                                                                                                                                                                                                                                           \
  do                                                                                                                                                                                                                                                     \
  {                                                                                                                                                                                                                                                      \
    STEP4(0);                                                                                                                                                                                                                                            \
    STEP4(1);                                                                                                                                                                                                                                            \
    STEP4(2);                                                                                                                                                                                                                                            \
    STEP4(3);                                                                                                                                                                                                                                            \
    p += 16;                                                                                                                                                                                                                                             \
  } while(0)

// Process 4 bytes that were already loaded into a word.
#define STEP4W(w)                                                                                                                                                                                                                                        \
  do                                                                                                                                                                                                                                                     \
  {                                                                                                                                                                                                                                                      \
    w ^= l;                                                                                                                                                                                                                                              \
    for(size_t i = 0; i < 4; ++i)                                                                                                                                                                                                                        \
    {                                                                                                                                                                                                                                                    \
      w = (w >> 8) ^ kByteExtensionTable[w & 0xff];                                                                                                                                                                                                      \
    }                                                                                                                                                                                                                                                    \
    l = w;                                                                                                                                                                                                                                               \
  } while(0)

        // Point x at first 4-byte aligned byte in the buffer. This might be past the
        // end of the buffer.
        const uint8_t* x = RoundUp<4>(p);
        if (x <= e)
        {
          // Process bytes p is 4-byte aligned.
          while (p != x)
          {
            STEP1;
          }
        }

        if ((e - p) >= 16)
        {
          // Load a 16-byte swath into the stride partial results.
          uint32_t crc0 = ReadUint32LE(p + 0 * 4) ^ l;
          uint32_t crc1 = ReadUint32LE(p + 1 * 4);
          uint32_t crc2 = ReadUint32LE(p + 2 * 4);
          uint32_t crc3 = ReadUint32LE(p + 3 * 4);
          p += 16;

          while ((e - p) > kPrefetchHorizon)
          {
            RequestPrefetch(p + kPrefetchHorizon);

            // Process 64 bytes at a time.
            STEP16;
            STEP16;
            STEP16;
            STEP16;
          }

          // Process one 16-byte swath at a time.
          while ((e - p) >= 16)
          {
            STEP16;
          }

          // Advance one word at a time as far as possible.
          while ((e - p) >= 4)
          {
            STEP4(0);
            uint32_t tmp = crc0;
            crc0 = crc1;
            crc1 = crc2;
            crc2 = crc3;
            crc3 = tmp;
            p += 4;
          }

          // Combine the 4 partial stride results.
          l = 0;
          STEP4W(crc0);
          STEP4W(crc1);
          STEP4W(crc2);
          STEP4W(crc3);
        }

        // Process the last few bytes.
        while (p != e)
        {
          STEP1;
        }
#undef STEP4W
#undef STEP16
#undef STEP4
#undef STEP1
        return l ^ kCRC32Xor;
      }

    } // namespace crc32c
  }   // namespace v1
} // namespace rsl

#endif // CRC32C_CRC32C_INTERNAL_H_
