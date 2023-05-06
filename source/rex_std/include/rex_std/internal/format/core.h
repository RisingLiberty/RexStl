// Formatting library for C++ - the core API for char/UTF-8
//
// Copyright (c) 2012 - present, Victor Zverovich
// All rights reserved.
//
// For the license information refer to format.h.

// NOLINTBEGIN

#ifndef FMT_CORE_H_
#define FMT_CORE_H_

#include "rex_std/internal/format/fmt_defines.h"
#include "rex_std/internal/format/fmt_string.h"
#include "rex_std/internal/iterator/back_insert_iterator.h"
#include "rex_std/internal/string/basic_string.h"
#include "rex_std/internal/string/memchr.h"
#include "rex_std/internal/string_view/basic_string_view.h"
#include "rex_std/internal/sstream/basic_sstream.h"
#include "rex_std/internal/type_traits/is_class.h"
#include "rex_std/internal/type_traits/is_constant_evaluated.h"
#include "rex_std/internal/type_traits/is_convertible.h"
#include "rex_std/internal/type_traits/is_function.h"
#include "rex_std/internal/type_traits/is_pointer.h"
#include "rex_std/internal/type_traits/remove_cvref.h"
#include "rex_std/internal/type_traits/remove_pointer.h"
#include "rex_std/internal/type_traits/underlying_type.h"

#include <cstddef> // rsl::byte
#include <cstdio>  // std::FILE
#include <cstring> // rsl::strlen
#include <iterator>
#include <limits>
#include <string>
#include <type_traits>

FMT_BEGIN_NAMESPACE
FMT_MODULE_EXPORT_BEGIN

FMT_BEGIN_DETAIL_NAMESPACE

// Suppresses "unused variable" warnings with the method described in
// https://herbsutter.com/2009/10/18/mailbag-shutting-up-compiler-warnings/.
// (void)var does not work on many Intel compilers.
template <typename... T>
FMT_CONSTEXPR void ignore_unused(const T&... /*unused*/)
{
}

constexpr FMT_INLINE auto is_constant_evaluated(bool defaultValue = false) noexcept -> bool
{
#ifdef __cpp_lib_is_constant_evaluated
  ignore_unused(defaultValue);
  return rsl::is_constant_evaluated();
#else
  return defaultValue;
#endif
}

// Suppresses "conditional expression is constant" warnings.
template <typename T>
constexpr FMT_INLINE auto const_check(T value) -> T
{
  return value;
}

FMT_NORETURN FMT_API void assert_fail(const char* file, int line, const char* message);

#ifndef FMT_ASSERT
  #ifdef NDEBUG
    // FMT_ASSERT is not empty to avoid -Wempty-body.
    #define FMT_ASSERT(condition, message) ::rsl::detail::ignore_unused((condition), (message))
  #else
    #define FMT_ASSERT(condition, message)                                                                                                                                                                                                               \
      ((condition) /* void() fails with -Winvalid-constexpr on clang 4.0.1 */                                                                                                                                                                            \
           ? (void)0                                                                                                                                                                                                                                     \
           : ::rsl::detail::assert_fail(__FILE__, __LINE__, (message)))
  #endif
#endif

#if defined(FMT_USE_STRING_VIEW)
template <typename Char>
using std_string_view = rsl::basic_string_view<Char>;
#elif defined(FMT_USE_EXPERIMENTAL_STRING_VIEW)
template <typename Char>
using std_string_view = rsl::experimental::basic_string_view<Char>;
#else
template <typename T>
struct std_string_view
{
};
#endif

#ifdef FMT_USE_INT128
// Do nothing.
#elif defined(__SIZEOF_INT128__) && !defined(__NVCC__) && !(FMT_CLANG_VERSION && FMT_MSC_VERSION)
  #define FMT_USE_INT128 1
using int128_opt = __int128_t; // An optional native 128-bit integer.
using uint128_opt = __uint128_t;
template <typename T>
inline auto convert_for_visit(T value) -> T
{
  return value;
}
#else
  #define FMT_USE_INT128 0
#endif
#if !FMT_USE_INT128
enum class int128_opt
{
};
enum class uint128_opt
{
};
// Reduce template instantiations.
template <typename T>
auto convert_for_visit(T /*unused*/) -> monostate
{
  return {};
}
#endif

// Casts a nonnegative integer to unsigned.
template <typename Int>
FMT_CONSTEXPR auto to_unsigned(Int value) -> typename rsl::make_unsigned<Int>::type
{
  FMT_ASSERT(rsl::is_unsigned<Int>::value || value >= 0, "negative value");
  return static_cast<typename rsl::make_unsigned<Int>::type>(value);
}

FMT_MSC_WARNING(suppress : 4566) constexpr unsigned char micro[] = "\u00B5"; // NOLINT(modernize-avoid-c-arrays)

constexpr auto is_utf8() -> bool
{
  // Avoid buggy sign extensions in MSVC's constant evaluation mode (#2297).
  using uchar = unsigned char;
  return FMT_UNICODE || (sizeof(micro) == 3 && uchar(micro[0]) == 0xC2 && uchar(micro[1]) == 0xB5); // NOLINT(google-readability-casting)
}
FMT_END_DETAIL_NAMESPACE

/** Specifies if ``T`` is a character type. Can be specialized by users. */
template <typename T>
struct is_char : rsl::false_type
{
};
template <>
struct is_char<char> : rsl::true_type
{
};

FMT_BEGIN_DETAIL_NAMESPACE

// Returns a string view of `s`.
template <typename Char, FMT_ENABLE_IF(is_char<Char>::value)>
FMT_INLINE auto to_string_view(const Char* s) -> basic_string_view<Char>
{
  return basic_string_view<Char>(s);
}
template <typename Char, typename Traits, typename Alloc>
inline auto to_string_view(const rsl::basic_string<Char, Traits, Alloc>& s) -> basic_string_view<Char>
{
  return s;
}
template <typename Char>
constexpr auto to_string_view(basic_string_view<Char> s) -> basic_string_view<Char>
{
  return s;
}
// template <typename Char,
//           FMT_ENABLE_IF(!rsl::is_empty<std_string_view<Char>>::value)>
// inline auto to_string_view(std_string_view<Char> s) -> basic_string_view<Char> {
//   return s;
// }
template <typename S, FMT_ENABLE_IF(is_compile_string<S>::value)>
constexpr auto to_string_view(const S& s) -> basic_string_view<typename S::char_type>
{
  return basic_string_view<typename S::char_type>(s);
}
void to_string_view(...);

// Specifies whether S is a string type convertible to rsl::basic_string_view.
// It should be a constexpr function but MSVC 2017 fails to compile it in
// enable_if and MSVC 2015 fails to compile it as an alias template.
// ADL invocation of to_string_view is DEPRECATED!
template <typename S>
struct is_string : rsl::is_class<decltype(to_string_view(rsl::declval<S>()))>
{
};

template <typename S, typename = void>
struct char_t_impl
{
};
template <typename S>
struct char_t_impl<S, enable_if_t<is_string<S>::value>>
{
  using result = decltype(to_string_view(rsl::declval<S>()));
  using type   = typename result::value_type;
};

#define FMT_TYPE_CONSTANT(Type, constant)                                                                                                                                                                                                                \
  template <typename Char>                                                                                                                                                                                                                               \
  struct type_constant<Type, Char> : rsl::integral_constant<type, type::constant>                                                                                                                                                                        \
  {                                                                                                                                                                                                                                                      \
  }

FMT_TYPE_CONSTANT(int, int_type);
FMT_TYPE_CONSTANT(unsigned, uint_type);
FMT_TYPE_CONSTANT(long long, long_long_type);
FMT_TYPE_CONSTANT(unsigned long long, ulong_long_type);
FMT_TYPE_CONSTANT(int128_opt, int128_type);
FMT_TYPE_CONSTANT(uint128_opt, uint128_type);
FMT_TYPE_CONSTANT(bool, bool_type);
FMT_TYPE_CONSTANT(Char, char_type);
FMT_TYPE_CONSTANT(float, float_type);
FMT_TYPE_CONSTANT(double, double_type);
FMT_TYPE_CONSTANT(long double, long_double_type);
FMT_TYPE_CONSTANT(const Char*, cstring_type);
FMT_TYPE_CONSTANT(basic_string_view<Char>, string_type);
FMT_TYPE_CONSTANT(const void*, pointer_type);

constexpr bool is_integral_type(type t)
{
  return t > type::none_type && t <= type::last_integer_type;
}

constexpr bool is_arithmetic_type(type t)
{
  return t > type::none_type && t <= type::last_numeric_type;
}

FMT_API void throw_format_error(const char* message);

struct error_handler
{
  constexpr error_handler()                     = default;
  constexpr error_handler(const error_handler&) = default;

  ~error_handler() = default;

  error_handler& operator=(const error_handler&) = default;

  // This function is intentionally not constexpr to give a compile-time error.
  FMT_NORETURN void on_error(const char* message) // NOLINT(readability-convert-member-functions-to-static)
  {
    throw_format_error(message);
  }
};
FMT_END_DETAIL_NAMESPACE

/** String's character type. */
template <typename S>
using char_t = typename detail::char_t_impl<S>::type;

/**
  \rst
  Parsing context consisting of a format string range being parsed and an
  argument counter for automatic indexing.
  You can use the ``format_parse_context`` type alias for ``char`` instead.
  \endrst
 */
template <typename Char, typename ErrorHandler = detail::error_handler>
class basic_format_parse_context : private ErrorHandler
{
private:
  basic_string_view<Char> m_format_str;
  int m_next_arg_id;

  FMT_CONSTEXPR void do_check_arg_id(int id);

public:
  using char_type = Char;
  using iterator  = typename basic_string_view<Char>::iterator;

  explicit constexpr basic_format_parse_context(basic_string_view<Char> formatStr, ErrorHandler eh = {}, int nextArgId = 0)
      : ErrorHandler(eh)
      , m_format_str(formatStr)
      , m_next_arg_id(nextArgId)
  {
  }

  /**
    Returns an iterator to the beginning of the format string range being
    parsed.
   */
  constexpr auto begin() const noexcept -> iterator
  {
    return m_format_str.begin();
  }

  /**
    Returns an iterator past the end of the format string range being parsed.
   */
  constexpr auto end() const noexcept -> iterator
  {
    return m_format_str.end();
  }

  /** Advances the begin iterator to ``it``. */
  FMT_CONSTEXPR void advance_to(iterator it)
  {
    m_format_str.remove_prefix(detail::to_unsigned(static_cast<count_t>(it - begin())));
  }

  /**
    Reports an error if using the manual argument indexing; otherwise returns
    the next argument index and switches to the automatic indexing.
   */
  FMT_CONSTEXPR auto next_arg_id() -> int
  {
    if(m_next_arg_id < 0)
    {
      on_error("cannot switch from manual to automatic argument indexing");
      return 0;
    }
    const int id = m_next_arg_id++;
    do_check_arg_id(id);
    return id;
  }

  /**
    Reports an error if using the automatic argument indexing; otherwise
    switches to the manual indexing.
   */
  FMT_CONSTEXPR void check_arg_id(int id)
  {
    if(m_next_arg_id > 0)
    {
      on_error("cannot switch from automatic to manual argument indexing");
      return;
    }
    m_next_arg_id = -1;
    do_check_arg_id(id);
  }
  FMT_CONSTEXPR void check_arg_id(basic_string_view<Char> /*unused*/) {}
  FMT_CONSTEXPR void check_dynamic_spec(int argId);

  FMT_CONSTEXPR void on_error(const char* message)
  {
    ErrorHandler::on_error(message);
  }

  constexpr auto error_handler() const -> const ErrorHandler&
  {
    return *this;
  }
};

using format_parse_context = basic_format_parse_context<char>;

FMT_BEGIN_DETAIL_NAMESPACE
// A parse context with extra data used only in compile-time checks.
template <typename Char, typename ErrorHandler = detail::error_handler>
class compile_parse_context : public basic_format_parse_context<Char, ErrorHandler>
{
private:
  int m_num_args;
  const type* m_types;
  using base = basic_format_parse_context<Char, ErrorHandler>;

public:
  explicit FMT_CONSTEXPR compile_parse_context(basic_string_view<Char> formatStr, int numArgs, const type* types, ErrorHandler eh = {}, int nextArgId = 0)
      : base(formatStr, eh, nextArgId)
      , m_num_args(numArgs)
      , m_types(types)
  {
  }

  constexpr auto num_args() const -> int
  {
    return m_num_args;
  }
  constexpr auto arg_type(int id) const -> type
  {
    return m_types[id];
  }

  FMT_CONSTEXPR auto next_arg_id() -> int
  {
    const int id = base::next_arg_id();
    if(id >= m_num_args)
      this->on_error("argument not found");
    return id;
  }

  FMT_CONSTEXPR void check_arg_id(int id)
  {
    base::check_arg_id(id);
    if(id >= m_num_args)
      this->on_error("argument not found");
  }
  using base::check_arg_id;

