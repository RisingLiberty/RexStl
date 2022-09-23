// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: function.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/cstddef/nullptr.h"
#include "rex_std/internal/functional/invoke.h"
#include "rex_std/internal/memory/byte.h"
#include "rex_std/internal/type_traits/alignment_of.h"
#include "rex_std/internal/type_traits/is_member_function_pointer.h"

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename T>
  bool is_null(const T&)
  {
    return false;
  }

  template <typename Result, typename... Arguments>
  bool is_null(Result (*const& function_pointer)(Arguments...))
  {
    return function_pointer == nullptr;
  }

  template <typename Result, typename Class, typename... Arguments>
  bool is_null(Result (Class::*const& function_pointer)(Arguments...))
  {
    return function_pointer == nullptr;
  }

  template <typename Result, typename Class, typename... Arguments>
  bool is_null(Result (Class::*const& function_pointer)(Arguments...) const)
  {
    return function_pointer == nullptr;
  }

  class UnusedClass
  {
  };

  union FunctorStorageAlignment
  {
    void (*unused_func_ptr)(void);
    void (UnusedClass::*unused_func_mem_ptr)(void);
    void* unused_ptr;
  };

  template <count_t SizeInBytes>
  struct alignas(sizeof(FunctorStorageAlignment)) FunctorStorage
  {
    static_assert(SizeInBytes >= 0, "functor storage must be a positive size");

    template <typename Ret>
    Ret& get_storage_type_ref() const
    {
      return *reinterpret_cast<Ret*>(const_cast<byte*>(&storage[0]));
    }

    byte storage[SizeInBytes];
  };

  template <>
  struct FunctorStorage<0>
  {
    template <typename Ret>
    Ret& get_storage_type_ref() const
    {
      return *reinterpret_cast<Ret*>(const_cast<byte*>(&storage[0]));
    }

    byte storage[sizeof(FunctorStorageAlignment)];
  };

  template <typename Functor, count_t SizeInBytes>
  struct IsFunctorInplaceAllocatable
  {
    static constexpr bool value = sizeof(Functor) <= sizeof(FunctorStorage<SizeInBytes>) && (rsl::alignment_of_v<FunctorStorage<SizeInBytes>> % rsl::alignment_of_v<Functor>) == 0;
  };

  template <count_t SizeInBytes>
  class FunctionDetailBase
  {
  public:
    using functor_storage_type = FunctorStorage<SizeInBytes>;

    enum class ManagerOperations
    {
      DestroyFunctor,
      CopyFunctor,
      MoveFunctor
    };

    // functor allocated inplace
    template <typename Functor, typename = void>
    class FunctionManagerBase
    {
    public:
      static Functor* get_functor_ptr(const functor_storage_type& storage)
      {
        return &storage.template get_storage_type_ref<Functor>();
      }

      template <typename T>
      static void create_functor(functor_storage_type& storage, T&& functor)
      {
        new(get_functor_ptr(storage)) Functor(rsl::forward<T>(functor));
      }

      static void destroy_functor(functor_storage_type& storage)
      {
        get_functor_ptr(storage)->~Functor();
      }

      static void copy_functor(functor_storage_type& to, const functor_storage_type& from)
      {
        new(get_functor_ptr(to)) Functor(*get_functor_ptr(from));
      }

      static void move_functor(functor_storage_type& to, functor_storage_type& from)
      {
        new(get_functor_ptr(to)) Functor(rsl::remove_cv_t(*get_functor_ptr(from)));
      }

      static void* manager(void* to, void* from, typename FunctionDetailBase::ManagerOperations ops)
      {
        switch(ops)
        {
          case FunctionDetailBase::ManagerOperations::DestroyFunctor:
          {
            destruct_functor(*static_cast<functor_storage_type*>(to));
          }
          break;
          case FunctionDetailBase::ManagerOperations::CopyFunctor:
          {
            copy_functor(*static_cast<functor_storage_type*>(to), *static_cast<const functor_storage_type*>(from));
          }
          break;
          case FunctionDetailBase::ManagerOperations::MoveFunctor:
          {
            move_functor(*static_cast<functor_storage_type*>(to), *static_cast<functor_storage_type*>(from));
            destroy_functor(*static_cast<functor_storage_type*>(from));
          }
          break;
          default: break;
        }

        return nullptr;
      }
    };

    // functor allocated on the heap
    template <typename Functor>
    class FunctionManagerBase<Functor, typename enable_if_t<!IsFunctorInplaceAllocatable<Functor, SizeInBytes>::value>::type>
    {
      static Functor* get_functor_ptr(const functor_storage_type& storage)
      {
        return storage.template get_storage_type_ref<Functor*>();
      }
      static Functor*& get_functor_ptr_ref(const functor_storage_type& storage)
      {
        return storage.template get_storage_type_ref<Functor*>();
      }

      template <typename T>
      static void create_functor(functor_storage_type& storage, T&& functor)
      {
        auto allocator = rsl::allocator();
        Functor* func  = static_cast<Functor*>(allocator.allocate(sizeof(Functor), alignof(Functor), 0));

        REX_ASSERT_X(func != nullptr, "Allocation with {} failed", allocator.name());

        new(static_cast<void*>(func)) Functor(rsl::forward<T>(functor));
        get_functor_ptr_ref(storage) = func;
      }

      static void destroy_functor(functor_storage_type& storage)
      {
        Functor* func = get_functor_ptr(storage);
        if(func)
        {
          func->~Functor();
          auto allocator = rsl::allocator();
          allocator.deallocate(static_cast<void*>(func), sizeof(Functor));
        }
      }

      static void copy_functor(functor_storage_type& to, const functor_storage_type& from)
      {
        auto allocator = rsl::allocator();
        Functor* func  = static_cast<Functor*>(allocator.allocate(sizeof(Functor), alignof(Functor), 0));

        REX_ASSERT_X(func != nullptr, "Allocation with {} failed", allocator.name());

        new(static_cast<void*>(func)) Functor(*get_functor_ptr(from));
        get_functor_ptr_ref(to) = func;
      }

      static void move_functor(functor_storage_type& to, functor_storage_type& from)
      {
        Functor* func             = get_functor_ptr(from);
        get_functor_ptr_ref(to)   = func;
        get_functor_ptr_ref(from) = nullptr;
      }

      static void* manager(void* to, void* from, typename FunctionDetailBase::ManagerOperations ops)
      {
        switch(ops)
        {
          case FunctionDetailBase::ManagerOperations::DestroyFunctor:
          {
            destroy_functor(*static_cast<functor_storage_type*>(to));
          }
          break;
          case FunctionDetailBase::ManagerOperations::CopyFunctor:
          {
            copy_functor(*static_cast<functor_storage_type*>(to), *static_cast<const functor_storage_type*>(from));
          }
          break;
          case FunctionDetailBase::ManagerOperations::MoveFunctor:
          {
            move_functor(*static_cast<functor_storage_type*>(to, *static_cast<functor_storage_type>(from)));
          }
          break;
          default: break;
        }

        return nullptr;
      }
    };

    template <typename Functor, typename R, typename... Args>
    class FunctionManager final : public FunctionManagerBase<Functor>
    {
    public:
      using base = FunctionManagerBase<Functor>;

      static R invoker(Args... args, const functor_storage_type& functor)
      {
        return rsl::invoke(*base::get_functor_ptr(functor), rsl::forward<Args>(args)...);
      }
    };

    FunctionDetailBase()  = default;
    ~FunctionDetailBase() = default;

  protected:
    functor_storage_type& storage()
    {
      return m_storage;
    }

  private:
    functor_storage_type m_storage;
  };

  template <count_t, typename>
  class FunctionDetail;

  template <count_t SizeInBytes, typename R, typename... Args>
  class FunctionDetail<SizeInBytes, R(Args...)> : public FunctionDetailBase<SizeInBytes>
  {
  private:
    using base = FunctionDetailBase<SizeInBytes>;

  public:
    FunctionDetail()
        : m_func_ptr_mgr(nullptr)
        , m_func_ptr_invoker(&invoke_bad_func_call)
    {
    }
    FunctionDetail(nullptr_t)
        : m_func_ptr_mgr(nullptr)
        , m_func_ptr_invoker(&invoke_bad_func_call)
    {
    }

    FunctionDetail(const FunctionDetail& other)
    {
      copy(other);
    }
    FunctionDetail(FunctionDetail&& other)
    {
      move(rsl::move(other));
    }
    template <typename Functor>
    FunctionDetail(Functor f)
    {
      create_forward_functor(rsl::move(f));
    }

    ~FunctionDetail()
    {
      destroy();
    }

    FunctionDetail& operator=(const FunctionDetail& other)
    {
      REX_ASSERT_X(this != rsl::addressof(other), "can't copy assign to yourself");

      destroy();
      copy(other);

      return *this;
    }
    FunctionDetail& operator=(FunctionDetail&& other)
    {
      REX_ASSERT_X(this != rsl::addressof(other), "can't move assign to yourself");

      destroy();
      move(rsl::move(other));

      return *this;
    }
    FunctionDetail& operator=(nullptr_t)
    {
      destroy();

      m_func_ptr_mgr     = nullptr;
      m_func_ptr_invoker = &invoke_bad_func_call;

      return *this;
    }
    template <typename Functor>
    FunctionDetail& operator=(Functor&& f)
    {
      destroy();
      create_forward_functor(rsl::forward<Functor>(f));

      return *this;
    }
    template <typename Functor>
    FunctionDetail& operator=(reference_wrapper<Functor> f)
    {
      destroy();
      create_forward_functor(f);

      return *this;
    }

    void swap(FunctionDetail& other)
    {
      REX_ASSERT_X(this != rsl::addressof(other));

      FunctorStorage<SizeInBytes> tmp_storage;
      if(other.has_manager())
      {
        (*other.m_func_ptr_mgr)(static_cast<void*>(&tmp_storage), static_cast<void*>(&other.storage()), base::ManagerOperations::MoveFunctor);
      }

      if(has_manager())
      {
        (*m_func_ptr_mgr)(static_cast<void*>(&other.storage()), static_cast<void*>(&base::storage()), base::ManagerOperations::MoveFunctor);
      }

      if(other.has_manager())
      {
        (*other.m_func_ptr_mgr)(static_cast<void*>(&base::storage()), static_cast<void*>(&tmp_storage), base::ManagerOperations::MoveFunctor);
      }

      rsl::swap(m_func_ptr_mgr, other.m_func_ptr_mgr);
      rsl::swap(m_func_ptr_invoker, other.m_func_ptr_invoker);
    }

    explicit operator bool() const
    {
      return has_manager();
    }

    R operator()(Args... args) const
    {
      return (*m_func_ptr_invoker)(rsl::forward<Args>(args)..., base::storage());
    }

  private:
    bool has_manager() const
    {
      return m_func_ptr_mgr != nullptr;
    }

    void destroy()
    {
      if(has_manager())
      {
        (*m_func_ptr_mgr)(static_cast<void*>(&base::storage()), nullptr, base::ManagerOperations::DestroyFunctor);
      }
    }

    void copy(const FunctionDetail& other)
    {
      if(other.has_manager())
      {
        (*other.m_func_ptr_mgr)(static_cast<void*>(&base::storage()), const_cast<void*>(static_cast<const void*>(&other.storage())), base::ManagerOperations::CopyFunctor);
      }

      m_func_ptr_mgr     = other.m_func_ptr_mgr;
      m_func_ptr_invoker = other.m_func_ptr_invoker;
    }

    void move(FunctionDetail&& other)
    {
      if(other.has_manager())
      {
        (*other.m_func_ptr_mgr)(static_cast<void*>(&base::storage()), static_cast<void*>(other.m_storage), base::ManagerOperations::MoveFunctor);
      }

      m_func_ptr_mgr           = other.m_func_ptr_mgr;
      m_func_ptr_invoker       = other.m_func_ptr_invoker;
      other.m_func_ptr_mgr     = nullptr;
      other.m_func_ptr_invoker = &invoke_bad_func_call;
    }

    template <typename Functor>
    void create_forward_functor(Functor&& f)
    {
      using DecayedFunctorType  = typename rsl::decay<Functor>::type;
      using FunctionManagerType = typename base::template function_manager<DecayedFunctorType, R, Args...>;

      if(is_null(f))
      {
        m_func_ptr_mgr     = nullptr;
        m_func_ptr_invoker = &invoke_bad_func_call;
      }
      else
      {
        m_func_ptr_mgr     = &FunctionManagerType::manager;
        m_func_ptr_invoker = &FunctionManagerType::invoker;
        FunctionManagerType::create_functor(base::storage(), rsl::forward<Functor>(f));
      }
    }

#pragma warning(push)
#pragma warning(disable : 4716) // 'function' must return a value
    static R invoke_bad_func_call(Args..., const base::functor_storage_type&)
    {
      // can't assume R is default constructible, so we disable no-return warning instead.
      REX_ASSERT("Bad function call!");
    }
#pragma warning(pop)

  private:
    using FuncPtrManager = void* (*)(void*, void*, typename base::ManagerOperations);
    using FuncPtrInvoker = R (*)(Args..., const base::functor_storage_type&);

    FuncPtrManager m_func_ptr_mgr;
    FuncPtrInvoker m_func_ptr_invoker;
  };
} // namespace internal

