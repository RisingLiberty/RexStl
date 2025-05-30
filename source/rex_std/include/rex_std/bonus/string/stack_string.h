// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: stack_string.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/algorithm/clamp_max.h"
#include "rex_std/bonus/functional/hash_result.h"
#include "rex_std/bonus/string/string_utils_impl.h"
#include "rex_std/bonus/string/char_traits_case_insensitive.h"
#include "rex_std/bonus/string/istring_view.h"
#include "rex_std/bonus/types.h"
#include "rex_std/initializer_list.h"
#include "rex_std/internal/algorithm/clamp.h"
#include "rex_std/internal/algorithm/copy_n.h"
#include "rex_std/internal/algorithm/max.h"
#include "rex_std/internal/array/array.h"
#include "rex_std/internal/assert/assert_fwd.h"
#include "rex_std/internal/functional/hash.h"
#include "rex_std/internal/memory/memcpy.h"
#include "rex_std/internal/memory/nullptr.h"
#include "rex_std/internal/optional/optional.h"
#include "rex_std/internal/string/char_traits.h"
#include "rex_std/internal/string/string_forward_declare.h"
#include "rex_std/internal/string_view/basic_string_view.h"
#include "rex_std/internal/type_traits/is_integral.h"
#include "rex_std/iosfwd.h"
#include "rex_std/stddef.h"

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, typename Traits>
    class basic_string_view;

    template <typename CharType, card32 StrMaxSize, typename Traits = char_traits<CharType>>
    class stack_string
    {
    public:
      static_assert(StrMaxSize > 0, "Can't have a stack string with a size of 0");
      static_assert(rsl::is_integral_v<CharType>, "CharType must be of integral type!");

      using traits_type = Traits;
      using size_type      = int32;
      using value_type     = CharType;
      using iterator       = typename rsl::array<CharType, StrMaxSize>::iterator;
      using const_iterator = typename rsl::array<CharType, StrMaxSize>::const_iterator;

      stack_string()
          : m_data()
          , m_null_terminator_offset(0)
      {
      }

      template <card32 N>
      explicit stack_string(const value_type str[N]) // NOLINT
          : stack_string()
      {
        static_assert(N < StrMaxSize, "Trying to copy more into a string than is allowed");
        m_null_terminator_offset = rsl::memcpy(m_data.data(), str, sizeof(CharType) * N);
      }

      stack_string(rsl::initializer_list<value_type> str) // NOLINT
          : stack_string()
      {
        const card32 copy_size = rsl::clamp_max(static_cast<card32>(str.size()), StrMaxSize);
        rsl::memcpy(m_data.data(), str.begin(), copy_size * sizeof(value_type));
        m_null_terminator_offset = copy_size;
      }

      explicit stack_string(const value_type* str)
          : stack_string()
      {
        const card32 string_length = rsl::string_length(str);
        const card32 copy_size     = rsl::clamp_max(string_length, StrMaxSize);
        rsl::memcpy(m_data.data(), str, copy_size);
        m_null_terminator_offset = copy_size;
      }

      stack_string(const value_type* str, card32 size)
          : stack_string()
      {
        const card32 copy_size = rsl::clamp_max(size, StrMaxSize);
        rsl::memcpy(m_data.data(), str, copy_size * sizeof(value_type));
        m_null_terminator_offset = copy_size;
      }

      stack_string(basic_string_view<CharType, char_traits<CharType>> view) // NOLINT(google-explicit-constructor)
          : stack_string()
      {
        const card32 copy_size = rsl::clamp_max(view.length(), StrMaxSize);
        rsl::memcpy(m_data.data(), view.data(), copy_size * sizeof(value_type));
        m_null_terminator_offset = copy_size;
      }

      template <card32 N>
      stack_string(const stack_string<CharType, N>& str) // NOLINT(google-explicit-constructor)
          : m_data()
          , m_null_terminator_offset(str.length())
      {
        const card32 copy_size = rsl::clamp_max(str.length(), StrMaxSize);
        rsl::copy_n(str.begin(), copy_size, m_data.data());
      }

      stack_string(rsl::nullptr_t) = delete;

      stack_string& operator=(basic_string_view<CharType, char_traits<CharType>> view)
      {
        const card32 new_length = rsl::clamp_max(view.length(), StrMaxSize);
        rsl::memcpy(m_data.data(), view.data(), new_length * sizeof(value_type));
        m_null_terminator_offset         = new_length;
        m_data[m_null_terminator_offset] = value_type();
        return *this;
      }
      stack_string& operator=(const value_type* str)
      {
        const card32 new_length = rsl::clamp_max(rsl::string_length(str), StrMaxSize);
        rsl::memcpy(m_data.data(), str, new_length);
        m_null_terminator_offset         = new_length;
        m_data[m_null_terminator_offset] = value_type();
        return *this;
      }
      stack_string& operator=(rsl::nullptr_t) = delete;

      void assign(const value_type* first, const value_type* last)
      {
        const card32 length    = static_cast<card32>(last - first);
        assign(first, 0, length);
      }
      void assign(const value_type* newData, card32 length)
      {
        assign(newData, 0, length);
      }
      void assign(const value_type* newData, size_type pos, size_type length)
      {
        // limit the number of characters to copy as we cannot copy beyond our buffer
        const card32 copy_size = clamp_max(length, StrMaxSize - pos - 1);
        rsl::memmove(data() + pos, newData, copy_size * sizeof(value_type));
        m_null_terminator_offset = pos + copy_size;
        m_data[m_null_terminator_offset] = value_type();
      }
      template <typename Traits2>
      void assign(rsl::basic_string_view<char8, Traits2> view)
      {
        assign(view.data(), view.length());
      }

      card32 length() const
      {
        return m_null_terminator_offset;
      }
      card32 size() const
      {
        return m_null_terminator_offset;
      }
      static constexpr card32 max_size()
      {
        return StrMaxSize;
      }

      value_type* data()
      {
        return m_data.data();
      }
      const value_type* data() const
      {
        return m_data.data();
      }

      const value_type* c_str() const
      {
        return m_data.data();
      }

      auto begin()
      {
        return m_data.begin();
      }
      auto begin() const
      {
        return m_data.begin();
      }
      auto end()
      {
        return begin() + m_null_terminator_offset;
      }
      auto end() const
      {
        return begin() + m_null_terminator_offset;
      }
      auto cbegin() const
      {
        return m_data.cbegin();
      }
      auto cend() const
      {
        return m_data.cend();
      }
      auto rbegin()
      {
        return m_data.rbegin() + (max_size() - length());
      }
      auto rend()
      {
        return m_data.rend();
      }
      auto crbegin() const
      {
        return m_data.crbegin() + (max_size() - length());
      }
      auto crend() const
      {
        return m_data.crend();
      }

      auto& operator[](card32 idx)
      {
        return m_data[idx];
      }
      const auto& operator[](card32 idx) const
      {
        return m_data[idx];
      }

      auto at(card32 idx)
      {
        RSL_ASSERT_X(idx < m_null_terminator_offset, "Index out of range");
        return m_data.at(idx);
      }
      const auto& at(card32 idx) const
      {
        RSL_ASSERT_X(idx < m_null_terminator_offset, "Index out of range");
        return m_data.at(idx);
      }

      auto& front()
      {
        return m_data.front();
      }
      const auto& front() const
      {
        return m_data.front();
      }

      auto& back()
      {
        return m_data.back();
      }
      const auto& back() const
      {
        return m_data.back();
      }

      bool empty() const
      {
        return length() == 0;
      }

      basic_string_view<CharType, char_traits<CharType>> to_view() const
      {
        return basic_string_view<CharType, char_traits<CharType>>(data(), length());
      }
      operator basic_string_view<CharType, char_traits<CharType>>() const // NOLINT(google-explicit-constructor)
      {
        return to_view();
      }

      void clear()
      {
        m_null_terminator_offset = 0;
        m_data[m_null_terminator_offset] = CharType();
      }
      void push_back(value_type c)
      {
        m_data[m_null_terminator_offset] = c;
        ++m_null_terminator_offset;
      }
      void pop_back()
      {
        --m_null_terminator_offset;
        m_data[m_null_terminator_offset] = CharType();
      }
      void resize(card32 size)
      {
        const card32 new_size = rsl::clamp_max(size, StrMaxSize - 1);
        const card32 old_size = length();

        for(card32 i = old_size; i < new_size; ++i)
        {
          m_data[i] = CharType();
        }

        m_null_terminator_offset = new_size;
        m_data[m_null_terminator_offset] = CharType();
      }
      // usually called after a memcpy call
      // can be solved be calling resize before the memcpy call
      void reset_null_termination_offset()
      {
        m_null_terminator_offset = rsl::string_length(data());
      }

      void remove_prefix(card32 count)
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        view.remove_prefix(count);
        *this = view;
      }
      void remove_prefix(rsl::string_view prefix)
      {
        if (starts_with(prefix))
        {
          remove_prefix(prefix.length());
        }
      }
      void remove_suffix(card32 count)
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        view.remove_suffix(count);
        *this = view;
      }
      void remove_suffix(rsl::string_view suffix)
      {
        if (ends_width(suffix))
        {
          remove_suffix(suffix.length());
        }
      }

      void copy(value_type* dest, card32 count, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        view.copy(dest, count, pos);
      }

      stack_string substr(card32 pos = 0, card32 count = npos()) const
      {
        basic_string_view<CharType, char_traits<CharType>> view   = to_view();
        basic_string_view<CharType, char_traits<CharType>> substr = view.substr(pos, count);
        return stack_string(substr);
      }

      template <card32 RhsSize>
      int32 compare(const stack_string<CharType, RhsSize>& rhs) const
      {
        basic_string_view<CharType, char_traits<CharType>> view     = to_view();
        basic_string_view<CharType, char_traits<CharType>> rhs_view = rhs.to_view();

        return view.compare(rhs_view);
      }
      template <card32 RhsSize>
      int32 compare(card32 pos1, card32 count1, const stack_string<CharType, RhsSize>& rhs, card32 pos2, card32 count2) const
      {
        basic_string_view<CharType, char_traits<CharType>> view     = to_view();
        basic_string_view<CharType, char_traits<CharType>> rhs_view = rhs.to_view();

        return view.compare(pos1, count1, rhs_view, pos2, count2);
      }
      int32 compare(const value_type* str) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.compare(str);
      }
      int32 compare(card32 pos1, card32 count1, const value_type* str) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.compare(pos1, count1, str);
      }
      int32 compare(card32 pos1, card32 count1, const value_type* str, card32 count2) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.compare(pos1, count1, str, count2);
      }


      // Inserts count copies of ch at position index
      stack_string& insert(size_type index, size_type count, value_type ch)
      {
        prepare_for_new_insert(index, count);

        value_type* offset_loc = data() + index;
        traits_type::assign(offset_loc, count, ch);

        return *this;
      }
      /// RSL Comment: Not in ISO C++ Standard at time of writing (30/Jun/2022)
      // the standard doesn't provide an overload for a string literal
      // Inserts character string pointed to by s at the position index
      template <count_t Size>
      stack_string& insert(size_type index, const value_type(&s)[Size]) // NOLINT(modernize-avoid-c-arrays)
      {
        return insert(index, s, Size - 1);
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (01/Jul/2022)
      // because we have the function above, we don't specify the following function
      // basic_string& insert(size_type index, const_pointer s);

      // inserts the character range [s, s + count) at position index
      stack_string& insert(size_type index, const value_type* s, size_type count)
      {
        prepare_for_new_insert(index, count);

        value_type* offset_loc = data() + index;
        traits_type::copy(offset_loc, s, count);

        return *this;
      }
      // inserts character ch before the character pointed by pos
      stack_string& insert(size_type index, value_type ch)
      {
        return insert(index, &ch, 1);
      }
      // inserts a single character at a certain position
      iterator insert(const_iterator pos, value_type ch)
      {
        return insert(pos, 1, ch);
      }
      // inserts count copies of character ch before the element (if any) pointed by pos
      iterator insert(const_iterator pos, size_type count, value_type ch)
      {
        const size_type pos_idx = rsl::distance(cbegin(), pos);

        prepare_for_new_insert(pos_idx, count);

        traits_type::assign(&m_begin[pos_idx], count, ch);

        return iterator(&m_begin[pos_idx]);
      }
      // inserts characters from teh range [first, last) before the element (if any) pointed by pos.
      template <typename InputIt>
      iterator insert(const_iterator pos, InputIt first, InputIt last)
      {
        const size_type pos_idx = rsl::distance(cbegin(), pos);
        const size_type num_elements_to_insert = rsl::distance(first, last);

        prepare_for_new_insert(pos_idx, num_elements_to_insert);

        size_type current_idx = pos_idx;
        while (first != last)
        {
          traits_type::assign(operator[](current_idx), *first);
          ++current_idx;
          ++first;
        }
        return iterator(&m_begin[current_idx]);
      }
      // inserts elements from the initializer list before the element (if any) pointed by pos
      iterator insert(const_iterator pos, rsl::initializer_list<value_type> ilist)
      {
        const size_type pos_idx = rsl::distance(cbegin(), pos);
        const size_type num_elements_to_insert = static_cast<size_type>(ilist.size());

        prepare_for_new_insert(pos, num_elements_to_insert);

        size_type current_idx = pos_idx;
        for (const value_type ch : ilist)
        {
          traits_type::assign(operator[](current_idx), ch);
          ++current_idx;
        }

        return iterator(&m_begin[current_idx]);
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (01/Jul/2022)
      // This is a template function in the standard due to ambiguous overload
      // as both basic_string and basic_string_view<value_type, traits_type> can be implicitly created with a const char*.
      // This is not possible in RSL though as the ctor for const char* for string is explicit.
      // Therefore this takes a basic_string_view
      // inserts the elements from sv before the element (if any) pointed by pos.
      stack_string& insert(size_type pos, const basic_string_view<value_type>& sv)
      {
        return insert(pos, sv.data(), sv.length());
      }
      /// RSL Comment: Different from ISO C++ Standard at time of writing (01/Jul/2022)
      // This is a template function in the standard due to ambiguous overload
      // as both basic_string and basic_string_view<value_type, traits_type> can be implicitly created with a const char*.
      // This is not possible in RSL though as the ctor for const char* for string is explicit.
      // Therefore this takes a basic_string_view
      // inserts the elements from sv starting at index_str before the element (if any) pointed by pos.
      stack_string& insert(size_type pos, const basic_string_view<value_type>& sv, size_type indexStr, size_type count = s_npos)
      {
        const size_type num_chars_to_insert = obj_length_or_count(sv, count, indexStr);
        return insert(pos, sv.data() + indexStr, num_chars_to_insert);
      }

      constexpr void erase(card32 offset)
      {
        for(card32 i = offset; i < max_size() - 1; ++i)
        {
          m_data[i] = m_data[i + 1];
        }

        --m_null_terminator_offset;
      }
      void erase(card32 offset, card32 count)
      {
        for(card32 i = offset; i < max_size() - count; ++i)
        {
          m_data[i] = m_data[i + count];
        }

        m_null_terminator_offset -= count;
      }
      // removes the character at position
      iterator erase(const_iterator position)
      {
        const size_type pos_idx = rsl::distance(cbegin(), position);

        traits_type::move(&m_begin[pos_idx], &m_begin[pos_idx + 1], size() - pos_idx);

        --m_end;
        traits_type::assign(*m_end, value_type());

        return iterator(&m_begin[pos_idx]);
      }
      // removes the characters in the range [frist, last)
      iterator erase(const_iterator first, const_iterator last)
      {
        const size_type first_idx = rsl::distance(cbegin(), first);
        const size_type last_idx = rsl::distance(cbegin(), last);
        const size_type count = last_idx - first_idx;
        const size_type num_to_move = rsl::min(count, rsl::distance(last, cend()));
        traits_type::move(&m_begin[first_idx], &m_begin[last_idx], num_to_move);

        m_end -= count;
        traits_type::assign(*m_end, value_type());

        return iterator(&m_begin[first_idx]);
      }

      card32 find(basic_string_view<CharType, char_traits<CharType>> view, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view_of_this = to_view();
        return view_of_this.find(view, pos);
      }
      card32 find(value_type c, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find(c, pos);
      }
      card32 find(const value_type* str, card32 pos, card32 count) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find(str, pos, count);
      }
      card32 find(const value_type* str, card32 pos) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find(str, pos);
      }

      card32 rfind(basic_string_view<CharType, char_traits<CharType>> view, card32 pos = npos()) const
      {
        basic_string_view<CharType, char_traits<CharType>> view_of_this = to_view();
        return view_of_this.rfind(view, pos);
      }
      card32 rfind(value_type c, card32 pos = npos()) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.rfind(c, pos);
      }
      card32 rfind(const value_type* str, card32 pos, card32 count) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.rfind(str, pos, count);
      }
      card32 rfind(const value_type* str, card32 pos = npos()) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.rfind(str, pos);
      }

      card32 find_first_of(basic_string_view<CharType, char_traits<CharType>> v, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_first_of(v, pos);
      }
      card32 find_first_of(value_type c, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_first_of(c, pos);
      }
      card32 find_first_of(const value_type* s, card32 pos, card32 count) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_first_of(s, pos, count);
      }
      card32 find_first_of(const value_type* s, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_first_of(s, pos);
      }

      card32 find_last_of(basic_string_view<CharType, char_traits<CharType>> v, card32 pos = npos()) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_last_of(v, pos);
      }
      card32 find_last_of(value_type c, card32 pos = npos()) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_last_of(c, pos);
      }
      card32 find_last_of(const value_type* s, card32 pos, card32 count) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_last_of(s, pos, count);
      }
      card32 find_last_of(const value_type* s, card32 pos = npos()) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_last_of(s, pos);
      }

      card32 find_first_not_of(basic_string_view<CharType, char_traits<CharType>> v, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_first_not_of(v, pos);
      }
      card32 find_first_not_of(value_type c, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_first_not_of(c, pos);
      }
      card32 find_first_not_of(const value_type* s, card32 pos, card32 count) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_first_not_of(s, pos, count);
      }
      card32 find_first_not_of(const value_type* s, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_first_not_of(s, pos);
      }

      card32 find_last_not_of(basic_string_view<CharType, char_traits<CharType>> v, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_last_not_of(v, pos);
      }
      card32 find_last_not_of(value_type c, card32 pos = npos()) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_last_not_of(c, pos);
      }
      card32 find_last_not_of(const value_type* s, card32 pos, card32 count) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_last_not_of(s, pos, count);
      }
      card32 find_last_not_of(const value_type* s, card32 pos = 0) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.find_last_not_of(s, pos);
      }

      template <card32 Size>
      bool starts_with(const stack_string<CharType, Size>& prefix) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.starts_with(prefix.to_view());
      }
      bool starts_with(const value_type* prefix) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.starts_with(prefix);
      }
      bool starts_with(value_type c) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.starts_with(c);
      }
      bool starts_with(const basic_string_view<CharType, char_traits<CharType>> prefix) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.starts_with(prefix);
      }

      template <card32 Size>
      bool ends_with(const stack_string<CharType, Size>& suffix) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.ends_with(suffix.to_view());
      }
      bool ends_with(const value_type* suffix) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.ends_with(suffix);
      }
      bool ends_with(value_type c) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.ends_with(c);
      }
      bool ends_width(const basic_string_view<CharType, char_traits<CharType>> suffix) const
      {
        basic_string_view<CharType, char_traits<CharType>> view = to_view();
        return view.ends_with(suffix);
      }

      stack_string<CharType, StrMaxSize> to_lower() const
      {
        stack_string<CharType, StrMaxSize> lowered = *this;
        lowered.lower();
        return lowered;
      }
      void lower()
      {
        rsl::to_lower(data(), data(), length());
      }
      stack_string<CharType, StrMaxSize> to_upper() const
      {
        stack_string<CharType, StrMaxSize> uppered = *this;
        uppered.upper();
        return uppered;
      }
      void upper()
      {
        rsl::to_upper(data(), data(), length());
      }

      bool is_letters() const
      {
        return rsl::is_letters(data(), length());
      }
      bool is_digits() const
      {
        return rsl::is_digits(data(), length());
      }
      bool is_digitsf() const
      {
        return rsl::is_digitsf(data(), length());
      }

      bool operator==(const basic_string_view<CharType, char_traits<CharType>> str) const
      {
        return to_view() == str;
      }
      bool operator!=(const basic_string_view<CharType, char_traits<CharType>> str) const
      {
        return !(*this == str);
      }

      stack_string operator+(const value_type c) const
      {
        stack_string res = *this;
        res.push_back(c);
        return res;
      }

      stack_string operator+(const basic_string_view<CharType, char_traits<CharType>>& str) const
      {
        stack_string res = *this;
        res += str;
        return res;
      }

      template <card32 RhsSize>
      auto operator+(const stack_string<CharType, RhsSize>& str) const
      {
        stack_string<CharType, (rsl::max)(StrMaxSize, RhsSize)> result;

        result += *this;
        result += str;

        return result;
      }

      stack_string& operator+=(value_type c)
      {
        push_back(c);
        return *this;
      }

      stack_string& operator+=(const value_type* str)
      {
        return operator+=(basic_string_view<CharType, char_traits<CharType>>(str));
      }

      stack_string& operator+=(const basic_string_view<CharType, char_traits<CharType>> str)
      {
        const card32 string_length   = str.length();
        const card32 remaining_bytes = rsl::clamp_max(string_length, StrMaxSize);

        append(str.data(), remaining_bytes);
        return *this;
      }

      void append(const value_type* str, card32 count)
      {
        RSL_ASSERT_X(length() + count <= max_size(), "copying into a stack string beyond its limit");

        value_type* dest = data();
        dest += length();
        rsl::memcpy(dest, str, count);
        m_null_terminator_offset += count;
        m_data[m_null_terminator_offset] = value_type();
      }

      static card32 npos()
      {
        return s_npos;
      }

      bool operator<(const stack_string<CharType, StrMaxSize>& str) const
      {
        return compare(str.data(), str.length()) < 0;
      }
      bool operator<=(const stack_string<CharType, StrMaxSize>& str) const
      {
        return compare(str.data(), str.length()) <= 0;
      }
      bool operator>(const stack_string<CharType, StrMaxSize>& str) const
      {
        return compare(str.data(), str.length()) > 0;
      }
      bool operator>=(const stack_string<CharType, StrMaxSize>& str) const
      {
        return compare(str.data(), str.length()) >= 0;
      }

      // moves every element starting at str[idx] 'count' space(s) to the right
      void prepare_for_new_insert(size_type idx, size_type count = 1)
      {
        const card32 dst_idx = idx + count;
        
        // If we'd have to move character outside of our buffer, we just do nothing here
        if (dst_idx >= StrMaxSize)
        {
          return;
        }

        const value_type* src = data() + idx;
        s32 count_to_copy = length() - idx;
        assign(src, dst_idx, count_to_copy);
      }
      // moves every element starting at 'pos' 'count' space(s) to the right
      void prepare_for_new_insert(const_iterator pos, size_type count = 1)
      {
        const auto pos_idx = rsl::distance(cbegin(), pos);
        prepare_for_new_insert(pos_idx, count);
      }

    private:
      rsl::array<CharType, StrMaxSize> m_data;
      card32 m_null_terminator_offset; // NOLINT(misc-non-private-member-variables-in-classes): ignoring false positive

      constexpr static card32 s_npos = -1;
    };

    template <typename CharType, card32 Size>
    bool operator==(basic_string_view<CharType> lhs, const stack_string<CharType, Size> rhs)
    {
      return rhs == lhs;
    }
    template <typename CharType, card32 Size>
    bool operator!=(basic_string_view<CharType> lhs, const stack_string<CharType, Size> rhs)
    {
      return !(lhs == rhs)
    }

    template <typename CharType, card32 Size>
    stack_string<CharType, Size> operator+(const CharType* str, const stack_string<CharType, Size>& string)
    {
      stack_string<CharType, Size> res(str);
      res += string;
      return res;
    }

    template <typename CharType>
    class stack_string<CharType, 0>
    {
    public:
      using value_type = CharType;

      static constexpr card32 max_size()
      {
        return 0;
      }

      void assign(const value_type* /*newData*/, card32 /*length*/)
      {
      }


      value_type* data()
      {
        return nullptr;
      }
      const value_type* data() const
      {
        return nullptr;
      }
    };

    using null_stack_string   = stack_string<char8, 0>;
    using tiny_stack_string   = stack_string<char8, 32>;  // NOLINT(readability-magic-numbers)
    using small_stack_string  = stack_string<char8, 64>;  // NOLINT(readability-magic-numbers)
    using medium_stack_string = stack_string<char8, 128>; // NOLINT(readability-magic-numbers)
    using big_stack_string    = stack_string<char8, 256>; // NOLINT(readability-magic-numbers)

    using wnull_stack_string    = stack_string<tchar, 0>;
    using wtiny_stack_string   = stack_string<tchar, 32>;  // NOLINT(readability-magic-numbers)
    using wsmall_stack_string  = stack_string<tchar, 64>;  // NOLINT(readability-magic-numbers)
    using wmedium_stack_string = stack_string<tchar, 128>; // NOLINT(readability-magic-numbers)
    using wbig_stack_string    = stack_string<tchar, 256>; // NOLINT(readability-magic-numbers)

    using itiny_stack_string = stack_string<char8, 32, ichar_traits<char8>>;  // NOLINT(readability-magic-numbers)
    using ismall_stack_string = stack_string<char8, 64, ichar_traits<char8>>;  // NOLINT(readability-magic-numbers)
    using imedium_stack_string = stack_string<char8, 128, ichar_traits<char8>>; // NOLINT(readability-magic-numbers)
    using ibig_stack_string = stack_string<char8, 256, ichar_traits<char8>>; // NOLINT(readability-magic-numbers)

    using iwtiny_stack_string = stack_string<tchar, 32, ichar_traits<tchar>>;  // NOLINT(readability-magic-numbers)
    using iwsmall_stack_string = stack_string<tchar, 64, ichar_traits<tchar>>;  // NOLINT(readability-magic-numbers)
    using iwmedium_stack_string = stack_string<tchar, 128, ichar_traits<tchar>>; // NOLINT(readability-magic-numbers)
    using iwbig_stack_string = stack_string<tchar, 256, ichar_traits<tchar>>; // NOLINT(readability-magic-numbers)

    tiny_stack_string to_stack_string(uint32 value);
    tiny_stack_string to_stack_string(int32 value);
    tiny_stack_string to_stack_string(uint64 value);
    tiny_stack_string to_stack_string(int64 value);
    tiny_stack_string to_stack_string(float32 value, card32 precision = 4);
    tiny_stack_string to_stack_string(float64 value, card32 precision = 4);
    tiny_stack_string to_stack_string(const void* ptr);

    template <typename CharType, card32 MaxSize>
    basic_ostream<CharType, char_traits<CharType>>& operator<<(basic_ostream<CharType, char_traits<CharType>>& os, const stack_string<CharType, MaxSize>& str)
    {
      os.rdbuf()->sputn(str.data(), str.length());
      return os;
    }

  } // namespace v1
} // namespace rsl

rsl::tiny_stack_string operator"" _tiny(const char* str, size_t length);
rsl::small_stack_string operator"" _small(const char* str, size_t length);
rsl::medium_stack_string operator"" _med(const char* str, size_t length);
rsl::big_stack_string operator"" _big(const char* str, size_t length);

namespace rsl
{
  inline namespace v1
  {
    template <typename CharType, card32 Size>
    struct hash<rsl::stack_string<CharType, Size>>
    {
      constexpr hash_result operator()(const rsl::stack_string<CharType, Size>& str) const
      {
        return rsl::hash<rsl::string_view> {}(str.to_view());
      }
    };

    template <typename CharType, card32 Size>
    struct hash<rsl::stack_string<CharType, Size, ichar_traits<CharType>>>
    {
      constexpr hash_result operator()(const rsl::stack_string<CharType, Size>& str) const
      {
        return rsl::hash<rsl::istring_view> {}(str.to_view());
      }
    };

  } // namespace v1
} // namespace rsl