  FMT_CONSTEXPR void check_dynamic_spec(int argId)
  {
    if(argId < m_num_args && m_types && !is_integral_type(m_types[argId])) // NOLINT(readability-implicit-bool-conversion)
      this->on_error("width/precision is not integer");
  }
};
FMT_END_DETAIL_NAMESPACE

template <typename Char, typename ErrorHandler>
FMT_CONSTEXPR void basic_format_parse_context<Char, ErrorHandler>::do_check_arg_id(int id)
{
  // Argument id is only checked at compile-time during parsing because
  // formatting has its own validation.
  if(detail::is_constant_evaluated() && FMT_GCC_VERSION >= 1200)
  {
    using context = detail::compile_parse_context<Char, ErrorHandler>;
    if(id >= static_cast<context*>(this)->num_args())
      on_error("argument not found");
  }
}

template <typename Char, typename ErrorHandler>
FMT_CONSTEXPR void basic_format_parse_context<Char, ErrorHandler>::check_dynamic_spec(int argId)
{
  if(detail::is_constant_evaluated())
  {
    using context = detail::compile_parse_context<Char, ErrorHandler>;
    static_cast<context*>(this)->check_dynamic_spec(argId);
  }
}

template <typename Context>
class basic_format_arg;
template <typename Context>
class basic_format_args;
template <typename Context>
class dynamic_format_arg_store;

/// RSL Comment: Different from ISO C++ Standard at time of writing (06/May/2023)
// This is the generic formatter which uses the result of writng T to ostream
// and uses that as a format
template <typename T, typename Char = char, typename Enable = void>
struct formatter
{
  auto parse(format_parse_context& ctx) const -> decltype(ctx.begin()) // NOLINT(readability-convert-member-functions-to-static)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const T& val, FormatContext& ctx) -> decltype(ctx.out())
  {
    rsl::stringstream ss;
    ss << val;
    return format_to(ctx.out(), "{}", ss.view());
  }
};

// Specifies if T has an enabled formatter specialization. A type can be
// formattable even if it doesn't have a formatter e.g. via a conversion.
template <typename T, typename Context>
using has_formatter = rsl::is_constructible<typename Context::template formatter_type<T>>;

// Checks whether T is a container with contiguous storage.
template <typename T>
struct is_contiguous : rsl::false_type
{
};
template <typename Char>
struct is_contiguous<rsl::basic_string<Char, rsl::char_traits<Char>, rsl::allocator>> : rsl::true_type
{
};

class appender;

FMT_BEGIN_DETAIL_NAMESPACE

template <typename Context, typename T>
constexpr auto has_const_formatter_impl(T* /*unused*/) -> decltype(typename Context::template formatter_type<T>().format(rsl::declval<const T&>(), rsl::declval<Context&>()), true)
{
  return true;
}
template <typename Context>
constexpr auto has_const_formatter_impl(...) -> bool
{
  return false;
}
template <typename T, typename Context>
constexpr auto has_const_formatter() -> bool
{
  return has_const_formatter_impl<Context>(static_cast<T*>(nullptr));
}

// Extracts a reference to the container from back_insert_iterator.
template <typename Container>
inline auto get_container(rsl::back_insert_iterator<Container> it) -> Container&
{
  using base = rsl::back_insert_iterator<Container>;
  struct accessor : base
  {
    accessor(base b) // NOLINT(google-explicit-constructor)
        : base(b)
    {
    }
    using base::container;
  };
  return *accessor(it).container();
}

template <typename Char, typename InputIt, typename OutputIt>
FMT_CONSTEXPR auto copy_str(InputIt begin, InputIt end, OutputIt out) -> OutputIt
{
  while(begin != end)
    *out++ = static_cast<Char>(*begin++);
  return out;
}

template <typename Char, typename T, typename U, FMT_ENABLE_IF(rsl::is_same<remove_const_t<T>, U>::value&& is_char<U>::value)>
FMT_CONSTEXPR auto copy_str(T* begin, T* end, U* out) -> U*
{
  if(is_constant_evaluated())
    return copy_str<Char, T*, U*>(begin, end, out);
  auto size = to_unsigned(end - begin);
  memcpy(out, begin, static_cast<count_t>(size * sizeof(U)));
  return out + size;
}

/**
  \rst
  A contiguous memory buffer with an optional growing ability. It is an internal
  class and shouldn't be used directly, only via `~rsl::basic_memory_buffer`.
  \endrst
 */
template <typename T>
class buffer
{
private:
  T* m_ptr;
  count_t m_size;
  count_t m_capacity;

protected:
  // Don't initialize ptr_ since it is not accessed to save a few cycles.
  FMT_MSC_WARNING(suppress : 26495)
  buffer(count_t sz) noexcept // NOLINT(google-explicit-constructor)
      : m_size(sz)
      , m_capacity(sz)
  {
  }

  FMT_CONSTEXPR20 buffer(T* p = nullptr, count_t sz = 0, count_t cap = 0) noexcept // NOLINT(google-explicit-constructor)
      : m_ptr(p)
      , m_size(sz)
      , m_capacity(cap)
  {
  }

  FMT_CONSTEXPR20 ~buffer()   = default;
  buffer(buffer&&)            = default;
  buffer& operator=(buffer&&) = default;

  /** Sets the buffer data and capacity. */
  FMT_CONSTEXPR void set(T* bufData, count_t bufCapacity) noexcept
  {
    m_ptr      = bufData;
    m_capacity = bufCapacity;
  }

  /** Increases the buffer capacity to hold at least *capacity* elements. */
  virtual FMT_CONSTEXPR20 void grow(count_t capacity) = 0;

public:
  using value_type      = T;
  using const_reference = const T&;

  buffer(const buffer&)         = delete;
  void operator=(const buffer&) = delete;

  auto begin() noexcept -> T*
  {
    return m_ptr;
  }
  auto end() noexcept -> T*
  {
    return m_ptr + m_size;
  }

  auto begin() const noexcept -> const T*
  {
    return m_ptr;
  }
  auto end() const noexcept -> const T*
  {
    return m_ptr + m_size;
  }

  /** Returns the size of this buffer. */
  constexpr auto size() const noexcept -> count_t
  {
    return m_size;
  }

  /** Returns the capacity of this buffer. */
  constexpr auto capacity() const noexcept -> count_t
  {
    return m_capacity;
  }

  /** Returns a pointer to the buffer data. */
  FMT_CONSTEXPR auto data() noexcept -> T*
  {
    return m_ptr;
  }

  /** Returns a pointer to the buffer data. */
  FMT_CONSTEXPR auto data() const noexcept -> const T*
  {
    return m_ptr;
  }

  /** Clears this buffer. */
  void clear()
  {
    m_size = 0;
  }

  // Tries resizing the buffer to contain *count* elements. If T is a POD type
  // the new elements may not be initialized.
  FMT_CONSTEXPR20 void try_resize(count_t count)
  {
    try_reserve(count);
    m_size = count <= m_capacity ? count : m_capacity;
  }

  // Tries increasing the buffer capacity to *new_capacity*. It can increase the
  // capacity by a smaller amount than requested but guarantees there is space
  // for at least one additional element either by increasing the capacity or by
  // flushing the buffer if it is full.
  FMT_CONSTEXPR20 void try_reserve(count_t newCapacity)
  {
    if(newCapacity > m_capacity)
      grow(newCapacity);
  }

  FMT_CONSTEXPR20 void push_back(const T& value)
  {
    try_reserve(m_size + 1);
    m_ptr[m_size++] = value;
  }

  /** Appends data to the end of the buffer. */
  template <typename U>
  void append(const U* begin, const U* end);

  template <typename Idx>
  FMT_CONSTEXPR auto operator[](Idx index) -> T&
  {
    return m_ptr[index];
  }
  template <typename Idx>
  FMT_CONSTEXPR auto operator[](Idx index) const -> const T&
  {
    return m_ptr[index];
  }
};

struct buffer_traits
{
  explicit buffer_traits(count_t /*unused*/) {}
  auto count() const -> count_t // NOLINT(readability-convert-member-functions-to-static)
  {
    return 0;
  }
  auto limit(count_t size) -> count_t // NOLINT(readability-convert-member-functions-to-static)
  {
    return size;
  }
};

class fixed_buffer_traits
{
private:
  count_t m_count = 0;
  count_t m_limit;

public:
  explicit fixed_buffer_traits(count_t limit)
      : m_limit(limit)
  {
  }
  auto count() const -> count_t
  {
    return m_count;
  }
  auto limit(count_t size) -> count_t
  {
    const count_t n = m_limit > m_count ? m_limit - m_count : 0;
    m_count += size;
    return size < n ? size : n;
  }
};

// A buffer that writes to an output iterator when flushed.
template <typename OutputIt, typename T, typename Traits = buffer_traits>
class iterator_buffer final : public Traits, public buffer<T>
{
private:
  OutputIt m_out;
  enum
  {
    buffer_size = 256
  };
  T m_data[buffer_size]; // NOLINT(modernize-avoid-c-arrays)

protected:
  FMT_CONSTEXPR20 void grow(count_t /*unused*/) override
  {
    if(this->size() == buffer_size)
      flush();
  }

  void flush()
  {
    auto size = this->size();
    this->clear();
    m_out = copy_str<T>(m_data, m_data + this->limit(size), m_out);
  }

public:
  explicit iterator_buffer(OutputIt out, count_t n = buffer_size)
      : Traits(n)
      , buffer<T>(m_data, 0, buffer_size)
      , m_out(out)
  {
  }
  iterator_buffer(const iterator_buffer&) = delete;
  iterator_buffer(iterator_buffer&& other)
      : Traits(other)
      , buffer<T>(m_data, 0, buffer_size)
      , m_out(other.m_out)
  {
  }
  ~iterator_buffer()
  {
    flush();
  }

  iterator_buffer& operator=(const iterator_buffer&) = delete;
  iterator_buffer& operator=(iterator_buffer&&)      = delete;

  auto out() -> OutputIt
  {
    flush();
    return m_out;
  }
  auto count() const -> count_t
  {
    return Traits::count() + this->size();
  }
};

template <typename T>
class iterator_buffer<T*, T, fixed_buffer_traits> final : public fixed_buffer_traits, public buffer<T>
{
private:
  T* m_out;
  enum
  {
    buffer_size = 256
  };
  T m_data[buffer_size]; // NOLINT(modernize-avoid-c-arrays)

protected:
  FMT_CONSTEXPR20 void grow(count_t /*unused*/) override
  {
    if(this->size() == this->capacity())
      flush();
  }

  void flush()
  {
    count_t n = this->limit(this->size());
    if(this->data() == m_out)
    {
      m_out += n;
      this->set(m_data, buffer_size);
    }
    this->clear();
  }

public:
  explicit iterator_buffer(T* out, count_t n = buffer_size)
      : fixed_buffer_traits(n)
      , buffer<T>(out, 0, n)
      , m_out(out)
  {
  }
  iterator_buffer(const iterator_buffer&) = delete;
  iterator_buffer(iterator_buffer&& other)
      : fixed_buffer_traits(other)
      , buffer<T>(rsl::move(other))
      , m_out(other.m_out)
  {
    if(this->data() != m_out)
    {
      this->set(m_data, buffer_size);
      this->clear();
    }
  }
  ~iterator_buffer()
  {
    flush();
  }

  iterator_buffer& operator=(iterator_buffer&)  = delete;
  iterator_buffer& operator=(iterator_buffer&&) = default;

  auto out() -> T*
  {
    flush();
    return m_out;
  }
  auto count() const -> count_t
  {
    return fixed_buffer_traits::count() + this->size();
  }
};

template <typename T>
class iterator_buffer<T*, T> final : public buffer<T>
{
protected:
  FMT_CONSTEXPR20 void grow(count_t /*unused*/) override {}

public:
  explicit iterator_buffer(T* out, count_t /*unused*/ = 0)
      : buffer<T>(out, 0, ~count_t())
  {
  }

  auto out() -> T*
  {
    return &*this->end();
  }
};

// A buffer that writes to a container with the contiguous storage.
template <typename Container>
class iterator_buffer<rsl::back_insert_iterator<Container>, enable_if_t<is_contiguous<Container>::value, typename Container::value_type>> final : public buffer<typename Container::value_type>
{
private:
  Container& m_container; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

protected:
  FMT_CONSTEXPR20 void grow(count_t capacity) override
  {
    m_container.resize(capacity);
    this->set(&m_container[0], capacity);
  }

public:
  explicit iterator_buffer(Container& c)
      : buffer<typename Container::value_type>(c.size())
      , m_container(c)
  {
  }
  explicit iterator_buffer(rsl::back_insert_iterator<Container> out, count_t /*unused*/ = 0)
      : iterator_buffer(get_container(out))
  {
  }

  auto out() -> rsl::back_insert_iterator<Container>
  {
    return rsl::back_inserter(m_container);
  }
};

// A buffer that counts the number of code units written discarding the output.
template <typename T = char>
class counting_buffer final : public buffer<T>
{
private:
  enum
  {
    buffer_size = 256
  };
  T m_data[buffer_size]; // NOLINT(modernize-avoid-c-arrays)
  count_t m_count = 0;

protected:
  FMT_CONSTEXPR20 void grow(count_t /*unused*/) override
  {
    if(this->size() != buffer_size)
      return;
    m_count += this->size();
    this->clear();
  }

public:
  counting_buffer()
      : buffer<T>(m_data, 0, buffer_size)
  {
  }

