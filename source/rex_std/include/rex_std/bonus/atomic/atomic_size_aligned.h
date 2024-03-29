#pragma once

namespace rsl
{

  inline namespace v1
  {

    namespace internal
    {

#define REX_ATOMIC_SIZE_ALIGNED_STATIC_ASSERT_CMPXCHG_IMPL(funcName)                                                                                                                                                                                     \
  template <typename OrderSuccess, typename OrderFailure>                                                                                                                                                                                                \
  bool funcName(T& /*expected*/, T /*desired*/, OrderSuccess /*orderSuccess*/, OrderFailure /*orderFailure*/)                                                                                                                                            \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(T);                                                                                                                                                                                                    \
    return false;                                                                                                                                                                                                                                        \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  template <typename OrderSuccess, typename OrderFailure>                                                                                                                                                                                                \
  bool funcName(T& /*expected*/, T /*desired*/, OrderSuccess /*orderSuccess*/, OrderFailure /*orderFailure*/) volatile                                                                                                                                   \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
    return false;                                                                                                                                                                                                                                        \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  template <typename Order>                                                                                                                                                                                                                              \
  bool funcName(T& /*expected*/, T /*desired*/, Order /*order*/)                                                                                                                                                                                         \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(T);                                                                                                                                                                                                    \
    return false;                                                                                                                                                                                                                                        \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  template <typename Order>                                                                                                                                                                                                                              \
  bool funcName(T& /*expected*/, T /*desired*/, Order /*order*/) volatile                                                                                                                                                                                \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
    return false;                                                                                                                                                                                                                                        \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  bool funcName(T& /*expected*/, T /*desired*/) volatile                                                                                                                                                                                                 \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
    return false;                                                                                                                                                                                                                                        \
  }

#define REX_ATOMIC_SIZE_ALIGNED_STATIC_ASSERT_CMPXCHG_WEAK_IMPL() REX_ATOMIC_SIZE_ALIGNED_STATIC_ASSERT_CMPXCHG_IMPL(compare_exchange_weak)

#define REX_ATOMIC_SIZE_ALIGNED_STATIC_ASSERT_CMPXCHG_STRONG_IMPL() REX_ATOMIC_SIZE_ALIGNED_STATIC_ASSERT_CMPXCHG_IMPL(compare_exchange_strong)

      template <typename T>
      struct atomic_size_aligned
      {
      public: /* ctors */
        constexpr explicit atomic_size_aligned(T desired)
            : m_atomic_storage {desired}
        {
        }

        constexpr atomic_size_aligned()
            : m_atomic_storage {} /* Value-Initialize which will Zero-Initialize Trivial Constructible types */
        {
        }

        ~atomic_size_aligned() = default;

        atomic_size_aligned(const atomic_size_aligned&) = delete;

      public: /* store */
        template <typename Order>
        void store(T /*desired*/, Order /*order*/)
        {
          REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(T);
        }

        template <typename Order>
        void store(T /*desired*/, Order /*order*/) volatile
        {
          REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);
        }

        void store(T /*desired*/) volatile
        {
          REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);
        }

      public: /* load */
        template <typename Order>
        T load(Order /*order*/) const
        {
          REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(T);
        }

        template <typename Order>
        T load(Order /*order*/) const volatile
        {
          REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);
        }

        T load() const volatile
        {
          REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);
        }

      public: /* exchange */
        template <typename Order>
        T exchange(T /*desired*/, Order /*order*/)
        {
          REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(T);
        }

        template <typename Order>
        T exchange(T /*desired*/, Order /*order*/) volatile
        {
          REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);
        }

        T exchange(T /*desired*/) volatile
        {
          REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);
        }

      public: /* compare_exchange_weak */
        REX_ATOMIC_SIZE_ALIGNED_STATIC_ASSERT_CMPXCHG_WEAK_IMPL()

      public: /* compare_exchange_strong */
        REX_ATOMIC_SIZE_ALIGNED_STATIC_ASSERT_CMPXCHG_STRONG_IMPL()

      public:                               /* assignment operator */
        T operator=(T /*desired*/) volatile // NOLINT(misc-unconventional-assign-operator)
        {
          REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);
        }

        atomic_size_aligned& operator=(const atomic_size_aligned&)          = delete;
        atomic_size_aligned& operator=(const atomic_size_aligned&) volatile = delete;

      protected: /* Accessors */
        T* atomic_address() const
        {
          return rsl::addressof(m_atomic_storage);
        }

      private:
        /**
         * Some compilers such as MSVC will align 64-bit values on 32-bit machines on
         * 4-byte boundaries which can ruin the atomicity guarantees.
         *
         * Ensure everything is size aligned.
         *
         * mutable is needed in cases such as when loads are only guaranteed to be atomic
         * using a compare exchange, such as for 128-bit atomics, so we need to be able
         * to have write access to the variable as one example.
         */
        alignas(sizeof(T)) mutable T m_atomic_storage;
      };

    } // namespace internal

  } // namespace v1

} // namespace rsl
