// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_or_fetch.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/atomic_xor_fetch.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/atomic/atomic_casts.h"
#include <intrin.h>

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    template <typename T>
    atomic_t<T> atomic_or_fetch_msvc(T* obj, T valToOr)
    {
      atomic_t<T> atom_value_to_add = valToOr;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      if constexpr (sizeof(T) == 1)
      {
        return _InterlockedOr8_np(volatile_obj, atom_value_to_add) | atom_value_to_add;
      }
      else if constexpr (sizeof(T) == 2)
      {
        return _InterlockedOr16_np(volatile_obj, atom_value_to_add) | atom_value_to_add;
      }
      else if constexpr (sizeof(T) == 4)
      {
        return _InterlockedOr_np(volatile_obj, atom_value_to_add) | atom_value_to_add;
      }
      else if constexpr (sizeof(T) == 8)
      {
        return _InterlockedOr64_np(volatile_obj, atom_value_to_add) | atom_value_to_add;
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic fetch or");
        return 0;
      }
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    atomic_t<T> atomic_or_fetch_clang(T* obj, T valToOr, rsl::memory_order order)
    {
      // GCC Documentation says:
      // These built-in functions perform the operation suggested by the name, and return the value that had previously been in *ptr. 
      // Operations on pointer arguments are performed as if the operands were of the uintptr_t type. 
      // That is, they are not scaled by the size of the type to which the pointer points.
      // { tmp = *ptr; *ptr op= val; return tmp; }
      // Therefore we save their value to a temporary of type uintptr first and perform the operation on that
      rsl::uintptr tmp = *obj;

      switch (order)
      {
      case rsl::v1::memory_order::relaxed: return __atomic_or_fetch(obj, valToOr, __ATOMIC_RELAXED);
      case rsl::v1::memory_order::consume: return __atomic_or_fetch(obj, valToOr, __ATOMIC_CONSUME);
      case rsl::v1::memory_order::acquire: return __atomic_or_fetch(obj, valToOr, __ATOMIC_ACQUIRE);
      case rsl::v1::memory_order::release: return __atomic_or_fetch(obj, valToOr, __ATOMIC_RELEASE);
      case rsl::v1::memory_order::acq_rel: return __atomic_or_fetch(obj, valToOr, __ATOMIC_ACQ_REL);
      case rsl::v1::memory_order::seq_cst: return __atomic_or_fetch(obj, valToOr, __ATOMIC_SEQ_CST);
      default:
        REX_ASSERT("Invalid memory order for operation");
        break;
      }
    }
#endif

    // bool
    bool atomic_or_fetch_relaxed(bool* obj, bool valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    bool atomic_or_fetch_acquire(bool* obj, bool valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    bool atomic_or_fetch_release(bool* obj, bool valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    bool atomic_or_fetch_acq_rel(bool* obj, bool valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    bool atomic_or_fetch_seq_cst(bool* obj, bool valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // char8
    char8 atomic_or_fetch_relaxed(char8* obj, char8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    char8 atomic_or_fetch_acquire(char8* obj, char8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    char8 atomic_or_fetch_release(char8* obj, char8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    char8 atomic_or_fetch_acq_rel(char8* obj, char8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    char8 atomic_or_fetch_seq_cst(char8* obj, char8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // uint8
    uint8 atomic_or_fetch_relaxed(uint8* obj, uint8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    uint8 atomic_or_fetch_acquire(uint8* obj, uint8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    uint8 atomic_or_fetch_release(uint8* obj, uint8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    uint8 atomic_or_fetch_acq_rel(uint8* obj, uint8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    uint8 atomic_or_fetch_seq_cst(uint8* obj, uint8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // int8
    int8 atomic_or_fetch_relaxed(int8* obj, int8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    int8 atomic_or_fetch_acquire(int8* obj, int8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    int8 atomic_or_fetch_release(int8* obj, int8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    int8 atomic_or_fetch_acq_rel(int8* obj, int8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    int8 atomic_or_fetch_seq_cst(int8* obj, int8 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // uint16
    uint16 atomic_or_fetch_relaxed(uint16* obj, uint16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    uint16 atomic_or_fetch_acquire(uint16* obj, uint16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    uint16 atomic_or_fetch_release(uint16* obj, uint16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    uint16 atomic_or_fetch_acq_rel(uint16* obj, uint16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    uint16 atomic_or_fetch_seq_cst(uint16* obj, uint16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // int16
    int16 atomic_or_fetch_relaxed(int16* obj, int16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    int16 atomic_or_fetch_acquire(int16* obj, int16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    int16 atomic_or_fetch_release(int16* obj, int16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    int16 atomic_or_fetch_acq_rel(int16* obj, int16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    int16 atomic_or_fetch_seq_cst(int16* obj, int16 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // uint32
    uint32 atomic_or_fetch_relaxed(uint32* obj, uint32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    uint32 atomic_or_fetch_acquire(uint32* obj, uint32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    uint32 atomic_or_fetch_release(uint32* obj, uint32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    uint32 atomic_or_fetch_acq_rel(uint32* obj, uint32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    uint32 atomic_or_fetch_seq_cst(uint32* obj, uint32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // int32
    int32 atomic_or_fetch_relaxed(int32* obj, int32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    int32 atomic_or_fetch_acquire(int32* obj, int32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    int32 atomic_or_fetch_release(int32* obj, int32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    int32 atomic_or_fetch_acq_rel(int32* obj, int32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    int32 atomic_or_fetch_seq_cst(int32* obj, int32 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // uint64
    uint64 atomic_or_fetch_relaxed(uint64* obj, uint64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    uint64 atomic_or_fetch_acquire(uint64* obj, uint64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    uint64 atomic_or_fetch_release(uint64* obj, uint64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    uint64 atomic_or_fetch_acq_rel(uint64* obj, uint64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    uint64 atomic_or_fetch_seq_cst(uint64* obj, uint64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }

    // int64
    int64 atomic_or_fetch_relaxed(int64* obj, int64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::relaxed);
#endif
    }
    int64 atomic_or_fetch_acquire(int64* obj, int64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acquire);
#endif
    }
    int64 atomic_or_fetch_release(int64* obj, int64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::release);
#endif
    }
    int64 atomic_or_fetch_acq_rel(int64* obj, int64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::acq_rel);
#endif
    }
    int64 atomic_or_fetch_seq_cst(int64* obj, int64 valToOr)
    {
#if defined(REX_COMPILER_MSVC)
      return atomic_or_fetch_msvc(obj, valToOr);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      return atomic_or_fetch_clang(obj, valToOr, rsl::memory_order::seq_cst);
#endif
    }
  }
}