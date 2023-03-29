// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: atomic_store.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std/bonus/atomic/atomic_xor_fetch.h"
#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"
#include "rex_std/bonus/atomic/atomic_memory_order.h"
#include "rex_std/bonus/atomic/atomic_casts.h"
#include "rex_std/bonus/atomic/atomic_compiler_barrier.h"
#include "rex_std/bonus/atomic/atomic_exchange.h"
#include <intrin.h>

namespace rsl
{
  inline namespace v1
  {
#if defined(REX_COMPILER_MSVC)
    template <typename T>
    void atomic_store_msvc(T* obj, T valToStore)
    {
      atomic_t<T> atom_value_to_store = valToStore;
      volatile atomic_t<T>* volatile_obj = rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>(obj);

      if constexpr (sizeof(T) == 1)
      {
#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store8(volatile_obj, atom_value_to_store);

#else
        (*rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>((obj))) = atom_value_to_store;
#endif
      }
      else if constexpr (sizeof(T) == 2)
      {
#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store16(volatile_obj, atom_value_to_store);
#else
        (*rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>((obj))) = atom_value_to_store;
#endif
      }
      else if constexpr (sizeof(T) == 4)
      {
#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store32(rsl::internal::atomic_volatile_integral_cast<int>(volatile_obj), atom_value_to_store);
#else
        (*rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>((obj))) = atom_value_to_store;
#endif
      }
      else if constexpr (sizeof(T) == 8)
      {
#if defined(REX_COMPILER_MSVC) && (REX_COMPILER_VERSION >= 1920) // >= VS2019
        __iso_volatile_store64(volatile_obj, atom_value_to_store);
#else
        (*rsl::internal::atomic_volatile_integral_cast<atomic_t<T>>((obj))) = atom_value_to_store;
#endif
      }
      else
      {
        static_assert(rsl::internal::always_false<T>, "Invalid type used for atomic fetch or");
        0;
      }
    }
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
    template <typename T>
    atomic_t<T> atomic_store_clang(T* obj, T valToStore, rsl::memory_order order)
    {
      // GCC Documentation says:
      // These built-in functions perform the operation suggested by the name, and the value that had previously been in *obj. 
      // Operations on pointer arguments are performed as if the operands were of the uintptr_t type. 
      // That is, they are not scaled by the size of the type to which the pointer points.
      // { tmp = *obj; *obj op= val; tmp; }
      // Therefore we save their value to a temporary of type uintptr first and perform the operation on that
      rsl::uintptr tmp = *obj;

      switch (order)
      {
      case rsl::v1::memory_order::relaxed: __atomic_store(obj, valToStore, __ATOMIC_RELAXED);
      case rsl::v1::memory_order::consume: __atomic_store(obj, valToStore, __ATOMIC_CONSUME);
      case rsl::v1::memory_order::acquire: __atomic_store(obj, valToStore, __ATOMIC_ACQUIRE);
      case rsl::v1::memory_order::release: __atomic_store(obj, valToStore, __ATOMIC_RELEASE);
      case rsl::v1::memory_order::acq_rel: __atomic_store(obj, valToStore, __ATOMIC_ACQ_REL);
      case rsl::v1::memory_order::seq_cst: __atomic_store(obj, valToStore, __ATOMIC_SEQ_CST);
      default:
        REX_ASSERT("Invalid memory order for operation");
        break;
      }
    }
#endif

    // uint8
    void atomic_store_relaxed(uint8* obj, uint8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::relaxed);
#endif
    }
    void atomic_store_acquire(uint8* obj, uint8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acquire);
#endif
    }
    void atomic_store_release(uint8* obj, uint8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::compiler_barrier();
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::release);
#endif
    }
    void atomic_store_acq_rel(uint8* obj, uint8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acq_rel);
#endif
    }
    void atomic_store_seq_cst(uint8* obj, uint8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::atomic_exchange_seq_cst(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::seq_cst);
#endif
    }

    // int8
    void atomic_store_relaxed(int8* obj, int8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::relaxed);
