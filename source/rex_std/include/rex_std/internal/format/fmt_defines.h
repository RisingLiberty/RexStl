#pragma once

// The fmt library version in the form major * 10000 + minor * 100 + patch.
#define FMT_VERSION 90000

#if defined(__clang__) && !defined(__ibmxl__)
  #define FMT_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#else
  #define FMT_CLANG_VERSION 0
#endif

#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__NVCOMPILER)
  #define FMT_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#else
  #define FMT_GCC_VERSION 0
#endif

#ifndef FMT_GCC_PRAGMA
// Workaround _Pragma bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59884.
  #if FMT_GCC_VERSION >= 504
    #define FMT_GCC_PRAGMA(arg) _Pragma(arg)
  #else
    #define FMT_GCC_PRAGMA(arg)
  #endif
#endif

#ifdef __ICL
  #define FMT_ICC_VERSION __ICL
#elif defined(__INTEL_COMPILER)
  #define FMT_ICC_VERSION __INTEL_COMPILER
#else
  #define FMT_ICC_VERSION 0
#endif

#ifdef _MSC_VER
  #define FMT_MSC_VERSION      _MSC_VER
  #define FMT_MSC_WARNING(...) __pragma(warning(__VA_ARGS__))
#else
  #define FMT_MSC_VERSION 0
  #define FMT_MSC_WARNING(...)
#endif

#ifdef _MSVC_LANG
  #define FMT_CPLUSPLUS _MSVC_LANG
#else
  #define FMT_CPLUSPLUS __cplusplus
#endif

#ifdef __has_feature
  #define FMT_HAS_FEATURE(x) __has_feature(x)
#else
  #define FMT_HAS_FEATURE(x) 0
#endif

#if(defined(__has_include) || FMT_ICC_VERSION >= 1600 || FMT_MSC_VERSION > 1900) && !defined(__INTELLISENSE__)
  #define FMT_HAS_INCLUDE(x) __has_include(x)
#else
  #define FMT_HAS_INCLUDE(x) 0
#endif

#ifdef __has_cpp_attribute
  #define FMT_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
  #define FMT_HAS_CPP_ATTRIBUTE(x) 0
#endif

#define FMT_HAS_CPP14_ATTRIBUTE(attribute) (FMT_CPLUSPLUS >= 201402L && FMT_HAS_CPP_ATTRIBUTE(attribute))

#define FMT_HAS_CPP17_ATTRIBUTE(attribute) (FMT_CPLUSPLUS >= 201703L && FMT_HAS_CPP_ATTRIBUTE(attribute))

// Check if relaxed C++14 constexpr is supported.
// GCC doesn't allow throw in constexpr until version 6 (bug 67371).
#ifndef FMT_USE_CONSTEXPR
  #if(FMT_HAS_FEATURE(cxx_relaxed_constexpr) || FMT_MSC_VERSION >= 1912 || (FMT_GCC_VERSION >= 600 && FMT_CPLUSPLUS >= 201402L)) && !FMT_ICC_VERSION && !defined(__NVCC__)
    #define FMT_USE_CONSTEXPR 1
  #else
    #define FMT_USE_CONSTEXPR 0
  #endif
#endif
#if FMT_USE_CONSTEXPR
  #define FMT_CONSTEXPR constexpr
#else
  #define FMT_CONSTEXPR
#endif

#if((FMT_CPLUSPLUS >= 202002L) && (!defined(_GLIBCXX_RELEASE) || _GLIBCXX_RELEASE > 9)) || (FMT_CPLUSPLUS >= 201709L && FMT_GCC_VERSION >= 1002)
  #define FMT_CONSTEXPR20 constexpr
#else
  #define FMT_CONSTEXPR20
#endif

// Check if constexpr rsl::char_traits<>::{compare,length} are supported.
#if defined(__GLIBCXX__)
  #if FMT_CPLUSPLUS >= 201703L && defined(_GLIBCXX_RELEASE) && _GLIBCXX_RELEASE >= 7 // GCC 7+ libstdc++ has _GLIBCXX_RELEASE.
    #define FMT_CONSTEXPR_CHAR_TRAITS constexpr
  #endif
