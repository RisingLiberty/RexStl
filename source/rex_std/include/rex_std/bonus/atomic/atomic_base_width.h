#pragma once

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {
      template <typename Type, unsigned Width = sizeof(Type)>
      struct atomic_base_width;

      template <typename Type>
      struct atomic_base_width<Type, 1> : public atomic_size_aligned<Type>
      {
      private:
        static_assert(alignof(atomic_size_aligned<Type>) == 1, "rsl::atomic<Type> must be sizeof(Type) aligned!");
        static_assert(alignof(atomic_size_aligned<Type>) == sizeof(Type), "rsl::atomic<Type> must be sizeof(Type) aligned!");
        using Base                     = atomic_size_aligned<Type>;
        static const size_t s_num_bits = sizeof(Type) * 8;

      public:
        constexpr explicit atomic_base_width(Type desired)
            : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;
        ~atomic_base_width()          = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public:
        using Base::store;

        void store(Type desired)
        {
          store(desired, memory_order_seq_cst);
        }

        void store(Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        void store(Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        void store(Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::load;

        Type load() const
        {
          return load(memory_order_seq_cst);
        }

        Type load(rsl::internal::memory_order_relaxed_s /*unused*/) const
        {
          return rsl::atomic_load(reinterpret_cast<unsigned char*>(this->atomic_address()), rsl::memory_order::relaxed); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        }

        Type load(rsl::internal::memory_order_acquire_s /*unused*/) const
        {
          return rsl::atomic_load(reinterpret_cast<unsigned char*>(this->atomic_address()), rsl::memory_order::acquire); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        }

        Type load(rsl::internal::memory_order_seq_cst_s /*unused*/) const
        {
          return rsl::atomic_load(reinterpret_cast<unsigned char*>(this->atomic_address()), rsl::memory_order::seq_cst); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        }

      public:
        using Base::exchange;

        Type exchange(Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

        Type exchange(Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        Type exchange(Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acquire);
        }

        Type exchange(Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        Type exchange(Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acq_rel);
        }

        Type exchange(Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(Type& expected, Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                  rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                          rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                          rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                  rsl::memory_order::seq_cst);
        }

      public:
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(Type& expected, Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                            rsl::memory_order::seq_cst);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                            rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                    rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                    rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                            rsl::memory_order::seq_cst);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                    rsl::memory_order::seq_cst);
        }

      public:
        using Base::operator=;

        Type operator=(Type desired) // NOLINT(misc-unconventional-assign-operator)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&)          = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };

      template <typename Type>
      struct atomic_base_width<Type, 2> : public atomic_size_aligned<Type>
      {
      private:
        static_assert(alignof(atomic_size_aligned<Type>) == 2, "rsl::atomic<Type> must be sizeof(Type) aligned!");
        static_assert(alignof(atomic_size_aligned<Type>) == sizeof(Type), "rsl::atomic<Type> must be sizeof(Type) aligned!");
        using Base                     = atomic_size_aligned<Type>;
        static const size_t s_num_bits = sizeof(Type) * 8;

      public:
        constexpr explicit atomic_base_width(Type desired)
            : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;
        ~atomic_base_width()          = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public:
        using Base::store;

        void store(Type desired)
        {
          store(desired, memory_order_seq_cst);
        }

        void store(Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        void store(Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        void store(Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::load;

        Type load() const
        {
          return load(memory_order_seq_cst);
        }

        Type load(rsl::internal::memory_order_relaxed_s /*unused*/) const
        {
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::relaxed));
        }

        Type load(rsl::internal::memory_order_acquire_s /*unused*/) const
        {
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::acquire));
        }

        Type load(rsl::internal::memory_order_seq_cst_s /*unused*/) const
        {
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::seq_cst));
        }

      public:
        using Base::exchange;

        Type exchange(Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst));
        }

        Type exchange(Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed));
        }

        Type exchange(Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acquire));
        }

        Type exchange(Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release));
        }

        Type exchange(Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acq_rel));
        }

        Type exchange(Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst));
        }

      public:
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(Type& expected, Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                  rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                          rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                          rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                  rsl::memory_order::seq_cst);
        }

      public:
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(Type& expected, Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                            rsl::memory_order::seq_cst);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                            rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                    rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                    rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                            rsl::memory_order::seq_cst);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                    rsl::memory_order::seq_cst);
        }

      public:
        using Base::operator=;

        Type operator=(Type desired) // NOLINT(misc-unconventional-assign-operator)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&)          = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };

      template <typename Type>
      struct atomic_base_width<Type, 4> : public atomic_size_aligned<Type>
      {
      private:
        static_assert(alignof(atomic_size_aligned<Type>) == 4, "rsl::atomic<Type> must be sizeof(Type) aligned!");
        static_assert(alignof(atomic_size_aligned<Type>) == sizeof(Type), "rsl::atomic<Type> must be sizeof(Type) aligned!");
        using Base                     = atomic_size_aligned<Type>;
        static const size_t s_num_bits = sizeof(Type) * 8;

      public:
        constexpr explicit atomic_base_width(Type desired)
            : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;
        ~atomic_base_width()          = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public:
        using Base::store;

        void store(Type desired)
        {
          store(desired, memory_order_seq_cst);
        }

        void store(Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        void store(Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        void store(Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::load;

        Type load() const
        {
          return load(memory_order_seq_cst);
        }

        Type load(rsl::internal::memory_order_relaxed_s /*unused*/) const
        {
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::relaxed));
        }

        Type load(rsl::internal::memory_order_acquire_s /*unused*/) const
        {
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::acquire));
        }

        Type load(rsl::internal::memory_order_seq_cst_s /*unused*/) const
        {
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::seq_cst));
        }

      public:
        using Base::exchange;

        Type exchange(Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst));
        }

        Type exchange(Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed));
        }

        Type exchange(Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acquire));
        }

        Type exchange(Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release));
        }

        Type exchange(Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acq_rel));
        }

        Type exchange(Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::internal::atomic_type_pun_cast<Type>(rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst));
        }

      public:
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(Type& expected, Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                  rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                          rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                          rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                  rsl::memory_order::seq_cst);
        }

      public:
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(Type& expected, Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                            rsl::memory_order::seq_cst);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                            rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                    rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                    rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                            rsl::memory_order::seq_cst);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                    rsl::memory_order::seq_cst);
        }

      public:
        using Base::operator=;

        Type operator=(Type desired) // NOLINT(misc-unconventional-assign-operator)
        {
          store(desired, rsl::memory_order_seq_cst);
          return desired;
        }

        atomic_base_width& operator=(const atomic_base_width&)          = delete;
        atomic_base_width& operator=(const atomic_base_width&) volatile = delete;
      };

      template <typename Type>
      struct atomic_base_width<Type, 8> : public atomic_size_aligned<Type>
      {
      private:
        static_assert(alignof(atomic_size_aligned<Type>) == 8, "rsl::atomic<Type> must be sizeof(Type) aligned!");
        static_assert(alignof(atomic_size_aligned<Type>) == sizeof(Type), "rsl::atomic<Type> must be sizeof(Type) aligned!");
        using Base                     = atomic_size_aligned<Type>;
        static const size_t s_num_bits = sizeof(Type) * 8;

      public:
        constexpr explicit atomic_base_width(Type desired)
            : Base(desired)
        {
        }

        constexpr atomic_base_width() = default;
        ~atomic_base_width()          = default;

        atomic_base_width(const atomic_base_width&) = delete;

      public:
        using Base::store;

        void store(Type desired)
        {
          store(desired, memory_order_seq_cst);
        }

        void store(Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
        }

        void store(Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
        }

        void store(Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          rsl::atomic_store(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
        }

      public:
        using Base::load;

        Type load() const
        {
          const auto result = load(memory_order_seq_cst);
          return reinterpret_cast<Type>(result);
        }

        Type load(rsl::internal::memory_order_relaxed_s /*unused*/) const
        {
          const auto result = rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::relaxed);
          return reinterpret_cast<Type>(result);
        }

        Type load(rsl::internal::memory_order_acquire_s /*unused*/) const
        {
          const auto result = rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::acquire);
          return reinterpret_cast<Type>(result);
        }

        Type load(rsl::internal::memory_order_seq_cst_s /*unused*/) const
        {
          const auto result = rsl::atomic_load(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), rsl::memory_order::seq_cst);
          return reinterpret_cast<Type>(result);
        }

      public:
        using Base::exchange;

        Type exchange(Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          const auto result = rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return reinterpret_cast<Type>(result);
        }

        Type exchange(Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          const auto result = rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::relaxed);
          return reinterpret_cast<Type>(result);
        }

        Type exchange(Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          const auto result = rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acquire);
          return reinterpret_cast<Type>(result);
        }

        Type exchange(Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          const auto result = rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::release);
          return reinterpret_cast<Type>(result);
        }

        Type exchange(Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          const auto result = rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::acq_rel);
          return reinterpret_cast<Type>(result);
        }

        Type exchange(Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          const auto result = rsl::atomic_exchange(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), fixed_width_desired, rsl::memory_order::seq_cst);
          return reinterpret_cast<Type>(result);
        }

      public:
        using Base::compare_exchange_weak;

        bool compare_exchange_weak(Type& expected, Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst, rsl::memory_order::seq_cst);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                  rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel, rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                          rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                  rsl::memory_order::relaxed);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                          rsl::memory_order::acquire);
        }

        bool compare_exchange_weak(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_weak(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                  rsl::memory_order::seq_cst);
        }

      public:
        using Base::compare_exchange_strong;

        bool compare_exchange_strong(Type& expected, Type desired)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                            rsl::memory_order::seq_cst);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                            rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                    rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                    rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                            rsl::memory_order::seq_cst);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_relaxed_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::relaxed,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acquire_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acquire,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_release_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::release,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_acq_rel_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::acq_rel,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_relaxed_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                    rsl::memory_order::relaxed);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_acquire_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                            rsl::memory_order::acquire);
        }

        bool compare_exchange_strong(Type& expected, Type desired, rsl::internal::memory_order_seq_cst_s /*unused*/, rsl::internal::memory_order_seq_cst_s /*unused*/)
        {
          const atomic_t<Type> fixed_width_desired = rsl::internal::atomic_type_pun_cast<atomic_t<Type>>((desired));
          return rsl::atomic_cmpxchg_strong(rsl::internal::atomic_type_cast<atomic_t<Type>>((this->atomic_address())), *rsl::internal::atomic_type_cast<atomic_t<Type>>((&expected)), fixed_width_desired, rsl::memory_order::seq_cst,
                                                    rsl::memory_order::seq_cst);
        }

      public:
        using Base::operator=;

        Type operator=(Type desired) // NOLINT(misc-unconventional-assign-operator)
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