template <typename>
class function;

template <typename R, typename... Args>
class function<R(Args...)> : internal::FunctionDetail<2 * sizeof(void*), R(Args...)>
{
private:
  using base = internal::FunctionDetail<2 * sizeof(void*), R(Args...)>;

public:
  using typename base::result_type;

  // creates an empty function
  function() = default;
  // creates an empty function
  function(nullptr_t p)
      : base(p)
  {
  }
  // copies the target of other to this
  function(const function& other)
      : base(other)
  {
  }
  // moves the target of other to this
  function(function&& other) noexcept
      : base(rsl::move(other))
  {
  }
  // initializes the target with rsl::forward<F>(f)
  template <typename F>
  function(F&& f)
      : base(rsl::move(f))
  {
  }

  // destroys the instance, if this is not empty, the target is also destroyed
  ~function() = default;

  // assigns a copy of target of other as if by execution function(other).swap(*this)
  function& operator=(const function& other)
  {
    base::operator=(other);
    return *this;
  }
  // moves the target of other to this.
  function& operator=(function&& other)
  {
    base::operator=(rsl::move(other));
    return *this;
  }
  // drops the current target, this is empty after the call
  function& operator=(nullptr_t p)
  {
    base::operator=(p);
    return *this;
  }
  // set the target of this to the callable f
  template <typename F>
  function& operator=(F&& f)
  {
    base::operator=(rsl::forward<F>(f));
    return *this;
  }
  // sets the target of this to a copy of f, as if by execution function(f).swap(*this)
  template <typename F>
  function& operator=(reference_wrapper<F> f)
  {
    base::operator=(f);
    return *this;
  }

