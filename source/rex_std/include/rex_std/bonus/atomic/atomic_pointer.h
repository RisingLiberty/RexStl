

#ifndef REX_ATOMIC_INTERNAL_POINTER_H
#define REX_ATOMIC_INTERNAL_POINTER_H

#pragma once

namespace rsl
{
  inline namespace v1
  {

    namespace internal
    {

      template <typename T, unsigned width = sizeof(T)>
      struct atomic_pointer_base;

#define REX_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(funcName)                                                                                                                                                                                            \
  template <typename Order>                                                                                                                                                                                                                              \
  T* funcName(ptrdiff_t /*arg*/, Order /*order*/)                                                                                                                                                                                                        \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_INVALID_MEMORY_ORDER(T);                                                                                                                                                                                                    \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  template <typename Order>                                                                                                                                                                                                                              \
  T* funcName(ptrdiff_t /*arg*/, Order /*order*/) volatile                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  T* funcName(ptrdiff_t /*arg*/) volatile                                                                                                                                                                                                                \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }

#define REX_ATOMIC_POINTER_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(operatorOp)                                                                                                                                                                               \
  T* operator operatorOp() volatile                                                                                                                                                                                                                      \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  T* operator operatorOp(int) volatile                                                                                                                                                                                                                   \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }

#define REX_ATOMIC_POINTER_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(operatorOp)                                                                                                                                                                            \
  T* operator operatorOp(ptrdiff_t /*arg*/) volatile                                                                                                                                                                                                     \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T);                                                                                                                                                                                                         \
  }

      template <typename T, unsigned width>
      struct atomic_pointer_base<T*, width> : public atomic_base_width<T*, width>
      {
      private:
        using Base = atomic_base_width<T*, width>;

      public: /* ctors */
        constexpr atomic_pointer_base(T* desired)
            : Base {desired}
        {
        }

        constexpr atomic_pointer_base() = default;

        atomic_pointer_base(const atomic_pointer_base&) = delete;

      public: /* assignment operators */
        using Base::operator=;

        atomic_pointer_base& operator=(const atomic_pointer_base&)          = delete;
        atomic_pointer_base& operator=(const atomic_pointer_base&) volatile = delete;

      public: /* fetch_add */
        REX_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(fetch_add)

      public: /* add_fetch */
        REX_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(add_fetch)

      public: /* fetch_sub */
        REX_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(fetch_sub)

      public: /* sub_fetch */
        REX_ATOMIC_POINTER_STATIC_ASSERT_FUNCS_IMPL(sub_fetch)

      public: /* operator++ && operator-- */
        REX_ATOMIC_POINTER_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(++)

        REX_ATOMIC_POINTER_STATIC_ASSERT_INC_DEC_OPERATOR_IMPL(--)

      public: /* operator+= && operator-= */
        REX_ATOMIC_POINTER_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(+=)

        REX_ATOMIC_POINTER_STATIC_ASSERT_ASSIGNMENT_OPERATOR_IMPL(-=)
      };

      template <typename T, unsigned width = sizeof(T)>
      struct atomic_pointer_width;

#define REX_ATOMIC_POINTER_FUNC_IMPL(op, bits)                                                                                                                                                                                                           \
  T* retVal;                                                                                                                                                                                                                                             \
  {                                                                                                                                                                                                                                                      \
    ptr_integral_type retType;                                                                                                                                                                                                                           \
    ptr_integral_type addend = static_cast<ptr_integral_type>(arg) * static_cast<ptr_integral_type>(sizeof(T));                                                                                                                                          \
                                                                                                                                                                                                                                                         \
    MERGE(op, bits)(ptr_integral_type, retType, REX_ATOMIC_INTEGRAL_CAST(ptr_integral_type, this->GetAtomicAddress()), addend);                                                                                                                          \
                                                                                                                                                                                                                                                         \
    retVal = reinterpret_cast<T*>(retType);                                                                                                                                                                                                              \
  }                                                                                                                                                                                                                                                      \
  return retVal;

