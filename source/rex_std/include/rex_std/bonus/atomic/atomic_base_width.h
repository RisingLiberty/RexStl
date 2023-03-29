

#ifndef REX_ATOMIC_INTERNAL_BASE_WIDTH_H
#define REX_ATOMIC_INTERNAL_BASE_WIDTH_H

#pragma once

#include "rex_std/bonus/atomic/atomic_fixed_width_type.h"

#include "rex_std/bonus/atomic/atomic_store.h"
#include "rex_std/bonus/atomic/atomic_load.h"

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <typename T, unsigned width = sizeof(T)>
      struct atomic_base_width;

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
        static const size_t NumBits = sizeof(T) * 8;

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
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store_relaxed(this->atomic_address(), fixed_width_desired);
          REX_ATOMIC_STORE_RELAXED_8(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELEASE_8(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_SEQ_CST_8(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          //atomic_t<T> retVal;
          return rsl::atomic_load_relaxed(reinterpret_cast<unsigned char*>(this->atomic_address()));
          //REX_ATOMIC_LOAD_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          //return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          //atomic_t<T> retVal;
          return rsl::atomic_load_acquire(reinterpret_cast<unsigned char*>(this->atomic_address()));
          //REX_ATOMIC_LOAD_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          //return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          //atomic_t<T> retVal;
          return rsl::atomic_load_seq_cst(reinterpret_cast<unsigned char*>(this->atomic_address()));
          //REX_ATOMIC_LOAD_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          //return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELEASE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQ_REL_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_8(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
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
        static const size_t NumBits = sizeof(T) * 8;

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
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELAXED_16(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELEASE_16(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_SEQ_CST_16(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELEASE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQ_REL_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_16(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
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
        static const size_t NumBits = sizeof(T) * 8;

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
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELAXED_32(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELEASE_32(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_SEQ_CST_32(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELEASE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQ_REL_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_32(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
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
        static const size_t NumBits = sizeof(T) * 8;

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
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELAXED_64(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELEASE_64(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_SEQ_CST_64(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELEASE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQ_REL_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_64(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
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
        static const size_t NumBits = sizeof(T) * 8;

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
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELAXED_128(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_RELEASE_128(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_STORE_SEQ_CST_128(atomic_t<T>, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
        }

      public: /* load */
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_t<T> retVal;
          REX_ATOMIC_LOAD_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())));
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);

        }

      public: /* exchange */
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_RELEASE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_ACQ_REL_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_EXCHANGE_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired);
          return REX_ATOMIC_TYPE_PUN_CAST(T, retVal);
        }

      public: /* compare_exchange_weak */
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELAXED_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQUIRE_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_RELEASE_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_ACQ_REL_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_WEAK_SEQ_CST_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

      public: /* compare_exchange_strong */
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELAXED_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQUIRE_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_RELEASE_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_ACQ_REL_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_RELAXED_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_ACQUIRE_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          REX_ATOMIC_CMPXCHG_STRONG_SEQ_CST_SEQ_CST_128(atomic_t<T>, retVal, rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), REX_ATOMIC_TYPE_CAST(atomic_t<T>, &expected), fixed_width_desired);
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
