// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: not_fn.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

REX_RSL_BEGIN_NAMESPACE

namespace internal
{
  template <typename F>
  struct NotFnType
  {
    F f;
    template <typename... Args>
    constexpr auto operator()(Args&&... args) & noexcept(noexcept(!rsl::invoke(f, rsl::forward<Args>(args)...))) -> decltype(!rsl::invoke(f, rsl::forward<Args>(args)...))
    {
      return !rsl::invoke(f, rsl::forward<Args>(args)...);
    }

    template <typename... Args>
    constexpr auto operator()(Args&&... args) const& noexcept(noexcept(!rsl::invoke(f, rsl::forward<Args>(args)...))) -> decltype(!rsl::invoke(f, rsl::forward<Args>(args)...))
    {
      return !rsl::invoke(f, rsl::forward<Args>(args)...);
    }

    template <typename... Args>
    constexpr auto operator()(Args&&... args) && noexcept(noexcept(!rsl::invoke(rsl::move(f), rsl::forward<Args>(args)...))) -> decltype(!rsl::invoke(rsl::move(f), rsl::forward<Args>(args)...))
    {
      return !rsl::invoke(rsl::move(f), rsl::forward<Args>(args)...);
    }

    template <typename... Args>
    constexpr auto operator()(Args&&... args) const&& noexcept(noexcept(!rsl::invoke(rsl::move(f), rsl::forward<Args>(args)...))) -> decltype(!rsl::invoke(rsl::move(f), rsl::forward<Args>(args)...))
    {
      return !rsl::invoke(rsl::move(f), rsl::forward<Args>(args)...);
    }
  };
} // namespace internal

// Creates a forwarding call wrapper that returns the negation of the callable object it holds.
template <typename F>
constexpr internal::NotFnType<rsl::decay<F>> not_fn(F&& f)
{
  return {rsl::forward<F>(f)};
}

REX_RSL_END_NAMESPACE