  auto count() -> count_t
  {
    return m_count + this->size();
  }
};

template <typename T>
using buffer_appender = conditional_t<rsl::is_same<T, char>::value, appender, rsl::back_insert_iterator<buffer<T>>>;

// Maps an output iterator to a buffer.
template <typename T, typename OutputIt>
auto get_buffer(OutputIt out) -> iterator_buffer<OutputIt, T>
{
  return iterator_buffer<OutputIt, T>(out);
}

template <typename Buffer>
auto get_iterator(Buffer& buf) -> decltype(buf.out())
{
  return buf.out();
}
template <typename T>
auto get_iterator(buffer<T>& buf) -> buffer_appender<T>
{
  return buffer_appender<T>(buf);
}

template <typename T, typename Char = char, typename Enable = void>
struct fallback_formatter
{
  fallback_formatter() = delete;
};

// Specifies if T has an enabled fallback_formatter specialization.
template <typename T, typename Char>
using has_fallback_formatter =
#ifdef FMT_DEPRECATED_OSTREAM
    rsl::is_constructible<fallback_formatter<T, Char>>;
#else
    rsl::false_type;
#endif

template <typename Char, typename T>
struct named_arg : view
{
  const Char* name;
  const T& value; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
  named_arg(const Char* n, const T& v)
      : name(n)
      , value(v)
  {
  }
};

template <typename Char>
struct named_arg_info
{
  const Char* name;
  int id;
};

template <typename T, typename Char, count_t NumArgs, count_t NumNamedArgs>
struct arg_data
{
  // args_[0].named_args points to named_args_ to avoid bloating format_args.
  // +1 to workaround a bug in gcc 7.5 that causes duplicated-branches warning.
  T arguments[1 + (NumArgs != 0 ? NumArgs : +1)];     // NOLINT(modernize-avoid-c-arrays)
  named_arg_info<Char> named_arguments[NumNamedArgs]; // NOLINT(modernize-avoid-c-arrays)

  template <typename... U>
  arg_data(const U&... init) // NOLINT(google-explicit-constructor)
      : arguments {T(named_arguments, NumNamedArgs), init...}
  {
  }
  arg_data(const arg_data& other) = delete;

  ~arg_data()                          = default;
  arg_data& operator=(const arg_data&) = delete;
  auto args() const -> const T*
  {
    return arguments + 1;
  }
  auto named_args() -> named_arg_info<Char>*
  {
    return named_arguments;
  }
};

template <typename T, typename Char, count_t NumArgs>
struct arg_data<T, Char, NumArgs, 0>
{
  // +1 to workaround a bug in gcc 7.5 that causes duplicated-branches warning.
  T arguments[NumArgs != 0 ? NumArgs : +1]; // NOLINT(modernize-avoid-c-arrays)

  template <typename... U>
  FMT_CONSTEXPR FMT_INLINE arg_data(const U&... init) // NOLINT(google-explicit-constructor)
      : arguments {init...}
  {
  }
  FMT_CONSTEXPR FMT_INLINE auto args() const -> const T*
  {
    return arguments;
  }
  FMT_CONSTEXPR FMT_INLINE auto named_args() -> rsl::nullptr_t
  {
    return nullptr;
  }
};

template <typename Char>
inline void init_named_args(named_arg_info<Char>* /*unused*/, int /*unused*/, int /*unused*/)
{
}

template <typename T>
struct is_named_arg : rsl::false_type
{
};
template <typename T>
struct is_statically_named_arg : rsl::false_type
{
};

template <typename T, typename Char>
struct is_named_arg<named_arg<Char, T>> : rsl::true_type
{
};

template <typename Char, typename T, typename... Tail, FMT_ENABLE_IF(!is_named_arg<T>::value)>
void init_named_args(named_arg_info<Char>* namedArgs, int argCount, int namedArgCount, const T& /*unused*/, const Tail&... args)
{
  init_named_args(namedArgs, argCount + 1, namedArgCount, args...);
}

template <typename Char, typename T, typename... Tail, FMT_ENABLE_IF(is_named_arg<T>::value)>
void init_named_args(named_arg_info<Char>* namedArgs, int argCount, int namedArgCount, const T& arg, const Tail&... args)
{
  namedArgs[namedArgCount++] = {arg.name, argCount};
  init_named_args(namedArgs, argCount + 1, namedArgCount, args...);
}

template <typename... Args>
FMT_CONSTEXPR FMT_INLINE void init_named_args(rsl::nullptr_t, int /*unused*/, int /*unused*/, const Args&... /*unused*/)
{
}

template <typename... Args>
constexpr auto count_named_args() -> count_t
{
  return count<is_named_arg<Args>::value...>();
}

template <typename... Args>
constexpr auto count_statically_named_args() -> count_t
{
  return count<is_statically_named_arg<Args>::value...>();
}

struct unformattable
{
};
struct unformattable_char : unformattable
{
};
struct unformattable_const : unformattable
{
};
struct unformattable_pointer : unformattable
{
};

template <typename Char>
struct string_value
{
  const Char* data;
  count_t size;
};

template <typename Char>
struct named_arg_value
{
  const named_arg_info<Char>* data;
  count_t size;
};

template <typename Context>
struct custom_value
{
  using parse_context = typename Context::parse_context_type;
  void* value;
  void (*format)(void* arg, parse_context& parseCtx, Context& ctx);
};

// A formatting argument value.
// NOLINTBEGIN(cppcoreguidelines-pro-type-member-init)
template <typename Context>
class value
{
public:
  using char_type = typename Context::char_type;

  union
  {
    monostate no_value;
    int int_value;
    unsigned uint_value;
    long long long_long_value;
    unsigned long long ulong_long_value;
    int128_opt int128_value;
    uint128_opt uint128_value;
    bool bool_value;
    char_type char_value;
    float float_value;
    double double_value;
    long double long_double_value;
    const void* pointer;
    string_value<char_type> string;
    custom_value<Context> custom;
    named_arg_value<char_type> named_args;
  };

  constexpr FMT_INLINE value()
      : no_value()
  {
  }
  constexpr FMT_INLINE value(int val) // NOLINT(google-explicit-constructor)
      : int_value(val)
  {
  }
  constexpr FMT_INLINE value(unsigned val) // NOLINT(google-explicit-constructor)
      : uint_value(val)
  {
  }
  constexpr FMT_INLINE value(long long val) // NOLINT(google-explicit-constructor)
      : long_long_value(val)
  {
  }
  constexpr FMT_INLINE value(unsigned long long val) // NOLINT(google-explicit-constructor)
      : ulong_long_value(val)
  {
  }
  FMT_INLINE value(int128_opt val) // NOLINT(google-explicit-constructor)
      : int128_value(val)
  {
  }
  FMT_INLINE value(uint128_opt val) // NOLINT(google-explicit-constructor)
      : uint128_value(val)
  {
  }
  constexpr FMT_INLINE value(float val) // NOLINT(google-explicit-constructor)
      : float_value(val)
  {
  }
  constexpr FMT_INLINE value(double val) // NOLINT(google-explicit-constructor)
      : double_value(val)
  {
  }
  FMT_INLINE value(long double val) // NOLINT(google-explicit-constructor)
      : long_double_value(val)
  {
  }
  constexpr FMT_INLINE value(bool val) // NOLINT(google-explicit-constructor)
      : bool_value(val)
  {
  }
  constexpr FMT_INLINE value(char_type val) // NOLINT(google-explicit-constructor)
      : char_value(val)
  {
  }
  FMT_CONSTEXPR FMT_INLINE value(const char_type* val) // NOLINT(google-explicit-constructor)
  {
    string.data = val;
    if(is_constant_evaluated())
      string.size = {};
  }
  FMT_CONSTEXPR FMT_INLINE value(basic_string_view<char_type> val) // NOLINT(google-explicit-constructor)
  {
    string.data = val.data();
    string.size = val.size();
  }
  FMT_INLINE value(const void* val) // NOLINT(google-explicit-constructor)
      : pointer(val)
  {
  }
  FMT_INLINE value(const named_arg_info<char_type>* args, count_t size)
      : named_args {args, size}
  {
  }

  template <typename T>
  FMT_CONSTEXPR FMT_INLINE value(T& val) // NOLINT(google-explicit-constructor)
  {
    using value_type = remove_cvref_t<T>;
    custom.value     = const_cast<value_type*>(&val); // NOLINT(cppcoreguidelines-pro-type-const-cast)
    // Get the formatter type through the context to allow different contexts
    // have different extension points, e.g. `formatter<T>` for `format` and
    // `printf_formatter<T>` for `printf`.
    custom.format = format_custom_arg<value_type, conditional_t<has_formatter<value_type, Context>::value, typename Context::template formatter_type<value_type>, fallback_formatter<value_type, char_type>>>;
  }
  value(unformattable);         // NOLINT(google-explicit-constructor)
  value(unformattable_char);    // NOLINT(google-explicit-constructor)
  value(unformattable_const);   // NOLINT(google-explicit-constructor)
  value(unformattable_pointer); // NOLINT(google-explicit-constructor)

private:
  // Formats an argument of a custom type, such as a user-defined class.
  template <typename T, typename Formatter>
  static void format_custom_arg(void* arg, typename Context::parse_context_type& parseCtx, Context& ctx)
  {
    auto f = Formatter();
    parseCtx.advance_to(f.parse(parseCtx));
    using qualified_type = conditional_t<has_const_formatter<T, Context>(), const T, T>;
    ctx.advance_to(f.format(*static_cast<qualified_type*>(arg), ctx));
  }
};
// NOLINTEND(cppcoreguidelines-pro-type-member-init)
template <typename Context, typename T>
FMT_CONSTEXPR auto make_arg(T&& value) -> basic_format_arg<Context>;

// To minimize the number of types we need to deal with, long is translated
// either to int or to long long depending on its size.
enum
{
  long_short = sizeof(long) == sizeof(int) // NOLINT(readability-implicit-bool-conversion)
};
using long_type  = conditional_t<long_short, int, long long>;               // NOLINT(readability-implicit-bool-conversion)
using ulong_type = conditional_t<long_short, unsigned, unsigned long long>; // NOLINT(readability-implicit-bool-conversion)

#ifdef __cpp_lib_byte
inline auto format_as(rsl::byte b) -> unsigned char
{
  return static_cast<unsigned char>(b);
}
#endif

template <typename T>
struct has_format_as
{
  template <typename U, typename V = decltype(format_as(U())), FMT_ENABLE_IF(rsl::is_enum<U>::value&& rsl::is_integral<V>::value)>
  static auto check(U*) -> rsl::true_type;
  static auto check(...) -> rsl::false_type;

  enum
  {
    value = decltype(check(static_cast<T*>(nullptr)))::value
  };
};

// Maps formatting arguments to core types.
// arg_mapper reports errors by returning unformattable instead of using
// static_assert because it's used in the is_formattable trait.
template <typename Context>
struct arg_mapper
{
  using char_type = typename Context::char_type;

  FMT_CONSTEXPR FMT_INLINE auto map(signed char val) -> int
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(unsigned char val) -> unsigned
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(short val) -> int
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(unsigned short val) -> unsigned
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(int val) -> int
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(unsigned val) -> unsigned
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(long val) -> long_type
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(unsigned long val) -> ulong_type
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(long long val) -> long long
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(unsigned long long val) -> unsigned long long
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(int128_opt val) -> int128_opt
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(uint128_opt val) -> uint128_opt
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(bool val) -> bool
  {
    return val;
  }

  template <typename T, FMT_ENABLE_IF(rsl::is_same<T, char>::value || rsl::is_same<T, char_type>::value)>
  FMT_CONSTEXPR FMT_INLINE auto map(T val) -> char_type
  {
    return val;
  }
  template <typename T, enable_if_t<(rsl::is_same<T, wchar_t>::value ||
#ifdef __cpp_char8_t
                                     rsl::is_same<T, char8_t>::value ||
#endif
                                     rsl::is_same<T, char16_t>::value || rsl::is_same<T, char32_t>::value) &&
                                        !rsl::is_same<T, char_type>::value,
                                    int> = 0>
  FMT_CONSTEXPR FMT_INLINE auto map(T /*unused*/) -> unformattable_char
  {
    return {};
  }

  FMT_CONSTEXPR FMT_INLINE auto map(float val) -> float
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(double val) -> double
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(long double val) -> long double
  {
    return val;
  }

