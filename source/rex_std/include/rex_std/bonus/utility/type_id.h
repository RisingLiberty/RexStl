// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: type_id.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/compiler.h"
#include "rex_std/internal/functional/hash.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/is_arithmetic.h"
#include "rex_std/internal/type_traits/is_class.h"
#include "rex_std/string_view.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      // we have to split create a constexpr and non-constexpr variable here pointing to the func signature
      // because the static_assert expects all variables passed in to be constexpr.
#if defined(RSL_COMPILER_MSVC)
      template <typename T>
      constexpr rsl::string_view msvc_class_type_name()
      {
        rsl::string_view name                = __FUNCSIG__;
        constexpr rsl::string_view func_name = __FUNCSIG__;
        constexpr rsl::string_view prefix    = "class rsl::v1::basic_string_view<char,class rsl::v1::char_traits<char> > __cdecl rsl::v1::internal::msvc_class_type_name<class ";
        constexpr rsl::string_view suffix    = ">(void)";

  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        static_assert(func_name.contains(prefix), "prefix not found in name!");
        static_assert(func_name.contains(suffix), "suffix not found in name!");
  #endif

        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());

        // Return the most inner scope
        // eg rex::MyClass -> MyClass
        auto idx = name.find(':');
        return name.substr(name.find_first_not_of(':', idx));
      }

      template <typename T>
      constexpr rsl::string_view msvc_struct_type_name()
      {
        rsl::string_view name                = __FUNCSIG__;
        constexpr rsl::string_view func_name = __FUNCSIG__;
        constexpr rsl::string_view prefix    = "class rsl::v1::basic_string_view<char,class rsl::v1::char_traits<char> > __cdecl rsl::v1::internal::msvc_struct_type_name<struct ";
        constexpr rsl::string_view suffix    = ">(void)";

  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        static_assert(func_name.contains(prefix), "prefix not found in name!");
        static_assert(func_name.contains(suffix), "suffix not found in name!");
  #endif

        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());

        // Return the most inner scope
        // eg rex::MyClass -> MyClass
        auto idx = name.find(':');
        return name.substr(name.find_first_not_of(':', idx));
      }
      template <typename T>
      constexpr rsl::string_view msvc_structless_type_name()
      {
        rsl::string_view name                = __FUNCSIG__;
        constexpr rsl::string_view func_name = __FUNCSIG__;
        constexpr rsl::string_view prefix    = "class rsl::v1::basic_string_view<char,class rsl::v1::char_traits<char> > __cdecl rsl::v1::internal::msvc_structless_type_name<";
        constexpr rsl::string_view suffix    = ">(void)";

  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        static_assert(func_name.contains(prefix), "prefix not found in name!");
        static_assert(func_name.contains(suffix), "suffix not found in name!");
  #endif

        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());

        // Return the most inner scope
        // eg rex::MyClass -> MyClass
        auto idx = name.find(':');
        return name.substr(name.find_first_not_of(':', idx));
      }

#endif

      template <typename T, rsl::enable_if_t<rsl::is_class_v<T>, bool> = true>
      constexpr rsl::string_view type_name()
      {
#ifdef RSL_COMPILER_CLANG
        rsl::string_view name                = __PRETTY_FUNCTION__;
        constexpr rsl::string_view func_name = __PRETTY_FUNCTION__;
        constexpr rsl::string_view prefix    = "rsl::string_view rsl::internal::type_name() [T = ";
        constexpr rsl::string_view suffix    = "]";

  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        static_assert(func_name.contains(prefix), "prefix not found in name!");
        static_assert(func_name.contains(suffix), "suffix not found in name!");
  #endif

        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());

        // Return the most inner scope
        // eg rex::MyClass -> MyClass
        auto idx = name.find(':');
        return name.substr(name.find_first_not_of(':', idx));

