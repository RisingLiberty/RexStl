

#ifndef REX_ATOMIC_INTERNAL_CASTS_H
#define REX_ATOMIC_INTERNAL_CASTS_H

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/internal/memory/addressof.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/string.h"

namespace rsl
{

  inline namespace v1
  {

    namespace internal
    {

      template <typename T>
      REX_FORCE_INLINE volatile T* atomic_volatile_cast(T* ptr)
      {
        static_assert(!rsl::is_volatile<volatile T*>::value, "rsl::atomic<T> : pointer must not be volatile, the pointed to type must be volatile!");
        static_assert(rsl::is_volatile<volatile T>::value, "rsl::atomic<T> : the pointed to type must be volatile!");

        return reinterpret_cast<volatile T*>(ptr);
      }

      /**
       * NOTE:
       *
       * Some compiler intrinsics do not operate on pointer types thus
       * doing atomic operations on pointers must be casted to the suitable
       * sized unsigned integral type.
       *
       * Some compiler intrinsics aren't generics and thus structs must also
       * be casted to the appropriate sized unsigned integral type.
       *
       * Atomic operations on an int* might have to be casted to a uint64 on
       * a platform with 8-byte pointers as an example.
       *
       * Also doing an atomic operation on a struct, we must ensure that we observe
       * the whole struct as one atomic unit with no shearing between the members.
       * A load of a struct with two uint32 members must be one uint64 load,
       * not two separate uint32 loads, thus casted to the suitable sized
       * unsigned integral type.
       */
      template <typename Integral, typename T>
      REX_FORCE_INLINE volatile Integral* atomic_volatile_integral_cast(T* ptr)
      {
        static_assert(!rsl::is_volatile<volatile Integral*>::value, "rsl::atomic<T> : pointer must not be volatile, the pointed to type must be volatile!");
        static_assert(rsl::is_volatile<volatile Integral>::value, "rsl::atomic<T> : the pointed to type must be volatile!");
        static_assert(rsl::is_integral<Integral>::value, "rsl::atomic<T> : Integral cast must cast to an Integral type!");
        static_assert(sizeof(Integral) == sizeof(T), "rsl::atomic<T> : Integral and T must be same size for casting!");

        return reinterpret_cast<volatile Integral*>(ptr);
      }

      template <typename Integral, typename T>
      REX_FORCE_INLINE Integral* atomic_integral_cast(T* ptr)
      {
        static_assert(rsl::is_integral<Integral>::value, "rsl::atomic<T> : Integral cast must cast to an Integral type!");
        static_assert(sizeof(Integral) == sizeof(T), "rsl::atomic<T> : Integral and T must be same size for casting!");

        return reinterpret_cast<Integral*>(ptr);
      }

      /**
       * NOTE:
       *
       * These casts are meant to be used with unions or structs of larger types that must be casted
       * down to the smaller integral types. Like with 128-bit atomics and msvc intrinsics.
       *
       * struct Foo128 { __int64 array[2]; }; can be casted to a __int64*
       * since a pointer to Foo128 is a pointer to the first member.
       */
      template <typename ToType, typename FromType>
      REX_FORCE_INLINE volatile ToType* atomic_volatile_type_cast(FromType* ptr)
      {
        static_assert(!rsl::is_volatile<volatile ToType*>::value, "rsl::atomic<T> : pointer must not be volatile, the pointed to type must be volatile!");
        static_assert(rsl::is_volatile<volatile ToType>::value, "rsl::atomic<T> : the pointed to type must be volatile!");

        return reinterpret_cast<volatile ToType*>(ptr);
      }

      template <typename ToType, typename FromType>
      REX_FORCE_INLINE ToType* atomic_type_cast(FromType* ptr)
      {
        return reinterpret_cast<ToType*>(ptr);
      }

      /**
       * NOTE:
       *
       * This is a compiler guaranteed safe type punning.
       * This is useful when dealing with user defined structs.
       * struct Test { uint32; unint32_t; };
       *
       * Example:
       * uint64 atomicLoad = *((volatile uint64*)&Test);
       * Test load = atomic_type_pun_cast<Test, uint64>(atomicLoad);
       *
       * uint64 comparand = atomic_type_pun_cast<uint64, Test>(Test);
       * cmpxchg(&Test, comparand, desired);
       *
       * This can be implemented in many different ways depending on the compiler such
       * as thru a union, memcpy, reinterpret_cast<Test&>(atomicLoad), etc.
       */
      template <typename Pun, typename T, rsl::enable_if_t<!rsl::is_same_v<Pun, T>, int> = 0>
      REX_FORCE_INLINE Pun atomic_type_pun_cast(const T& fromType)
      {
        static_assert(sizeof(Pun) == sizeof(T), "rsl::atomic<T> : Pun and T must be the same size for type punning!");

        /**
         * aligned_storage ensures we can TypePun objects that aren't trivially default constructible
         * but still trivially copyable.
         */
        rsl::aligned_storage<sizeof(Pun), alignof(Pun)> ret;
        memcpy(ret.template get<Pun>(), rsl::addressof(fromType), sizeof(Pun));
        return reinterpret_cast<Pun&>(ret);
      }

      template <typename Pun, typename T, rsl::enable_if_t<rsl::is_same_v<Pun, T>, int> = 0>
      REX_FORCE_INLINE Pun atomic_type_pun_cast(const T& fromType)
      {
        return fromType;
      }

      template <typename T>
      REX_FORCE_INLINE T atomic_negate_operand(T val)
      {
        static_assert(rsl::is_integral<T>::value, "rsl::atomic<T> : Integral Negation must be an Integral type!");
        static_assert(!rsl::is_volatile<T>::value, "rsl::atomic<T> : T must not be volatile!");

        return static_cast<T>(0U - static_cast<rsl::make_unsigned_t<T>>(val));
      }

      REX_FORCE_INLINE ptrdiff_t atomic_negate_operand(ptrdiff_t val)
      {
        return -val;
      }

    } // namespace internal

  } // namespace v1

} // namespace rsl

/**
 *  NOTE:
 *
 *  These macros are meant to prevent inclusion hell.
 *  Also so that it fits with the style of the rest of the atomic macro implementation.
 */
#define REX_ATOMIC_VOLATILE_CAST(ptr) rsl::internal::atomic_volatile_cast((ptr))

#define REX_ATOMIC_VOLATILE_INTEGRAL_CAST(IntegralType, ptr) rsl::internal::atomic_volatile_integral_cast<IntegralType>((ptr))

#define REX_ATOMIC_INTEGRAL_CAST(IntegralType, ptr) rsl::internal::atomic_integral_cast<IntegralType>((ptr))

#define REX_ATOMIC_VOLATILE_TYPE_CAST(ToType, ptr) rsl::internal::atomic_volatile_type_cast<ToType>((ptr))

#define REX_ATOMIC_TYPE_CAST(ToType, ptr) rsl::internal::atomic_type_cast<ToType>((ptr))

#define REX_ATOMIC_TYPE_PUN_CAST(PunType, fromType) rsl::internal::atomic_type_pun_cast<PunType>((fromType))

#define REX_ATOMIC_NEGATE_OPERAND(val) rsl::internal::atomic_negate_operand((val))

#endif /* REX_ATOMIC_INTERNAL_CASTS_H */