#endif
    }
    void atomic_store_acquire(int8* obj, int8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acquire);
#endif
    }
    void atomic_store_release(int8* obj, int8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::compiler_barrier();
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::release);
#endif
    }
    void atomic_store_acq_rel(int8* obj, int8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acq_rel);
#endif
    }
    void atomic_store_seq_cst(int8* obj, int8 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::atomic_exchange_seq_cst(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::seq_cst);
#endif
    }

    // uint16
    void atomic_store_relaxed(uint16* obj, uint16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::relaxed);
#endif
    }
    void atomic_store_acquire(uint16* obj, uint16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acquire);
#endif
    }
    void atomic_store_release(uint16* obj, uint16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::compiler_barrier();
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::release);
#endif
    }
    void atomic_store_acq_rel(uint16* obj, uint16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acq_rel);
#endif
    }
    void atomic_store_seq_cst(uint16* obj, uint16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::atomic_exchange_seq_cst(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::seq_cst);
#endif
    }

    // int16
    void atomic_store_relaxed(int16* obj, int16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::relaxed);
#endif
    }
    void atomic_store_acquire(int16* obj, int16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acquire);
#endif
    }
    void atomic_store_release(int16* obj, int16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::compiler_barrier();
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::release);
#endif
    }
    void atomic_store_acq_rel(int16* obj, int16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acq_rel);
#endif
    }
    void atomic_store_seq_cst(int16* obj, int16 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::atomic_exchange_seq_cst(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::seq_cst);
#endif
    }

    // uint32
    void atomic_store_relaxed(uint32* obj, uint32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::relaxed);
#endif
    }
    void atomic_store_acquire(uint32* obj, uint32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acquire);
#endif
    }
    void atomic_store_release(uint32* obj, uint32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::compiler_barrier();
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::release);
#endif
    }
    void atomic_store_acq_rel(uint32* obj, uint32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acq_rel);
#endif
    }
    void atomic_store_seq_cst(uint32* obj, uint32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::atomic_exchange_seq_cst(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::seq_cst);
#endif
    }

    // int32
    void atomic_store_relaxed(int32* obj, int32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::relaxed);
#endif
    }
    void atomic_store_acquire(int32* obj, int32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acquire);
#endif
    }
    void atomic_store_release(int32* obj, int32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::compiler_barrier();
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::release);
#endif
    }
    void atomic_store_acq_rel(int32* obj, int32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acq_rel);
#endif
    }
    void atomic_store_seq_cst(int32* obj, int32 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::atomic_exchange_seq_cst(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::seq_cst);
#endif
    }

    // uint64
    void atomic_store_relaxed(uint64* obj, uint64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::relaxed);
#endif
    }
    void atomic_store_acquire(uint64* obj, uint64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acquire);
#endif
    }
    void atomic_store_release(uint64* obj, uint64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::compiler_barrier();
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::release);
#endif
    }
    void atomic_store_acq_rel(uint64* obj, uint64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acq_rel);
#endif
    }
    void atomic_store_seq_cst(uint64* obj, uint64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::atomic_exchange_seq_cst(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::seq_cst);
#endif
    }

    // int64
    void atomic_store_relaxed(int64* obj, int64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::relaxed);
#endif
    }
    void atomic_store_acquire(int64* obj, int64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acquire);
#endif
    }
    void atomic_store_release(int64* obj, int64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::compiler_barrier();
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::release);
#endif
    }
    void atomic_store_acq_rel(int64* obj, int64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      atomic_store_msvc(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::acq_rel);
#endif
    }
    void atomic_store_seq_cst(int64* obj, int64 valToStore)
    {
#if defined(REX_COMPILER_MSVC)
      rsl::atomic_exchange_seq_cst(obj, valToStore);
#elif defined(REX_COMPILER_GCC) || defined(REX_COMPILER_CLANG)
      atomic_store_clang(obj, valToStore, rsl::memory_order::seq_cst);
#endif
    }
  }
}