#define REX_ATOMIC_POINTER_FETCH_IMPL(funcName, op, bits)                                                                                                                                                                                                \
  T* funcName(ptrdiff_t arg)                                                                                                                                                                                                                             \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_TYPE_IS_OBJECT(T);                                                                                                                                                                                                          \
    REX_ATOMIC_POINTER_FUNC_IMPL(op, bits);                                                                                                                                                                                                              \
  }

#define REX_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, orderType, op, bits)                                                                                                                                                                               \
  T* funcName(ptrdiff_t arg, orderType)                                                                                                                                                                                                                  \
  {                                                                                                                                                                                                                                                      \
    REX_ATOMIC_STATIC_ASSERT_TYPE_IS_OBJECT(T);                                                                                                                                                                                                          \
    REX_ATOMIC_POINTER_FUNC_IMPL(op, bits);                                                                                                                                                                                                              \
  }

#define REX_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, Order) MERGE(MERGE(REX_ATOMIC_, fetchOp), Order)

#define REX_ATOMIC_POINTER_FETCH_FUNCS_IMPL(funcName, fetchOp, bits)                                                                                                                                                                                     \
  using Base::funcName;                                                                                                                                                                                                                                  \
                                                                                                                                                                                                                                                         \
  REX_ATOMIC_POINTER_FETCH_IMPL(funcName, REX_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _SEQ_CST_), bits)                                                                                                                                                    \
                                                                                                                                                                                                                                                         \
  REX_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_relaxed_s, REX_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _RELAXED_), bits)                                                                                                       \
                                                                                                                                                                                                                                                         \
  REX_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_acquire_s, REX_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _ACQUIRE_), bits)                                                                                                       \
                                                                                                                                                                                                                                                         \
  REX_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_release_s, REX_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _RELEASE_), bits)                                                                                                       \
                                                                                                                                                                                                                                                         \
  REX_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_acq_rel_s, REX_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _ACQ_REL_), bits)                                                                                                       \
                                                                                                                                                                                                                                                         \
  REX_ATOMIC_POINTER_FETCH_ORDER_IMPL(funcName, rsl::internal::memory_order_seq_cst_s, REX_ATOMIC_POINTER_FETCH_OP_JOIN(fetchOp, _SEQ_CST_), bits)

#define REX_ATOMIC_POINTER_FETCH_INC_DEC_OPERATOR_IMPL(operatorOp, preFuncName, postFuncName)                                                                                                                                                            \
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

#define REX_ATOMIC_POINTER_FETCH_ASSIGNMENT_OPERATOR_IMPL(operatorOp, funcName)                                                                                                                                                                          \
  using Base::operator operatorOp;                                                                                                                                                                                                                       \
                                                                                                                                                                                                                                                         \
  T* operator operatorOp(ptrdiff_t arg)                                                                                                                                                                                                                  \
  {                                                                                                                                                                                                                                                      \
    return funcName(arg, rsl::memory_order_seq_cst);                                                                                                                                                                                                     \
  }

