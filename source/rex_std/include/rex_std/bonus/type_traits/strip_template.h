// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: templated_type.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/remove_cvref.h"

// this class strips the templated class of all template arguments
// this allows to user to convert one templated class to another
// eg. rsl::hash<rsl::string> can be converted to rsl::hash<rsl::string_view
// by using the following code. using type = rsl::change_template_t<rsl::hash<rsl::string>><rsl::string_view>;

// Example usage
// -----------------------------------------------------------------------------------------
//   using first_tuple = std::tuple<int, int, int>;
//   using second_tuple = rsl::change_template_t<first_tuple, float, float>;
//
//   static_assert(rsl::is_same_v<second_tuple, std::tuple<float, float>>, "new type");
//
//   rsl::hash<rsl::string> str_hash;
//   using type = rsl::change_template_t<decltype(str_hash), rsl::string_view>;
//
//   static_assert(rsl::is_same_v<type, rsl::hash<rsl::string_view>>, "new type");
//
//   rsl::unordered_map<rsl::string, int> my_map;
//   rsl::string_view view = "";
//
//   my_map.find(view);
// -----------------------------------------------------------------------------------------

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <typename>
      struct strip_template_impl;

      template <template <typename> class C, typename... TArgs>
      struct strip_template_impl<C<TArgs...>>
      {
        template <typename... UArgs>
        using type = C<UArgs...>;
      };
    } // namespace internal

    template <typename C>
    struct strip_template : internal::strip_template_impl<rsl::remove_cvref_t<C>>
    {
    };

    // the following code doesn't make sense as it'd return a stripped down template type
    // which is not allowed in C++
    // template <typename C>
    // using strip_template_t = strip_template<C>::type;

    // this is a utility function to make it easier for the user to switch template types
    template <typename C, typename... Args>
    using change_template_t = typename strip_template<C>::template type<Args...>;
  } // namespace v1
} // namespace rsl
