#pragma once

#include "rex_std/internal/format/fmt_defines.h"
#include "rex_std/internal/string/basic_string.h"
#include "rex_std/internal/string_view/basic_string_view.h"
#include "rex_std/internal/type_traits/is_base_of.h"
#include "rex_std/internal/type_traits/is_reference.h"
#include "rex_std/internal/type_traits/remove_reference.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename OutputIt, typename Char>
    class basic_format_context;

    namespace detail
    {
      struct view
      {
      };

      // A base class for compile-time strings.
      struct compile_string
      {
      };

      template <typename S>
      struct is_compile_string : rsl::is_base_of<compile_string, S>
      {
      };

      template <typename Char, typename ErrorHandler>
      class compile_parse_context;

      inline constexpr int invalid_arg_index = -1;

      enum class type
      {
        none_type,
        // Integer types should go first,
        int_type,
        uint_type,
        long_long_type,
        ulong_long_type,
        int128_type,
        uint128_type,
        bool_type,
        char_type,
        last_integer_type = char_type,
        // followed by floating-point types.
        float_type,
        double_type,
        long_double_type,
        last_numeric_type = long_double_type,
        cstring_type,
        string_type,
        pointer_type,
        custom_type
      };

      struct error_handler;

      template <bool IsConstexpr, typename Char, typename Handler>
      FMT_CONSTEXPR FMT_INLINE void parse_format_string(basic_string_view<Char> formatStr, Handler&& handler);

      template <typename Char, typename SpecHandler>
      FMT_CONSTEXPR FMT_INLINE const Char* parse_format_specs(const Char* begin, const Char* end, SpecHandler&& handler);

      template <typename T, typename ParseContext>
      FMT_CONSTEXPR auto parse_format_specs(ParseContext& ctx) -> decltype(rsl::iterator_to_pointer(ctx.begin()));

      // Maps core type T to the corresponding type enum constant.
      template <typename T, typename Char>
      struct type_constant : rsl::integral_constant<type, type::custom_type>
      {
      };

      template <typename Context>
      struct arg_mapper;

      // A type constant after applying arg_mapper<Context>.
      template <typename T, typename Context>
      using mapped_type_constant = type_constant<decltype(arg_mapper<Context>().map(rsl::declval<const T&>())), typename Context::char_type>;

      template <typename Char, typename ErrorHandler, typename... Args>
      class format_string_checker
      {
      private:
        // In the future basic_format_parse_context will replace compile_parse_context
        // here and will use is_constant_evaluated and downcasting to access the data
        // needed for compile-time checks: https://godbolt.org/z/GvWzcTjh1.
        using parse_context_type      = compile_parse_context<Char, ErrorHandler>;
        static constexpr int num_args = sizeof...(Args);

        // Format specifier parsing function.
        using parse_func = const Char* (*)(parse_context_type&);

        parse_context_type m_context;
        parse_func m_parse_funcs[num_args > 0 ? static_cast<count_t>(num_args) : 1]; // NOLINT(modernize-avoid-c-arrays)
        type m_types[num_args > 0 ? static_cast<count_t>(num_args) : 1];             // NOLINT(modernize-avoid-c-arrays)

      public:
        explicit FMT_CONSTEXPR format_string_checker(basic_string_view<Char> formatStr, ErrorHandler eh)
            : m_context(formatStr, num_args, m_types, eh)
            , m_parse_funcs {&parse_format_specs<Args, parse_context_type>...}
            , m_types {mapped_type_constant<Args, basic_format_context<Char*, Char>>::value...}
        {
        }

        FMT_CONSTEXPR void on_text(const Char* /*unused*/, const Char* /*unused*/) {}

        FMT_CONSTEXPR int on_arg_id()
        {
          return m_context.next_arg_id();
        }
        FMT_CONSTEXPR int on_arg_id(int id)
        {
          return m_context.check_arg_id(id), id;
        }
        FMT_CONSTEXPR int on_arg_id(basic_string_view<Char> id)
        {
#if FMT_USE_NONTYPE_TEMPLATE_ARGS
          auto index = get_arg_index_by_name<Args...>(id);
          if(index == invalid_arg_index)
            on_error("named argument is not found");
          return m_context.check_arg_id(index), index;
#else
          (void)id;
          on_error("compile-time checks for named arguments require C++20 support");
          return 0;
#endif
        }

        FMT_CONSTEXPR void on_replacement_field(int /*unused*/, const Char* /*unused*/) {}

        FMT_CONSTEXPR const Char* on_format_specs(int id, const Char* begin, const Char* /*unused*/)
        {
          m_context.advance_to(m_context.begin() + (static_cast<count_t>(begin - &*m_context.begin())));
          // id >= 0 check is a workaround for gcc 10 bug (#2065).
          return id >= 0 && id < num_args ? m_parse_funcs[id](m_context) : begin; // NOLINT(misc-redundant-expression)
        }

        FMT_CONSTEXPR void on_error(const char* message)
        {
          m_context.on_error(message);
        }
      };

      // Reports a compile-time error if S is not a valid format string.
      template <typename..., typename S, FMT_ENABLE_IF(!is_compile_string<S>::value)>
      FMT_INLINE void check_format_string(const S& /*unused*/)
      {
#ifdef FMT_ENFORCE_COMPILE_STRING
        static_assert(is_compile_string<S>::value, "FMT_ENFORCE_COMPILE_STRING requires all format strings to use "
                                                   "FMT_STRING.");
#endif
      }
      template <typename... Args, typename S, FMT_ENABLE_IF(is_compile_string<S>::value)>
      void check_format_string(S formatStr)
      {
        FMT_CONSTEXPR auto s              = basic_string_view<typename S::char_type>(formatStr);
        using checker                     = format_string_checker<typename S::char_type, error_handler, remove_cvref_t<Args>...>;
        FMT_CONSTEXPR bool invalid_format = (parse_format_string<true>(s, checker(s, {})), true);
        ignore_unused(invalid_format);
      }

      template <bool B = false>
      constexpr count_t count()
      {
        return B ? 1 : 0;
      }
      template <bool B1, bool B2, bool... Tail>
      constexpr count_t count()
      {
        return (B1 ? 1 : 0) + count<B2, Tail...>();
      }
    } // namespace detail

    template <typename Char>
    struct basic_runtime
    {
      basic_string_view<Char, rsl::char_traits<Char>> str;
    };

    /** A compile-time format string. */
    template <typename Char, typename... Args>
    class basic_format_string
    {
    private:
      basic_string_view<Char, rsl::char_traits<Char>> m_str;

    public:
      template <typename S, FMT_ENABLE_IF(rsl::is_convertible<const S&, basic_string_view<Char, rsl::char_traits<Char>>>::value)>
      FMT_CONSTEVAL FMT_INLINE basic_format_string(const S& s) // NOLINT(google-explicit-constructor)
          : m_str(s)
      {
        static_assert(detail::count<(rsl::is_base_of<detail::view, remove_reference_t<Args>>::value && rsl::is_reference<Args>::value)...>() == 0, "passing views as lvalues is disallowed");
#ifdef FMT_HAS_CONSTEVAL
        if constexpr(detail::count_named_args<Args...>() == detail::count_statically_named_args<Args...>())
        {
          using checker = detail::format_string_checker<Char, detail::error_handler, remove_cvref_t<Args>...>;
          detail::parse_format_string<true>(m_str, checker(s, {}));
        }
#else
        detail::check_format_string<Args...>(s);
#endif
      }
      basic_format_string(basic_runtime<Char> r) // NOLINT(google-explicit-constructor)
          : m_str(r.str)
      {
      }

      FMT_INLINE operator basic_string_view<Char, rsl::char_traits<Char>>() const // NOLINT(google-explicit-constructor)
      {
        return m_str;
      }
    };

#if FMT_GCC_VERSION && FMT_GCC_VERSION < 409
    // Workaround broken conversion on older gcc.
    template <typename...>
    using format_string = string_view;
    inline auto runtime(string_view s) -> string_view
    {
      return s;
    }
#else
    template <typename... Args>
    using format_string = basic_format_string<char, type_identity_t<Args>...>;
    /**
      \rst
      Creates a runtime format string.

      **Example**::

        // Check format string at runtime instead of compile-time.
        rsl::print(rsl::runtime("{:d}"), "I am not a number");
      \endrst
     */
    inline basic_runtime<char> runtime(string_view s)
    {
      return {{s}};
    }
#endif

  } // namespace v1
} // namespace rsl