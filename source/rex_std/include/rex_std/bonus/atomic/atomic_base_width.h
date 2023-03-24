

#ifndef REX_ATOMIC_INTERNAL_BASE_WIDTH_H
#define REX_ATOMIC_INTERNAL_BASE_WIDTH_H

#pragma once

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <typename T, unsigned width = sizeof(T)>
      struct atomic_base_width;

      template <size_t bytes>
      struct atomic_fixed_width_type
      {

      };

      template <>
      struct atomic_fixed_width_type<8>
      {
#ifdef REX_COMPILER_MSVC
        using type = rsl::int8;
#elif REX_COMPILER_CLANG
        using type = rsl::uint8;
#endif
      };
      template <>
      struct atomic_fixed_width_type<16>
      {
#ifdef REX_COMPILER_MSVC
        using type = rsl::int16;
#else
        using type = rsl::uint16;
#endif
      };
      template <>
      struct atomic_fixed_width_type<32>
      {
#ifdef REX_COMPILER_MSVC
        using type = rsl::int32;
#elif REX_COMPILER_CLANG
        using type = rsl::uint32;
#endif
      };
      template <>
      struct atomic_fixed_width_type<64>
      {
#ifdef REX_COMPILER_MSVC
        using type = rsl::int64;
#elif REX_COMPILER_CLANG
        using type = rsl::uint64;
#endif
      };

      template <size_t Bits>
      using atomic_fixed_width_type_t = typename atomic_fixed_width_type<Bits>::type;

      /**
       * NOTE:
       *
       * T does not have to be trivially default constructible but it still
       * has to be a trivially copyable type for the primary atomic template.
       * Thus we must type pun into whatever storage type of the given fixed width
       * the platform designates. This ensures T does not have to be trivially constructible.
       */

      template <typename T>
      struct atomic_base_width<T, 1> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 1, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base = atomic_size_aligned<T>;

      public: /* ctors */
        constexpr atomic_base_width(T desired)
          : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public: /* store */
        using Base::store;

        void store(T desired)
        {
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_STORE_SEQ_CST_8(atomic_fixed_width_type_t<8>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_STORE_RELAXED_8(atomic_fixed_width_type_t<8>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_STORE_RELEASE_8(atomic_fixed_width_type_t<8>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_STORE_SEQ_CST_8(atomic_fixed_width_type_t<8>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired)
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          atomic_fixed_width_type_t<8> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_fixed_width_type_t<8> retVal;
          REX_ATOMIC_LOAD_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_fixed_width_type_t<8> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_fixed_width_type_t<8> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_fixed_width_type_t<8> retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<8> retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_EXCHANGE_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_fixed_width_type_t<8> retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_EXCHANGE_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<8> retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_EXCHANGE_RELEASE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_fixed_width_type_t<8> retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_EXCHANGE_ACQ_REL_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<8> retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<8> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<8>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_8(atomic_fixed_width_type_t<8>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<8>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* assignment operator */
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&) = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };



      template <typename T>
      struct atomic_base_width<T, 2> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 2, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base = atomic_size_aligned<T>;

      public: /* ctors */
        constexpr atomic_base_width(T desired)
          : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public: /* store */
        using Base::store;

        void store(T desired)
        {
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_STORE_SEQ_CST_16(atomic_fixed_width_type_t<16>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_STORE_RELAXED_16(atomic_fixed_width_type_t<16>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_STORE_RELEASE_16(atomic_fixed_width_type_t<16>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_STORE_SEQ_CST_16(atomic_fixed_width_type_t<16>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired)
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          atomic_fixed_width_type_t<16> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_fixed_width_type_t<16> retVal;
          REX_ATOMIC_LOAD_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_fixed_width_type_t<16> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_fixed_width_type_t<16> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_fixed_width_type_t<16> retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<16> retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_EXCHANGE_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_fixed_width_type_t<16> retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_EXCHANGE_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<16> retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_EXCHANGE_RELEASE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_fixed_width_type_t<16> retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_EXCHANGE_ACQ_REL_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<16> retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<16> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<16>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_16(atomic_fixed_width_type_t<16>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<16>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* assignment operator */
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&) = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };


      template <typename T>
      struct atomic_base_width<T, 4> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 4, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base = atomic_size_aligned<T>;

      public: /* ctors */
        constexpr atomic_base_width(T desired)
          : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public: /* store */
        using Base::store;

        void store(T desired)
        {
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_STORE_SEQ_CST_32(atomic_fixed_width_type_t<32>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_STORE_RELAXED_32(atomic_fixed_width_type_t<32>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_STORE_RELEASE_32(atomic_fixed_width_type_t<32>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_STORE_SEQ_CST_32(atomic_fixed_width_type_t<32>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired)
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          atomic_fixed_width_type_t<32> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_fixed_width_type_t<32> retVal;
          REX_ATOMIC_LOAD_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_fixed_width_type_t<32> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_fixed_width_type_t<32> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_fixed_width_type_t<32> retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<32> retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_EXCHANGE_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_fixed_width_type_t<32> retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_EXCHANGE_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<32> retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_EXCHANGE_RELEASE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_fixed_width_type_t<32> retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_EXCHANGE_ACQ_REL_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<32> retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<32> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<32>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_32(atomic_fixed_width_type_t<32>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<32>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* assignment operator */
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&) = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };


      template <typename T>
      struct atomic_base_width<T, 8> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 8, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base = atomic_size_aligned<T>;

      public: /* ctors */
        constexpr atomic_base_width(T desired)
          : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public: /* store */
        using Base::store;

        void store(T desired)
        {
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_STORE_SEQ_CST_64(atomic_fixed_width_type_t<64>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_STORE_RELAXED_64(atomic_fixed_width_type_t<64>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_STORE_RELEASE_64(atomic_fixed_width_type_t<64>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_STORE_SEQ_CST_64(atomic_fixed_width_type_t<64>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired)
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          atomic_fixed_width_type_t<64> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_fixed_width_type_t<64> retVal;
          REX_ATOMIC_LOAD_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_fixed_width_type_t<64> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_fixed_width_type_t<64> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_fixed_width_type_t<64> retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<64> retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_EXCHANGE_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_fixed_width_type_t<64> retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_EXCHANGE_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<64> retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_EXCHANGE_RELEASE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_fixed_width_type_t<64> retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_EXCHANGE_ACQ_REL_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<64> retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<64> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<64>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_64(atomic_fixed_width_type_t<64>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<64>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* assignment operator */
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&) = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };

      template <typename T>
      struct atomic_base_width<T, 16> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 16, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base = atomic_size_aligned<T>;

      public: /* ctors */
        constexpr atomic_base_width(T desired)
          : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public: /* store */
        using Base::store;

        void store(T desired)
        {
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_STORE_SEQ_CST_128(atomic_fixed_width_type_t<128>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_STORE_RELAXED_128(atomic_fixed_width_type_t<128>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_STORE_RELEASE_128(atomic_fixed_width_type_t<128>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired)
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_STORE_SEQ_CST_128(atomic_fixed_width_type_t<128>, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired)
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          atomic_fixed_width_type_t<128> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_fixed_width_type_t<128> retVal;
          REX_ATOMIC_LOAD_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_fixed_width_type_t<128> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_fixed_width_type_t<128> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_fixed_width_type_t<128> retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_fixed_width_type_t<128> retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_EXCHANGE_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_fixed_width_type_t<128> retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_EXCHANGE_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_fixed_width_type_t<128> retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_EXCHANGE_RELEASE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_fixed_width_type_t<128> retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_EXCHANGE_ACQ_REL_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_fixed_width_type_t<128> retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_EXCHANGE_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), fixedWidthDesired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_fixed_width_type_t<128> fixedWidthDesired = REX_ATOMIC_TYPE_PUN_CAST(atomic_fixed_width_type_t<128>, desired);
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_128(atomic_fixed_width_type_t<128>, retVal, REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, this->GetAtomicAddress()), REX_ATOMIC_TYPE_CAST(atomic_fixed_width_type_t<128>, &expected), fixedWidthDesired);
          return retVal;
        }

      public: /* assignment operator */
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&) = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };


    } // namespace internal
  }   // namespace v1

} // namespace rsl

#endif /* REX_ATOMIC_INTERNAL_BASE_WIDTH_H */