#define REX_ATOMIC_POINTER_WIDTH_SPECIALIZE(bytes, bits)                                                                                                                                                                                                 \
  template <typename T>                                                                                                                                                                                                                                  \
  struct atomic_pointer_width<T*, bytes> : public atomic_pointer_base<T*, bytes>                                                                                                                                                                         \
  {                                                                                                                                                                                                                                                      \
  private:                                                                                                                                                                                                                                               \
    using Base                = atomic_pointer_base<T*, bytes>;                                                                                                                                                                                          \
    using u_ptr_integral_type = MERGE(MERGE(uint, bits), _t);                                                                                                                                                                                            \
    using ptr_integral_type   = MERGE(MERGE(int, bits), _t);                                                                                                                                                                                             \
                                                                                                                                                                                                                                                         \
  public: /* ctors */                                                                                                                                                                                                                                    \
    constexpr atomic_pointer_width(T* desired)                                                                                                                                                                                                           \
        : Base {desired}                                                                                                                                                                                                                                 \
    {                                                                                                                                                                                                                                                    \
    }                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                         \
    constexpr atomic_pointer_width() = default;                                                                                                                                                                                                          \
                                                                                                                                                                                                                                                         \
    atomic_pointer_width(const atomic_pointer_width&) = delete;                                                                                                                                                                                          \
                                                                                                                                                                                                                                                         \
  public: /* assignment operators */                                                                                                                                                                                                                     \
    using Base::operator=;                                                                                                                                                                                                                               \
                                                                                                                                                                                                                                                         \
    atomic_pointer_width& operator=(const atomic_pointer_width&)          = delete;                                                                                                                                                                      \
    atomic_pointer_width& operator=(const atomic_pointer_width&) volatile = delete;                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  public: /* fetch_add */                                                                                                                                                                                                                                \
    REX_ATOMIC_POINTER_FETCH_FUNCS_IMPL(fetch_add, FETCH_ADD, bits)                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  public: /* add_fetch */                                                                                                                                                                                                                                \
    REX_ATOMIC_POINTER_FETCH_FUNCS_IMPL(add_fetch, ADD_FETCH, bits)                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  public: /* fetch_sub */                                                                                                                                                                                                                                \
    REX_ATOMIC_POINTER_FETCH_FUNCS_IMPL(fetch_sub, FETCH_SUB, bits)                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  public: /* sub_fetch */                                                                                                                                                                                                                                \
    REX_ATOMIC_POINTER_FETCH_FUNCS_IMPL(sub_fetch, SUB_FETCH, bits)                                                                                                                                                                                      \
                                                                                                                                                                                                                                                         \
  public: /* operator++ && operator-- */                                                                                                                                                                                                                 \
    REX_ATOMIC_POINTER_FETCH_INC_DEC_OPERATOR_IMPL(++, add_fetch, fetch_add)                                                                                                                                                                             \
                                                                                                                                                                                                                                                         \
    REX_ATOMIC_POINTER_FETCH_INC_DEC_OPERATOR_IMPL(--, sub_fetch, fetch_sub)                                                                                                                                                                             \
                                                                                                                                                                                                                                                         \
  public: /* operator+= && operator-= */                                                                                                                                                                                                                 \
    REX_ATOMIC_POINTER_FETCH_ASSIGNMENT_OPERATOR_IMPL(+=, add_fetch)                                                                                                                                                                                     \
                                                                                                                                                                                                                                                         \
    REX_ATOMIC_POINTER_FETCH_ASSIGNMENT_OPERATOR_IMPL(-=, sub_fetch)                                                                                                                                                                                     \
                                                                                                                                                                                                                                                         \
  public:                                                                                                                                                                                                                                                \
    using Base::load;                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                         \
    T* load(rsl::internal::memory_order_read_depends_s)                                                                                                                                                                                                  \
    {                                                                                                                                                                                                                                                    \
      T* retPointer;                                                                                                                                                                                                                                     \
      MERGE(REX_ATOMIC_LOAD_READ_DEPENDS_, bits)(T*, retPointer, this->GetAtomicAddress());                                                                                                                                                              \
      return retPointer;                                                                                                                                                                                                                                 \
    }                                                                                                                                                                                                                                                    \
  };

#if defined(REX_ATOMIC_HAS_32BIT) && REX_PLATFORM_PTR_SIZE == 4
      REX_ATOMIC_POINTER_WIDTH_SPECIALIZE(4, 32)
#endif

#if defined(REX_ATOMIC_HAS_64BIT) && REX_PLATFORM_PTR_SIZE == 8
      REX_ATOMIC_POINTER_WIDTH_SPECIALIZE(8, 64)
#endif

    } // namespace internal
  }   // namespace v1

} // namespace rsl

#endif /* REX_ATOMIC_INTERNAL_POINTER_H */
