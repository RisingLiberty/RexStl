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

#define RSL_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(type)                                                                                                                                                                                                   \
  static_assert(!rsl::is_same<type, type>::value, "rsl::atomic<T> : volatile rsl::atomic<T> is not what you expect! Read the docs in rex_std/atomic.h! Use the memory orders to access the atomic object!");

#define RSL_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(type) static_assert(!rsl::is_same<type, type>::value, "rsl::atomic<T> : invalid memory order for the given operation!");

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