#elif defined(_LIBCPP_VERSION) && FMT_CPLUSPLUS >= 201703L && _LIBCPP_VERSION >= 4000
  #define FMT_CONSTEXPR_CHAR_TRAITS constexpr
#elif FMT_MSC_VERSION >= 1914 && FMT_CPLUSPLUS >= 201703L
  #define FMT_CONSTEXPR_CHAR_TRAITS constexpr
#endif
#ifndef FMT_CONSTEXPR_CHAR_TRAITS
  #define FMT_CONSTEXPR_CHAR_TRAITS
#endif

// Check if exceptions are disabled.
/// [15/Sep/2022] RSL Comment: Rex Standard Library doesn't use exceptions
#define FMT_EXCEPTIONS 0
// #ifndef FMT_EXCEPTIONS
// #  if (defined(__GNUC__) && !defined(__EXCEPTIONS)) || \
//       (FMT_MSC_VERSION && !_HAS_EXCEPTIONS)
// #    define FMT_EXCEPTIONS 0
// #  else
// #    define FMT_EXCEPTIONS 1
// #  endif
// #endif

#ifndef FMT_DEPRECATED
  #if FMT_HAS_CPP14_ATTRIBUTE(deprecated) || FMT_MSC_VERSION >= 1900
    #define FMT_DEPRECATED [[deprecated]]
  #else
    #if(defined(__GNUC__) && !defined(__LCC__)) || defined(__clang__)
      #define FMT_DEPRECATED __attribute__((deprecated))
    #elif FMT_MSC_VERSION
      #define FMT_DEPRECATED __declspec(deprecated)
    #else
      #define FMT_DEPRECATED /* deprecated */
    #endif
  #endif
#endif

// [[noreturn]] is disabled on MSVC and NVCC because of bogus unreachable code
// warnings.
#if FMT_EXCEPTIONS && FMT_HAS_CPP_ATTRIBUTE(noreturn) && !FMT_MSC_VERSION && !defined(__NVCC__)
  #define FMT_NORETURN [[noreturn]]
#else
  #define FMT_NORETURN
#endif

#if FMT_HAS_CPP17_ATTRIBUTE(fallthrough)
  #define FMT_FALLTHROUGH [[fallthrough]]
#elif defined(__clang__)
  #define FMT_FALLTHROUGH [[clang::fallthrough]]
#elif FMT_GCC_VERSION >= 700 && (!defined(__EDG_VERSION__) || __EDG_VERSION__ >= 520)
  #define FMT_FALLTHROUGH [[gnu::fallthrough]]
#else
  #define FMT_FALLTHROUGH
#endif

#ifndef FMT_NODISCARD
  #if FMT_HAS_CPP17_ATTRIBUTE(nodiscard)
    #define FMT_NODISCARD [[nodiscard]]
  #else
    #define FMT_NODISCARD
  #endif
#endif

#ifndef FMT_USE_FLOAT
  #define FMT_USE_FLOAT 1
#endif
#ifndef FMT_USE_DOUBLE
  #define FMT_USE_DOUBLE 1
#endif
#ifndef FMT_USE_LONG_DOUBLE
  #define FMT_USE_LONG_DOUBLE 1
#endif

#ifndef FMT_INLINE
  #if FMT_GCC_VERSION || FMT_CLANG_VERSION
    #define FMT_INLINE inline __attribute__((always_inline))
  #else
    #define FMT_INLINE inline
  #endif
#endif

// An inline rsl::forward replacement.
#define FMT_FORWARD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

#ifdef _MSC_VER
  #define FMT_UNCHECKED_ITERATOR(It) using _Unchecked_type = It // Mark iterator as checked.
#else
  #define FMT_UNCHECKED_ITERATOR(It) using unchecked_type = It
#endif

#ifndef FMT_BEGIN_NAMESPACE
  #define FMT_BEGIN_NAMESPACE                                                                                                                                                                                                                            \
    namespace rsl                                                                                                                                                                                                                                        \
    {                                                                                                                                                                                                                                                    \
      inline namespace v1                                                                                                                                                                                                                                \
      {
  #define FMT_END_NAMESPACE                                                                                                                                                                                                                              \
    }                                                                                                                                                                                                                                                    \
    }