  FMT_CONSTEXPR FMT_INLINE auto map(char_type* val) -> const char_type*
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(const char_type* val) -> const char_type*
  {
    return val;
  }
  template <typename T, FMT_ENABLE_IF(is_string<T>::value && !rsl::is_pointer<T>::value && rsl::is_same<char_type, char_t<T>>::value)>
  FMT_CONSTEXPR FMT_INLINE auto map(const T& val) -> basic_string_view<char_type>
  {
    return to_string_view(val);
  }
  template <typename T, FMT_ENABLE_IF(is_string<T>::value && !rsl::is_pointer<T>::value && !rsl::is_same<char_type, char_t<T>>::value)>
  FMT_CONSTEXPR FMT_INLINE auto map(const T& /*unused*/) -> unformattable_char
  {
    return {};
  }
  template <typename T, FMT_ENABLE_IF(rsl::is_convertible<T, basic_string_view<char_type>>::value && !is_string<T>::value && !has_formatter<T, Context>::value && !has_fallback_formatter<T, char_type>::value)>
  FMT_CONSTEXPR FMT_INLINE auto map(const T& val) -> basic_string_view<char_type>
  {
    return basic_string_view<char_type>(val);
  }
  template <typename T, FMT_ENABLE_IF(rsl::is_convertible<T, std_string_view<char_type>>::value && !rsl::is_convertible<T, basic_string_view<char_type>>::value && !is_string<T>::value && !has_formatter<T, Context>::value &&
                                      !has_fallback_formatter<T, char_type>::value)>
  FMT_CONSTEXPR FMT_INLINE auto map(const T& val) -> basic_string_view<char_type>
  {
    return std_string_view<char_type>(val);
  }

  FMT_CONSTEXPR FMT_INLINE auto map(void* val) -> const void*
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(const void* val) -> const void*
  {
    return val;
  }
  FMT_CONSTEXPR FMT_INLINE auto map(rsl::nullptr_t val) -> const void*
  {
    return val;
  }

  // We use SFINAE instead of a const T* parameter to avoid conflicting with
  // the C array overload.
  template <typename T, FMT_ENABLE_IF(rsl::is_pointer<T>::value || rsl::is_member_pointer<T>::value || rsl::is_function<typename rsl::remove_pointer<T>::type>::value ||
                                      (rsl::is_convertible<const T&, const void*>::value && !rsl::is_convertible<const T&, const char_type*>::value && !has_formatter<T, Context>::value))>
  FMT_CONSTEXPR auto map(const T& /*unused*/) -> unformattable_pointer
  {
    return {};
  }

  template <typename T, count_t N, FMT_ENABLE_IF(!rsl::is_same<T, wchar_t>::value)>
  FMT_CONSTEXPR FMT_INLINE auto map(const T (&values)[N]) -> const T (&)[N] // NOLINT(modernize-avoid-c-arrays)
  {
    return values;
  }

  template <typename T, FMT_ENABLE_IF(rsl::is_enum<T>::value&& rsl::is_convertible<T, int>::value && !has_format_as<T>::value && !has_formatter<T, Context>::value && !has_fallback_formatter<T, char_type>::value)>
  FMT_DEPRECATED FMT_CONSTEXPR FMT_INLINE auto map(const T& val) -> decltype(rsl::declval<arg_mapper>().map(static_cast<underlying_type_t<T>>(val)))
  {
    return map(static_cast<underlying_type_t<T>>(val));
  }

  template <typename T, FMT_ENABLE_IF(has_format_as<T>::value && !has_formatter<T, Context>::value)>
  FMT_CONSTEXPR FMT_INLINE auto map(const T& val) -> decltype(rsl::declval<arg_mapper>().map(format_as(T())))
  {
    return map(format_as(val));
  }

  template <typename T, typename U = remove_cvref_t<T>>
  struct formattable : bool_constant<has_const_formatter<U, Context>() || !rsl::is_const<remove_reference_t<T>>::value || has_fallback_formatter<U, char_type>::value>
  {
  };

#if(FMT_MSC_VERSION != 0 && FMT_MSC_VERSION < 1910) || FMT_ICC_VERSION != 0 || defined(__NVCC__)
  // Workaround a bug in MSVC and Intel (Issue 2746).
  template <typename T>
  FMT_CONSTEXPR FMT_INLINE auto do_map(T&& val) -> T&
  {
    return val;
  }
#else
  template <typename T, FMT_ENABLE_IF(formattable<T>::value)>
  FMT_CONSTEXPR FMT_INLINE auto do_map(T&& val) -> T&
  {
    return val;
  }
  template <typename T, FMT_ENABLE_IF(!formattable<T>::value)>
  FMT_CONSTEXPR FMT_INLINE auto do_map(T&& /*unused*/) -> unformattable_const
  {
    return {};
  }
#endif

  template <typename T, typename U = remove_cvref_t<T>,
            FMT_ENABLE_IF(!is_string<U>::value && !is_char<U>::value && !rsl::is_array<U>::value && !rsl::is_pointer<U>::value && !has_format_as<U>::value && (has_formatter<U, Context>::value || has_fallback_formatter<U, char_type>::value))>
  FMT_CONSTEXPR FMT_INLINE auto map(T&& val) -> decltype(this->do_map(rsl::forward<T>(val)))
  {
    return do_map(rsl::forward<T>(val));
  }

  template <typename T, FMT_ENABLE_IF(is_named_arg<T>::value)>
  FMT_CONSTEXPR FMT_INLINE auto map(const T& namedArg) -> decltype(rsl::declval<arg_mapper>().map(namedArg.value))
  {
    return map(namedArg.value);
  }

  auto map(...) -> unformattable
  {
    return {};
  }
};

enum
{
  packed_arg_bits = 4
};
// Maximum number of arguments with packed types.
enum
{
  max_packed_args = 62 / packed_arg_bits
};
enum : unsigned long long
{
  is_unpacked_bit = 1ULL << 63
};
enum : unsigned long long
{
  has_named_args_bit = 1ULL << 62
};

FMT_END_DETAIL_NAMESPACE

// An output iterator that appends to a buffer.
// It is used to reduce symbol sizes for the common case.
class appender : public rsl::back_insert_iterator<detail::buffer<char>>
{
  using base = rsl::back_insert_iterator<detail::buffer<char>>;

  template <typename T>
  friend auto get_buffer(appender out) -> detail::buffer<char>&
  {
    return detail::get_container(out);
  }

public:
  using rsl::back_insert_iterator<detail::buffer<char>>::back_insert_iterator;
  appender(base it) noexcept // NOLINT(google-explicit-constructor)
      : base(it)
  {
  }
  FMT_UNCHECKED_ITERATOR(appender);

  auto operator++() noexcept -> appender&
  {
    return *this;
  }
  auto operator++(int) noexcept -> appender
  {
    return *this;
  }
};

// A formatting argument. It is a trivially copyable/constructible type to
// allow storage in basic_memory_buffer.
template <typename Context>
class basic_format_arg
{
private:
  detail::value<Context> m_value;
  detail::type m_type;

  template <typename ContextType, typename T>
  friend FMT_CONSTEXPR auto detail::make_arg(T&& value) -> basic_format_arg<ContextType>;

  template <typename Visitor, typename Ctx>
  friend FMT_CONSTEXPR auto visit_format_arg(Visitor&& vis, const basic_format_arg<Ctx>& arg) -> decltype(vis(0));

  friend class basic_format_args<Context>;
  friend class dynamic_format_arg_store<Context>;

  using char_type = typename Context::char_type;

  template <typename T, typename Char, count_t NumArgs, count_t NumNamedArgs>
  friend struct detail::arg_data;

  basic_format_arg(const detail::named_arg_info<char_type>* args, count_t size)
      : m_value(args, size)
  {
  }

public:
  class handle
  {
  public:
    explicit handle(detail::custom_value<Context> custom)
        : m_custom(custom)
    {
    }

    void format(typename Context::parse_context_type& parseCtx, Context& ctx) const
    {
      m_custom.format(m_custom.value, parseCtx, ctx);
    }

  private:
    detail::custom_value<Context> m_custom;
  };

  constexpr basic_format_arg()
      : m_type(detail::type::none_type)
  {
  }

  constexpr explicit operator bool() const noexcept
  {
    return m_type != detail::type::none_type;
  }

  auto type() const -> detail::type
  {
    return m_type;
  }

  auto is_integral() const -> bool
  {
    return detail::is_integral_type(m_type);
  }
  auto is_arithmetic() const -> bool
  {
    return detail::is_arithmetic_type(m_type);
  }
};

/**
  \rst
  Visits an argument dispatching to the appropriate visit method based on
  the argument type. For example, if the argument type is ``double`` then
  ``vis(value)`` will be called with the value of type ``double``.
  \endrst
 */
template <typename Visitor, typename Context>
FMT_CONSTEXPR FMT_INLINE auto visit_format_arg(Visitor&& vis, const basic_format_arg<Context>& arg) -> decltype(vis(0))
{
  switch(arg.m_type)
  {
    case detail::type::none_type: break;
    case detail::type::int_type: return vis(arg.m_value.int_value);
    case detail::type::uint_type: return vis(arg.m_value.uint_value);
    case detail::type::long_long_type: return vis(arg.m_value.long_long_value);
    case detail::type::ulong_long_type: return vis(arg.m_value.ulong_long_value);
    case detail::type::int128_type: return vis(detail::convert_for_visit(arg.m_value.int128_value));
    case detail::type::uint128_type: return vis(detail::convert_for_visit(arg.m_value.uint128_value));
    case detail::type::bool_type: return vis(arg.m_value.bool_value);
    case detail::type::char_type: return vis(arg.m_value.char_value);
    case detail::type::float_type: return vis(arg.m_value.float_value);
    case detail::type::double_type: return vis(arg.m_value.double_value);
    case detail::type::long_double_type: return vis(arg.m_value.long_double_value);
    case detail::type::cstring_type: return vis(arg.m_value.string.data);
    case detail::type::string_type: using sv = basic_string_view<typename Context::char_type>; return vis(sv(arg.m_value.string.data, arg.m_value.string.size));
    case detail::type::pointer_type: return vis(arg.m_value.pointer);
    case detail::type::custom_type: return vis(typename basic_format_arg<Context>::handle(arg.m_value.custom));
  }
  return vis(monostate());
}

FMT_BEGIN_DETAIL_NAMESPACE

template <typename Char, typename InputIt>
auto copy_str(InputIt begin, InputIt end, appender out) -> appender
{
  get_container(out).append(rsl::iterator_to_pointer(begin), rsl::iterator_to_pointer(end));
  return out;
}

template <typename Char, typename R, typename OutputIt>
FMT_CONSTEXPR auto copy_str(R&& rng, OutputIt out) -> OutputIt
{
  return detail::copy_str<Char>(rng.begin(), rng.end(), out);
}

#if FMT_GCC_VERSION && FMT_GCC_VERSION < 500
// A workaround for gcc 4.8 to make void_t work in a SFINAE context.
template <typename... Ts>
struct void_t_impl
{
  using type = void;
};
template <typename... Ts>
using void_t = typename detail::void_t_impl<Ts...>::type;
#else
template <typename...>
using void_t = void;
#endif

template <typename Iter, typename T, typename Enable = void>
struct is_output_iterator : rsl::false_type
{
};

template <typename Iter, typename T>
struct is_output_iterator<Iter, T, void_t<typename rsl::iterator_traits<Iter>::iterator_category, decltype(*rsl::declval<Iter>() = rsl::declval<T>())>> : rsl::true_type
{
};

template <typename OutputIt>
struct is_back_insert_iterator : rsl::false_type
{
};
template <typename Container>
struct is_back_insert_iterator<rsl::back_insert_iterator<Container>> : rsl::true_type
{
};

template <typename OutputIt>
struct is_contiguous_back_insert_iterator : rsl::false_type
{
};
template <typename Container>
struct is_contiguous_back_insert_iterator<rsl::back_insert_iterator<Container>> : is_contiguous<Container>
{
};
template <>
struct is_contiguous_back_insert_iterator<appender> : rsl::true_type
{
};

// A type-erased reference to an rsl::locale to avoid a heavy <locale> include.
class locale_ref
{
private:
  const void* m_locale; // A type-erased pointer to rsl::locale.

public:
  constexpr locale_ref()
      : m_locale(nullptr)
  {
  }
  template <typename Locale>
  explicit locale_ref(const Locale& loc);

  explicit operator bool() const noexcept
  {
    return m_locale != nullptr;
  }

  template <typename Locale>
  auto get() const -> Locale;
};

template <typename>
constexpr auto encode_types() -> unsigned long long
{
  return 0;
}

template <typename Context, typename Arg, typename... Args>
constexpr auto encode_types() -> unsigned long long
{
  return static_cast<unsigned>(mapped_type_constant<Arg, Context>::value) | (encode_types<Context, Args...>() << packed_arg_bits);
}

template <typename Context, typename T>
FMT_CONSTEXPR FMT_INLINE auto make_value(T&& val) -> value<Context>
{
  const auto& arg = arg_mapper<Context>().map(FMT_FORWARD(val));

  constexpr bool formattable_char = !rsl::is_same<decltype(arg), const unformattable_char&>::value;
  static_assert(formattable_char, "Mixing character types is disallowed.");

  constexpr bool formattable_const = !rsl::is_same<decltype(arg), const unformattable_const&>::value;
  static_assert(formattable_const, "Cannot format a const argument.");

  // Formatting of arbitrary pointers is disallowed. If you want to output
  // a pointer cast it to "void *" or "const void *". In particular, this
  // forbids formatting of "[const] volatile char *" which is printed as bool
  // by iostreams.
  constexpr bool formattable_pointer = !rsl::is_same<decltype(arg), const unformattable_pointer&>::value;
  static_assert(formattable_pointer, "Formatting of non-void pointers is disallowed.");

  constexpr bool formattable = !rsl::is_same<decltype(arg), const unformattable&>::value;
  static_assert(formattable, "Cannot format an argument. To make type T formattable provide a "
                             "formatter<T> specialization: https://fmt.dev/latest/api.html#udt");
  return {arg};
}

