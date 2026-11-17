// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: span.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/internal/array/array.h"
#include "rex_std/internal/assert/assert_fwd.h"
#include "rex_std/internal/iterator/random_access_iterator.h"
#include "rex_std/internal/iterator/reverse_iterator.h"
#include "rex_std/internal/memory/byte.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/type_traits/is_const.h"
#include "rex_std/internal/type_traits/is_convertible.h"
#include "rex_std/internal/type_traits/remove_cv.h"
#include "rex_std/internal/type_traits/remove_pointer.h"
#include "rex_std/internal/type_traits/remove_reference.h"
#include "rex_std/internal/type_traits/void.h"
#include "rex_std/internal/utility/declval.h"

namespace rsl
{
  inline namespace v1
  {
    // Indicates the span has a size that's only known at runtime
    /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Nov/2026)
    // rsl uses count_t for sizes, so dynamic_extent is -1 instead of the max value of size_t
    inline constexpr count_t dynamic_extent = -1;

    template <typename T, count_t Extent = dynamic_extent>
    class span;

    namespace internal
    {
      template <typename T>
      struct is_span : false_type
      {
      };
      template <typename T, count_t Extent>
      struct is_span<span<T, Extent>> : true_type
      {
      };

      template <typename T>
      struct is_rsl_array : false_type
      {
      };
      template <typename T, count_t Size>
      struct is_rsl_array<rsl::array<T, Size>> : true_type
      {
      };

      // Elements of type From can be viewed as elements of type To if this doesn't require a conversion
      // eg. int -> const int is allowed, derived -> base is not
      template <typename From, typename To>
      inline constexpr bool is_span_element_convertible_v = is_convertible_v<From (*)[], To (*)[]>; // NOLINT(modernize-avoid-c-arrays)

      // A container can be viewed by a span if it has data() and size() member functions
      // and its elements can be viewed as elements of the span
      template <typename Container, typename T, typename = void>
      struct is_span_compatible_container : false_type
      {
      };
      template <typename Container, typename T>
      struct is_span_compatible_container<Container, T, void_t<decltype(rsl::declval<Container&>().data()), decltype(rsl::declval<Container&>().size())>>
          : bool_constant<!is_span<remove_cv_t<Container>>::value && !is_rsl_array<remove_cv_t<Container>>::value && !is_array_v<Container> &&
                          is_span_element_convertible_v<remove_pointer_t<decltype(rsl::declval<Container&>().data())>, T>>
      {
      };
      template <typename Container, typename T>
      inline constexpr bool is_span_compatible_container_v = is_span_compatible_container<Container, T>::value;

      // A span with a static extent doesn't need to store its size
      template <typename T, count_t Extent>
      class span_storage
      {
      public:
        constexpr span_storage(T* data, count_t /*size*/)
            : m_data(data)
        {
        }

        constexpr T* data() const
        {
          return m_data;
        }
        constexpr count_t size() const
        {
          return Extent;
        }

      private:
        T* m_data;
      };

      template <typename T>
      class span_storage<T, dynamic_extent>
      {
      public:
        constexpr span_storage(T* data, count_t size)
            : m_data(data)
            , m_size(size)
        {
        }

        constexpr T* data() const
        {
          return m_data;
        }
        constexpr count_t size() const
        {
          return m_size;
        }

      private:
        T* m_data;
        count_t m_size;
      };

      template <count_t Extent, count_t Offset, count_t Count>
      inline constexpr count_t subspan_extent = Count != dynamic_extent ? Count : (Extent != dynamic_extent ? Extent - Offset : dynamic_extent);
    } // namespace internal

