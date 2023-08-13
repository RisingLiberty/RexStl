// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: bitset.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/types.h"
#include "rex_std/limits.h"
#include "rex_std/bit.h"
#include "rex_std/array.h"
#include "rex_std/bonus/string/stack_string.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      template <card32 N, typename WordType>
      struct bitset_base
      {
      public:
        using word_type = WordType;
        using this_type = bitset_base<N, WordType>;
        using size_type = card32;

        static constexpr size_type BitsPerWord = limits_byte::num_bits_per_byte * sizeof(word_type);
        static constexpr size_type BitsPerWordMask = BitsPerWord - 1;
        static constexpr size_type BitsPerWordShift = ((BitsPerWord == 8) ? 3 : ((BitsPerWord == 16) ? 4 : ((BitsPerWord == 32) ? 5 : (((BitsPerWord == 64) ? 6 : 7)))));

      public:
        bitset_base()
        {
          reset();
        }
        bitset_base(card32 value)
        {
          reset();
          m_word.front() = static_cast<word_type>(value);
        }

        void operator&=(const this_type& other)
        {
          for (size_type i = 0; i < N; ++i)
          {
            m_word[i] &= other.m_word[i];
          }
        }
        void operator|=(const this_type& other)
        {
          for (size_type i = 0; i < N; ++i)
          {
            m_word[i] |= other.m_word[i];
          }
        }
        void operator^=(const this_type& other)
        {
          for (size_type i = 0; i < N; ++i)
          {
            m_word[i] ^= other.m_word[i];
          }
        }

        void operator<<=(size_type n)
        {
          const size_type word_shift = static_cast<size_type>(n >> BitsPerWordShift);

          if (word_shift)
          {
            for (size_type i = static_cast<size_type>(N - 1); i >= 0; --i)
            {
              m_word[i] = (word_shift <= static_cast<size_type>(i)) ? m_word[i - word_shift] : static_cast<word_type>(0);
            }
          }

          if (n &= BitsPerWordMask)
          {
            for (size_type i = (N - 1); i > 0; --i)
            {
              m_word[i] = static_cast<word_type>(m_word[i] << n) | (m_word[i - 1] >> (BitsPerWord - n));
            }
            m_word.front() <<= n;
          }
        }
        void operator>>=(size_type n)
        {
          const size_type word_shift = static_cast<size_type>(n >> BitsPerWordShift);

          if (word_shift)
          {
            for (size_type i = 0; i < N; ++i)
            {
              m_word[i] = ((word_shift < (N - i)) ? m_word[i + word_shift] : static_cast<word_type>(0));
            }
          }

          if (n &= BitsPerWordMask)
          {
            for (size_type i = 0; i < (N - 1); ++i)
            {
              m_word[i] = static_cast<word_type>((m_word[i] >> n) | (m_word[i + 1] << (BitsPerWord - n)));
            }
            m_word[N - 1] >>= n;
          }
        }

        void flip()
        {
          for (size_type i = 0; i < N; ++i)
          {
            m_word[i] = ~m_word[i];
          }
        }
        void set()
        {
          for (size_type i = 0; i < N; ++i)
          {
            m_word[i] = static_cast<word_type>(~static_cast<word_type>(0));
          }
        }
        void set(size_type idx, bool value)
        {
          if (value)
          {
            m_word[idx >> BitsPerWordShift] |= (static_cast<word_type>(1) << (idx & BitsPerWordMask));
          }
          else
          {
            m_word[idx >> BitsPerWordShift] &= ~(static_cast<word_type>(1) << (idx & BitsPerWordMask));
          }
        }
        void reset()
        {
          if constexpr (N > 16)
          {
            rsl::memset(m_word.data(), 0, sizeof(m_word));
          }
          else
          {
            for (size_type i = 0; i < N; ++i)
            {
              m_word[i] = 0;
            }
          }
        }

        bool operator==(const this_type& other) const
        {
          for (size_type i = 0; i < N; ++i)
          {
            if (m_word[i] != other.m_word[i])
            {
              return false;
            }
          }

          return true;
        }
        bool operator!=(const this_type& other) const
        {
          return !(*this == other);
        }

        bool any() const
        {
          for (size_type i = 0; i < N; i++)
          {
            if (m_word[i])
            {
              return true;
            }
          }
          return false;
        }
        size_type size() const
        {
          return BitsPerWord * N;
        }
        size_type count() const
        {
          size_type res = 0;
          for (size_type i = 0; i < N; ++i)
          {
            res += rsl::popcount(m_word[i]);
          }

          return res;
        }

        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses to_ulong and we use to uint32.
        // the size of long is not platform agnostic while the size of uint32 is.
        uint32 to_uint32() const
        {
          return static_cast<uint32>(m_word.front());
        }
        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses to_ullong and we use to uint64.
        // because we don't use ulong, we're also not using to_ullong
        uint64 to_uint64() const
        {
          return static_cast<uint64>(m_word.front());
        }
        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses a std::string to convert here
        // we use a stack_string instead.
        rsl::stack_string<char8, N * BitsPerWord> to_string() const
        {
          rsl::stack_string<char8, N* BitsPerWord> res{};
          
          for (size_type i = 0; i < size(); ++i)
          {
            if ((*this)[i])
              res[size() - 1 - i] = '1';
          }

          return res;
        }

      protected:
        rsl::array<word_type, N>& word()
        {
          return m_word;
        }
        const rsl::array<word_type, N>& word() const
        {
          return m_word;
        }

      private:
        rsl::array<word_type, N> m_word;
      };

      template <typename WordType>
      struct bitset_base<1, WordType>
      {
      public:
        using word_type = WordType;
        using this_type = bitset_base<1, WordType>;
        using size_type = card32;

        static constexpr size_type BitsPerWord = limits_byte::num_bits_per_byte * sizeof(word_type);
        static constexpr size_type BitsPerWordMask = BitsPerWord - 1;
        static constexpr size_type BitsPerWordShift = ((BitsPerWord == 8) ? 3 : ((BitsPerWord == 16) ? 4 : ((BitsPerWord == 32) ? 5 : (((BitsPerWord == 64) ? 6 : 7)))));

      public:
        bitset_base()
        {
          m_word.front() = 0;
        }
        bitset_base(card32 value)
        {
          m_word.front() = static_cast<word_type>(value);
        }

        void operator&=(const this_type& other)
        {
          m_word.front() &= other.m_word[0];
        }
        void operator|=(const this_type& other)
        {
          m_word.front() |= other.m_word[0];
        }
        void operator^=(const this_type& other)
        {
          m_word.front() ^= other.m_word[0];
        }

        void operator<<=(size_type n)
        {
          m_word.front() <<= n;
        }
        void operator>>=(size_type n)
        {
          m_word.front() >>= n;
        }

        void flip()
        {
          m_word.front() = ~m_word.front();
        }
        void set()
        {
          m_word.front() = static_cast<word_type>(~static_cast<word_type>(0));
        }
        void set(size_type idx, bool value)
        {
          if (value)
          {
            m_word.front() |= (static_cast<word_type>(1) << idx);
          }
          else
          {
            m_word.front() &= ~(static_cast<word_type>(1) << idx);
          }
        }
        void reset()
        {
          m_word.front() = 0;
        }

        bool operator==(const this_type& other) const
        {
          return m_word.front() == other.m_word.front();
        }
        bool operator!=(const this_type& other) const
        {
          return !(*this == other);
        }

        bool any() const
        {
          return m_word.front() != 0;
        }
        size_type count() const
        {
          size_type n = 0;
          for (word_type w = m_word.front(); w; w >>= 4)
          {
            n += rsl::popcount(w & 0xF);
          }
          return n;
        }
        size_type size() const
        {
          return BitsPerWord * 1;
        }
        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses to_ulong and we use to uint32.
        // the size of long is not platform agnostic while the size of uint32 is.
        uint32 to_uint32() const
        {
          return static_cast<uint32>(m_word.front());
        }
        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses to_ullong and we use to uint64.
        // because we don't use ulong, we're also not using to_ullong
        uint64 to_uint64() const
        {
          return static_cast<uint64>(m_word.front());
        }
        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses a std::string to convert here
        // we use a stack_string instead.
        rsl::stack_string<char8, 1 * BitsPerWord> to_string() const
        {
          rsl::stack_string<char8, N * BitsPerWord> res{};

          for (size_type i = 0; i < size(); ++i)
          {
            if ((*this)[i])
              res[size() - 1 - i] = '1';
          }

          return res;
        }

      protected:
        rsl::array<word_type, 1>& word()
        {
          return m_word;
        }
        const rsl::array<word_type, 1>& word() const
        {
          return m_word;
        }

      private:
        rsl::array<word_type, 1> m_word;
      };

      template <typename WordType>
      struct bitset_base<2, WordType>
      {
      public:
        using word_type = WordType;
        using this_type = bitset_base<2, WordType>;
        using size_type = card32;

        static constexpr size_type BitsPerWord = limits_byte::num_bits_per_byte * sizeof(word_type);
        static constexpr size_type BitsPerWordMask = BitsPerWord - 1;
        static constexpr size_type BitsPerWordShift = ((BitsPerWord == 8) ? 3 : ((BitsPerWord == 16) ? 4 : ((BitsPerWord == 32) ? 5 : (((BitsPerWord == 64) ? 6 : 7)))));

      public:
        bitset_base()
        {
          m_word[0] = 0;
          m_word[1] = 0;
        }
        bitset_base(card32 value)
        {
          m_word[0] = static_cast<word_type>(value);
          m_word[1] = 0;
        }

        void operator&=(const this_type& other)
        {
          m_word[0] &= other.m_word[0];
          m_word[1] &= other.m_word[1];
        }
        void operator|=(const this_type& other)
        {
          m_word[0] |= other.m_word[0];
          m_word[1] |= other.m_word[1];
        }
        void operator^=(const this_type& other)
        {
          m_word[0] ^= other.m_word[0];
          m_word[1] ^= other.m_word[1];
        }

        void operator<<=(size_type n)
        {
          if (n)
          {
            if (n >= BitsPerWord)
            {
              m_word[1] = rsl::exchange(m_word[0], 0);
              n -= BitsPerWord;
            }

            m_word[1] = (m_word[1] << n) | (m_word[0] >> (BitsPerWord - n));
            m_word[0] <<= n;
          }
        }
        void operator>>=(size_type n)
        {
          if (n)
          {
            if (n >= BitsPerWord)
            {
              m_word[0] = rsl::exchange(m_word[1], 0);
              n -= BitsPerWord;
            }

            m_word[0] = (m_word[0] >> n) | (m_word[1] << (BitsPerWord - n));
            m_word[1] >>= n;
          }
        }

        void flip()
        {
          m_word[0] = ~m_word[0];
          m_word[1] = ~m_word[1];
        }
        void set()
        {
          m_word[0] = ~static_cast<word_type>(0);
          m_word[1] = ~static_cast<word_type>(0);
        }
        void set(size_type idx, bool value)
        {
          if (value)
          {
            m_word[idx >> BitsPerWordShift] |= (static_cast<word_type>(1) << (idx & BitsPerWordMask));
          }
          else
          {
            m_word[idx >> BitsPerWordShift] &= ~(static_cast<word_type>(1) << (idx & BitsPerWordMask));
          }
        }
        void reset()
        {
          m_word[0] = 0;
          m_word[1] = 0;
        }

        bool operator==(const this_type& other) const
        {
          return (m_word[0] == other.m_word[0]) && (m_word[1] == other.m_word[1]);
        }
        bool operator!=(const this_type& other) const
        {
          return !(*this == other);
        }

        bool any() const
        {
          return (m_word[0] | m_word[1]) != 0;
        }
        size_type count() const
        {
          return rsl::popcount(m_word[0]) + rsl::popcount(m_word[1]);
        }
        size_type size() const
        {
          return BitsPerWord * 2;
        }

        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses to_ulong and we use to uint32.
        // the size of long is not platform agnostic while the size of uint32 is.
        uint32 to_uint32() const
        {
          return static_cast<uint32>(m_word[0]);
        }
        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses to_ullong and we use to uint64.
        // because we don't use ulong, we're also not using to_ullong
        uint64 to_uint64() const
        {
          return static_cast<uint64>(m_word[0]);
        }
        /// RSL Comment: Different from ISO C++ Standard at time of writing (13/Aug/2023)
        // The standard uses a std::string to convert here
        // we use a stack_string instead.
        rsl::stack_string<char8, 2 * BitsPerWord> to_string() const
        {
          rsl::stack_string<char8, N* BitsPerWord> res{};

          for (size_type i = 0; i < size(); ++i)
          {
            if ((*this)[i])
              res[size() - 1 - i] = '1';
          }

          return res;
        }

      protected:
        rsl::array<word_type, 2>& word()
        {
        return m_word;
        }

        const rsl::array<word_type, 2>& word() const
        {
          return m_word;
        }

      private:
        rsl::array<word_type, 2> m_word;
      };

      template <typename WordType>
      constexpr card32 word_count(card32 bitCount)
      {
        return (bitCount == 0 ? 1 : ((bitCount - 1) / (8 * sizeof(WordType)) + 1));
      }
    }

    template <card32 N>
    class bitset : public internal::bitset_base<internal::word_count<uint64>(N), uint64>
    {
    private:
      using base_type = internal::bitset_base<internal::word_count<uint64>(N), uint64>;
      using this_type = bitset<N>;
      using word_type = typename base_type::word_type;
      
      static constexpr card32 BitsPerWord      = limits_byte::num_bits_per_byte * sizeof(word_type);
      static constexpr card32 BitsPerWordMask  = (BitsPerWord - 1);
      static constexpr card32 BitsPerWordShift = ((BitsPerWord == 8) ? 3 : ((BitsPerWord == 16) ? 4 : ((BitsPerWord == 32) ? 5 : (((BitsPerWord == 64) ? 6 : 7)))));
			static constexpr card32 Size             = N;                                    // The number of bits the bitset holds
			static constexpr card32 WordSize         = sizeof(word_type);                    // The size of individual words the bitset uses to hold the bits.
			static constexpr card32 WordCount        = (N == 0 ? 1 : ((N - 1) / (8 * sizeof(word_type)) + 1)); // The number of words the bitset uses to hold the bits. sizeof(bitset<N, WordType>) == kWordSize * kWordCount.

    public:
      using size_type = typename base_type::size_type;

      class reference
      {
      public:
        reference(const bitset& word, card32 idx)
          : m_bit_word(&const_cast<bitset&>(word).word()[idx >> BitsPerWordShift])
          , m_bit_idx(idx)
        {}

        reference& operator=(bool value)
        {
          if (value)
          {
            *m_bit_word |= (static_cast<word_type>(1) << (m_bit_idx & BitsPerWordMask));
          }
          else
          {
            *m_bit_word &= ~(static_cast<word_type>(1) << (m_bit_idx & BitsPerWordMask));
          }

          return *this;
        }
        reference& operator=(const reference& other)
        {
          if (*other.m_bit_word & (static_cast<word_type>(1) << (other.m_bit_idx & BitsPerWordMask)))
          {
            *m_bit_word |= (static_cast<word_type>(1) << (m_bit_idx & BitsPerWordMask));
          }
          else
          {
            *m_bit_word &= ~(static_cast<word_type>(1) << (m_bit_idx & BitsPerWordMask));
          }

          return *this;
        }

        bool operator~() const
        {
          return (*m_bit_word & (static_cast<word_type>(1) << (m_bit_idx & BitsPerWordMask))) == 0;
        }
        operator bool() const
        {
          return (*m_bit_word & (static_cast<word_type>(1) << (m_bit_idx & BitsPerWordMask))) != 0;
        }

        reference& flip()
        {
          *m_bit_word ^= static_cast<word_type>(1) << (m_bit_idx & BitsPerWordMask);
          return *this;
        }

      private:
        word_type* m_bit_word;
        size_type m_bit_idx;
      };

      bitset() = default;
      bitset(size_type value)
        : base_type(value)
      {
        if constexpr ((N & BitsPerWordMask) || N == 0)
        {
          base_type::word()[WordCount - 1] &= ~(static_cast<word_type>(~static_cast<word_type>(0)) << (N & BitsPerWordMask));
        }
      }

      this_type& operator&=(const this_type& other)
      {
        base_type::operator&=(other);
        return *this;
      }
      this_type& operator|=(const this_type& other)
      {
        base_type::operator|=(other);
        return *this;
      }
      this_type& operator^=(const this_type& other)
      {
        base_type::operator^=(other);
        return *this;
      }

      this_type& operator<<=(size_type n)
      {
        if ((static_cast<intptr>(n) < static_cast<intptr>(N)))
        {
          base_type::operator<<=(n);
          if constexpr ((N & BitsPerWordMask) || (N == 0))
          {
            base_type::word()[WordCount - 1] &= ~(static_cast<word_type>(~static_cast<word_type>(0)) << (N & BitsPerWordMask));
          }
        }
        else
        {
          base_type::reset();
        }

        return *this;
      }
      this_type& operator>>=(size_type n)
      {
        if (n < N)
        {
          base_type::operator>>=(n);
        }
        else
        {
          base_type::reset();
        }

        return *this;
      }

      this_type& set()
      {
        base_type::set();
        if constexpr ((N & BitsPerWordMask) || (N == 0))
        {
          base_type::word()[WordCount - 1] &= ~(static_cast<word_type>(~static_cast<word_type>(0)) << (N & BitsPerWordMask));
        }

        return *this;
      }
      this_type& set(size_type idx, bool value = true)
      {
        if (idx < N)
        {
          base_type::set(idx, value);
        }
        else
        {
          RSL_ASSERT("idx out of range");
        }

        return *this;
      }

      this_type& reset()
      {
        base_type::reset();
        return *this;
      }
      this_type& reset(size_type idx)
      {
        RSL_ASSERT_X(idx < N, "index out of range");

        base_type::word()[idx >> BitsPerWordShift] &= ~(static_cast<word_type>(1) << (idx & BitsPerWordMask));

        return *this;
      }

      this_type& flip()
      {
        base_type::flip();
        if constexpr ((N & BitsPerWordMask) || (N == 0))
        {
          base_type::word()[WordCount - 1] &= ~(static_cast<word_type>(~static_cast<word_type>(0)) << (N & BitsPerWordMask));
        }

        return *this;
      }
      this_type& flip(size_type idx)
      {
        RSL_ASSERT_X(idx < N, "index out of range");

        base_type::word()[idx >> BitsPerWordShift] ^= (static_cast<word_type>(1) << (idx & BitsPerWordMask));

        return *this;
      }

      this_type& operator~() const
      {
        return this_type(*this).flip();
      }

      reference operator[](size_type idx)
      {
        RSL_ASSERT_X(idx < N, "index out of range");

        return reference(*this, idx);
      }
      bool      operator[](size_type idx) const
      {
        RSL_ASSERT_X(idx < N, "index out of range");

        auto word = base_type::word()[idx >> BitsPerWordShift];

        return (word & (static_cast<word_type>(1) << (idx & BitsPerWordMask))) != 0;
      }

      size_type size() const
      {
        return static_cast<size_type>(N);
      }

      bool operator==(const this_type& other) const
      {
        return base_type::operator==(other);
      }
      bool operator!=(const this_type& other) const
      {
        return base_type::operator!=(other);
      }

      bool test(size_type idx) const
      {
        RSL_ASSERT_X(idx < N, "index out of range");

        const auto word = base_type::word()[idx >> BitsPerWordShift];
        const auto mask = (static_cast<word_type>(1) << (idx & BitsPerWordMask));
        return ((word & mask) != 0);
      }
      //bool any() const;                   // We inherit this from the base class.
      bool all() const
      {
        return count() == size();
      }
      bool none() const
      {
        return !base_type::any();
      }

      this_type operator<<(size_type n) const
      {
        return this_type(*this).operator<<=(n);
      }
      this_type operator>>(size_type n) const
      {
        return this_type(*this).operator>>=(n);
      }
    };
  } // namespace v1
} // namespace rsl