  // exchanges the stored callable objects of this and other
  void swap(function& other)
  {
    base::swap(other);
  }

  // checks wheter this stores a callable function target, i.e. is not empty
  explicit operator bool() const
  {
    return base::operator bool();
  }

  // invokes the stored callable function target with the parameter args
  R operator()(Args... args) const
  {
    return base::operator()(rsl::forward<Args>(args)...);
  }

  /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Jul/2022)
  // the following functions are not implemented
  // as rsl does not support rtti.
  // returns the type of the stored function
  // const type_info& target_type() const;
  // returns a pointer to the stored callable function
  // template <typename T>
  // T* target();
  // returns a pointer to the stored callable function
  // template <typename T>
  // const T* target() const;
};

// overloads the swap algorithm for function::swap.
template <typename R, typename... Args>
void swap(function<R(Args...)>& lhs, function<R(Args...)>& rhs)
{
  return lhs.swap(rhs);
}

// compares a function with a null pointer. empty functions will return true
template <typename R, typename... Args>
bool operator==(function<R(Args...)>& f, nullptr_t)
{
  return !f;
}

// compares a function with a null pointer. empty functions will return true
template <typename R, typename... Args>
bool operator==(nullptr_t, function<R(Args...)>& f)
{
  return !f;
}

// compares a function with a null pointer. non-empty functions will return true
template <typename R, typename... Args>
bool operator!=(function<R(Args...)>& f, nullptr_t)
{
  return !!f;
}

// compares a function with a null pointer. non-empty functions will return true
template <typename R, typename... Args>
bool operator!=(nullptr_t, function<R(Args...)>& f)
{
  return !!f;
}

template <typename R, typename... Args>
function(R (*)(Args...)) -> function<R(Args...)>;

namespace internal
{

  template <typename Fx, class = void>
  struct DeduceSignature
  {
  }; // can't deduce signature when &Fx::operator() is missing, inaccessible, or ambiguous

  template <typename Fx>
  struct DeduceSignature<Fx, void_t<decltype(&Fx::operator())>> : is_member_function_pointer<decltype(&Fx::operator())>::GuideType
  {
  };
} // namespace internal

template <typename Fx>
function(Fx) -> function<typename internal::DeduceSignature<Fx>::type>;

REX_RSL_END_NAMESPACE
