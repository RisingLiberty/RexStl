// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: hash_set.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/functional/hash.h"
#include "rex_std/internal/functional/equal_to.h"
#include "rex_std/internal/memory/allocator.h"
#include "rex_std/bonus/hashtable/hashtable.h"
#include "rex_std/bonus/utility/use_self.h"
#include "rex_std/bonus/hashtable/mod_range_hashing.h"
#include "rex_std/internal/utility/pair.h"

namespace rsl
{
  inline namespace v1
  {
		template <typename Value, typename Hash = rsl::hash<Value>, typename Predicate = rsl::equal_to<Value>,
			typename Alloc = rsl::allocator>
			class hash_set : public hashtable<Value, Value, Alloc, rsl::use_self<Value>, Predicate, Hash, mod_range_hashing, prime_rehash_policy, false, true>
		{
		public:
			using base_type = hashtable<Value, Value, Alloc, rsl::use_self<Value>, Predicate, Hash, mod_range_hashing, prime_rehash_policy, false, true>;
			using this_type = hash_set<Value, Hash, Predicate, Alloc>;
			using size_type = typename base_type::size_type;
			using value_type = typename base_type::value_type;
			using allocator_type = typename base_type::allocator_type;
			using node_type = typename base_type::node_type;

		public:
			/// hash_set
			///
			/// Default constructor.
			/// 
			explicit hash_set(const allocator_type& allocator = allocator_type())
				: base_type(0_size, Hash(), mod_range_hashing(), Predicate(), rsl::use_self<Value>(), allocator)
			{
				// Empty
			}


			/// hash_set
			///
			/// Constructor which creates an empty container, but start with nBucketCount buckets.
			/// We default to a small nBucketCount value, though the user really should manually 
			/// specify an appropriate value in order to prevent memory from being reallocated.
			///
			explicit hash_set(size_type nBucketCount, const Hash& hashFunction = Hash(), const Predicate& predicate = Predicate(),
				const allocator_type& allocator = allocator_type())
				: base_type(nBucketCount, hashFunction, mod_range_hashing(), predicate, rsl::use_self<Value>(), allocator)
			{
				// Empty
			}


			hash_set(const this_type& x)
				: base_type(x)
			{
			}


			hash_set(this_type&& x)
				: base_type(rsl::move(x))
			{
			}


			hash_set(this_type&& x, const allocator_type& allocator)
				: base_type(rsl::move(x), allocator)
			{
			}


			/// hash_set
			///
			/// initializer_list-based constructor. 
			/// Allows for initializing with brace values (e.g. hash_set<int> hs = { 3, 4, 5, }; )
			///     
			hash_set(std::initializer_list<value_type> ilist, size_type nBucketCount = 0, const Hash& hashFunction = Hash(),
				const Predicate& predicate = Predicate(), const allocator_type& allocator = allocator_type())
				: base_type(ilist.begin(), ilist.end(), nBucketCount, hashFunction, mod_range_hashing(), predicate, rsl::use_self<Value>(), allocator)
			{
				// Empty
			}


			/// hash_set
			///
			/// An input bucket count of <= 1 causes the bucket count to be equal to the number of 
			/// elements in the input range.
			///
			template <typename FowardIterator>
			hash_set(FowardIterator first, FowardIterator last, size_type nBucketCount = 0, const Hash& hashFunction = Hash(),
				const Predicate& predicate = Predicate(), const allocator_type& allocator = allocator_type())
				: base_type(first, last, nBucketCount, hashFunction, mod_range_hashing(), predicate, rsl::use_self<Value>(), allocator)
			{
				// Empty
			}


			this_type& operator=(const this_type& x)
			{
				return static_cast<this_type&>(base_type::operator=(x));
			}


			this_type& operator=(std::initializer_list<value_type> ilist)
			{
				return static_cast<this_type&>(base_type::operator=(ilist));
			}


			this_type& operator=(this_type&& x)
			{
				return static_cast<this_type&>(base_type::operator=(rsl::move(x)));
			}

		}; // hash_set

		/// hash_set erase_if
		///
		/// https://en.cppreference.com/w/cpp/container/unordered_set/erase_if
		template <typename Value, typename Hash, typename Predicate, typename Alloc, typename UserPredicate>
		void erase_if(rsl::hash_set<Value, Hash, Predicate, Alloc>& c, UserPredicate predicate)
		{
			// Erases all elements that satisfy the predicate pred from the container.
			for (auto i = c.begin(), last = c.end(); i != last;)
			{
				if (predicate(*i))
				{
					i = c.erase(i);
				}
				else
				{
					++i;
				}
			}
		}


		/// hash_multiset
		///
		/// Implements a hash_multiset, which is the same thing as a hash_set 
		/// except that contained elements need not be unique. See the documentation 
		/// for hash_set for details.
		///
		template <typename Value, typename Hash = rsl::hash<Value>, typename Predicate = rsl::equal_to<Value>,
			typename Alloc = rsl::allocator>
			class hash_multiset : public hashtable<Value, Value, Alloc, rsl::use_self<Value>, Predicate, Hash, mod_range_hashing, prime_rehash_policy, false, false>
		{
		public:
			using base_type = hashtable<Value, Value, Alloc, rsl::use_self<Value>, Predicate, Hash, mod_range_hashing, prime_rehash_policy, false, false>;
			using this_type = hash_multiset<Value, Hash, Predicate, Alloc>;
			using size_type = typename base_type::size_type;
			using value_type = typename base_type::value_type;
			using allocator_type = typename base_type::allocator_type;
			using node_type = typename base_type::node_type;

		public:
			/// hash_multiset
			///
			/// Default constructor.
			/// 
			explicit hash_multiset(const allocator_type& allocator = allocator_type())
				: base_type(0, Hash(), mod_range_hashing(), Predicate(), rsl::use_self<Value>(), allocator)
			{
				// Empty
			}


			/// hash_multiset
			///
			/// Constructor which creates an empty container, but start with nBucketCount buckets.
			/// We default to a small nBucketCount value, though the user really should manually 
			/// specify an appropriate value in order to prevent memory from being reallocated.
			///
			explicit hash_multiset(size_type nBucketCount, const Hash& hashFunction = Hash(),
				const Predicate& predicate = Predicate(), const allocator_type& allocator = allocator_type())
				: base_type(nBucketCount, hashFunction, mod_range_hashing(), predicate, rsl::use_self<Value>(), allocator)
			{
				// Empty
			}


			hash_multiset(const this_type& x)
				: base_type(x)
			{
			}


			hash_multiset(this_type&& x)
				: base_type(rsl::move(x))
			{
			}


			hash_multiset(this_type&& x, const allocator_type& allocator)
				: base_type(rsl::move(x), allocator)
			{
			}


			/// hash_multiset
			///
			/// initializer_list-based constructor. 
			/// Allows for initializing with brace values (e.g. hash_set<int> hs = { 3, 3, 4, }; )
			///     
			hash_multiset(std::initializer_list<value_type> ilist, size_type nBucketCount = 0, const Hash& hashFunction = Hash(),
				const Predicate& predicate = Predicate(), const allocator_type& allocator = allocator_type())
				: base_type(ilist.begin(), ilist.end(), nBucketCount, hashFunction, mod_range_hashing(), predicate, rsl::use_self<Value>(), allocator)
			{
				// Empty
			}


			/// hash_multiset
			///
			/// An input bucket count of <= 1 causes the bucket count to be equal to the number of 
			/// elements in the input range.
			///
			template <typename FowardIterator>
			hash_multiset(FowardIterator first, FowardIterator last, size_type nBucketCount = 0, const Hash& hashFunction = Hash(),
				const Predicate& predicate = Predicate(), const allocator_type& allocator = allocator_type())
				: base_type(first, last, nBucketCount, hashFunction, mod_range_hashing(), predicate, rsl::use_self<Value>(), allocator)
			{
				// Empty
			}


			this_type& operator=(const this_type& x)
			{
				return static_cast<this_type&>(base_type::operator=(x));
			}


			this_type& operator=(std::initializer_list<value_type> ilist)
			{
				return static_cast<this_type&>(base_type::operator=(ilist));
			}


			this_type& operator=(this_type&& x)
			{
				return static_cast<this_type&>(base_type::operator=(rsl::move(x)));
			}

		}; // hash_multiset

		/// hash_multiset erase_if
		///
		/// https://en.cppreference.com/w/cpp/container/unordered_multiset/erase_if
		template <typename Value, typename Hash, typename Predicate, typename Alloc, typename UserPredicate>
		void erase_if(rsl::hash_multiset<Value, Hash, Predicate, Alloc>& c, UserPredicate predicate)
		{
			// Erases all elements that satisfy the predicate pred from the container.
			for (auto i = c.begin(), last = c.end(); i != last;)
			{
				if (predicate(*i))
				{
					i = c.erase(i);
				}
				else
				{
					++i;
				}
			}
		}



		///////////////////////////////////////////////////////////////////////
		// global operators
		///////////////////////////////////////////////////////////////////////

		template <typename Value, typename Hash, typename Predicate, typename Alloc>
		inline bool operator==(const hash_set<Value, Hash, Predicate, Alloc>& a,
			const hash_set<Value, Hash, Predicate, Alloc>& b)
		{
			using const_iterator = typename hash_set<Value, Hash, Predicate, Alloc>::const_iterator ;

			// We implement branching with the assumption that the return value is usually false.
			if (a.size() != b.size())
				return false;

			// For set (with its unique keys), we need only test that each element in a can be found in b,
			// as there can be only one such pairing per element. multiset needs to do a something more elaborate.
			for (const_iterator ai = a.begin(), aiEnd = a.end(), biEnd = b.end(); ai != aiEnd; ++ai)
			{
				const_iterator bi = b.find(*ai);

				if ((bi == biEnd) || !(*ai == *bi)) // We have to compare values in addition to making sure the lookups succeeded. This is because the lookup is done via the user-supplised Predicate
					return false;                  // which isn't strictly required to be identical to the Value operator==, though 99% of the time it will be so.  
			}

			return true;
		}

		template <typename Value, typename Hash, typename Predicate, typename Alloc>
		inline bool operator!=(const hash_set<Value, Hash, Predicate, Alloc>& a,
			const hash_set<Value, Hash, Predicate, Alloc>& b)
		{
			return !(a == b);
		}


		template <typename Value, typename Hash, typename Predicate, typename Alloc>
		inline bool operator==(const hash_multiset<Value, Hash, Predicate, Alloc>& a,
			const hash_multiset<Value, Hash, Predicate, Alloc>& b)
		{
			using const_iterator = typename hash_multiset<Value, Hash, Predicate, Alloc>::const_iterator;
			typedef typename rsl::iterator_traits<const_iterator>::difference_type difference_type;

			// We implement branching with the assumption that the return value is usually false.
			if (a.size() != b.size())
				return false;

			// We can't simply search for each element of a in b, as it may be that the bucket for 
			// two elements in a has those same two elements in b but in different order (which should 
			// still result in equality). Also it's possible that one bucket in a has two elements which 
			// both match a solitary element in the equivalent bucket in b (which shouldn't result in equality).
			rsl::pair<const_iterator, const_iterator> aRange;
			rsl::pair<const_iterator, const_iterator> bRange;

			for (const_iterator ai = a.begin(), aiEnd = a.end(); ai != aiEnd; ai = aRange.second) // For each element in a...
			{
				aRange = a.equal_range(*ai); // Get the range of elements in a that are equal to ai.
				bRange = b.equal_range(*ai); // Get the range of elements in b that are equal to ai.

				// We need to verify that aRange == bRange. First make sure the range sizes are equivalent...
				const difference_type aDistance = rsl::distance(aRange.first, aRange.second);
				const difference_type bDistance = rsl::distance(bRange.first, bRange.second);

				if (aDistance != bDistance)
					return false;

				// At this point, aDistance > 0 and aDistance == bDistance.
				// Implement a fast pathway for the case that there's just a single element.
				if (aDistance == 1)
				{
					if (!(*aRange.first == *bRange.first))   // We have to compare values in addition to making sure the distance (element count) was equal. This is because the lookup is done via the user-supplised Predicate
						return false;                       // which isn't strictly required to be identical to the Value operator==, though 99% of the time it will be so. Ditto for the is_permutation usage below.
				}
				else
				{
					// Check to see if these aRange and bRange are any permutation of each other. 
					// This check gets slower as there are more elements in the range.
					if (!rsl::is_permutation(aRange.first, aRange.second, bRange.first))
						return false;
				}
			}

			return true;
		}

		template <typename Value, typename Hash, typename Predicate, typename Alloc>
		inline bool operator!=(const hash_multiset<Value, Hash, Predicate, Alloc>& a,
			const hash_multiset<Value, Hash, Predicate, Alloc>& b)
		{
			return !(a == b);
		}

  }
}
