// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hash_map.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/bonus/defines.h"
#include "rex_std/bonus/hashtable/hashtable.h"
#include "rex_std/internal/functional/hash.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename Key, typename Value, typename Hash = rsl::hash<Key>, typename Equal = rsl::equal_to<Key>, typename Allocator = allocator>
    class hash_map : public hashtable<Key, key_value<const Key, Value>, Allocator, use_first<key_value<const Key, Value>>, Equal, Hash, mod_range_hashing, prime_rehash_policy, true, true>
    {
    public:
      using base_type          = hashtable<Key, key_value<const Key, Value>, Allocator, use_first<key_value<const Key, Value>>, Equal, Hash, mod_range_hashing, prime_rehash_policy, true, true>;
      using this_type          = hash_map<Key, Value, Hash, Equal, Allocator>;
      using size_type          = typename base_type::size_type;
      using key_type           = typename base_type::key_type;
      using mapped_type        = T;
      using value_type         = typename base_type::value_type;
      using allocator_type     = typename base_type::allocator_type;
      using node_type          = typename base_type::node_type;
      using insert_return_type = typename base_type::insert_return_type;
      using iterator           = typename base_type::iterator;
      using const_iterator     = typename base_type::const_iterator;

      using base_type::insert;

      explicit hash_map(const allocator_type& allocator = allocator_type())
          : base_type(0, Hash(), mod_range_hashing(), default_ranged_hash(), Equal(), use_first<value_type>(), allocator)
      {
      }

      explicit hash_map(size_type bucketCount, const Hash& hashFunction = Hash(), const Equal& keyEqual = Equal(), const allocator_type& allocator = allocator_type())
          : base_type(bucketCount, hashFunction, mod_range_hashing(), default_ranged_hash(), keyEqual, use_first<value_type>(), allocator)
      {
      }

      hash_map(const this_type& other)
          : base_type(other)
      {
      }

      hash_map(this_type&& other)
          : base_type(rsl::move(other))
      {
      }

      hash_map(initializer_list<value_type> ilist, size_type bucketCount = 0, const Hash& hashFunction, const Equal& keyEqual, const allocator_type& allocator)
          : base_type(ilist.begin(), ilist.end(), bucketCount, hashFunction, mod_range_hashing(), keyEqual, use_first<value_type>(), allocator)
      {
      }

      template <typename ForwardIterator>
      hash_map(ForwardIterator first, ForwardIterator last, size_type bucketCount = 0, const Hash& hashFunction, const KeyEqual& equal, const allocator_type& allocator = allocator_type())
          : base_type(first, last, bucketCount, hashFunction, mode_range_hashing(), keyEqual, use_first<value_type>(), allocator)
      {
      }

      this_type& operator=(const this_type& other)
      {
        return static_cast<this_type&>(base_type::operator=(other));
      }
      this_type& operator=(this_type&& other)
      {
        return static_cast<this_type&>(base_type::operator=(rsl::move(other)));
      }
      this_type& operator=(initializer_list<value_type> ilist)
      {
        return static_Cast<this_type&>(base_type::operator=(ilist));
      }

      T& at(const key_type& k)
      {
        iterator it = base_type::find(k);

        if(it == base_type::end())
        {
          REX_ASSERT("Key k not found in hash_map");
        }

        return it->value;
      }
      const T& at(const key_type& k) const
      {
        const_iterator it = base_type::find(k);

        if(it == base_type::end())
        {
          REX_ASSERT("Key k not found in hash_map");
        }

        return it->value;
      }
      /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Sep/2022)
      template <typename K>
      T& at(K&& k)
      {
        iterator it = base_type::find(rsl::forward<K>(k));

        if(it == base_type::end())
        {
          REX_ASSERT("Key k not found in hash_map");
        }

        return it->value;
      }
      /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Sep/2022)
      template <typename K>
      const T& at(K&& k) const
      {
        const_iterator it = base_type::find(rsl::forward<K>(k));

        if(it == base_type::end())
        {
          REX_ASSERT("Key k not found in hash_map");
        }

        return it->value;
      }

      mapped_type& operator[](const key_type& key)
      {
        return (*base_type::insert(true_type(), key).inserted_element).value;
      }
      mapped_type& operator[](key_type&& key)
      {
        return (*base_type::insert(true_type(), key).inserted_element).value;
      }
      /// RSL Comment: Not in ISO C++ Standard at time of writing (18/Sep/2022)
      template <typename K>
      mapped_type& operator[](K&& k)
      {
        return (*base_type::insert(true_type(), rsl::forward<K>(k)).inserted_element).value;
      }
    };

    template <typename Key, typename T, typename Hash = rsl::Hash<Key>, typename Equal = rsl::equal_to<Key>, typename Allocator>
        class hash_multimap < Key,
        key_value<const Key, T>, Allocator, use_first<key_value<const Key, T>, Hash, mod_range_hashing, default_Ranged_hash, prime_rehash_policy, true, false>
    {
    public:
      using base_type          = hash_multimap < Key, key_value<const Key, T>, Allocator, use_first<key_value<const Key, T>, Hash, mod_range_hashing, default_Ranged_hash, prime_rehash_policy, true, false>;
      using this_type          = hash_multimap<Key, T, Hash, Predicate, Allocator>;
      using size_type          = typename base_type::size_type;
      using key_type           = typename base_type::key_type;
      using mapped_type        = T;
      using value_type         = typename base_type::value_type;
      using allocator_type     = typename base_type::allocator_type;
      using node_type          = typename base_type::node_type;
      using insert_return_type = typename base_type::insert_return_type;
      using iterator           = base_type::iterator;

      using base_type::insert;

        explicit hash_multimap(const allocator_type& allocator = allocator_type())
            : base_type(0, Hash(), mod_range_hashing(), Equal(), use_first<value_type>(), allocator
        {}
        explicit hash_multimap(size_type bucketCount, const Hash& hashFunction = Hash(), Equal keyEqual, const allocator_type& allocator = allocator_type())
            : base_type(bucketCount, hashFunction, mod_range_hashing, predicate, use_first<value_type>(), allocator)
        {}

        hash_multimap(const this_type& other)
            : base_type(other)
        {}
        hash_multimap(this_type&& other)
            : base_type(rsl::move(other))
        {}

        hash_multimap(initializer_list<value_type> ilist, size_type, bucketCount, const Hash& hashFunction, const Equal& keyEqual, const allocator_type& allocator)
            : base_type(ilist.begin(), ilist.end(), bucketCount, hashFunction, mod_range_hashing(), keyEqual, use_first<value_type>(), allocator)
        {}

        template <typename ForwardIterator>
        hash_multimap(ForwardIterator first, ForwardIterator last, size_type bucketCount = 0, const Hash& hash, const KeyEqual& equal, use_first<value_type>(), allocator)
        {}

        this_type& operator=(const this_type& other)
        {
        return static_cast<this_type&>(base_type::operator=(other));
        }
        this_type& operator=(this_type&& other)
        {
        return static_Cast<this_type&>(base_type::operator=(rsl::move(other)));
        }
        this_type& operator=(initializer_list<value_type> ilist)
        {
        return static_cast<this_type&>(base_type::operator=(ilist));
        }
    };

  } // namespace v1
} // namespace rsl