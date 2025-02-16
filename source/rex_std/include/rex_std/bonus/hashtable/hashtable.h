// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: hashtable.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/bonus/functional/hash_result.h"
#include "rex_std/bonus/hashtable/hashtable_iterator.h"
#include "rex_std/bonus/hashtable/node_iterator.h"
#include "rex_std/bonus/hashtable/rehash_base.h"
#include "rex_std/bonus/type_traits/strip_template.h"
#include "rex_std/bonus/utility/compressed_pair.h"
#include "rex_std/bonus/utility/emplace_result.h"
#include "rex_std/bonus/utility/range.h"
#include "rex_std/initializer_list.h"
#include "rex_std/internal/algorithm/max.h"
#include "rex_std/internal/assert/assert_fwd.h"
#include "rex_std/internal/memory/addressof.h"
#include "rex_std/internal/memory/memset.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/integral_constant.h"
#include "rex_std/internal/type_traits/is_constructible.h"
#include "rex_std/internal/utility/forward.h"
#include "rex_std/internal/utility/move.h"
#include "rex_std/internal/utility/piecewise_construct.h"
#include "rex_std/internal/utility/swap.h"

namespace rsl
{
  inline namespace v1
  {

    template <typename Key, typename Value, typename Alloc, typename ExtractKey, typename Equal, typename KeyHash, typename BucketIndexFinder, typename RehashPolicy, bool UsesMutableIterators, bool UsesUniqueKeys>
    class hashtable : public rehash_base<RehashPolicy, hashtable<Key, Value, Alloc, ExtractKey, Equal, KeyHash, BucketIndexFinder, RehashPolicy, UsesMutableIterators, UsesUniqueKeys>>
    {
    public:
      using key_type                 = Key;
      using value_type               = Value;
      using mapped_type              = typename ExtractKey::result_type;
      using allocator_type           = Alloc;
      using key_equal                = Equal;
      using difference_type          = ptrdiff;
      using size_type                = count_t;
      using reference                = value_type&;
      using const_reference          = const value_type&;
      using local_iterator           = node_iterator<value_type, !UsesMutableIterators>;
      using const_local_iterator     = node_iterator<value_type, true>;
      using iterator                 = hashtable_iterator<value_type>;
      using const_iterator           = const_hashtable_iterator<value_type>;
      using node_type                = hash_node<value_type>;
      using insert_return_type       = typename type_select<UsesUniqueKeys, insert_result<iterator>, iterator>::type;
      using this_type                = hashtable<Key, Value, Alloc, ExtractKey, Equal, KeyHash, BucketIndexFinder, RehashPolicy, UsesMutableIterators, UsesUniqueKeys>;
      using rehash_policy_type       = RehashPolicy;
      using extract_key_type         = ExtractKey;
      using key_hash_type            = KeyHash;
      using bucket_index_finder_type = BucketIndexFinder;
      using has_unique_keys_type     = bool_constant<UsesUniqueKeys>;

      hashtable()
          : rehash_base<RehashPolicy, hashtable>()
          , m_cp_key_equal_and_bucket_array(nullptr)
          , m_cp_key_hash_and_bucket_count(0)
          , m_cp_bucket_idx_finder_and_element_count(0)
          , m_cp_extract_key_and_rehash_policy()
          , m_allocator()
      {
        allocate_buckets(1); // always have at least 1 bucket allocated
      }
      hashtable(Size bucketCount, const KeyHash& keyHash, const BucketIndexFinder& bucketIndexFinder, const Equal& equal, const ExtractKey& extractKey, const allocator_type& allocator)
          : m_cp_key_equal_and_bucket_array(equal)
          , m_cp_key_hash_and_bucket_count(keyHash, bucketCount.get())
          , m_cp_bucket_idx_finder_and_element_count(bucketIndexFinder)
          , m_cp_extract_key_and_rehash_policy(extractKey)
          , m_allocator(allocator)
      {
        if(bucket_count() > 0)
        {
          m_cp_key_equal_and_bucket_array.second() = allocate_buckets(bucket_count());
        }
        else
        {
          m_cp_key_hash_and_bucket_count.second()  = 1;
          m_cp_key_equal_and_bucket_array.second() = allocate_buckets(1); // always have at least 1 bucket allocated
        }
      }

      template <typename ForwardIterator>
      hashtable(ForwardIterator first, ForwardIterator last, Size bucketCount, const KeyHash& keyHash, const BucketIndexFinder& bucketIndexFinder, const Equal& equal, const ExtractKey& extractKey, const allocator_type& allocator)
          : hashtable(bucketCount, keyHash, bucketIndexFinder, equal, extractKey, allocator)
      {
        if(bucketCount.get() < 2)
        {
          const size_type element_count           = static_cast<size_type>(internal::ht_distance(first, last));
          m_cp_key_hash_and_bucket_count.second() = static_cast<size_type>(m_cp_extract_key_and_rehash_policy.second().get_bucket_count(element_count));
        }
        else
        {
          RSL_ASSERT_X(bucketCount.get() < 10'000'000, "Bucket count too big for hashtable. bucketcount: {}", bucketCount.get());
          m_cp_key_hash_and_bucket_count.second() = bucketCount.get();
        }

        m_cp_key_hash_and_bucket_count.second()  = (rsl::max)(1, bucket_count());
        m_cp_key_equal_and_bucket_array.second() = allocate_buckets(m_cp_key_hash_and_bucket_count.second()); // always have at least 1 bucket allocated

        for(; first != last; ++first)
        {
          insert(*first);
        }
      }

      hashtable(const hashtable& other)
          : rehash_base<RehashPolicy, hashtable>(other)
          , m_cp_key_equal_and_bucket_array(other.m_cp_key_equal_and_bucket_array)
          , m_cp_key_hash_and_bucket_count(other.m_cp_key_hash_and_bucket_count)
          , m_cp_bucket_idx_finder_and_element_count(other.m_cp_bucket_idx_finder_and_element_count)
          , m_cp_extract_key_and_rehash_policy(other.m_cp_extract_key_and_rehash_policy)
          , m_allocator(other.m_allocator)
      {
        if(size())
        {
          m_cp_key_equal_and_bucket_array.second() = allocate_buckets(bucket_count());

          for(size_type i = 0; i < other.bucket_count(); ++i)
          {
            node_type* node_source = other.bucket_array()[i];
            node_type** node_dest  = bucket_array() + i;

            while(node_source)
            {
              *node_dest  = allocate_node(node_source->value);
              node_dest   = &(*node_dest)->next;
              node_source = node_source->next;
            }
          }
        }
        else
        {
          m_cp_key_hash_and_bucket_count.second()  = 1;
          m_cp_key_equal_and_bucket_array.second() = allocate_buckets(1); // always have at least 1 bucket allocated
        }
      }

      hashtable(this_type&& other)
          : hashtable()
      {
        swap(other);
      }

      /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Sep/2022)
      // We're not implementing an overload taking it's own allocator, as allocators
      // need to be equivalent when moving in Rex Standard Library

      ~hashtable()
      {
        clear();
        free_buckets(bucket_array());
      }

      /// RSL Comment: Different from ISO C++ Standard at time of writing (17/Sep/2022)
      // This returns a copy of the allocator in the C++ Standard.
      const allocator_type& get_allocator() const
      {
        return m_allocator;
      }

      this_type& operator=(const this_type& other)
      {
        RSL_ASSERT_X(this != addressof(other), "Can't copy to yourself");

        clear();
        insert(other.begin(), other.end());

        return *this;
      }
      this_type& operator=(initializer_list<value_type> ilist)
      {
        clear();
        insert(ilist.begin(), ilist.end());
        return *this;
      }
      this_type& operator=(this_type&& other)
      {
        RSL_ASSERT_X(this != rsl::addressof(other), "Can't move to yourself");

        clear();
        swap(other);
        return *this;
      }

      void swap(this_type& other)
      {
        rsl::swap(m_cp_key_equal_and_bucket_array, other.m_cp_key_equal_and_bucket_array);
        rsl::swap(m_cp_key_hash_and_bucket_count, other.m_cp_key_hash_and_bucket_count);
        rsl::swap(m_cp_bucket_idx_finder_and_element_count, other.m_cp_bucket_idx_finder_and_element_count);
        rsl::swap(m_cp_extract_key_and_rehash_policy, other.m_cp_extract_key_and_rehash_policy);
        rsl::swap(m_allocator, other.m_allocator);
      }

      iterator begin()
      {
        iterator it(m_cp_key_equal_and_bucket_array.second());
        if(!it.node())
        {
          it.increment_bucket();
        }
        return it;
      }
      const_iterator begin() const
      {
        const_iterator it(m_cp_key_equal_and_bucket_array.second());
        if(!it.node())
        {
          it.increment_bucket();
        }
        return it;
      }
      const_iterator cbegin() const
      {
        return begin();
      }
      iterator end()
      {
        return iterator(bucket_array() + bucket_count());
      }
      const_iterator end() const
      {
        return const_iterator(bucket_array() + bucket_count());
      }
      const_iterator cend() const
      {
        return end();
      }

      local_iterator begin(size_type n)
      {
        return local_iterator(m_cp_key_equal_and_bucket_array.second()[n]);
      }
      const_local_iterator begin(size_type n) const
      {
        return const_local_iterator(m_cp_key_equal_and_bucket_array.second()[n]);
      }
      const_local_iterator cbegin(size_type n) const
      {
        return const_local_iterator(m_cp_key_equal_and_bucket_array.second()[n]);
      }

      local_iterator end(size_type /*unused*/)
      {
        return local_iterator(nullptr);
      }
      const_local_iterator end(size_type /*unused*/) const
      {
        return const_local_iterator(nullptr);
      }
      const_local_iterator cend(size_type /*unused*/) const
      {
        return const_local_iterator(nullptr);
      }

      bool empty() const
      {
        return m_cp_bucket_idx_finder_and_element_count.second() == 0;
      }

      size_type size() const
      {
        return m_cp_bucket_idx_finder_and_element_count.second();
      }
      size_type bucket_count() const
      {
        return m_cp_key_hash_and_bucket_count.second();
      }
      size_type bucket_size(size_type n) const
      {
        return static_cast<size_type>(distance(begin(n), end(n)));
      }

      float32 load_factor() const
      {
        const float32 element_count = static_cast<float32>(m_cp_bucket_idx_finder_and_element_count.second());
        const float32 bucket_count  = static_cast<float32>(m_cp_key_hash_and_bucket_count.second());
        return bucket_count == 0.0f ? 0.0f : element_count / bucket_count;
      }

      const rehash_policy_type& rehash_policy() const
      {
        return m_cp_extract_key_and_rehash_policy.second();
      }

      void rehash_policy(rehash_policy_type rehashPolicy)
      {
        m_cp_extract_key_and_rehash_policy.second() = rehashPolicy;

        const size_type new_bucket_count = rehashPolicy.get_bucket_count(m_cp_bucket_idx_finder_and_element_count.second());
        if(new_bucket_count > bucket_count())
        {
          rehash(new_bucket_count);
        }
      }

      template <typename... Args>
      insert_return_type emplace(Args&&... args)
      {
        return insert_value(has_unique_keys_type(), rsl::forward<Args>(args)...);
      }

      template <typename... Args>
      insert_return_type try_emplace(const key_type& k, Args&&... args)
      {
        return insert_value(has_unique_keys_type(), k, rsl::forward<Args>(args)...);
      }
      template <typename... Args>
      insert_return_type try_emplace(key_type&& k, Args&&... args)
      {
        return insert_value(has_unique_keys_type(), rsl::move(k), rsl::forward<Args>(args)...);
      }

      insert_return_type insert(const value_type& value)
      {
        return insert_value(has_unique_keys_type(), value);
      }
      insert_return_type insert(value_type&& otherValue)
      {
        return insert_value(has_unique_keys_type(), rsl::move(otherValue));
      }
      void insert(initializer_list<value_type> ilist)
      {
        return insert(ilist.begin(), ilist.end());
      }
      template <typename InputIterator>
      void insert(InputIterator first, InputIterator last)
      {
        const count_t num_elements_to_add = static_cast<count_t>(internal::ht_distance(first, last));
        hash_required_result result       = m_cp_extract_key_and_rehash_policy.second().is_rehash_required(bucket_count(), size(), num_elements_to_add);

        if(result.is_hash_required)
        {
          rehash(result.new_bucket_count);
        }
        else
        {
          for(; first != last; ++first)
          {
            insert_value(has_unique_keys_type(), *first);
          }
        }
      }

      template <typename P, typename = enable_if_t<!is_constructible_v<value_type, P&&>>>
      insert_return_type insert(P&& otherValue)
      {
        return emplace(rsl::forward<P>(otherValue));
      }

      template <typename M>
      insert_return_type insert_or_assign(const key_type& k, M&& obj)
      {
        auto it = find(k);
        if(it == end())
        {
          return insert(value_type(k, rsl::forward<M>(obj)));
        }
        else
        {
          it->second = rsl::forward<M>(obj);
          return {it, false};
        }
      }
      template <typename M>
      insert_return_type insert_or_assign(key_type&& k, M&& obj)
      {
        auto it = find(k);
        if(it == end())
        {
          return insert(value_type(rsl::move(k), rsl::forward<M>(obj)));
        }
        else
        {
          it->second = rsl::forward<M>(obj);
          return {it, false};
        }
      }

      iterator erase(const_iterator position)
      {
        iterator it_next(position.node(), position.bucket());
        ++it_next;

        node_type* node         = it_next.node();
        node_type* current_node = *it_next.bucket();

        if(current_node == node)
        {
          *it_next.bucket() = current_node->next;
        }
        else
        {
          node_type* next_node = current_node->next;

          while(next_node != node)
          {
            current_node = next_node;
            next_node    = current_node->next;
          }

          current_node->next = next_node->next;
        }

        free_node(node);
        --m_cp_bucket_idx_finder_and_element_count.second();

        return it_next;
      }
      iterator erase(const_iterator first, const_iterator last)
      {
        while(first != last)
          first = erase(first);

        return iterator(first.node(), first.bucket());
      }
      size_type erase(const key_type& k)
      {
        const hash_result hr                = hash_keylike_type(k);
        const size_type n                   = static_cast<size_type>(bucket_index(hr, bucket_count()));
        const size_type element_count_saved = size();

        node_type** bucket_array = m_cp_key_equal_and_bucket_array.second() + n;

        while(*bucket_array && !compare_key(k, m_cp_extract_key_and_rehash_policy.first()((*bucket_array)->value)))
        {
          bucket_array = &(*bucket_array)->next;
        }

        while(*bucket_array && compare_key(k, m_cp_extract_key_and_rehash_policy.first()((*bucket_array)->value)))
        {
          node_type* node = *bucket_array;
          *bucket_array   = node->next;
          free_node(node);
          --m_cp_bucket_idx_finder_and_element_count.second();
        }

        return element_count_saved - size();
      }

      template <typename K>
      size_type erase(K&& k)
      {
        const hash_result hr                = hash_keylike_type(rsl::forward<K>(k));
        const size_type n                   = static_cast<size_type>(bucket_index(hr, bucket_count()));
        const size_type element_count_saved = size();

        node_type** bucket_arr = bucket_array() + n;

        while(*bucket_arr && !compare_key(rsl::forward<K>(k), m_cp_extract_key_and_rehash_policy.first()((*bucket_arr)->value)))
        {
          bucket_arr = &(*bucket_arr)->next;
        }

        while(*bucket_arr && compare_key(rsl::forward<K>(k), m_cp_extract_key_and_rehash_policy.first()((*bucket_arr)->value)))
        {
          node_type* node = *bucket_arr;
          *bucket_arr     = node->next;
          free_node(node);
          --m_cp_bucket_idx_finder_and_element_count.second();
        }

        return element_count_saved - size();
      }

      void clear()
      {
        free_nodes(bucket_array(), bucket_count());
        m_cp_bucket_idx_finder_and_element_count.second() = 0;
      }
      void rehash(size_type bucketCount)
      {
        node_type** const new_bucket_array = allocate_buckets(bucketCount);

        node_type* node = nullptr;

        for(size_type i = 0; i < bucket_count(); ++i)
        {
          while((node = bucket_array()[i]) != nullptr)
          {
            const size_type new_bucket_index = bucket_index(node, bucketCount);

            bucket_array()[i]                  = node->next;
            node->next                         = new_bucket_array[new_bucket_index];
            new_bucket_array[new_bucket_index] = node;
          }
        }

        free_buckets(bucket_array());
        m_cp_key_hash_and_bucket_count.second()  = bucketCount;
        m_cp_key_equal_and_bucket_array.second() = new_bucket_array;
      }
      void reserve(size_type elementCount)
      {
        rehash(rehash_policy().get_bucket_count(elementCount));
      }

      iterator find(const key_type& key)
      {
        const hash_result hr = hash_keylike_type(key);
        const size_type n    = static_cast<size_type>(bucket_index(hr, bucket_count()));

        node_type* node = find_node(bucket_array()[n], key);
        return node ? iterator(node, bucket_array() + n) : end();
      }
      const_iterator find(const key_type& key) const
      {
        const hash_result hr = hash_keylike_type(key);
        const size_type n    = static_cast<size_type>(bucket_index(hr, bucket_count()));

        node_type* node = find_node(bucket_array()[n], key);
        return node ? const_iterator(node, bucket_array() + n) : cend();
      }
      template <typename K>
      iterator find(const K& x)
      {
        const hash_result hr = hash_keylike_type(x);
        const size_type n    = static_cast<size_type>(bucket_index(hr, bucket_count()));

        node_type* node = find_node(bucket_array()[n], x);
        return node ? iterator(node, bucket_array() + n) : end();
      }
      template <typename K>
      const_iterator find(const K& x) const
      {
        const hash_result hr = hash_keylike_type(x);
        const size_type n    = static_cast<size_type>(bucket_index(hr, bucket_count()));

        node_type* node = find_node(bucket_array()[n], x);
        return node ? const_iterator(node, bucket_array() + n) : cend();
      }
      template <typename K>
      size_type count(const K& x) const
      {
        const hash_result hr = hash_keylike_type(x);
        const size_type n    = static_cast<size_type>(bucket_index(hr, bucket_count()));

        node_type* node = find_node(bucket_array()[n], x);

        if constexpr(has_unique_keys_type::value)
        {
          return node ? 1 : 0;
        }
        else
        {
          size_type result = 0;

          // To do: Make a specialization for bU (unique keys) == true and take
          // advantage of the fact that the count will always be zero or one in that case.
          for(; node; node = node->next)
          {
            if(!compare_key(x, m_cp_extract_key_and_rehash_policy.first()((*bucket_array())->value)))
            {
              ++result;
            }
          }
          return result;
        }
      }

      bool contains(const Key& key) const
      {
        return find(key) != cend();
      }
      template <typename K>
      bool contains(const K& x) const
      {
        return find(x) != cend();
      }

      range<iterator> equal_range(const key_type& k)
      {
        const size_type n = static_cast<size_type>(bucket_index(k, bucket_count()));
        node_type** head  = bucket_array() + n;
        node_type* node   = find_node(*head, k);

        if(node)
        {
          node_type* p1 = node->next;

          for(; p1; p1 = p1->next)
          {
            if(!compare_key(k, m_cp_extract_key_and_rehash_policy.first()((*bucket_array)->value)))
            {
              break;
            }
          }

          iterator first(node, head);
          iterator last(p1, head);

          if(!p1)
          {
            last.increment_bucket();
          }

          return {first, last};
        }

        return {end(), end()};
      }
      range<const_iterator> equal_range(const key_type& k) const
      {
        const size_type n = static_cast<size_type>(bucket_index(k, bucket_count()));
        node_type** head  = bucket_array() + n;
        node_type* node   = find_node(*head, k);

        if(node)
        {
          node_type* p1 = node->next;

          for(; p1; p1 = p1->next)
          {
            if(!compare_key(k, m_cp_extract_key_and_rehash_policy.first()((*bucket_array)->value)))
            {
              break;
            }
          }

          const_iterator first(node, head);
          const_iterator last(p1, head);

          if(!p1)
          {
            last.increment_bucket();
          }

          return {first, last};
        }

        return {end(), end()};
      }

    protected:
      template <typename... Args>
      insert_return_type insert_value(true_type /*unused*/, Args&&... args)
      {
        value_type new_val     = value_type {rsl::forward<Args>(args)...};
        const key_type& k      = m_cp_extract_key_and_rehash_policy.first()(new_val);
        const hash_result hr   = hash_keylike_type(k);
        size_type n            = static_cast<size_type>(bucket_index(hr, bucket_count()));
        node_type* node        = nullptr;
        node_type** bucket_arr = bucket_array();
        if(bucket_arr)
        {
          node = find_node(bucket_arr[n], k);
        }

        if(node == nullptr)
        {
          void* new_node_addr               = static_cast<node_type*>(m_allocator.allocate(sizeof(node_type)));
          node_type* new_node               = new(new_node_addr) node_type(rsl::move(new_val));
          const hash_required_result result = m_cp_extract_key_and_rehash_policy.second().is_rehash_required(bucket_count(), size(), 1);

          if(result.is_hash_required)
          {
            n = static_cast<size_type>(bucket_index(hr, result.new_bucket_count));
            rehash(result.new_bucket_count);
          }

          new_node->next                              = m_cp_key_equal_and_bucket_array.second()[n];
          m_cp_key_equal_and_bucket_array.second()[n] = new_node;
          ++m_cp_bucket_idx_finder_and_element_count.second();

          return insert_return_type {iterator(new_node, m_cp_key_equal_and_bucket_array.second() + n), true};
        }

        return insert_return_type {iterator(node, m_cp_key_equal_and_bucket_array.second() + n), false};
      }

    private:
      node_type**& bucket_array()
      {
        return m_cp_key_equal_and_bucket_array.second();
      }
      node_type** bucket_array() const
      {
        return m_cp_key_equal_and_bucket_array.second();
      }
      bucket_index_finder_type bucket_index_finder()
      {
        return m_cp_bucket_idx_finder_and_element_count.first();
      }
      extract_key_type extract_key()
      {
        return m_cp_extract_key_and_rehash_policy.first();
      }
      rehash_policy_type rehash_policy()
      {
        return m_cp_extract_key_and_rehash_policy.second();
      }

      node_type** allocate_buckets(size_type bucketCount)
      {
        node_type** const bucket_array = static_cast<node_type**>(m_allocator.allocate((bucketCount + 1) * sizeof(node_type**))); // + 1 for the sentinal
        rsl::memset(bucket_array, 0, bucketCount * sizeof(node_type**));
        // set the sentinal bucket to an invalid value
        rsl::memset(bucket_array + bucketCount, 0xFFi8, sizeof(node_type**));
        return bucket_array;
      }

      void free_buckets(node_type** bucketArray)
      {
        m_allocator.deallocate(bucketArray, (bucket_count() + 1) * sizeof(node_type**)); // +1 for sentinal
      }

      void free_nodes(node_type** nodeArray, size_type bucketCount)
      {
        for(size_type i = 0; i < bucketCount; ++i)
        {
          node_type* p_node = nodeArray[i];
          while(p_node)
          {
            node_type* const p_temp_node = p_node;
            p_node                       = p_node->next;
            free_node(p_temp_node);
          }
          nodeArray[i] = nullptr;
        }
      }

      void free_node(node_type* node)
      {
        node->~node_type();
        m_allocator.deallocate(node, sizeof(node_type));
      }

      template <typename... Args>
      node_type* allocate_node(Args&&... args)
      {
        void* node = m_allocator.allocate(sizeof(node_type));
        new(node) node_type(rsl::forward<Args>(args)...);
        return static_cast<node_type*>(node);
      }

      size_type bucket_index(hash_result hr, size_type bucketCount) const
      {
        const hash_result res = hr % bucketCount;
        return static_cast<size_type>(res);
      }

      size_type bucket_index(node_type* node, size_type bucketCount) const
      {
        const hash_result hr = hash_keylike_type(m_cp_extract_key_and_rehash_policy.first()(node->value));
        return bucket_index(hr, bucketCount);
      }

      template <typename K>
      node_type* find_node(node_type* node, const K& k) const
      {
        for(; node; node = node->next)
        {
          if(m_cp_key_equal_and_bucket_array.first()(k, m_cp_extract_key_and_rehash_policy.first()(node->value)))
          {
            return node;
          }
        }

        return nullptr;
      }

      template <typename K>
      hash_result hash_keylike_type(const K& type) const
      {
        // it's possible the type we pass in to look for something is different than the key type.
        // eg. it's possible you pass in a string view while the hashtable itself is storing strings as keys
        // it was not possible look for these keys with a string_view while using the default hash functor (rsl::hash)
        // as rsl::hash had no overload taking in a string_view (or it's not implicilty convertible) which is so by design.
        // so instead, we have this function which uses the "change_hash_type" to use rsl::hash<rsl::string_view> when a string view
        // is passed in. This bypasses the hasher stored in the table, but the same underlying type is still used.
        // it just uses rsl::hash<rsl::string_view> instead of rsl::hash<rsl::string>, neither of which has side effects.
        using new_hash_type = rsl::change_template_t<key_hash_type, K>;
        if constexpr(rsl::is_same_v<new_hash_type, key_hash_type>)
        {
          return m_cp_key_hash_and_bucket_count.first()(type);
        }
        else
        {
          static_assert(rsl::is_constructible_v<key_type, K>, "key_type is not constructible from 'K'");

          const new_hash_type hasher {};
          return hasher(type);
        }
      }

      template <typename K1, typename K2>
      bool compare_key(const K1& k1, const K2& k2)
      {
        const auto& comparer = m_cp_key_equal_and_bucket_array.first();
        using other_type     = rsl::conditional_t<rsl::is_same_v<K1, Key>, K2, K1>;
        return comparer(k1, k2);
      }

    private:
      compressed_pair<key_equal, node_type**> m_cp_key_equal_and_bucket_array;
      compressed_pair<key_hash_type, size_type> m_cp_key_hash_and_bucket_count;
      compressed_pair<bucket_index_finder_type, size_type> m_cp_bucket_idx_finder_and_element_count;
      compressed_pair<extract_key_type, rehash_policy_type> m_cp_extract_key_and_rehash_policy;
      allocator_type m_allocator;
    };

  } // namespace v1
} // namespace rsl
