#pragma once

#include "rex_std/bonus/utility/always_false.h"
#include "rex_std/internal/type_traits/is_const.h"
#include "rex_std/internal/type_traits/is_copy_assignable.h"
#include "rex_std/internal/type_traits/is_copy_constructible.h"
#include "rex_std/internal/type_traits/is_move_assignable.h"
#include "rex_std/internal/type_traits/is_move_constructible.h"
#include "rex_std/internal/type_traits/is_standard_layout.h"
#include "rex_std/internal/type_traits/is_trivially_copyable.h"
#include "rex_std/internal/type_traits/is_trivially_destructible.h"
#include "rex_std/internal/type_traits/is_volatile.h"

#define REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(type)                                                                                                                                                                                                   \
  static_assert(!rsl::is_same<type, type>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");

#define REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(type) static_assert(!rsl::is_same<type, type>::value, "rsl::atomic<T> : invalid memory order for the given operation!");

#define REX_ATOMIC_STATIC_ASSERT_TYPE(type)                                                                                                                                                                                                              \
  /* User Provided T must not be cv qualified */                                                                                                                                                                                                         \
  static_assert(!rsl::is_const<type>::value, "rsl::atomic<T> : Template Typename T cannot be const!");                                                                                                                                                   \
  static_assert(!rsl::is_volatile<type>::value, "rsl::atomic<T> : Template Typename T cannot be volatile! Use the memory orders to access the underlying type for the guarantees you need.");                                                            \
  /* T must satisfy StandardLayoutType */                                                                                                                                                                                                                \
  static_assert(rsl::is_standard_layout<type>::value, "rsl::atomic<T> : Must have standard layout!");                                                                                                                                                    \
  /* T must be TriviallyCopyable but it does not have to be TriviallyConstructible */                                                                                                                                                                    \
  static_assert(rsl::is_trivially_copyable<type>::value, "rsl::atomci<T> : Template Typename T must be trivially copyable!");                                                                                                                            \
  static_assert(rsl::is_copy_constructible<type>::value, "rsl::atomic<T> : Template Typename T must be copy constructible!");                                                                                                                            \
  static_assert(rsl::is_move_constructible<type>::value, "rsl::atomic<T> : Template Typename T must be move constructible!");                                                                                                                            \
  static_assert(rsl::is_copy_assignable<type>::value, "rsl::atomic<T> : Template Typename T must be copy assignable!");                                                                                                                                  \
  static_assert(rsl::is_move_assignable<type>::value, "rsl::atomic<T> : Template Typename T must be move assignable!");                                                                                                                                  \
  static_assert(rsl::is_trivially_destructible<type>::value, "rsl::atomic<T> : Must be trivially destructible!");                                                                                                                                        \
  static_assert(rsl::internal::is_atomic_lockfree_size<type>::value, "rsl::atomic<T> : Template Typename T must be a lockfree size!");

#define REX_ATOMIC_STATIC_ASSERT_TYPE_IS_OBJECT(type) static_assert(rsl::is_object<type>::value, "rsl::atomic<T> : Template Typename T must be an object type!");

#define REX_ATOMIC_ASSERT_ALIGNED(alignment)                                                                                                                                                                                                             \
  REX_ASSERT((alignment & (alignment - 1)) == 0);                                                                                                                                                                                                        \
  REX_ASSERT((reinterpret_cast<uintptr_t>(this) & (alignment - 1)) == 0)

namespace rsl
{

  inline namespace v1
  {

    namespace internal
    {

      template <typename T>
      struct atomic_invalid_type
      {
        /**
         * class Test { int i; int j; int k; }; sizeof(Test) == 96 bits
         *
         * std::atomic allows non-primitive types to be used for the template type.
         * This causes the api to degrade to locking for types that cannot fit into the lockfree size
         * of the target platform such as std::atomic<Test> leading to performance traps.
         *
         * If this static_assert() fired, this means your template type T is larger than any atomic instruction
         * supported on the given platform.
         */

        static_assert(!rsl::internal::always_false<T>, "rsl::atomic<T> : invalid template type T!");
      };

    } // namespace internal

  } // namespace v1

} // namespace rsl
