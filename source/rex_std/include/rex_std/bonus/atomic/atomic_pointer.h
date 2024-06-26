#pragma once

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {

      template <typename T, unsigned Width = sizeof(T)>
      struct atomic_pointer_base;

#define RSL_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(funcName)                                                                                                                                                                                            \
  template <typename Order>                                                                                                                                                                                                                              \
  T* funcName(ptrdiff_t /*arg*/, Order /*order*/)                                                                                                                                                                                                        \
  {                                                                                                                                                                                                                                                      \
    RSL_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(T);                                                                                                                                                                                                    \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  template <typename Order>                                                                                                                                                                                                                              \
  T* funcName(ptrdiff_t /*arg*/, Order /*order*/) volatile                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                      \
    RSL_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  T* funcName(ptrdiff_t /*arg*/) volatile                                                                                                                                                                                                                \
  {                                                                                                                                                                                                                                                      \
    RSL_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }

#define RSL_ATOMIC_POINTER_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(operatorOp)                                                                                                                                                                               \
  T* operator operatorOp() volatile                                                                                                                                                                                                                      \
  {                                                                                                                                                                                                                                                      \
    RSL_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  T* operator operatorOp(int) volatile                                                                                                                                                                                                                   \
  {                                                                                                                                                                                                                                                      \
    RSL_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }

#define RSL_ATOMIC_POINTER_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(operatorOp)                                                                                                                                                                            \
  T* operator operatorOp(ptrdiff_t /*arg*/) volatile                                                                                                                                                                                                     \
  {                                                                                                                                                                                                                                                      \
    RSL_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }

      template <typename T, unsigned Width>
      struct atomic_pointer_base<T*, Width> : public atomic_base_width<T*, Width>
      {
      private:
        using Base = atomic_base_width<T*, Width>;

      public:                                     /* ctors */
        constexpr atomic_pointer_base(T* desired) // NOLINT(google-explicit-constructor)
            : Base {desired}
        {
        }

        constexpr atomic_pointer_base() = default;
        ~atomic_pointer_base()          = default;

        atomic_pointer_base(const atomic_pointer_base&) = delete;

      public: /* assignment operators */
        using Base::operator=;

        atomic_pointer_base& operator=(const atomic_pointer_base&)          = delete;
        atomic_pointer_base& operator=(const atomic_pointer_base&) volatile = delete;

      public: /* fetch_add */
        RSL_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(fetch_add)

      public: /* add_fetch */
        RSL_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(add_fetch)

      public: /* fetch_sub */
        RSL_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(fetch_sub)

      public: /* sub_fetch */
        RSL_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(sub_fetch)

      public:                                                      /* operator++ && operator-- */
        RSL_ATOMIC_POINTER_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(++) // NOLINT(bugprone-macro-repeated-side-effects)

        RSL_ATOMIC_POINTER_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(--) // NOLINT(bugprone-macro-repeated-side-effects)

      public: /* operator+= && operator-= */
        RSL_ATOMIC_POINTER_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(+=)

        RSL_ATOMIC_POINTER_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(-=)
      };

      template <typename T, unsigned Width = sizeof(T)>
      struct atomic_pointer_width;

#define RSL_ATOMIC_POINTER_FUNC_IMPL(op, bits)                                                                                                                                                                                                           \
  T* retVal;                                                                                                                                                                                                                                             \
  {                                                                                                                                                                                                                                                      \
    ptr_integral_type retType;                                                                                                                                                                                                                           \
    ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));                                                                                                                                          \
                                                                                                                                                                                                                                                         \
    MERGE(op, 64)(ptr_integral_type, retType, RSL_ATOMIC_INTEGRAL_CAST(ptr_integral_type, this->this->atomic_address()), addend);                                                                                                                        \
                                                                                                                                                                                                                                                         \
    retVal = reinterpret_cast<T*>(retType);                                                                                                                                                                                                              \
  }                                                                                                                                                                                                                                                      \
  return retVal;

#define RSL_ATOMIC_POINTER_FETCH_IMPL(funcName, op, bits)                                                                                                                                                                                                \
  T* funcName(ptrdiff_t arg)                                                                                                                                                                                                                             \
  {                                                                                                                                                                                                                                                      \
    RSL_ATOMIC_STATIC_ASSERT_TYPE_IS_OBJECT(T);                                                                                                                                                                                                          \
    RSL_ATOMIC_POINTER_FUNC_IMPL(op, 64);                                                                                                                                                                                                                \
  }

#define RSL_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, orderType, op, bits)                                                                                                                                                                               \
  T* funcName(ptrdiff_t arg, orderType)                                                                                                                                                                                                                  \
  {                                                                                                                                                                                                                                                      \
    RSL_ATOMIC_STATIC_ASSERT_TYPE_IS_OBJECT(T);                                                                                                                                                                                                          \
    RSL_ATOMIC_POINTER_FUNC_IMPL(op, 64);                                                                                                                                                                                                                \
  }

#define RSL_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, Order) MERGE(MERGE(RSL_ATOMIC_, fetchOp), Order)

#define RSL_ATOMIC_POINTER_FETCH_FUNCS_IMPL(funcName, fetchOp, bits)                                                                                                                                                                                     \
  using Base::funcName;                                                                                                                                                                                                                                  \
                                                                                                                                                                                                                                                         \
  RSL_ATOMIC_POINTER_FETCH_IMPL(funcName, RSL_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _SEQ_CST_), 64)                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  RSL_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_relaxed_s, RSL_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _RELAXED_), 64)                                                                                                         \
                                                                                                                                                                                                                                                         \
  RSL_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_acquire_s, RSL_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _ACQUIRE_), 64)                                                                                                         \
                                                                                                                                                                                                                                                         \
  RSL_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_release_s, RSL_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _RELEASE_), 64)                                                                                                         \
                                                                                                                                                                                                                                                         \
  RSL_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_acq_rel_s, RSL_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _ACQ_REL_), 64)                                                                                                         \
                                                                                                                                                                                                                                                         \
  RSL_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_seq_cst_s, RSL_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _SEQ_CST_), 64)

