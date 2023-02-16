// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: aligned_storage.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/memory/byte.h"
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/utility/forward.h"

#include <new> // needed for placement new

namespace rsl
{
  inline namespace v1
  {
    /// RSL Comment: Different from ISO C++ Standard at time of writing (26/Aug/2022)
    template <size_t Size, size_t Alignment>
    class aligned_storage
    {
    public:
      constexpr aligned_storage()
          : m_buff()
      {
      }
      constexpr aligned_storage(const aligned_storage& other) // NOLINT(cppcoreguidelines-pro-type-member-init)
      {
        memcpy(m_buff, other.m_buff, Size);
      }
      constexpr aligned_storage(aligned_storage&& other) // NOLINT(cppcoreguidelines-pro-type-member-init)
      {
        memcpy(m_buff, other.m_buff, Size);
      }

      ~aligned_storage() = default;

      constexpr aligned_storage& operator=(const aligned_storage& other) // NOLINT(bugprone-unhandled-self-assignment)
      {
        REX_ASSERT_X(this != addressof(other), "Can't copy to yourself");
        memcpy(m_buff, other.m_buff, Size);
        return *this;
      }
      constexpr aligned_storage& operator=(aligned_storage&& other)
      {
        REX_ASSERT_X(this != addressof(other), "Can't move to yourself");
        memcpy(m_buff, other.m_buff, Size);
        return *this;
      }

      template <typename T, typename... Args>
      constexpr void set(Args&&... args)
      {
        static_assert(sizeof(T) <= Size, "trying to set to aligned_storage that's too big");
        new(static_cast<void*>(m_buff)) T(rsl::forward<Args>(args)...);
      }
      template <typename T>
      constexpr void set(const T* newVal)
      {
        static_assert(sizeof(T) <= Size, "trying to set to aligned_storage that's too big");
        rsl::memcpy(m_buff, newVal, Size);
      }
      template <typename T>
      constexpr const T* get() const
      {
        return reinterpret_cast<const T*>(m_buff); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }
      template <typename T>
      constexpr T* get()
      {
        return reinterpret_cast<T*>(m_buff); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
      }

    private:
      alignas(Alignment) rsl::byte m_buff[Size] = {}; // NOLINT(modernize-avoid-c-arrays)
    };

    template <typename T, typename U = T>
    using aligned_storage_t = aligned_storage<sizeof(T), alignof(U)>;

  } // namespace v1
} // namespace rsl