template <typename Context, typename T>
FMT_CONSTEXPR auto make_arg(T&& value) -> basic_format_arg<Context>
{
  basic_format_arg<Context> arg;
  arg.m_type  = mapped_type_constant<T, Context>::value;
  arg.m_value = make_value<Context>(value);
  return arg;
}

// The type template parameter is there to avoid an ODR violation when using
// a fallback formatter in one translation unit and an implicit conversion in
// another (not recommended).
template <bool IsPacked, typename Context, type, typename T, FMT_ENABLE_IF(IsPacked)>
FMT_CONSTEXPR FMT_INLINE auto make_arg(T&& val) -> value<Context>
{
  return make_value<Context>(val);
}

template <bool IsPacked, typename Context, type, typename T, FMT_ENABLE_IF(!IsPacked)>
FMT_CONSTEXPR inline auto make_arg(T&& value) -> basic_format_arg<Context>
{
  return make_arg<Context>(value);
}
FMT_END_DETAIL_NAMESPACE

// Formatting context.
template <typename OutputIt, typename Char>
class basic_format_context
{
public:
  /** The character type for the output. */
  using char_type = Char;

private:
  OutputIt m_out;
  basic_format_args<basic_format_context> m_args;
  detail::locale_ref m_loc;

public:
  using iterator           = OutputIt;
  using format_arg         = basic_format_arg<basic_format_context>;
  using parse_context_type = basic_format_parse_context<Char>;
  template <typename T>
  using formatter_type = formatter<T, char_type>;

  basic_format_context(basic_format_context&&)                 = default;
  basic_format_context(const basic_format_context&)            = delete;
  basic_format_context& operator=(const basic_format_context&) = delete;
  basic_format_context& operator=(basic_format_context&&)      = default;

  /**
   Constructs a ``basic_format_context`` object. References to the arguments are
   stored in the object so make sure they have appropriate lifetimes.
   */
  constexpr basic_format_context(OutputIt out, basic_format_args<basic_format_context> ctxArgs, detail::locale_ref loc = detail::locale_ref())
      : m_out(out)
      , m_args(ctxArgs)
      , m_loc(loc)
  {
  }

  ~basic_format_context() = default;

  constexpr auto arg(int id) const -> format_arg
  {
    return m_args.get(id);
  }
  FMT_CONSTEXPR auto arg(basic_string_view<char_type> name) -> format_arg
  {
    return m_args.get(name);
  }
  FMT_CONSTEXPR auto arg_id(basic_string_view<char_type> name) -> int
  {
    return m_args.get_id(name);
  }
  auto args() const -> const basic_format_args<basic_format_context>&
  {
    return m_args;
  }

  FMT_CONSTEXPR auto error_handler() -> detail::error_handler
  {
    return {};
  }
  void on_error(const char* message)
  {
    error_handler().on_error(message);
  }

  // Returns an iterator to the beginning of the output range.
  FMT_CONSTEXPR auto out() -> iterator
  {
    return m_out;
  }

  // Advances the begin iterator to ``it``.
  void advance_to(iterator it)
  {
    if(!detail::is_back_insert_iterator<iterator>())
      m_out = it;
  }

  FMT_CONSTEXPR auto locale() -> detail::locale_ref
  {
    return m_loc;
  }
};

template <typename Char>
using buffer_context = basic_format_context<detail::buffer_appender<Char>, Char>;
using format_context = buffer_context<char>;

// Workaround an alias issue: https://stackoverflow.com/q/62767544/471164.
#define FMT_BUFFER_CONTEXT(Char) basic_format_context<detail::buffer_appender<Char>, Char>

template <typename T, typename Char = char>
using is_formattable = bool_constant<!rsl::is_base_of<detail::unformattable, decltype(detail::arg_mapper<buffer_context<Char>>().map(rsl::declval<T>()))>::value && !detail::has_fallback_formatter<T, Char>::value>;

/**
  \rst
  An array of references to arguments. It can be implicitly converted into
  `~rsl::basic_format_args` for passing into type-erased formatting functions
  such as `~rsl::vformat`.
  \endrst
 */
template <typename Context, typename... Args>
class format_arg_store
#if FMT_GCC_VERSION && FMT_GCC_VERSION < 409
    // Workaround a GCC template argument substitution bug.
    : public basic_format_args<Context>
#endif
{
private:
  static const count_t s_num_args       = sizeof...(Args);
  static const count_t s_num_named_args = detail::count_named_args<Args...>();
  static const bool s_is_packed         = s_num_args <= detail::max_packed_args;

  using value_type = conditional_t<s_is_packed, detail::value<Context>, basic_format_arg<Context>>;

  detail::arg_data<value_type, typename Context::char_type, s_num_args, s_num_named_args> m_data;

  friend class basic_format_args<Context>;

  static constexpr unsigned long long desc = (s_is_packed ? detail::encode_types<Context, Args...>() : detail::is_unpacked_bit | s_num_args) | (s_num_named_args != 0 ? static_cast<unsigned long long>(detail::has_named_args_bit) : 0);

public:
  template <typename... T>
  FMT_CONSTEXPR FMT_INLINE format_arg_store(T&&... args) // NOLINT(google-explicit-constructor)
      :
#if FMT_GCC_VERSION && FMT_GCC_VERSION < 409
      basic_format_args<Context>(*this)
      ,
#endif
      m_data {detail::make_arg<s_is_packed, Context, detail::mapped_type_constant<remove_cvref_t<T>, Context>::value>(FMT_FORWARD(args))...}
  {
    detail::init_named_args(m_data.named_args(), 0, 0, args...);
  }
};

/**
  \rst
  Constructs a `~rsl::format_arg_store` object that contains references to
  arguments and can be implicitly converted to `~rsl::format_args`. `Context`
  can be omitted in which case it defaults to `~rsl::context`.
  See `~rsl::arg` for lifetime considerations.
  \endrst
 */
template <typename Context = format_context, typename... Args>
constexpr auto make_format_args(Args&&... args) -> format_arg_store<Context, remove_cvref_t<Args>...>
{
  return {FMT_FORWARD(args)...};
}

/**
  \rst
  Returns a named argument to be used in a formatting function.
  It should only be used in a call to a formatting function or
  `dynamic_format_arg_store::push_back`.

  **Example**::

    rsl::print("Elapsed time: {s:.2f} seconds", rsl::arg("s", 1.23));
  \endrst
 */
template <typename Char, typename T>
inline auto arg(const Char* name, const T& arg) -> detail::named_arg<Char, T>
{
  static_assert(!detail::is_named_arg<T>(), "nested named arguments");
  return {name, arg};
}

/**
  \rst
  A view of a collection of formatting arguments. To avoid lifetime issues it
  should only be used as a parameter type in type-erased functions such as
  ``vformat``::

    void vlog(string_view format_str, format_args args);  // OK
    format_args args = make_format_args(42);  // Error: dangling reference
  \endrst
 */
template <typename Context>
class basic_format_args
{
public:
  using size_type  = int;
  using format_arg = basic_format_arg<Context>;

private:
  // A descriptor that contains information about formatting arguments.
  // If the number of arguments is less or equal to max_packed_args then
  // argument types are passed in the descriptor. This reduces binary code size
  // per formatting function call.
  unsigned long long m_desc;
  union
  {
    // If is_packed() returns true then argument values are stored in values_;
    // otherwise they are stored in args_. This is done to improve cache
    // locality and reduce compiled code size since storing larger objects
    // may require more code (at least on x86-64) even if the same amount of
    // data is actually copied to stack. It saves ~10% on the bloat test.
    const detail::value<Context>* values;
    const format_arg* args;
  };

  constexpr auto is_packed() const -> bool
  {
    return (m_desc & detail::is_unpacked_bit) == 0;
  }
  auto has_named_args() const -> bool
  {
    return (m_desc & detail::has_named_args_bit) != 0;
  }

  FMT_CONSTEXPR auto type(int index) const -> detail::type
  {
    const int shift         = index * detail::packed_arg_bits;
    const unsigned int mask = (1 << detail::packed_arg_bits) - 1;
    return static_cast<detail::type>((m_desc >> shift) & mask);
  }

  constexpr FMT_INLINE basic_format_args(unsigned long long desc, const detail::value<Context>* values)
      : m_desc(desc)
      , values(values)
  {
  }
  constexpr basic_format_args(unsigned long long desc, const format_arg* args)
      : m_desc(desc)
      , args(args)
  {
  }

public:
  constexpr basic_format_args()
      : m_desc(0)
      , args(nullptr)
  {
  }

  /**
   \rst
   Constructs a `basic_format_args` object from `~rsl::format_arg_store`.
   \endrst
   */
  template <typename... Args>
  constexpr FMT_INLINE basic_format_args(const format_arg_store<Context, Args...>& store) // NOLINT(cppcoreguidelines-pro-type-member-init, google-explicit-constructor)
      : basic_format_args(format_arg_store<Context, Args...>::desc, store.m_data.args())
  {
  }

  /**
   \rst
   Constructs a `basic_format_args` object from
   `~rsl::dynamic_format_arg_store`.
   \endrst
   */
  constexpr FMT_INLINE basic_format_args(const dynamic_format_arg_store<Context>& store) // NOLINT(cppcoreguidelines-pro-type-member-init, google-explicit-constructor)
      : basic_format_args(store.get_types(), store.data())
  {
  }

  /**
   \rst
   Constructs a `basic_format_args` object from a dynamic set of arguments.
   \endrst
   */
  constexpr basic_format_args(const format_arg* args, int count) // NOLINT(cppcoreguidelines-pro-type-member-init, google-explicit-constructor)
      : basic_format_args(detail::is_unpacked_bit | detail::to_unsigned(count), args)
  {
  }

  /** Returns the argument with the specified id. */
  FMT_CONSTEXPR auto get(int id) const -> format_arg
  {
    format_arg arg;
    if(!is_packed())
    {
      if(id < max_size())
        arg = args[id];
      return arg;
    }
    if(id >= detail::max_packed_args)
      return arg;
    arg.m_type = type(id);
    if(arg.m_type == detail::type::none_type)
      return arg;
    arg.m_value = values[id];
    return arg;
  }

  template <typename Char>
  auto get(basic_string_view<Char> name) const -> format_arg
  {
    const int id = get_id(name);
    return id >= 0 ? get(id) : format_arg();
  }

  template <typename Char>
  auto get_id(basic_string_view<Char> name) const -> int
  {
    if(!has_named_args())
      return -1;
    const auto& named_args = (is_packed() ? values[-1] : args[-1].m_value).named_args;
    for(count_t i = 0; i < named_args.size; ++i)
    {
      if(basic_string_view<Char>(named_args.data[i].name) == name)
        return named_args.data[i].id;
    }
    return -1;
  }

  auto max_size() const -> int
  {
    const unsigned long long max_packed = detail::max_packed_args;
    return static_cast<int>(is_packed() ? max_packed : m_desc & ~detail::is_unpacked_bit);
  }
};

/** An alias to ``basic_format_args<format_context>``. */
// A separate type would result in shorter symbols but break ABI compatibility
// between clang and gcc on ARM (#1919).
using format_args = basic_format_args<format_context>;

// We cannot use enum classes as bit fields because of a gcc bug, so we put them
// in namespaces instead (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=61414).
// Additionally, if an underlying type is specified, older gcc incorrectly warns
// that the type is too small. Both bugs are fixed in gcc 9.3.
#if FMT_GCC_VERSION && FMT_GCC_VERSION < 903
  #define FMT_ENUM_UNDERLYING_TYPE(type)
#else
  #define FMT_ENUM_UNDERLYING_TYPE(type) : type
#endif
namespace align
{
  enum type FMT_ENUM_UNDERLYING_TYPE(unsigned char) {none, left, right, center, numeric};
} // namespace align
using align_t = align::type;
namespace sign
{
  enum type FMT_ENUM_UNDERLYING_TYPE(unsigned char) {none, minus, plus, space};
} // namespace sign
using sign_t = sign::type;

FMT_BEGIN_DETAIL_NAMESPACE

// Workaround an array initialization issue in gcc 4.8.
template <typename Char>
struct fill_t
{
private:
  enum
  {
    max_size = 4
  };
  Char m_data[max_size] = {Char(' '), Char(0), Char(0), Char(0)}; // NOLINT(google-readability-casting, modernize-avoid-c-arrays)
  unsigned char m_size  = 1;

public:
  FMT_CONSTEXPR fill_t& operator=(basic_string_view<Char> s)
  {
    auto size = s.size();
    if(size > max_size)
    {
      throw_format_error("invalid fill");
      return *this;
    }
    for(count_t i = 0; i < size; ++i)
      m_data[i] = s[i];
    m_size = static_cast<unsigned char>(size);

    return *this;
  }

