// Copyright 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef CRC32C_CRC32C_SSE42_H_
#define CRC32C_CRC32C_SSE42_H_

// X86-specific code.

#include "rex_std/bonus/functional/crc/crc32c_config.h"
#include "rex_std/bonus/functional/crc/crc32c_constants.h"

#include <cstddef>
#include <cstdint>

// The hardware-accelerated implementation is only enabled for 64-bit builds,
// because a straightforward 32-bit implementation actually runs slower than the
// portable version. Most X86 machines are 64-bit nowadays, so it doesn't make
// much sense to spend time building an optimized hardware-accelerated
// implementation.
#if HAVE_SSE42 && (defined(_M_X64) || defined(__x86_64__))

namespace rsl
{
  inline namespace v1
  {
    namespace crc32c
    {
      // SSE4.2-accelerated implementation in crc32c_sse42.cc
      constexpr uint32_t ExtendSse42(uint32_t crc, const uint8_t* data, size_t size)
      {
        const uint8_t* p = data;
        const uint8_t* e = data + size;
        uint32_t l = crc ^ kCRC32Xor;

#define STEP1                                                                                                                                                                                                                                          \
    do                                                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      l = _mm_crc32_u8(l, *p++);                                                                                                                                                                                                                         \
    } while(0)

#define STEP4(crc)                                                                                                                                                                                                                                     \
    do                                                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      crc = _mm_crc32_u32(crc, ReadUint32LE(p));                                                                                                                                                                                                         \
      p += 4;                                                                                                                                                                                                                                            \
    } while(0)

#define STEP8(crc, data)                                                                                                                                                                                                                               \
    do                                                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      crc = _mm_crc32_u64(crc, ReadUint64LE(data));                                                                                                                                                                                                      \
      data += 8;                                                                                                                                                                                                                                         \
    } while(0)

#define STEP8BY3(crc0, crc1, crc2, p0, p1, p2)                                                                                                                                                                                                         \
    do                                                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      STEP8(crc0, p0);                                                                                                                                                                                                                                   \
      STEP8(crc1, p1);                                                                                                                                                                                                                                   \
      STEP8(crc2, p2);                                                                                                                                                                                                                                   \
    } while(0)

#define STEP8X3(crc0, crc1, crc2, bs)                                                                                                                                                                                                                  \
    do                                                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      crc0 = _mm_crc32_u64(crc0, ReadUint64LE(p));                                                                                                                                                                                                       \
      crc1 = _mm_crc32_u64(crc1, ReadUint64LE(p + bs));                                                                                                                                                                                                  \
      crc2 = _mm_crc32_u64(crc2, ReadUint64LE(p + 2 * bs));                                                                                                                                                                                              \
      p += 8;                                                                                                                                                                                                                                            \
    } while(0)

#define SKIP_BLOCK(crc, tab)                                                                                                                                                                                                                           \
    do                                                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      crc = tab[0][crc & 0xf] ^ tab[1][(crc >> 4) & 0xf] ^ tab[2][(crc >> 8) & 0xf] ^ tab[3][(crc >> 12) & 0xf] ^ tab[4][(crc >> 16) & 0xf] ^ tab[5][(crc >> 20) & 0xf] ^ tab[6][(crc >> 24) & 0xf] ^ tab[7][(crc >> 28) & 0xf];                         \
    } while(0)

        // Point x at first 8-byte aligned byte in the buffer. This might be past the
        // end of the buffer.
        const uint8_t* x = RoundUp<8>(p);
        if (x <= e)
        {
          // Process bytes p is 8-byte aligned.
          while (p != x)
          {
            STEP1;
          }
        }

        // Process the data in predetermined block sizes with tables for quickly
        // combining the checksum. Experimentally it's better to use larger block
        // sizes where possible so use a hierarchy of decreasing block sizes.
        uint64_t l64 = l;
        while ((e - p) >= kGroups * kBlock0Size)
        {
          uint64_t l641 = 0;
          uint64_t l642 = 0;
          for (int i = 0; i < kBlock0Size; i += 8 * 8)
          {
            // Prefetch ahead to hide latency.
            RequestPrefetch(p + kPrefetchHorizon);
            RequestPrefetch(p + kBlock0Size + kPrefetchHorizon);
            RequestPrefetch(p + 2 * kBlock0Size + kPrefetchHorizon);

            // Process 64 bytes at a time.
            STEP8X3(l64, l641, l642, kBlock0Size);
            STEP8X3(l64, l641, l642, kBlock0Size);
            STEP8X3(l64, l641, l642, kBlock0Size);
            STEP8X3(l64, l641, l642, kBlock0Size);
            STEP8X3(l64, l641, l642, kBlock0Size);
            STEP8X3(l64, l641, l642, kBlock0Size);
            STEP8X3(l64, l641, l642, kBlock0Size);
            STEP8X3(l64, l641, l642, kBlock0Size);
          }

          // Combine results.
          SKIP_BLOCK(l64, kBlock0SkipTable);
          l64 ^= l641;
          SKIP_BLOCK(l64, kBlock0SkipTable);
          l64 ^= l642;
          p += (kGroups - 1) * kBlock0Size;
        }
        while ((e - p) >= kGroups * kBlock1Size)
        {
          uint64_t l641 = 0;
          uint64_t l642 = 0;
          for (int i = 0; i < kBlock1Size; i += 8)
          {
            STEP8X3(l64, l641, l642, kBlock1Size);
          }
          SKIP_BLOCK(l64, kBlock1SkipTable);
          l64 ^= l641;
          SKIP_BLOCK(l64, kBlock1SkipTable);
          l64 ^= l642;
          p += (kGroups - 1) * kBlock1Size;
        }
        while ((e - p) >= kGroups * kBlock2Size)
        {
          uint64_t l641 = 0;
          uint64_t l642 = 0;
          for (int i = 0; i < kBlock2Size; i += 8)
          {
            STEP8X3(l64, l641, l642, kBlock2Size);
          }
          SKIP_BLOCK(l64, kBlock2SkipTable);
          l64 ^= l641;
          SKIP_BLOCK(l64, kBlock2SkipTable);
          l64 ^= l642;
          p += (kGroups - 1) * kBlock2Size;
        }

        // Process bytes 16 at a time
        while ((e - p) >= 16)
        {
          STEP8(l64, p);
          STEP8(l64, p);
        }

        l = static_cast<uint32_t>(l64);
        // Process the last few bytes.
        while (p != e)
        {
          STEP1;
        }
#undef SKIP_BLOCK
#undef STEP8X3
#undef STEP8BY3
#undef STEP8
#undef STEP4
#undef STEP1

        return l ^ kCRC32Xor;
      }

    } // namespace crc32c
  }   // namespace v1
} // namespace rsl
#endif // HAVE_SSE42 && (defined(_M_X64) || defined(__x86_64__))

#endif // CRC32C_CRC32C_SSE42_H_
