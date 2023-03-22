#pragma once

#include "rex_std/type_traits.h"

#include "rex_std/internal/atomic/atomic_macros.h"
#include "rex_std/internal/atomic/atomic_casts.h"

#include "rex_std/internal/atomic/atomic_memory_order.h"
#include "rex_std/internal/atomic/atomic_asserts.h"

#include "rex_std/internal/atomic/atomic_size_aligned.h"
#include "rex_std/internal/atomic/atomic_base_width.h"

#include "rex_std/internal/atomic/atomic_integral.h"

#include "rex_std/internal/atomic/atomic_pointer.h"


namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename T>
      struct is_atomic_lockfree_size
      {
				static inline constexpr bool value =
					sizeof(T) == 1 ||
					sizeof(T) == 2 ||
					sizeof(T) == 4 ||
					sizeof(T) == 8 ||
					sizeof(T) == 16;
      };


      template <typename T>
      struct is_user_type_suitable_for_primary_template
      {
        static inline constexpr bool value = rsl::internal::is_atomic_lockfree_size<T>::value;
      };


      template <typename T>
      using select_atomic_inherit_0 = typename rsl::conditional<rsl::is_same_v<bool, T> || rsl::internal::is_user_type_suitable_for_primary_template<T>::value,
        rsl::internal::atomic_base_width<T>, /* True */
        rsl::internal::atomic_invalid_type<T> /* False */
      >::type;

      template <typename T>
      using select_atomic_inherit = select_atomic_inherit_0<T>;

    } // namespace internal
  }


#define REX_ATOMIC_CLASS_IMPL(type, base, valueType, differenceType)	\
	private:															\
																		\
		REX_ATOMIC_STATIC_ASSERT_TYPE(type);							\
																		\
		using Base = base;												\
																		\
	public:																\
																		\
		typedef valueType value_type;									\
		typedef differenceType difference_type;							\
																		\
	public:																\
																		\
		static inline constexpr bool is_always_lock_free = rsl::internal::is_atomic_lockfree_size<type>::value; \
																		\
	public: /* deleted ctors && assignment operators */					\
																		\
		atomic(const atomic&) = delete;						\
																		\
		atomic& operator=(const atomic&)          = delete; \
		atomic& operator=(const atomic&) volatile = delete; \
																		\
	public: /* ctors */													\
																		\
		constexpr atomic(type desired)					\
			: Base{ desired }											\
		{																\
		}																\
																		\
		constexpr atomic() = default; \
																		\
	public:																\
																		\
		bool is_lock_free() const							\
		{																\
			return rsl::internal::is_atomic_lockfree_size<type>::value; \
		}																\
																		\
		bool is_lock_free() const volatile					\
		{																\
			REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(type);			\
			return false;												\
		}


#define REX_ATOMIC_USING_ATOMIC_BASE(type)		\
	public:											\
													\
		using Base::operator=;						\
		using Base::store;							\
		using Base::load;							\
		using Base::exchange;						\
		using Base::compare_exchange_weak;			\
		using Base::compare_exchange_strong;		\
													\
	public:											\
													\
		operator type() const volatile	\
		{											\
			REX_ATOMIC_STATIC_ASSERT_VOLATILE_MEM_FN(T); \
		}											\
													\
		operator type() const			\
		{											\
			return load(rsl::memory_order_seq_cst); \
		}


#define REX_ATOMIC_USING_ATOMIC_INTEGRAL()	\
	public:										\
												\
		using Base::fetch_add;					\
		using Base::add_fetch;					\
												\
		using Base::fetch_sub;					\
		using Base::sub_fetch;					\
												\
		using Base::fetch_and;					\
		using Base::and_fetch;					\
												\
		using Base::fetch_or;					\
		using Base::or_fetch;					\
												\
		using Base::fetch_xor;					\
		using Base::xor_fetch;					\
												\
		using Base::operator++;					\
		using Base::operator--;					\
		using Base::operator+=;					\
		using Base::operator-=;					\
		using Base::operator&=;					\
		using Base::operator|=;					\
		using Base::operator^=;


#define REX_ATOMIC_USING_ATOMIC_POINTER()		\
	public:										\
												\
		using Base::fetch_add;					\
		using Base::add_fetch;					\
		using Base::fetch_sub;					\
		using Base::sub_fetch;					\
												\
		using Base::operator++;					\
		using Base::operator--;					\
		using Base::operator+=;					\
		using Base::operator-=;


  template <typename T, typename = void>
  struct atomic : protected rsl::internal::select_atomic_inherit<T>
  {
    REX_ATOMIC_CLASS_IMPL(T, rsl::internal::select_atomic_inherit<T>, T, T)

      REX_ATOMIC_USING_ATOMIC_BASE(T)
  };


  template <typename T>
  struct atomic<T, rsl::enable_if_t<rsl::is_integral_v<T> && !rsl::is_same_v<bool, T>>> : protected rsl::internal::atomic_integral_width<T>
  {
    REX_ATOMIC_CLASS_IMPL(T, rsl::internal::atomic_integral_width<T>, T, T)

      REX_ATOMIC_USING_ATOMIC_BASE(T)

      REX_ATOMIC_USING_ATOMIC_INTEGRAL()
  };


  template <typename T>
  struct atomic<T*> : protected rsl::internal::atomic_pointer_width<T*>
  {
    REX_ATOMIC_CLASS_IMPL(T*, rsl::internal::atomic_pointer_width<T*>, T*, ptrdiff_t)

      REX_ATOMIC_USING_ATOMIC_BASE(T*)

      REX_ATOMIC_USING_ATOMIC_POINTER()
  };


} // namespace rsl




