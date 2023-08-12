// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: atomic_load.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    template <typename T>
    atomic_t<T> atomic_load(T* obj, rsl::memory_order order)
    {
      (void)order;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      if constexpr(sizeof(T) == 1)
      {
  #if(REX_COMPILER_VERSION >= 1920)
        return __iso_volatile_load8(volatile_obj);
  #else
        return (*(rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj)));
  #endif
      }
      else if constexpr(sizeof(T) == 2)
      {
  #if(REX_COMPILER_VERSION >= 1920)
        return __iso_volatile_load16(volatile_obj);
  #else
        return (*(rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj)));
  #endif
      }
      else if constexpr(sizeof(T) == 4)
      {
  #if(REX_COMPILER_VERSION >= 1920)
        return __iso_volatile_load32(rsl::internal::atomic_volatile_integral_cast<int>(volatile_obj));
  #else
        return (*(rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj)));
  #endif
      }
      else if constexpr(sizeof(T) == 8)
      {
  #if(REX_COMPILER_VERSION >= 1920)
        return __iso_volatile_load64(volatile_obj);
  #else
        return (*(rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj)));
  #endif
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic add fetch");
        return 0;
      }
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    atomic_t<T> atomic_load(T* obj, rsl::memory_order order)
    {
      switch(order)
      {
        case rsl::v1::memory_order::relaxed: return __atomic_load_n(obj, __ATOMIC_RELAXED);
        case rsl::v1::memory_order::consume: return __atomic_load_n(obj, __ATOMIC_CONSUME);
        case rsl::v1::memory_order::acquire: return __atomic_load_n(obj, __ATOMIC_ACQUIRE);
        case rsl::v1::memory_order::seq_cst: return __atomic_load_n(obj, __ATOMIC_SEQ_CST);
        default: RSL_ASSERT("Invalid memory order for atomic load"); break;
      }

      return 0;
    }
#endif
  } // namespace v1
} // namespace rsl
