// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: strong_type.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#define REX_CREATE_STRONG_TYPE(Type, UnderlyingType)                                                                                                                                                                                                     \
                                                                                                                                                                                                                                                         \
  class Type                                                                                                                                                                                                                                             \
  {                                                                                                                                                                                                                                                      \
  public:                                                                                                                                                                                                                                                \
    using underlying_type = UnderlyingType;                                                                                                                                                                                                              \
                                                                                                                                                                                                                                                         \
    constexpr explicit Type(underlying_type val)                                                                                                                                                                                                         \
        : m_value(val)                                                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
    }                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                         \
    constexpr underlying_type& get()                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                    \
      return m_value;                                                                                                                                                                                                                                    \
    }                                                                                                                                                                                                                                                    \
    constexpr const underlying_type& get() const                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                                    \
      return m_value;                                                                                                                                                                                                                                    \
    }                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                         \
    constexpr bool operator==(const Type& other) const                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      return m_value == other.m_value;                                                                                                                                                                                                                   \
    }                                                                                                                                                                                                                                                    \
    constexpr bool operator!=(const Type& other) const                                                                                                                                                                                                   \
    {                                                                                                                                                                                                                                                    \
      return m_value != other.m_value;                                                                                                                                                                                                                   \
    }                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                         \
  private:                                                                                                                                                                                                                                               \
    underlying_type m_value;                                                                                                                                                                                                                             \
  };

namespace rsl
{
  inline namespace v1
  {
    ::internal
    {
      template <typename T>
      struct underlying_type
      {
        using type = typename T::underlying_type;
      };

      template <typename T>
      using underlying_type_t = typename underlying_type<T>::type;

      template <typename T>
      using literal_type = rsl::conditional_t<rsl::IsIntegral<T>, unsigned long long, long double>;
    }

#define CREATE_LITERAL_FOR_STRONG_TYPE(type, lit_suffix)                                                                                                                                                                                                 \
  constexpr type operator"" _##lit_suffix(rsl::internal::literal_type<rsl::internal::underlying_type_t<type>> value)                                                                                                                                     \
  {                                                                                                                                                                                                                                                      \
    return type(static_cast<rsl::internal::underlying_type_t<type>>(value));                                                                                                                                                                             \
  }
