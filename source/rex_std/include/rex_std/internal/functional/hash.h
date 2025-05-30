// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/functional/crc/crc32c.h"
#include "rex_std/bonus/functional/hash_result.h"
#include "rex_std/bonus/types.h"
#include "rex_std/bonus/utility/always_false.h"
#include "rex_std/cstring.h"
#include "rex_std/internal/stddef/nullptr.h"
#include "rex_std/internal/type_traits/is_enum.h"

namespace rsl
{
  inline namespace v1
  {

    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
    // the standard uses size_t for the hash result.
    // we use uint32 for this, but define it outside of the type
    // which makes it easy to configure should we want to change it to be 64 bit.
    namespace internal
    {
      template <typename CharType>
      constexpr hash_result hash(const CharType* key, count_t count)
      {
        count = count * sizeof(CharType);
        return static_cast<hash_result>(crc32::compute(key, count));
      }

      template <typename CharType>
      constexpr hash_result hash(const CharType* key)
      {
        count_t len = rsl::strlen(key);

        return hash(key, len);
      }

      template <typename CharType>
      constexpr hash_result hash_as_lower(const CharType* key, count_t count)
      {
        count = count * sizeof(CharType);
        return static_cast<hash_result>(crc32::compute_as_lower(key, count));
      }

      template <typename CharType>
      constexpr hash_result hash_as_lower(const CharType* key)
      {
        count_t len = rsl::strlen(key);

        return hash_as_lower(key, len);
      }

    } // namespace internal

    template <typename T>
    struct hash;

    namespace internal
    {
      template <typename T, bool IsEnum>
      struct conditional_hash
      {
        hash_result operator()(T val) const
        {
          return static_cast<hash_result>(val);
        }
      };

      template <typename T>
      struct conditional_hash<T, false>
      {
        static_assert(rsl::internal::always_false<T>, "No rsl::hash implementation for type T");

        conditional_hash()                        = delete;
        conditional_hash(const conditional_hash&) = delete;
        conditional_hash(conditional_hash&&)      = delete;
        ~conditional_hash()                       = delete;

        conditional_hash& operator=(const conditional_hash&) = delete;
        conditional_hash& operator=(conditional_hash&&)      = delete;
      };
    } // namespace internal

    template <typename T>
    struct hash : public internal::conditional_hash<T, rsl::is_enum_v<T>>
    {
    };

    template <typename T>
    struct hash<T*>
    {
      constexpr hash_result operator()(T* p) const
      {
        return static_cast<hash_result>(*reinterpret_cast<uintptr*>(&p)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }
    };

    template <>
    struct hash<bool>
    {
      constexpr hash_result operator()(bool val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<int8>
    {
      constexpr hash_result operator()(int8 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<int16>
    {
      constexpr hash_result operator()(int16 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<int32>
    {
      constexpr hash_result operator()(int32 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<int64>
    {
      constexpr hash_result operator()(int64 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<uint8>
    {
      constexpr hash_result operator()(uint8 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<uint16>
    {
      constexpr hash_result operator()(uint16 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<uint32>
    {
      constexpr hash_result operator()(uint32 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<uint64>
    {
      constexpr hash_result operator()(uint64 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<float32>
    {
      constexpr hash_result operator()(float32 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<float64>
    {
      constexpr hash_result operator()(float64 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<lfloat64>
    {
      constexpr hash_result operator()(lfloat64 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<long>
    {
      constexpr hash_result operator()(long val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<ulong>
    {
      constexpr hash_result operator()(ulong val) const
      {
        return static_cast<hash_result>(val);
      }
    };

    template <>
    struct hash<char8>
    {
      constexpr hash_result operator()(char8 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<char16>
    {
      constexpr hash_result operator()(char16 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<char32>
    {
      constexpr hash_result operator()(char32 val) const
      {
        return static_cast<hash_result>(val);
      }
    };
    template <>
    struct hash<tchar>
    {
      constexpr hash_result operator()(tchar val) const
      {
        return static_cast<hash_result>(val);
      }
    };

    template <>
    struct hash<nullptr_t>
    {
      hash_result operator()(nullptr_t) const
      {
        void* p {};
        return static_cast<hash_result>(reinterpret_cast<uintptr>(p)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }
    };

    constexpr hash_result hash_combine(uint64 seed, hash_result hash)
    {
      hash += static_cast<hash_result>(0X9E3779B9 + (seed << 6) + (seed >> 2)); // NOLINT(hicpp-signed-bitwise)
      return static_cast<hash_result>(seed ^ hash);   // NOLINT(hicpp-signed-bitwise)
    }

    template <typename T>
    constexpr rsl::hash_result comp_hash(const T& obj)
    {
      return rsl::hash<T>{}(obj);
    }

  } // namespace v1
} // namespace rsl