#endif

#ifndef FMT_MODULE_EXPORT
  #define FMT_MODULE_EXPORT
  #define FMT_MODULE_EXPORT_BEGIN
  #define FMT_MODULE_EXPORT_END
  #define FMT_BEGIN_DETAIL_NAMESPACE                                                                                                                                                                                                                     \
    namespace detail                                                                                                                                                                                                                                     \
    {
  #define FMT_END_DETAIL_NAMESPACE }
#endif

#if !defined(FMT_HEADER_ONLY) && defined(_WIN32)
  #define FMT_CLASS_API FMT_MSC_WARNING(suppress : 4275)
  #ifdef FMT_EXPORT
    #define FMT_API __declspec(dllexport)
  #elif defined(FMT_SHARED)
    #define FMT_API __declspec(dllimport)
  #endif
#else
  #define FMT_CLASS_API
  #if defined(FMT_EXPORT) || defined(FMT_SHARED)
    #if defined(__GNUC__) || defined(__clang__)
      #define FMT_API __attribute__((visibility("default")))
    #endif
  #endif
#endif
#ifndef FMT_API
  #define FMT_API
#endif

// libc++ supports string_view in pre-c++17.
#if FMT_HAS_INCLUDE(<string_view>) && (FMT_CPLUSPLUS >= 201703L || defined(_LIBCPP_VERSION))
  #include <string_view>
  #define FMT_USE_STRING_VIEW
#elif FMT_HAS_INCLUDE("experimental/string_view") && FMT_CPLUSPLUS >= 201402L
  #include <experimental/string_view>
  #define FMT_USE_EXPERIMENTAL_STRING_VIEW
#endif

#ifndef FMT_UNICODE
  #define FMT_UNICODE !FMT_MSC_VERSION
#endif

#ifndef FMT_CONSTEVAL
  #if((FMT_GCC_VERSION >= 1000 || FMT_CLANG_VERSION >= 1101) && FMT_CPLUSPLUS >= 202002L && !defined(__apple_build_version__)) || (defined(__cpp_consteval) && (!FMT_MSC_VERSION || _MSC_FULL_VER >= 193030704))
  // consteval is broken in MSVC before VS2022 and Apple clang 13.
    #define FMT_CONSTEVAL consteval
    #define FMT_HAS_CONSTEVAL
  #else
    #define FMT_CONSTEVAL
  #endif
#endif

#ifndef FMT_USE_NONTYPE_TEMPLATE_ARGS
  #if defined(__cpp_nontype_template_args) && ((FMT_GCC_VERSION >= 903 && FMT_CPLUSPLUS >= 201709L) || __cpp_nontype_template_args >= 201911L) && !defined(__NVCOMPILER)
    #define FMT_USE_NONTYPE_TEMPLATE_ARGS 1
  #else
    #define FMT_USE_NONTYPE_TEMPLATE_ARGS 0
  #endif
#endif

// Enable minimal optimizations for more compact code in debug mode.
FMT_GCC_PRAGMA("GCC push_options")
#if !defined(__OPTIMIZE__) && !defined(__NVCOMPILER)
FMT_GCC_PRAGMA("GCC optimize(\"Og\")")
#endif

FMT_BEGIN_NAMESPACE
FMT_MODULE_EXPORT_BEGIN

// Implementations of enable_if_t and other metafunctions for older systems.
struct monostate
{
  constexpr monostate() = default;
};

// An enable_if helper to be used in template parameters which results in much
// shorter symbols: https://godbolt.org/z/sWw4vP. Extra parentheses are needed
// to workaround a bug in MSVC 2019 (see #1140 and #1186).
#ifdef FMT_DOC
  #define FMT_ENABLE_IF(...)
#else
  #define FMT_ENABLE_IF(...) enable_if_t<(__VA_ARGS__), int> = 0
#endif

FMT_MODULE_EXPORT_END
FMT_END_NAMESPACE
