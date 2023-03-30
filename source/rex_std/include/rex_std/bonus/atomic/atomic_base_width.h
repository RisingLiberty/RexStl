#pragma once

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <typename T, unsigned width = sizeof(T)>
      struct atomic_base_width;

      template <typename T>
      struct atomic_base_width<T, 1> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 1, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base                  = atomic_size_aligned<T>;
        static const size_t NumBits = sizeof(T) * 8;

      public:
        constexpr atomic_base_width(T desired)
            : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public:
        using Base::store;

        void store(T desired)
        {
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          return rsl::atomic_load(reinterpret_cast<unsigned char*>(this->atomic_address()), rsl::memory_order::relaxed);
        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          return rsl::atomic_load(reinterpret_cast<unsigned char*>(this->atomic_address()), rsl::memory_order::acquire);
        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          return rsl::atomic_load(reinterpret_cast<unsigned char*>(this->atomic_address()), rsl::memory_order::seq_cst);
        }

      public:
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acquire);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acq_rel);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

      public:
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_relaxed(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                           rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_acq_rel_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                   rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                   rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                           rsl::memory_order::seq_cst);
          return retVal;
        }

      public:
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                             rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                             rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_relaxed(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                             rsl::memory_order::seq_cst);
          return retVal;
        }

      public:
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&)          = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };

      template <typename T>
      struct atomic_base_width<T, 2> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 2, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base                  = atomic_size_aligned<T>;
        static const size_t NumBits = sizeof(T) * 8;

      public:
        constexpr atomic_base_width(T desired)
            : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public:
        using Base::store;

        void store(T desired)
        {
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::relaxed);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::acquire);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

      public:
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acquire);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acq_rel);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

      public:
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_relaxed(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                           rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_acq_rel_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                   rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                   rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                           rsl::memory_order::seq_cst);
          return retVal;
        }

      public:
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                             rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                             rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_relaxed(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                             rsl::memory_order::seq_cst);
          return retVal;
        }

      public:
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&)          = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };

      template <typename T>
      struct atomic_base_width<T, 4> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 4, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base                  = atomic_size_aligned<T>;
        static const size_t NumBits = sizeof(T) * 8;

      public:
        constexpr atomic_base_width(T desired)
            : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public:
        using Base::store;

        void store(T desired)
        {
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::relaxed);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::acquire);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

      public:
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acquire);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acq_rel);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

      public:
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_relaxed(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                           rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_acq_rel_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                   rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                   rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                           rsl::memory_order::seq_cst);
          return retVal;
        }

      public:
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                             rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                             rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_relaxed(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                             rsl::memory_order::seq_cst);
          return retVal;
        }

      public:
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&)          = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };

      template <typename T>
      struct atomic_base_width<T, 8> : public atomic_size_aligned<T>
      {
      private:
        static_assert(alignof(atomic_size_aligned<T>) == 8, "rsl::atomic<T> must be sizeof(T) aligned!");
        static_assert(alignof(atomic_size_aligned<T>) == sizeof(T), "rsl::atomic<T> must be sizeof(T) aligned!");
        using Base                  = atomic_size_aligned<T>;
        static const size_t NumBits = sizeof(T) * 8;

      public:
        constexpr atomic_base_width(T desired)
            : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public:
        using Base::store;

        void store(T desired)
        {
          store(desired, memory_order_seq_cst);
        }

        void store(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        void store(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        void store(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::load;

        T load() const
        {
          return load(memory_order_seq_cst);
        }

        T load(rsl::internal::memory_order_relaxed_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::relaxed);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T load(rsl::internal::memory_order_acquire_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::acquire);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T load(rsl::internal::memory_order_seq_cst_s) const
        {
          atomic_t<T> retVal;
          rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

      public:
        using Base::exchange;

        T exchange(T desired)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_relaxed_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_acquire_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acquire);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_release_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_acq_rel_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acq_rel);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

        T exchange(T desired, rsl::internal::memory_order_seq_cst_s)
        {
          atomic_t<T> retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return rsl::internal::atomic_type_pun_cast<T>((retVal));
        }

      public:
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_relaxed(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                           rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_acq_rel_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                   rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                           rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                   rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_weak(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_weak_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                           rsl::memory_order::seq_cst);
          return retVal;
        }

      public:
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(T& expected, T desired)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                             rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                             rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_relaxed_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_relaxed(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acquire_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acquire_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_release_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_release(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_acq_rel_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_acq_rel_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_relaxed_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                             rsl::memory_order::relaxed);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_acquire_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst_acquire(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                     rsl::memory_order::acquire);
          return retVal;
        }

        bool compare_exchange_strong(T& expected, T desired, rsl::internal::memory_order_seq_cst_s, rsl::internal::memory_order_seq_cst_s)
        {
          bool retVal;
          atomic_t<T> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<T>>((desired));
          rsl::atomic_cmpxchg_strong_seq_cst(rsl::internal::atomic_type_cast<atomic_t<T>>((this->atomic_address())), rsl::internal::atomic_type_cast<atomic_t<T>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                             rsl::memory_order::seq_cst);
          return retVal;
        }

      public:
        using Base::operator=;

        T operator=(T desired)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&)          = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };
    } // namespace internal
  }   // namespace v1

} // namespace rsl