  constexpr auto size() const -> count_t
  {
    return m_size;
  }
  constexpr auto data() const -> const Char*
  {
    return m_data;
  }

  FMT_CONSTEXPR auto operator[](count_t index) -> Char&
  {
    return m_data[index];
  }
  FMT_CONSTEXPR auto operator[](count_t index) const -> const Char&
  {
    return m_data[index];
  }
};
FMT_END_DETAIL_NAMESPACE

enum class presentation_type : unsigned char
{
  none,
  // Integer types should go first,
  dec,            // 'd'
  oct,            // 'o'
  hex_lower,      // 'x'
  hex_upper,      // 'X'
  bin_lower,      // 'b'
  bin_upper,      // 'B'
  hexfloat_lower, // 'a'
  hexfloat_upper, // 'A'
  exp_lower,      // 'e'
  exp_upper,      // 'E'
  fixed_lower,    // 'f'
  fixed_upper,    // 'F'
  general_lower,  // 'g'
  general_upper,  // 'G'
  chr,            // 'c'
  string,         // 's'
  pointer,        // 'p'
  debug           // '?'
};

// Format specifiers for built-in and string types.
template <typename Char>
struct basic_format_specs
{
  int width;
  int precision;
  presentation_type type;
  align_t align : 4;
  sign_t sign : 3;
  bool alt : 1; // Alternate form ('#').
  bool localized : 1;
  detail::fill_t<Char> fill;

  constexpr basic_format_specs()
      : width(0)
      , precision(-1)
      , type(presentation_type::none)
      , align(align::none)
      , sign(sign::none)
      , alt(false)
      , localized(false)
  {
  }
};

using format_specs = basic_format_specs<char>;

FMT_BEGIN_DETAIL_NAMESPACE

enum class arg_id_kind
{
  none,
  index,
  name
};

// An argument reference.
template <typename Char>
struct arg_ref
{
  FMT_CONSTEXPR arg_ref()
      : kind(arg_id_kind::none)
      , val()
  {
  }

  FMT_CONSTEXPR explicit arg_ref(int index)
      : kind(arg_id_kind::index)
      , val(index)
  {
  }
  FMT_CONSTEXPR explicit arg_ref(basic_string_view<Char> name)
      : kind(arg_id_kind::name)
      , val(name)
  {
  }

  FMT_CONSTEXPR auto operator=(int idx) -> arg_ref&
  {
    kind      = arg_id_kind::index;
    val.index = idx;
    return *this;
  }

  arg_id_kind kind;
  union Value
  {
    FMT_CONSTEXPR Value(int id = 0) // NOLINT(google-explicit-constructor)
        : index {id}
    {
    }
    FMT_CONSTEXPR Value(basic_string_view<Char> n) // NOLINT(google-explicit-constructor)
        : name(n)
    {
    }

    int index;
    basic_string_view<Char> name;
  } val;
};

// Format specifiers with width and precision resolved at formatting rather
// than parsing time to allow re-using the same parsed specifiers with
// different sets of arguments (precompilation of format strings).
template <typename Char>
struct dynamic_format_specs : basic_format_specs<Char>
{
  arg_ref<Char> width_ref;
  arg_ref<Char> precision_ref;
};

struct auto_id
{
};

// A format specifier handler that sets fields in basic_format_specs.
template <typename Char>
class specs_setter
{
protected:
  basic_format_specs<Char>& m_specs; // NOLINT(misc-non-private-member-variables-in-classes, cppcoreguidelines-avoid-const-or-ref-data-members)

public:
  explicit FMT_CONSTEXPR specs_setter(basic_format_specs<Char>& specs)
      : m_specs(specs)
  {
  }

  FMT_CONSTEXPR specs_setter(const specs_setter& other)
      : m_specs(other.m_specs)
  {
  }
  ~specs_setter() = default; // constexpr dtor exists in C++20

  FMT_CONSTEXPR void on_align(align_t align)
  {
    m_specs.align = align;
  }
  FMT_CONSTEXPR void on_fill(basic_string_view<Char> fill)
  {
    m_specs.fill = fill;
  }
  FMT_CONSTEXPR void on_sign(sign_t s)
  {
    m_specs.sign = s;
  }
  FMT_CONSTEXPR void on_hash()
  {
    m_specs.alt = true;
  }
  FMT_CONSTEXPR void on_localized()
  {
    m_specs.localized = true;
  }

  FMT_CONSTEXPR void on_zero()
  {
    if(m_specs.align == align::none)
      m_specs.align = align::numeric;
    m_specs.fill[0] = Char('0'); // NOLINT(google-readability-casting)
  }

  FMT_CONSTEXPR void on_width(int width)
  {
    m_specs.width = width;
  }
  FMT_CONSTEXPR void on_precision(int precision)
  {
    m_specs.precision = precision;
  }
  FMT_CONSTEXPR void end_precision() {}

  FMT_CONSTEXPR void on_type(presentation_type type)
  {
    m_specs.type = type;
  }

  FMT_CONSTEXPR specs_setter& operator=(const specs_setter&) = default;
};

// Format spec handler that saves references to arguments representing dynamic
// width and precision to be resolved at formatting time.
template <typename ParseContext>
class dynamic_specs_handler : public specs_setter<typename ParseContext::char_type>
{
public:
  using char_type = typename ParseContext::char_type;

  FMT_CONSTEXPR dynamic_specs_handler(dynamic_format_specs<char_type>& specs, ParseContext& ctx)
      : specs_setter<char_type>(specs)
      , m_specs(specs)
      , m_context(ctx)
  {
  }

  FMT_CONSTEXPR dynamic_specs_handler(const dynamic_specs_handler& other)
      : specs_setter<char_type>(other)
      , m_specs(other.m_specs)
      , m_context(other.m_context)
  {
  }

  ~dynamic_specs_handler() = default; // constexpr dtor exists in C++20

  FMT_CONSTEXPR dynamic_specs_handler& operator=(const dynamic_specs_handler&) = default;

  template <typename Id>
  FMT_CONSTEXPR void on_dynamic_width(Id argId)
  {
    m_specs.width_ref = make_arg_ref(argId);
  }

  template <typename Id>
  FMT_CONSTEXPR void on_dynamic_precision(Id argId)
  {
    m_specs.precision_ref = make_arg_ref(argId);
  }

  FMT_CONSTEXPR void on_error(const char* message)
  {
    m_context.on_error(message);
  }

private:
  dynamic_format_specs<char_type>& m_specs; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
  ParseContext& m_context;                  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

  using arg_ref_type = arg_ref<char_type>;

  FMT_CONSTEXPR auto make_arg_ref(int argId) -> arg_ref_type
  {
    m_context.check_arg_id(argId);
    m_context.check_dynamic_spec(argId);
    return arg_ref_type(argId);
  }

  FMT_CONSTEXPR auto make_arg_ref(auto_id /*unused*/) -> arg_ref_type
  {
    const int arg_id = m_context.next_arg_id();
    m_context.check_dynamic_spec(arg_id);
    return arg_ref_type(arg_id);
  }

  FMT_CONSTEXPR auto make_arg_ref(basic_string_view<char_type> argId) -> arg_ref_type
  {
    m_context.check_arg_id(argId);
    const basic_string_view<char_type> format_str(rsl::iterator_to_pointer(m_context.begin()), to_unsigned(static_cast<count_t>(m_context.end() - m_context.begin())));
    return arg_ref_type(argId);
  }
};

