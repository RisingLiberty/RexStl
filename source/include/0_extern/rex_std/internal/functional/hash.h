// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/functional/hash_result.h"
#include "rex_std/bonus/types.h"
#include "rex_std/internal/cstddef/nullptr.h"
#include "rex_std/internal/type_traits/is_enum.h"

REX_RSL_BEGIN_NAMESPACE

/// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
// the standard uses size_t for the hash result.
// we use uint32 for this, but define it outside of the type
// which makes it easy to configure should we want to change it to be 64 bit.
namespace internal
{
  constexpr hash_result hash_combine(uint64 seed, uint64 hash)
  {
    hash += 0X9E3779B9 + (seed << 6) + (seed >> 2);
    return static_cast<hash_result>(seed ^ hash);
  }

#pragma warning(push)
#pragma warning(disable : 4307)
  template <typename CharType>
  constexpr hash_result hash(const CharType* key)
  {
    uint64 p          = 31;
    const uint64 m    = (uint64)1e9 + 9;
    int64 hash_value  = 0;
    int64 p_pow       = 1;
    const CharType* c = key;
    while(*c)
    {
      hash_value = (hash_value + (*c - (uint64)'a' + 1) * p_pow) % m;
      p_pow      = (p_pow * p) % m;
      c++;
    }

    return static_cast<hash_result>(hash_value);
  }
  template <typename CharType>
  constexpr hash_result hash(const CharType* key, count_t count)
  {
    uint64 p          = 31;
    const uint64 m    = (uint64)1e9 + 9;
    int64 hash_value  = 0;
    int64 p_pow       = 1;
    const CharType* c = key;
    while(count > 0)
    {
      hash_value = (hash_value + (*c - (uint64)'a' + 1) * p_pow) % m;
      p_pow      = (p_pow * p) % m;
      c++;
      --count;
    }

    return static_cast<hash_result>(hash_value);
  }
#pragma warning(pop)
} // namespace internal

template <typename T>
struct hash;

namespace internal
{
  template <typename T, bool IsEnum>
  struct ConditionalHash
  {
    hash_result operator()(T val) const
    {
      return static_cast<hash_result>(val);
    }
  };

  template <typename T>
  struct ConditionalHash<T, false>
  {
    ConditionalHash()                       = delete;
    ConditionalHash(const ConditionalHash&) = delete;
    ConditionalHash(ConditionalHash&&)      = delete;

    ConditionalHash& operator=(const ConditionalHash&) = delete;
    ConditionalHash& operator=(ConditionalHash&&)      = delete;
  };
} // namespace internal

template <typename T>
struct hash : public internal::ConditionalHash<T, rsl::is_enum_v<T>>
{
};

template <typename T>
struct hash<T*>
{
  hash_result operator()(T* p) const
  {
    return static_cast<hash_result>(static_cast<uintptr>(p));
  }
};

template <>
struct hash<bool>
{
  hash_result operator()(bool val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<int8>
{
  hash_result operator()(int8 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<int16>
{
  hash_result operator()(int16 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<int32>
{
  hash_result operator()(int32 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<int64>
{
  hash_result operator()(int64 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<uint8>
{
  hash_result operator()(uint8 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<uint16>
{
  hash_result operator()(uint16 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<uint32>
{
  hash_result operator()(uint32 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<uint64>
{
  hash_result operator()(uint64 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<float32>
{
  hash_result operator()(float32 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<float64>
{
  hash_result operator()(float64 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<lfloat64>
{
  hash_result operator()(lfloat64 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<long>
{
  hash_result operator()(long val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<ulong>
{
  hash_result operator()(ulong val) const
  {
    return static_cast<hash_result>(val);
  }
};

template <>
struct hash<char8>
{
  hash_result operator()(char8 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<char16>
{
  hash_result operator()(char16 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<char32>
{
  hash_result operator()(char32 val) const
  {
    return static_cast<hash_result>(val);
  }
};
template <>
struct hash<tchar>
{
  hash_result operator()(tchar val) const
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
    return static_cast<hash_result>((uintptr)(p));
  }
};

REX_RSL_END_NAMESPACE
