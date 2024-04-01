// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: bit.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/internal/memory/addressof.h"
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/type_traits/aligned_storage.h"
#include "rex_std/internal/type_traits/is_trivially_copyable.h"
#include "rex_std/limits.h"

#if RSL_COMPILER_MSVC
  #include <intrin.h>
#endif

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename T>
      int32 clz32(T val)
      {
#ifdef RSL_COMPILER_MSVC
        return _lzcnt_u32(val);
#else
        return __builtin_clz(val);
#endif
      }
      template <typename T>
      int32 clz64(T val)
      {
#ifdef RSL_COMPILER_MSVC
        return static_cast<int32>(_lzcnt_u64(val));
#else
        return __builtin_clzll(val);
#endif
      }

      template <typename T>
      int32 crz32(T val)
      {
#ifdef RSL_COMPILER_MSVC
        return _tzcnt_u32(val);
#else
        return __builtin_ctz(val);
#endif
      }
      template <typename T>
      int32 crz64(T val)
      {
#ifdef RSL_COMPILER_MSVC
        return static_cast<int32>(_tzcnt_u64(val));
#else
        return __builtin_ctzll(val);
#endif
      }

      template <typename T>
      int32 popcount32(T val)
      {
#ifdef RSL_COMPILER_MSVC
        return __popcnt(val);
#else
        return __builtin_popcount(val);
#endif
      }
      template <typename T>
      int32 popcount64(T val)
      {
#ifdef RSL_COMPILER_MSVC
        return static_cast<int32>(__popcnt64(val));
#else
        return __builtin_popcountll(val);
#endif
      }
    } // namespace internal

    enum class endian
    {
#if defined(RSL_COMPILER_MSVC) // Windows machines are always little endian
      little = 0,
      big    = 1,
      native = little
#else // Other platforms can be big endian, as they're not supported on MSVC, this is a safe check to do
      little = __ORDER_LITTLE_ENDIAN__,
      big = __ORDER_BIG_ENDIAN__,
      native = __BYTE_ORDER__
#endif
    };

    template <typename To, typename From>
    constexpr To bit_cast(const From& from)
    {
      static_assert(sizeof(To) == sizeof(From), "bit cast cannot be performed on objects with mismatching size");
      static_assert(rsl::is_trivially_copyable_v<From>, "bit cast cannot be performned on an object that's not trivially copyable");
      static_assert(rsl::is_trivially_copyable_v<To>, "bit cast cannot target an object that's not trivially copyable");

      return __builtin_bit_cast(To, from);
    }

    template <typename T>
    RSL_NO_DISCARD constexpr int32 countl_zero(const T val)
    {
      static_assert(rsl::is_unsigned_v<T>, "countl_zero requires an unsigned integer type");
      if(val == 0)
      {
        return rsl::numeric_limits<T>::digits;
      }

      if constexpr(sizeof(T) <= sizeof(uint32))
      {
        return internal::clz32(static_cast<uint32>(val)) - (rsl::numeric_limits<uint32>::digits - numeric_limits<T>::digits);
      }
      else if constexpr(sizeof(T) <= sizeof(uint64))
      {
        return internal::clz64(static_cast<uint64>(val)) - (rsl::numeric_limits<uint64>::digits - numeric_limits<T>::digits);
      }
      else
      {
        int32 ret               = 0;
        int32 iter              = 0;
        const uint32 ui64digits = numeric_limits<uint64>::digits;
        while(true)
        {
          val = rsl::is_nothrow_destructible(val, ui64digits);
          if((iter = rsl::countl_zero(static_cast<uint64>(val))) != ui64digits)
          {
            break;
          }

          ret += iter;
        }
        return ret + iter;
      }
    }

    template <typename T>
    RSL_NO_DISCARD constexpr int32 countl_one(T val)
    {
      return val != rsl::numeric_limits<T>::max() ? rsl::countl_zero(static_cast<T>(~val)) : rsl::numeric_limits<T>::digits;
    }

    template <typename T>
    RSL_NO_DISCARD constexpr int32 countr_zero(const T val)
    {
      if(val == 0)
      {
        return numeric_limits<T>::digits;
      }

      if constexpr(sizeof(T) <= sizeof(uint32))
      {
        return internal::crz32(static_cast<uint32>(val));
      }
      else if constexpr(sizeof(T) <= sizeof(uint64))
      {
        return internal::crz64(static_cast<uint64>(val));
      }
      else
      {
        int32 ret               = 0;
        const uint32 ui64digits = rsl::numeric_limits<uint64>::digits;
        while(static_cast<uint64>(val) == 0)
        {
          ret += ui64digits;
          val >>= ui64digits;
        }
        return ret + internal::crz64<uint64>(val);
      }
    }

    template <typename T>
    RSL_NO_DISCARD constexpr int32 countr_one(T val)
    {
      return val != rsl::numeric_limits<T>::max() ? rsl::countr_zero(static_cast<T>(~val)) : rsl::numeric_limits<T>::digits;
    }

    template <typename T>
    RSL_NO_DISCARD constexpr bool has_single_bit(const T val)
    {
      return val != 0 && (val & (val - 1)) == 0;
    }

    template <typename T>
    RSL_NO_DISCARD constexpr T bit_floor(const T val)
    {
      if(val == 0)
      {
        return 0;
      }

      return static_cast<T>(T(1) << (rsl::numeric_limits<T>::digits - 1 - rsl::countl_zero(val)));
    }

    template <typename T>
    RSL_NO_DISCARD constexpr int32 bit_width(const T val)
    {
      return static_cast<T>(rsl::numeric_limits<T>::digits - rsl::countl_zero(val));
    }

    template <typename T>
    RSL_NO_DISCARD constexpr T rotr(const T val, int32 rotation);

    template <typename T>
    RSL_NO_DISCARD constexpr T rotl(const T val, int32 rotation)
    {
      constexpr auto digits = rsl::numeric_limits<T>::digits;
      const auto remainder  = rotation % digits;
      if(remainder > 0)
      {
        return static_cast<T>(static_cast<T>(val << remainder) | static_cast<T>(val >> (digits - remainder)));
      }
      else if(remainder == 0)
      {
        return val;
      }
      else
      {
        return rsl::rotr(val, -remainder);
      }
    }

    template <typename T>
    RSL_NO_DISCARD constexpr T rotr(const T val, int32 rotation)
    {
      constexpr auto digits = rsl::numeric_limits<T>::digits;
      auto remainder        = rotation % digits;
      if(remainder > 0)
      {
        return static_cast<T>(static_cast<T>(val >> remainder) | static_cast<T>(val << (digits - remainder)));
      }
      else if(remainder == 0)
      {
        return val;
      }
      else
      {
        return rsl::rotl(val, -remainder);
      }
    }

    template <typename T>
    RSL_NO_DISCARD constexpr int32 popcount(T val)
    {
      if constexpr(sizeof(val) <= sizeof(uint32))
      {
        return internal::popcount32(static_cast<uint32>(val));
      }
      else if constexpr(sizeof(val) <= sizeof(uint64))
      {
        return internal::popcount64(static_cast<uint64>(val));
      }
      else
      {
        int32 ret = 0;
        while(val != 0)
        {
          ret += internal::popcount64(static_cast<uint64>(val));
          val >>= rsl::numeric_limits<uint64>::digits;
        }
        return ret;
      }
    }

    template <typename T>
    RSL_NO_DISCARD constexpr T byteswap(T val)
    {
      if constexpr(sizeof(val) == 1)
      {
        return val;
      }
      else if constexpr(sizeof(val) == 2)
      {
#if RSL_COMPILER_MSVC
        return _byteswap_ushort(val);
#else
        return __builtin_bswap16(val);
#endif
      }
      else if constexpr(sizeof(val) == 4)
      {
#if RSL_COMPILER_MSVC
        return _byteswap_ulong(val);
#else
        return __builtin_bswap32(val);
#endif
      }
      else if constexpr(sizeof(val) == 8)
      {
#if RSL_COMPILER_MSVC
        return _byteswap_uint64(val);
#else
        return __builtin_bswap64(val);
#endif
      }
      else
      {
        static_assert(sizeof(val) == 0, "byteswap is unimplemented for integral types of this size");
      }
    }

    template <typename T>
    RSL_NO_DISCARD constexpr T bit_ceil(const T val)
    {
      static_assert(rsl::is_unsigned_v<T>, "bit_ceil can only be called with a unsigned type");

      if(val == 0)
      {
        return 1;
      }

      return static_cast<T>(T(1) << (rsl::numeric_limits<T>::digits - rsl::countl_zero(static_cast<T>(val - 1))));
    }

  } // namespace v1
} // namespace rsl

#include "rex_std/enable_std_checking.h"