#elif defined(RSL_COMPILER_GCC)
        rsl::string_view name                = __PRETTY_FUNCTION__;
        constexpr rsl::string_view func_name = __PRETTY_FUNCTION__;
        constexpr rsl::string_view prefix    = "rsl::string_view rsl::internal::type_name() [T = ";
        constexpr rsl::string_view suffix    = "]";

  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        static_assert(func_name.contains(prefix), "prefix not found in name!");
        static_assert(func_name.contains(suffix), "suffix not found in name!");
  #endif

        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());

        // Return the most inner scope
        // eg rex::MyClass -> MyClass
        auto idx = name.find(':');
        return name.substr(name.find_first_not_of(':', idx));

#elif defined(RSL_COMPILER_MSVC)
        constexpr rsl::string_view func_name = __FUNCSIG__;
  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        if constexpr(func_name.contains("struct"))
  #else
        if(func_name.contains("type_name<struct"))
  #endif
        {
          return msvc_struct_type_name<T>();
        }
        else if(func_name.contains("type_name<class"))
        {
          return msvc_class_type_name<T>();
        }
        else
        {
          return msvc_structless_type_name<T>();
        }
#else
  #error "Unknown Compiler."
#endif
      }

      template <typename T, rsl::enable_if_t<rsl::is_arithmetic_v<T>, bool> = true>
      constexpr rsl::string_view type_name()
      {
#ifdef RSL_COMPILER_CLANG
        rsl::string_view name                = __PRETTY_FUNCTION__;
        constexpr rsl::string_view func_name = __PRETTY_FUNCTION__;
        constexpr rsl::string_view prefix    = "rsl::string_view rsl::internal::type_name() [T = ";
        constexpr rsl::string_view suffix    = "]";

  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        static_assert(func_name.contains(prefix), "prefix not found in name!");
        static_assert(func_name.contains(suffix), "suffix not found in name!");
  #endif

#elif defined(RSL_COMPILER_GCC)
        rsl::string_view name                = __PRETTY_FUNCTION__;
        constexpr rsl::string_view func_name = __PRETTY_FUNCTION__;
        constexpr rsl::string_view prefix    = "rsl::string_view rsl::internal::type_name() [T = ";
        constexpr rsl::string_view suffix    = "]";

  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        static_assert(func_name.contains(prefix), "prefix not found in name!");
        static_assert(func_name.contains(suffix), "suffix not found in name!");
  #endif

#elif defined(RSL_COMPILER_MSVC)
        rsl::string_view name                = __FUNCSIG__;
        constexpr rsl::string_view func_name = __FUNCSIG__;
        constexpr rsl::string_view prefix    = "class rsl::v1::basic_string_view<char,class rsl::v1::char_traits<char> > __cdecl rsl::v1::internal::type_name<";
        constexpr rsl::string_view suffix    = ",true>(void)";

  #ifndef RSL_ENABLE_ASSERTS // "contains" has an internal assert
        static_assert(func_name.contains(prefix), "prefix not found in name!");
        static_assert(func_name.contains(suffix), "suffix not found in name!");
  #endif

#else
  #error "Unknown Compiler."
#endif

        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());
        return name;
      }
    } // namespace internal

    class type_id_t
    {
    public:
      constexpr type_id_t(rsl::string_view name)
          : m_name(name)
          , m_hash_code(rsl::internal::hash(name.data(), name.length()))
      {
      }

      constexpr rsl::string_view name() const
      {
        return m_name;
      }
      constexpr hash_result hash_code() const
      {
        return m_hash_code;
      }

    private:
      rsl::string_view m_name;
      hash_result m_hash_code;
    };
    constexpr bool operator==(type_id_t lhs, type_id_t rhs)
    {
      return lhs.hash_code() == rhs.hash_code();
    }
    constexpr bool operator!=(type_id_t lhs, type_id_t rhs)
    {
      return !(lhs == rhs);
    }

    template <typename T>
    constexpr type_id_t type_id()
    {
      type_id_t type_id(internal::type_name<T>());
      return type_id;
    }

    template<>
    struct hash<type_id_t>
    {
      constexpr hash_result operator()(type_id_t typeId) const
      {
        return typeId.hash_code();
      }
    };
  } // namespace v1
} // namespace rsl