template <typename Char>
constexpr bool is_ascii_letter(Char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Converts a character to ASCII. Returns a number > 127 on conversion failure.
template <typename Char, FMT_ENABLE_IF(rsl::is_integral<Char>::value)>
constexpr auto to_ascii(Char c) -> Char
{
  return c;
}
template <typename Char, FMT_ENABLE_IF(rsl::is_enum<Char>::value)>
constexpr auto to_ascii(Char c) -> underlying_type_t<Char>
{
  return c;
}

template <typename Char>
FMT_CONSTEXPR auto code_point_length(const Char* begin) -> int
{
  if(const_check(sizeof(Char) != 1))
    return 1;
  const auto* lengths = "\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\0\0\0\0\0\0\0\0\2\2\2\2\3\3\4";
  const int len       = lengths[static_cast<unsigned char>(*begin) >> 3]; // NOLINT(bugprone-signed-char-misuse)

  // Compute the pointer to the next character early so that the next
  // iteration can start working on the next character. Neither Clang
  // nor GCC figure out this reordering on their own.
  return len + !len;
}

// Return the result via the out param to workaround gcc bug 77539.
template <bool IsConstexpr, typename T, typename Ptr = const T*>
FMT_CONSTEXPR auto find(Ptr first, Ptr last, T value, Ptr& out) -> bool
{
  for(out = first; out != last; ++out)
  {
    if(*out == value)
      return true;
  }
  return false;
}

template <>
inline auto find<false, char>(const char* first, const char* last, char value, const char*& out) -> bool
{
  out = static_cast<const char*>(rsl::memchr(first, value, to_unsigned(static_cast<count_t>(last - first)))); // NOLINT(cppcoreguidelines-narrowing-conversions)
  return out != nullptr;
}

// Parses the range [begin, end) as an unsigned integer. This function assumes
// that the range is non-empty and the first character is a digit.
template <typename Char>
FMT_CONSTEXPR auto parse_nonnegative_int(const Char*& begin, const Char* end, int errorValue) noexcept -> int
{
  FMT_ASSERT(begin != end && '0' <= *begin && *begin <= '9', "");
  unsigned value = 0, prev = 0; // NOLINT(readability-isolate-declaration)
  auto p = begin;
  do
  {
    prev  = value;
    value = value * 10 + unsigned(*p - '0'); // NOLINT(google-readability-casting)
    ++p;
  } while(p != end && '0' <= *p && *p <= '9');
  auto num_digits = p - begin;
  begin           = p;
  if(num_digits <= rsl::numeric_limits<int>::digits10)
    return static_cast<int>(value);
  // Check for overflow.
  const unsigned max = to_unsigned((rsl::numeric_limits<int>::max)());
  return num_digits == rsl::numeric_limits<int>::digits10 + 1 && prev * 10ull + unsigned(p[-1] - '0') <= max ? static_cast<int>(value) : errorValue; // NOLINT(google-readability-casting)
}

// Parses fill and alignment.
template <typename Char, typename Handler>
FMT_CONSTEXPR auto parse_align(const Char* begin, const Char* end, Handler&& handler) -> const Char*
{
  FMT_ASSERT(begin != end, "");
  auto align = align::none;
  auto p     = begin + code_point_length(begin);
  if(end - p <= 0)
    p = begin;
  for(;;)
  {
    switch(to_ascii(*p))
    {
      case '<': align = align::left; break;
      case '>': align = align::right; break;
      case '^': align = align::center; break;
      default: break;
    }
    if(align != align::none)
    {
      if(p != begin)
      {
        auto c = *begin;
        if(c == '{')
          return handler.on_error("invalid fill character '{'"), begin;
        handler.on_fill(basic_string_view<Char>(begin, to_unsigned(static_cast<count_t>(p - begin))));
        begin = p + 1;
      }
      else
        ++begin;
      handler.on_align(align);
      break;
    }
    else if(p == begin)
    {
      break;
    }
    p = begin;
  }
  return begin;
}

template <typename Char>
FMT_CONSTEXPR bool is_name_start(Char c)
{
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || '_' == c;
}

template <typename Char, typename IDHandler>
FMT_CONSTEXPR auto do_parse_arg_id(const Char* begin, const Char* end, IDHandler&& handler) -> const Char*
{
  FMT_ASSERT(begin != end, "");
  Char c = *begin;
  if(c >= '0' && c <= '9')
  {
    int index = 0;
    if(c != '0')
    {
      index = parse_nonnegative_int(begin, end, (rsl::numeric_limits<int>::max)());
    }
    else
    {
      ++begin;
    }
    if(begin == end || (*begin != '}' && *begin != ':'))
    {
      handler.on_error("invalid format string");
    }
    else
    {
      handler(index);
    }
    return begin;
  }
  if(!is_name_start(c))
  {
    handler.on_error("invalid format string");
    return begin;
  }
  auto it = begin;
  do
  {
    ++it;
  } while(it != end && (is_name_start(c = *it) || ('0' <= c && c <= '9')));
  handler(basic_string_view<Char>(begin, to_unsigned(static_cast<count_t>(it - begin))));
  return it;
}

template <typename Char, typename IDHandler>
FMT_CONSTEXPR FMT_INLINE auto parse_arg_id(const Char* begin, const Char* end, IDHandler&& handler) -> const Char*
{
  Char c = *begin;
  if(c != '}' && c != ':')
    return do_parse_arg_id(begin, end, handler);
  handler();
  return begin;
}

template <typename Char, typename Handler>
FMT_CONSTEXPR auto parse_width(const Char* begin, const Char* end, Handler&& handler) -> const Char*
{
  using detail::auto_id;
  struct width_adapter
  {
    Handler& handler; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

    FMT_CONSTEXPR void operator()()
    {
      handler.on_dynamic_width(auto_id());
    }
    FMT_CONSTEXPR void operator()(int id)
    {
      handler.on_dynamic_width(id);
    }
    FMT_CONSTEXPR void operator()(basic_string_view<Char> id)
    {
      handler.on_dynamic_width(id);
    }
    FMT_CONSTEXPR void on_error(const char* message)
    {
      if(message)
        handler.on_error(message);
    }
  };

  FMT_ASSERT(begin != end, "");
  if('0' <= *begin && *begin <= '9')
  {
    const int width = parse_nonnegative_int(begin, end, -1);
    if(width != -1)
    {
      handler.on_width(width);
    }
    else
    {
      handler.on_error("number is too big");
    }
  }
  else if(*begin == '{')
  {
    ++begin;
    if(begin != end)
      begin = parse_arg_id(begin, end, width_adapter {handler});
    if(begin == end || *begin != '}')
      return handler.on_error("invalid format string"), begin;
    ++begin;
  }
  return begin;
}

template <typename Char, typename Handler>
FMT_CONSTEXPR auto parse_precision(const Char* begin, const Char* end, Handler&& handler) -> const Char*
{
  using detail::auto_id;
  struct precision_adapter
  {
    Handler& handler; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

    FMT_CONSTEXPR void operator()()
    {
      handler.on_dynamic_precision(auto_id());
    }
    FMT_CONSTEXPR void operator()(int id)
    {
      handler.on_dynamic_precision(id);
    }
    FMT_CONSTEXPR void operator()(basic_string_view<Char> id)
    {
      handler.on_dynamic_precision(id);
    }
    FMT_CONSTEXPR void on_error(const char* message)
    {
      if(message)
        handler.on_error(message);
    }
  };

  ++begin;
  auto c = begin != end ? *begin : Char();
  if('0' <= c && c <= '9')
  {
    auto precision = parse_nonnegative_int(begin, end, -1);
    if(precision != -1)
    {
      handler.on_precision(precision);
    }
    else
    {
      handler.on_error("number is too big");
    }
  }
  else if(c == '{')
  {
    ++begin;
    if(begin != end)
      begin = parse_arg_id(begin, end, precision_adapter {handler});
    if(begin == end || *begin++ != '}')
      return handler.on_error("invalid format string"), begin;
  }
  else
  {
    return handler.on_error("missing precision specifier"), begin;
  }
  handler.end_precision();
  return begin;
}

template <typename Char>
FMT_CONSTEXPR auto parse_presentation_type(Char type) -> presentation_type
{
  switch(to_ascii(type))
  {
    case 'd': return presentation_type::dec;
    case 'o': return presentation_type::oct;
    case 'x': return presentation_type::hex_lower;
    case 'X': return presentation_type::hex_upper;
    case 'b': return presentation_type::bin_lower;
    case 'B': return presentation_type::bin_upper;
    case 'a': return presentation_type::hexfloat_lower;
    case 'A': return presentation_type::hexfloat_upper;
    case 'e': return presentation_type::exp_lower;
    case 'E': return presentation_type::exp_upper;
    case 'f': return presentation_type::fixed_lower;
    case 'F': return presentation_type::fixed_upper;
    case 'g': return presentation_type::general_lower;
    case 'G': return presentation_type::general_upper;
    case 'c': return presentation_type::chr;
    case 's': return presentation_type::string;
    case 'p': return presentation_type::pointer;
    case '?': return presentation_type::debug;
    default: return presentation_type::none;
  }
}

// Parses standard format specifiers and sends notifications about parsed
// components to handler.
template <typename Char, typename SpecHandler>
FMT_CONSTEXPR FMT_INLINE auto parse_format_specs(const Char* begin, const Char* end, SpecHandler&& handler) -> const Char*
{
  if(1 < end - begin && begin[1] == '}' && is_ascii_letter(*begin) && *begin != 'L')
  {
    const presentation_type type = parse_presentation_type(*begin++);
    if(type == presentation_type::none)
      handler.on_error("invalid type specifier");
    handler.on_type(type);
    return begin;
  }

  if(begin == end)
    return begin;

  begin = parse_align(begin, end, handler);
  if(begin == end)
    return begin;

  // Parse sign.
  switch(to_ascii(*begin))
  {
    case '+':
      handler.on_sign(sign::plus);
      ++begin;
      break;
    case '-':
      handler.on_sign(sign::minus);
      ++begin;
      break;
    case ' ':
      handler.on_sign(sign::space);
      ++begin;
      break;
    default: break;
  }
  if(begin == end)
    return begin;

  if(*begin == '#')
  {
    handler.on_hash();
    if(++begin == end)
      return begin;
  }

  // Parse zero flag.
  if(*begin == '0')
  {
    handler.on_zero();
    if(++begin == end)
      return begin;
  }

  begin = parse_width(begin, end, handler);
  if(begin == end)
    return begin;

  // Parse precision.
  if(*begin == '.')
  {
    begin = parse_precision(begin, end, handler);
    if(begin == end)
      return begin;
  }

  if(*begin == 'L')
  {
    handler.on_localized();
    ++begin;
  }

  // Parse type.
  if(begin != end && *begin != '}')
  {
    const presentation_type type = parse_presentation_type(*begin++);
    if(type == presentation_type::none)
      handler.on_error("invalid type specifier");
    handler.on_type(type);
  }
  return begin;
}

template <typename Char, typename Handler>
FMT_CONSTEXPR auto parse_replacement_field(const Char* begin, const Char* end, Handler&& handler) -> const Char*
{
  struct id_adapter
  {
    Handler& handler; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    int arg_id;

    FMT_CONSTEXPR void operator()()
    {
      arg_id = handler.on_arg_id();
    }
    FMT_CONSTEXPR void operator()(int id)
    {
      arg_id = handler.on_arg_id(id);
    }
    FMT_CONSTEXPR void operator()(basic_string_view<Char> id)
    {
      arg_id = handler.on_arg_id(id);
    }
    FMT_CONSTEXPR void on_error(const char* message)
    {
      if(message)
        handler.on_error(message);
    }
  };

  ++begin;
  if(begin == end)
    return handler.on_error("invalid format string"), end;
  if(*begin == '}')
  {
    handler.on_replacement_field(handler.on_arg_id(), begin);
  }
  else if(*begin == '{')
  {
    handler.on_text(begin, begin + 1);
  }
  else
  {
    auto adapter = id_adapter {handler, 0};
    begin        = parse_arg_id(begin, end, adapter);
    Char c       = begin != end ? *begin : Char();
    if(c == '}')
    {
      handler.on_replacement_field(adapter.arg_id, begin);
    }
    else if(c == ':')
    {
      begin = handler.on_format_specs(adapter.arg_id, begin + 1, end);
      if(begin == end || *begin != '}')
        return handler.on_error("unknown format specifier"), end;
    }
    else
    {
      return handler.on_error("missing '}' in format string"), end;
    }
  }
  return begin + 1;
}

template <bool IsConstexpr, typename Char, typename Handler>
FMT_CONSTEXPR FMT_INLINE void parse_format_string(basic_string_view<Char> formatStr, Handler&& handler) // NOLINT(readability-function-cognitive-complexity)
{
  // Workaround a name-lookup bug in MSVC's modules implementation.
  using detail::find;

  auto begin = formatStr.data();
  auto end   = begin + formatStr.size();
  if(end - begin < 32)
  {
    // Use a simple loop instead of memchr for small strings.
    const Char* p = begin;
    while(p != end)
    {
      auto c = *p++;
      if(c == '{')
      {
        handler.on_text(begin, p - 1);
        begin = p = parse_replacement_field(p - 1, end, handler);
      }
      else if(c == '}')
      {
        if(p == end || *p != '}')
          return handler.on_error("unmatched '}' in format string");
        handler.on_text(begin, p);
        begin = ++p;
      }
    }
    handler.on_text(begin, end);
    return;
  }
  struct writer
  {
    FMT_CONSTEXPR void operator()(const Char* from, const Char* to)
    {
      if(from == to)
        return;
      for(;;)
      {
        const Char* p = nullptr;
        if(!find<IsConstexpr>(from, to, Char('}'), p)) // NOLINT(google-readability-casting)
          return handler.on_text(from, to);
        ++p;
        if(p == to || *p != '}')
          return handler.on_error("unmatched '}' in format string");
        handler.on_text(from, p);
        from = p + 1;
      }
    }
    Handler& handler; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
  } write = {handler};
  while(begin != end)
  {
    // Doing two passes with memchr (one for '{' and another for '}') is up to
    // 2.5x faster than the naive one-pass implementation on big format strings.
    const Char* p = begin;
    if(*begin != '{' && !find<IsConstexpr>(begin + 1, end, Char('{'), p)) // NOLINT(google-readability-casting)
      return write(begin, end);
    write(begin, p);
    begin = parse_replacement_field(p, end, handler);
  }
}

template <typename T, bool = is_named_arg<T>::value>
struct strip_named_arg
{
  using type = T;
};
template <typename T>
struct strip_named_arg<T, true>
{
  using type = remove_cvref_t<decltype(T::value)>;
};

template <typename T, typename ParseContext>
FMT_CONSTEXPR auto parse_format_specs(ParseContext& ctx) -> decltype(rsl::iterator_to_pointer(ctx.begin()))
{
  using char_type     = typename ParseContext::char_type;
  using context       = buffer_context<char_type>;
  using stripped_type = typename strip_named_arg<T>::type;
  using mapped_type   = conditional_t<mapped_type_constant<T, context>::value != type::custom_type, decltype(arg_mapper<context>().map(rsl::declval<const T&>())), stripped_type>;
  auto f              = conditional_t<has_formatter<mapped_type, context>::value, formatter<mapped_type, char_type>, fallback_formatter<stripped_type, char_type>>();
  using return_type   = decltype(rsl::iterator_to_pointer(ctx.begin()));
  return return_type(rsl::iterator_to_pointer(f.parse(ctx))); // NOLINT(google-readability-casting)
}

template <typename ErrorHandler>
FMT_CONSTEXPR void check_int_type_spec(presentation_type type, ErrorHandler&& eh)
{
  if(type > presentation_type::bin_upper && type != presentation_type::chr)
    eh.on_error("invalid type specifier");
}

// Checks char specs and returns true if the type spec is char (and not int).
template <typename Char, typename ErrorHandler = error_handler>
FMT_CONSTEXPR auto check_char_specs(const basic_format_specs<Char>& specs, ErrorHandler&& eh = {}) -> bool
{
  if(specs.type != presentation_type::none && specs.type != presentation_type::chr && specs.type != presentation_type::debug)
  {
    check_int_type_spec(specs.type, eh);
    return false;
  }
  if(specs.align == align::numeric || specs.sign != sign::none || specs.alt)
    eh.on_error("invalid format specifier for char");
  return true;
}

// A floating-point presentation format.
enum class float_format : unsigned char
{
  general, // General: exponent notation or fixed point based on magnitude.
  exp,     // Exponent notation with the default precision of 6, e.g. 1.2e-3.
  fixed,   // Fixed point with the default precision of 6, e.g. 0.0012.
  hex
};

struct float_specs
{
  int precision;
  float_format format : 8;
  sign_t sign : 8;
  bool upper : 1;
  bool locale : 1;
  bool binary32 : 1;
  bool showpoint : 1;
};

template <typename ErrorHandler = error_handler, typename Char>
FMT_CONSTEXPR auto parse_float_type_spec(const basic_format_specs<Char>& specs, ErrorHandler&& eh = {}) -> float_specs
{
  auto result      = float_specs();
  result.showpoint = specs.alt;
  result.locale    = specs.localized;
  switch(specs.type)
  {
    case presentation_type::none: result.format = float_format::general; break;
    case presentation_type::general_upper: result.upper = true; FMT_FALLTHROUGH;
    case presentation_type::general_lower: result.format = float_format::general; break;
    case presentation_type::exp_upper: result.upper = true; FMT_FALLTHROUGH;
    case presentation_type::exp_lower:
      result.format = float_format::exp;
      result.showpoint |= specs.precision != 0;
      break;
    case presentation_type::fixed_upper: result.upper = true; FMT_FALLTHROUGH;
    case presentation_type::fixed_lower:
      result.format = float_format::fixed;
      result.showpoint |= specs.precision != 0;
      break;
    case presentation_type::hexfloat_upper: result.upper = true; FMT_FALLTHROUGH;
    case presentation_type::hexfloat_lower: result.format = float_format::hex; break;
    default: eh.on_error("invalid type specifier"); break;
  }
  return result;
}

template <typename ErrorHandler = error_handler>
FMT_CONSTEXPR auto check_cstring_type_spec(presentation_type type, ErrorHandler&& eh = {}) -> bool
{
  if(type == presentation_type::none || type == presentation_type::string || type == presentation_type::debug)
    return true;
  if(type != presentation_type::pointer)
    eh.on_error("invalid type specifier");
  return false;
}

template <typename ErrorHandler = error_handler>
FMT_CONSTEXPR void check_string_type_spec(presentation_type type, ErrorHandler&& eh = {})
{
  if(type != presentation_type::none && type != presentation_type::string && type != presentation_type::debug)
    eh.on_error("invalid type specifier");
}

template <typename ErrorHandler>
FMT_CONSTEXPR void check_pointer_type_spec(presentation_type type, ErrorHandler&& eh)
{
  if(type != presentation_type::none && type != presentation_type::pointer)
    eh.on_error("invalid type specifier");
}

// A parse_format_specs handler that checks if specifiers are consistent with
// the argument type.
template <typename Handler>
class specs_checker : public Handler
{
private:
  detail::type m_arg_type;

  FMT_CONSTEXPR void require_numeric_argument()
  {
    if(!is_arithmetic_type(m_arg_type))
      this->on_error("format specifier requires numeric argument");
  }

public:
  FMT_CONSTEXPR specs_checker(const Handler& handler, detail::type argType)
      : Handler(handler)
      , m_arg_type(argType)
  {
  }

  FMT_CONSTEXPR void on_align(align_t align)
  {
    if(align == align::numeric)
      require_numeric_argument();
    Handler::on_align(align);
  }

  FMT_CONSTEXPR void on_sign(sign_t s)
  {
    require_numeric_argument();
    if(is_integral_type(m_arg_type) && m_arg_type != type::int_type && m_arg_type != type::long_long_type && m_arg_type != type::int128_type && m_arg_type != type::char_type)
    {
      this->on_error("format specifier requires signed argument");
    }
    Handler::on_sign(s);
  }

  FMT_CONSTEXPR void on_hash()
  {
    require_numeric_argument();
    Handler::on_hash();
  }

  FMT_CONSTEXPR void on_localized()
  {
    require_numeric_argument();
    Handler::on_localized();
  }

  FMT_CONSTEXPR void on_zero()
  {
    require_numeric_argument();
    Handler::on_zero();
  }

  FMT_CONSTEXPR void end_precision()
  {
    if(is_integral_type(m_arg_type) || m_arg_type == type::pointer_type)
      this->on_error("precision not allowed for this argument type");
  }
};

#if FMT_USE_NONTYPE_TEMPLATE_ARGS
template <int N, typename T, typename... Args, typename Char>
constexpr auto get_arg_index_by_name(basic_string_view<Char> name) -> int
{
  if constexpr(detail::is_statically_named_arg<T>())
  {
    if(name == T::name)
      return N;
  }
  if constexpr(sizeof...(Args) > 0)
    return get_arg_index_by_name<N + 1, Args...>(name);
  (void)name; // Workaround an MSVC bug about "unused" parameter.
  return invalid_arg_index;
}
#endif

template <typename... Args, typename Char>
FMT_CONSTEXPR auto get_arg_index_by_name(basic_string_view<Char> name) -> int
{
#if FMT_USE_NONTYPE_TEMPLATE_ARGS
  if constexpr(sizeof...(Args) > 0)
    return get_arg_index_by_name<0, Args...>(name);
#endif
  (void)name;
  return invalid_arg_index;
}
template <typename Char>
void vformat_to(buffer<Char>& buf, basic_string_view<Char> fmt, basic_format_args<FMT_BUFFER_CONTEXT(type_identity_t<Char>)> args, locale_ref loc = {});

FMT_API void vprint_mojibake(std::FILE* /*f*/, string_view /*format_str*/, format_args /*args*/);
#ifndef _WIN32
inline void vprint_mojibake(std::FILE*, string_view, format_args) {}
#endif
FMT_END_DETAIL_NAMESPACE

// A formatter specialization for the core types corresponding to detail::type
// constants.
template <typename T, typename Char>
struct formatter<T, Char, enable_if_t<detail::type_constant<T, Char>::value != detail::type::custom_type>>
{
private:
  detail::dynamic_format_specs<Char> m_specs;

public:
  // Parses format specifiers stopping either at the end of the range or at the
  // terminating '}'.
  template <typename ParseContext>
  FMT_CONSTEXPR auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    auto begin = ctx.begin(), end = ctx.end(); // NOLINT(readability-isolate-declaration)
    if(begin == end)
      return begin;
    using handler_type = detail::dynamic_specs_handler<ParseContext>;
    auto type          = detail::type_constant<T, Char>::value;
    auto checker       = detail::specs_checker<handler_type>(handler_type(m_specs, ctx), type);
    auto it            = detail::parse_format_specs(rsl::iterator_to_pointer(begin), rsl::iterator_to_pointer(end), checker);
    auto eh            = ctx.error_handler();
    switch(type)
    {
      case detail::type::none_type: FMT_ASSERT(false, "invalid argument type"); break;
      case detail::type::bool_type:
        if(m_specs.type == presentation_type::none || m_specs.type == presentation_type::string)
        {
          break;
        }
        FMT_FALLTHROUGH;
      case detail::type::int_type:
      case detail::type::uint_type:
      case detail::type::long_long_type:
      case detail::type::ulong_long_type:
      case detail::type::int128_type:
      case detail::type::uint128_type: detail::check_int_type_spec(m_specs.type, eh); break;
      case detail::type::char_type: detail::check_char_specs(m_specs, eh); break;
      case detail::type::float_type:
        if(detail::const_check(FMT_USE_FLOAT))
        {
          detail::parse_float_type_spec(m_specs, eh);
        }
        else
        {
          FMT_ASSERT(false, "float support disabled");
        }
        break;
      case detail::type::double_type:
        if(detail::const_check(FMT_USE_DOUBLE))
        {
          detail::parse_float_type_spec(m_specs, eh);
        }
        else
        {
          FMT_ASSERT(false, "double support disabled");
        }
        break;
      case detail::type::long_double_type:
        if(detail::const_check(FMT_USE_LONG_DOUBLE))
        {
          detail::parse_float_type_spec(m_specs, eh);
        }
        else
        {
          FMT_ASSERT(false, "long double support disabled");
        }
        break;
      case detail::type::cstring_type: detail::check_cstring_type_spec(m_specs.type, eh); break;
      case detail::type::string_type: detail::check_string_type_spec(m_specs.type, eh); break;
      case detail::type::pointer_type: detail::check_pointer_type_spec(m_specs.type, eh); break;
      case detail::type::custom_type:
        // Custom format specifiers are checked in parse functions of
        // formatter specializations.
        break;
    }

    using return_type = decltype(ctx.begin());
    return return_type(it);
  }

  template <detail::type U = detail::type_constant<T, Char>::value, enable_if_t<(U == detail::type::string_type || U == detail::type::cstring_type || U == detail::type::char_type), int> = 0>
  FMT_CONSTEXPR void set_debug_format()
  {
    m_specs.type = presentation_type::debug;
  }

  template <typename FormatContext>
  FMT_CONSTEXPR auto format(const T& val, FormatContext& ctx) const -> decltype(ctx.out());
};

