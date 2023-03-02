// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: mutex_base.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/aligned_storage.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
#if defined(REX_PLATFORM_X64)
      inline constexpr card32 g_mutex_size      = 16;
      inline constexpr card32 g_mutex_alignment = 8;
#elif defined(REX_PLATFORM_X86)
      inline constexpr card32 g_mutex_size      = 12;
      inline constexpr card32 g_mutex_alignment = 4;
#else
  #error No platform defined
#endif

      class mutex_base
      {
      public:
        class internal;
        using native_handle_type = void*;

        mutex_base();
        ~mutex_base() = default;

        mutex_base(const mutex_base&) = delete;
        mutex_base(mutex_base&&)      = delete;

        mutex_base& operator=(const mutex_base&) = delete;
        mutex_base& operator=(mutex_base&&)      = delete;

        void lock();
        bool try_lock();
        void unlock();

        native_handle_type native_handle();

      private:
        aligned_storage<g_mutex_size, g_mutex_alignment> m_internal_storage;
        internal* m_internal;
      };
    } // namespace internal
  }   // namespace v1
} // namespace rsl