#define RSL_ATOMIC_POINTER_FETCH_INC_DEC_OPERATOR_IMPL(operatorOp, preFuncName, postFuncName)                                                                                                                                                            \
  using Base::operator operatorOp;                                                                                                                                                                                                                       \
                                                                                                                                                                                                                                                         \
  T* operator operatorOp()                                                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                      \
    return preFuncName(1, rsl::memory_order_seq_cst);                                                                                                                                                                                                    \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  T* operator operatorOp(int)                                                                                                                                                                                                                            \
  {                                                                                                                                                                                                                                                      \
    return postFuncName(1, rsl::memory_order_seq_cst);                                                                                                                                                                                                   \
  }

#define RSL_ATOMIC_POINTER_FETCH_ASSIGNMENT_OPERATOR_IMPL(operatorOp, funcName)                                                                                                                                                                          \
  using Base::operator operatorOp;                                                                                                                                                                                                                       \
                                                                                                                                                                                                                                                         \
  T* operator operatorOp(ptrdiff_t arg)                                                                                                                                                                                                                  \
  {                                                                                                                                                                                                                                                      \
    return funcName(arg, rsl::memory_order_seq_cst);                                                                                                                                                                                                     \
  }

      template <typename T>
      struct atomic_pointer_width<T*, 8> : public atomic_pointer_base<T*, 8>
      {
      private:
        using Base                = atomic_pointer_base<T*, 8>;
        using u_ptr_integral_type = uint64_t;
        using ptr_integral_type   = int64_t;

      public:
        constexpr atomic_pointer_width(T* desired) noexcept
            : Base {desired}
        {
        }

        constexpr atomic_pointer_width() noexcept                  = default;
        atomic_pointer_width(const atomic_pointer_width&) noexcept = delete;

      public:
        using Base::operator=;
        atomic_pointer_width& operator=(const atomic_pointer_width&) noexcept          = delete;
        atomic_pointer_width& operator=(const atomic_pointer_width&) volatile noexcept = delete;

      public:
        using Base::fetch_add;

        T* fetch_add(ptrdiff_t arg) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_add(ptrdiff_t arg, rsl::internal::memory_order_relaxed_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_add(ptrdiff_t arg, rsl::internal::memory_order_acquire_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_add(ptrdiff_t arg, rsl::internal::memory_order_release_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_add(ptrdiff_t arg, rsl::internal::memory_order_acq_rel_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_add(ptrdiff_t arg, rsl::internal::memory_order_seq_cst_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }

      public:
        using Base::add_fetch;
        T* add_fetch(ptrdiff_t arg) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) + ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* add_fetch(ptrdiff_t arg, rsl::internal::memory_order_relaxed_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) + ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* add_fetch(ptrdiff_t arg, rsl::internal::memory_order_acquire_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) + ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* add_fetch(ptrdiff_t arg, rsl::internal::memory_order_release_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) + ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* add_fetch(ptrdiff_t arg, rsl::internal::memory_order_acq_rel_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) + ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* add_fetch(ptrdiff_t arg, rsl::internal::memory_order_seq_cst_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = ((addend));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) + ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }

      public:
        using Base::fetch_sub;
        T* fetch_sub(ptrdiff_t arg) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_sub(ptrdiff_t arg, rsl::internal::memory_order_relaxed_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_sub(ptrdiff_t arg, rsl::internal::memory_order_acquire_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_sub(ptrdiff_t arg, rsl::internal::memory_order_release_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_sub(ptrdiff_t arg, rsl::internal::memory_order_acq_rel_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* fetch_sub(ptrdiff_t arg, rsl::internal::memory_order_seq_cst_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              ;
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }

      public:
        using Base::sub_fetch;
        T* sub_fetch(ptrdiff_t arg) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) - ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* sub_fetch(ptrdiff_t arg, rsl::internal::memory_order_relaxed_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) - ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* sub_fetch(ptrdiff_t arg, rsl::internal::memory_order_acquire_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) - ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* sub_fetch(ptrdiff_t arg, rsl::internal::memory_order_release_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) - ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* sub_fetch(ptrdiff_t arg, rsl::internal::memory_order_acq_rel_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) - ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }
        T* sub_fetch(ptrdiff_t arg, rsl::internal::memory_order_seq_cst_s) noexcept
        {
          static_assert(rsl::is_object<T>::value, "rsl::atomic<T> : Template Typename T must be an object type!");
          ;
          T* retVal;

          {
            ptr_integral_type retType;
            ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));

            {
              __int64 retIntegral;
              ptr_integral_type valCompute;
              valCompute                = rsl::internal::atomic_negate_operand((((addend))));
              const __int64 valIntegral = rsl::internal::atomic_type_pun_cast<__int64>((valCompute));
              retIntegral               = _InterlockedExchangeAdd64(rsl::internal::atomic_volatile_integral_cast<__int64>(((rsl::internal::atomic_integral_cast<ptr_integral_type>((this->atomic_address()))))), valIntegral);
              retType                   = rsl::internal::atomic_type_pun_cast<ptr_integral_type>((retIntegral));
              retType                   = (retType) - ((addend));
            };
            retVal = reinterpret_cast<T*>(retType);
          }
          return retVal;
          ;
        }

      public:
        using Base::operator++;
        T* operator++() noexcept
        {
          return add_fetch(1, rsl::memory_order_seq_cst);
        }
        T* operator++(int) noexcept
        {
          return fetch_add(1, rsl::memory_order_seq_cst);
        }
        using Base::operator--;
        T* operator--() noexcept
        {
          return sub_fetch(1, rsl::memory_order_seq_cst);
        }
        T* operator--(int) noexcept
        {
          return fetch_sub(1, rsl::memory_order_seq_cst);
        }

      public:
        using Base::operator+=;
        T* operator+=(ptrdiff_t arg) noexcept
        {
          return add_fetch(arg, rsl::memory_order_seq_cst);
        }
        using Base::operator-=;
        T* operator-=(ptrdiff_t arg) noexcept
        {
          return sub_fetch(arg, rsl::memory_order_seq_cst);
        }

      public:
        using Base::load;
        T* load(rsl::internal::memory_order_read_depends_s) noexcept
        {
          static_assert(rsl::is_pointer_v<T*>, "rsl::atomic<T> : Read Depends Type must be a Pointer Type!");
          static_assert(rsl::is_pointer_v<rsl::remove_pointer_t<decltype(this->atomic_address())>>, "rsl::atomic<T> : Read Depends Ptr must be a Pointer to a Pointer!");

          return (*rsl::internal::atomic_volatile_cast((this->atomic_address())));
        }
      };

    } // namespace internal
  }   // namespace v1

} // namespace rsl