#define FMT_FORMAT_AS(Type, Base)                                                                                                                                                                                                                        \
  template <typename Char>                                                                                                                                                                                                                               \
  struct formatter<Type, Char> : formatter<Base, Char>                                                                                                                                                                                                   \
  {                                                                                                                                                                                                                                                      \
    template <typename FormatContext>                                                                                                                                                                                                                    \
    auto format(Type const& val, FormatContext& ctx) const -> decltype(ctx.out())                                                                                                                                                                        \
    {                                                                                                                                                                                                                                                    \
      return formatter<Base, Char>::format(static_cast<Base>(val), ctx);                                                                                                                                                                                 \
    }                                                                                                                                                                                                                                                    \
  }

FMT_FORMAT_AS(signed char, int);
FMT_FORMAT_AS(unsigned char, unsigned);
FMT_FORMAT_AS(short, int);
FMT_FORMAT_AS(unsigned short, unsigned);
FMT_FORMAT_AS(long, long long);
FMT_FORMAT_AS(unsigned long, unsigned long long);
FMT_FORMAT_AS(char*, const char*);
using fmt_string = rsl::basic_string<char, rsl::char_traits<char>, rsl::allocator>;
FMT_FORMAT_AS(rsl::fmt_string, basic_string_view<char>);
FMT_FORMAT_AS(rsl::nullptr_t, const void*);
// FMT_FORMAT_AS(detail::std_string_view<Char>, basic_string_view<Char>);

using fmt_stack_string = rsl::stack_string<char8, 500>;

FMT_API auto vformat(string_view fmt, format_args args) -> fmt_stack_string;

/**
  \rst
  Formats ``args`` according to specifications in ``fmt`` and returns the result
  as a string.

  **Example**::

    #include <fmt/core.h>
    rsl::string message = rsl::format("The answer is {}.", 42);
  \endrst
*/
template <typename... T>
FMT_NODISCARD FMT_INLINE auto format(format_string<T...> fmt, T&&... args) -> fmt_stack_string
{
  return vformat(fmt, rsl::make_format_args(args...));
}

/** Formats a string and writes the output to ``out``. */
template <typename OutputIt, FMT_ENABLE_IF(detail::is_output_iterator<OutputIt, char>::value)>
auto vformat_to(OutputIt out, string_view fmt, format_args args) -> OutputIt
{
  using detail::get_buffer;
  auto&& buf = get_buffer<char>(out);
  detail::vformat_to(buf, fmt, args, {});
  return detail::get_iterator(buf);
}

/**
 \rst
 Formats ``args`` according to specifications in ``fmt``, writes the result to
 the output iterator ``out`` and returns the iterator past the end of the output
 range. `format_to` does not append a terminating null character.

 **Example**::

   auto out = rsl::vector<char>();
   rsl::format_to(rsl::back_inserter(out), "{}", 42);
 \endrst
 */
template <typename OutputIt, typename... T, FMT_ENABLE_IF(detail::is_output_iterator<OutputIt, char>::value)>
FMT_INLINE auto format_to(OutputIt out, format_string<T...> fmt, T&&... args) -> OutputIt
{
  return vformat_to(out, fmt, rsl::make_format_args(args...));
}

template <typename OutputIt>
struct format_to_n_result
{
  /** Iterator past the end of the output range. */
  OutputIt out;
  /** Total (not truncated) output size. */
  count_t size;
};

template <typename OutputIt, typename... T, FMT_ENABLE_IF(detail::is_output_iterator<OutputIt, char>::value)>
auto vformat_to_n(OutputIt out, count_t n, string_view fmt, format_args args) -> format_to_n_result<OutputIt>
{
  using traits = detail::fixed_buffer_traits;
  auto buf     = detail::iterator_buffer<OutputIt, char, traits>(out, n);
  detail::vformat_to(buf, fmt, args, {});
  return {buf.out(), buf.count()};
}

/**
  \rst
  Formats ``args`` according to specifications in ``fmt``, writes up to ``n``
  characters of the result to the output iterator ``out`` and returns the total
  (not truncated) output size and the iterator past the end of the output range.
  `format_to_n` does not append a terminating null character.
  \endrst
 */
template <typename OutputIt, typename... T, FMT_ENABLE_IF(detail::is_output_iterator<OutputIt, char>::value)>
FMT_INLINE auto format_to_n(OutputIt out, count_t n, format_string<T...> fmt, T&&... args) -> format_to_n_result<OutputIt>
{
  return vformat_to_n(out, n, fmt, rsl::make_format_args(args...));
}

/** Returns the number of chars in the output of ``format(fmt, args...)``. */
template <typename... T>
FMT_NODISCARD FMT_INLINE auto formatted_size(format_string<T...> fmt, T&&... args) -> count_t
{
  auto buf = detail::counting_buffer<>();
  detail::vformat_to(buf, string_view(fmt), rsl::make_format_args(args...), {});
  return buf.count();
}

FMT_API void vprint(string_view formatString, format_args args);
FMT_API void vprint(std::FILE* f, string_view formatStr, format_args args);

/**
  \rst
  Formats ``args`` according to specifications in ``fmt`` and writes the output
  to ``stdout``.

  **Example**::

    rsl::print("Elapsed time: {0:.2f} seconds", 1.23);
  \endrst
 */
template <typename... T>
FMT_INLINE void print(format_string<T...> fmt, T&&... args)
{
  const auto& vargs = rsl::make_format_args(args...);
  return detail::is_utf8() ? vprint(fmt, vargs) : detail::vprint_mojibake(stdout, fmt, vargs);
}

/**
  \rst
  Formats ``args`` according to specifications in ``fmt`` and writes the
  output to the file ``f``.

  **Example**::

    rsl::print(stderr, "Don't {}!", "panic");
  \endrst
 */
template <typename... T>
FMT_INLINE void print(std::FILE* f, format_string<T...> fmt, T&&... args)
{
  const auto& vargs = rsl::make_format_args(args...);
  return detail::is_utf8() ? vprint(f, fmt, vargs) : detail::vprint_mojibake(f, fmt, vargs);
}

FMT_MODULE_EXPORT_END
FMT_GCC_PRAGMA("GCC pop_options")
FMT_END_NAMESPACE

#ifdef FMT_HEADER_ONLY
  #include "format.h"
#endif

// NOLINTEND

#endif // FMT_CORE_H_