    // A non owning view over a contiguous sequence of objects.
    // A span can either have a static extent, in which case the number of elements is known at compile time
    // or a dynamic extent, in which case the number of elements is only known at runtime.
    template <typename T, count_t Extent>
    class span
    {
    public:
      using element_type    = T;
      using value_type      = remove_cv_t<T>;
      using size_type       = count_t; /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Nov/2026)
      using difference_type = int32;   /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Nov/2026)
      using pointer         = T*;
      using const_pointer   = const T*;
      using reference       = T&;
      using const_reference = const T&;

      using iterator       = random_access_iterator<T>;
      using const_iterator = const_random_access_iterator<T>;

      using reverse_iterator       = rsl::reverse_iterator<iterator>;
      using const_reverse_iterator = rsl::reverse_iterator<const_iterator>;

      static constexpr size_type extent = Extent;

      static_assert(Extent == dynamic_extent || Extent >= 0, "a span's extent cannot be negative");

      // Constructs an empty span. Only available for spans with a dynamic extent or an extent of 0.
      template <count_t E = Extent, enable_if_t<E == 0 || E == dynamic_extent, bool> = true>
      constexpr span()
          : m_storage(nullptr, 0)
      {
      }

      // Constructs a span that is a view over the range [first, first + count)
      // if the span has a static extent, count must be equal to the extent
      constexpr span(pointer first, size_type count)
          : m_storage(first, count)
      {
        RSL_ASSERT_X(Extent == dynamic_extent || count == Extent, "span constructed with a count different from its extent");
      }
      // Constructs a span that is a view over the range [first, last)
      // if the span has a static extent, last - first must be equal to the extent
      constexpr span(pointer first, pointer last)
          : m_storage(first, static_cast<size_type>(last - first))
      {
        RSL_ASSERT_X(Extent == dynamic_extent || last - first == Extent, "span constructed with a range size different from its extent");
      }

      // Constructs a span that is a view over a c style array
      template <typename U, count_t N, enable_if_t<(Extent == dynamic_extent || Extent == N) && internal::is_span_element_convertible_v<U, T>, bool> = true>
      constexpr span(U (&arr)[N]) // NOLINT(google-explicit-constructor, modernize-avoid-c-arrays)
          : m_storage(arr, N)
      {
      }
      // Constructs a span that is a view over a rsl::array
      template <typename U, count_t N, enable_if_t<(Extent == dynamic_extent || Extent == N) && internal::is_span_element_convertible_v<U, T>, bool> = true>
      constexpr span(rsl::array<U, N>& arr) // NOLINT(google-explicit-constructor)
          : m_storage(arr.data(), N)
      {
      }
      // Constructs a span that is a view over a rsl::array
      template <typename U, count_t N, enable_if_t<(Extent == dynamic_extent || Extent == N) && internal::is_span_element_convertible_v<const U, T>, bool> = true>
      constexpr span(const rsl::array<U, N>& arr) // NOLINT(google-explicit-constructor)
          : m_storage(arr.data(), N)
      {
      }

      // Constructs a span that is a view over a container that has a data() and size() member function
      // eg. rsl::vector, rsl::string, rsl::string_view
      template <typename Container, count_t E = Extent, enable_if_t<E == dynamic_extent && internal::is_span_compatible_container_v<Container, T>, bool> = true>
      constexpr span(Container& cont) // NOLINT(google-explicit-constructor)
          : m_storage(cont.data(), static_cast<size_type>(cont.size()))
      {
      }
      template <typename Container, count_t E = Extent, enable_if_t<E == dynamic_extent && internal::is_span_compatible_container_v<const Container, T>, bool> = true>
      constexpr span(const Container& cont) // NOLINT(google-explicit-constructor)
          : m_storage(cont.data(), static_cast<size_type>(cont.size()))
      {
      }
      // Constructs a span with a static extent that is a view over a container.
      // The size of the container must be equal to the extent of the span
      template <typename Container, count_t E = Extent, enable_if_t<E != dynamic_extent && internal::is_span_compatible_container_v<Container, T>, bool> = true>
      constexpr explicit span(Container& cont)
          : m_storage(cont.data(), static_cast<size_type>(cont.size()))
      {
        RSL_ASSERT_X(static_cast<size_type>(cont.size()) == Extent, "span constructed with a container whose size is different from its extent");
      }
      template <typename Container, count_t E = Extent, enable_if_t<E != dynamic_extent && internal::is_span_compatible_container_v<const Container, T>, bool> = true>
      constexpr explicit span(const Container& cont)
          : m_storage(cont.data(), static_cast<size_type>(cont.size()))
      {
        RSL_ASSERT_X(static_cast<size_type>(cont.size()) == Extent, "span constructed with a container whose size is different from its extent");
      }

      // Converting constructor from another span. eg. span<int> -> span<const int>
      template <typename U, count_t N, enable_if_t<(Extent == dynamic_extent || Extent == N) && internal::is_span_element_convertible_v<U, T>, bool> = true>
      constexpr span(const span<U, N>& other) // NOLINT(google-explicit-constructor)
          : m_storage(other.data(), other.size())
      {
      }
      // Converting a span with a dynamic extent to a span with a static extent needs to be explicit.
      // The size of the other span must be equal to the extent of this span
      template <typename U, count_t N, enable_if_t<Extent != dynamic_extent && N == dynamic_extent && internal::is_span_element_convertible_v<U, T>, bool> = true>
      constexpr explicit span(const span<U, N>& other)
          : m_storage(other.data(), other.size())
      {
        RSL_ASSERT_X(other.size() == Extent, "span constructed from a span whose size is different from its extent");
      }

      constexpr span(const span& other) = default;
      constexpr span& operator=(const span& other) = default;

      // Returns an iterator to the first element of the span.
      constexpr iterator begin() const
      {
        return iterator(data());
      }
      // Returns an iterator to the first element of the span.
      constexpr const_iterator cbegin() const
      {
        return const_iterator(data());
      }
      // Returns an iterator to the element following the last element of the span.
      constexpr iterator end() const
      {
        return iterator(data() + size());
      }
      // Returns an iterator to the element following the last element of the span.
      constexpr const_iterator cend() const
      {
        return const_iterator(data() + size());
      }
      // Returns a reverse iterator to the first element of the reversed span.
      // It corresponds to the last element of the non-reversed span.
      constexpr reverse_iterator rbegin() const
      {
        return reverse_iterator(end());
      }
      // Returns a reverse iterator to the first element of the reversed span.
      // It corresponds to the last element of the non-reversed span.
      constexpr const_reverse_iterator crbegin() const
      {
        return const_reverse_iterator(cend());
      }
      // Returns a reverse iterator to the element following the last element of the reversed span.
      // It corresponds to the element preceding the first element of the non-reversed span.
      constexpr reverse_iterator rend() const
      {
        return reverse_iterator(begin());
      }
      // Returns a reverse iterator to the element following the last element of the reversed span.
      // It corresponds to the element preceding the first element of the non-reversed span.
      constexpr const_reverse_iterator crend() const
      {
        return const_reverse_iterator(cbegin());
      }

      // Returns a reference to the first element in the span.
      constexpr reference front() const
      {
        RSL_ASSERT_X(!empty(), "front called on an empty span");
        return *data();
      }
      // Returns a reference to the last element in the span.
      constexpr reference back() const
      {
        RSL_ASSERT_X(!empty(), "back called on an empty span");
        return *(data() + size() - 1);
      }
      // Returns a reference to the element at specified location pos, with bounds checking.
      // if pos is not within range of the span, an assertion is raised
      constexpr reference at(size_type pos) const
      {
        RSL_ASSERT_X(pos >= 0 && pos < size(), "span out of bounds");
        return data()[pos];
      }
      // Returns a reference to the element at specified location pos. No bounds checking is performed.
      constexpr reference operator[](size_type pos) const
      {
        return data()[pos];
      }
      // Returns a pointer to the beginning of the sequence.
      constexpr pointer data() const
      {
        return m_storage.data();
      }

      // Returns the number of elements in the span
      constexpr size_type size() const
      {
        return m_storage.size();
      }
      // Returns the size of the sequence in bytes
      constexpr size_type size_bytes() const
      {
        return size() * static_cast<size_type>(sizeof(element_type));
      }
      // Checks if the span is empty
      RSL_NO_DISCARD constexpr bool empty() const
      {
        return size() == 0;
      }

      // Obtains a span that is a view over the first Count elements of this span.
      template <count_t Count>
      constexpr span<T, Count> first() const
      {
        static_assert(Count >= 0, "count cannot be negative");
        static_assert(Extent == dynamic_extent || Count <= Extent, "count cannot be bigger than the extent of the span");
        RSL_ASSERT_X(Count <= size(), "count cannot be bigger than the size of the span");
        return span<T, Count>(data(), Count);
      }
      // Obtains a span that is a view over the first count elements of this span.
      constexpr span<T, dynamic_extent> first(size_type count) const
      {
        RSL_ASSERT_X(count >= 0 && count <= size(), "count cannot be bigger than the size of the span");
        return span<T, dynamic_extent>(data(), count);
      }

      // Obtains a span that is a view over the last Count elements of this span.
      template <count_t Count>
      constexpr span<T, Count> last() const
      {
        static_assert(Count >= 0, "count cannot be negative");
        static_assert(Extent == dynamic_extent || Count <= Extent, "count cannot be bigger than the extent of the span");
        RSL_ASSERT_X(Count <= size(), "count cannot be bigger than the size of the span");
        return span<T, Count>(data() + (size() - Count), Count);
      }
      // Obtains a span that is a view over the last count elements of this span.
      constexpr span<T, dynamic_extent> last(size_type count) const
      {
        RSL_ASSERT_X(count >= 0 && count <= size(), "count cannot be bigger than the size of the span");
        return span<T, dynamic_extent>(data() + (size() - count), count);
      }

      // Obtains a span that is a view over the Count elements of this span starting at offset Offset.
      // If Count is dynamic_extent, the subspan goes until the end of this span
      template <count_t Offset, count_t Count = dynamic_extent>
      constexpr span<T, internal::subspan_extent<Extent, Offset, Count>> subspan() const
      {
        static_assert(Offset >= 0, "offset cannot be negative");
        static_assert(Extent == dynamic_extent || Offset <= Extent, "offset cannot be bigger than the extent of the span");
        static_assert(Count == dynamic_extent || Extent == dynamic_extent || Count <= Extent - Offset, "subspan goes out of the bounds of the span");
        RSL_ASSERT_X(Offset <= size(), "offset cannot be bigger than the size of the span");
        RSL_ASSERT_X(Count == dynamic_extent || Count <= size() - Offset, "subspan goes out of the bounds of the span");
        return span<T, internal::subspan_extent<Extent, Offset, Count>>(data() + Offset, Count == dynamic_extent ? size() - Offset : Count);
      }
      // Obtains a span that is a view over the count elements of this span starting at offset offset.
      // If count is dynamic_extent, the subspan goes until the end of this span
      constexpr span<T, dynamic_extent> subspan(size_type offset, size_type count = dynamic_extent) const
      {
        RSL_ASSERT_X(offset >= 0 && offset <= size(), "offset cannot be bigger than the size of the span");
        RSL_ASSERT_X(count == dynamic_extent || (count >= 0 && count <= size() - offset), "subspan goes out of the bounds of the span");
        return span<T, dynamic_extent>(data() + offset, count == dynamic_extent ? size() - offset : count);
      }

    private:
      internal::span_storage<T, Extent> m_storage;
    };

    // Obtains a view to the object representation of the elements of the span
    template <typename T, count_t Extent>
    span<const byte, Extent == dynamic_extent ? dynamic_extent : static_cast<count_t>(sizeof(T)) * Extent> as_bytes(span<T, Extent> s)
    {
      using result_type = span<const byte, Extent == dynamic_extent ? dynamic_extent : static_cast<count_t>(sizeof(T)) * Extent>;
      return result_type(reinterpret_cast<const byte*>(s.data()), s.size_bytes()); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }
    // Obtains a writable view to the object representation of the elements of the span
    template <typename T, count_t Extent, enable_if_t<!is_const_v<T>, bool> = true>
    span<byte, Extent == dynamic_extent ? dynamic_extent : static_cast<count_t>(sizeof(T)) * Extent> as_writable_bytes(span<T, Extent> s)
    {
      using result_type = span<byte, Extent == dynamic_extent ? dynamic_extent : static_cast<count_t>(sizeof(T)) * Extent>;
      return result_type(reinterpret_cast<byte*>(s.data()), s.size_bytes()); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }

    // deduction guides
    template <typename T, count_t N>
    span(T (&)[N]) -> span<T, N>; // NOLINT(modernize-avoid-c-arrays)
    template <typename T, count_t N>
    span(rsl::array<T, N>&) -> span<T, N>;
    template <typename T, count_t N>
    span(const rsl::array<T, N>&) -> span<const T, N>;
    template <typename Container>
    span(Container&) -> span<remove_reference_t<decltype(*rsl::declval<Container&>().data())>>;
    template <typename Container>
    span(const Container&) -> span<remove_reference_t<decltype(*rsl::declval<const Container&>().data())>>;

  } // namespace v1
} // namespace rsl
