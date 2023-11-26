// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_bitcast.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/bit.h"
#include "rex_std/type_traits.h"

namespace rsl::test
{
	inline namespace v1
	{
    struct A {};
    enum       E1 : unsigned char { rEd };
    enum class E2 : unsigned char { red };

		template <typename T>
		bool test_bit_ceil()
		{
      CHECK(rsl::is_same_v<decltype(rsl::bit_ceil(T())), T>);

      CHECK(rsl::bit_ceil(T(0)) == T(1));
      CHECK(rsl::bit_ceil(T(1)) == T(1));
      CHECK(rsl::bit_ceil(T(2)) == T(2));
      CHECK(rsl::bit_ceil(T(3)) == T(4));
      CHECK(rsl::bit_ceil(T(4)) == T(4));
      CHECK(rsl::bit_ceil(T(5)) == T(8));
      CHECK(rsl::bit_ceil(T(6)) == T(8));
      CHECK(rsl::bit_ceil(T(7)) == T(8));
      CHECK(rsl::bit_ceil(T(8)) == T(8));
      CHECK(rsl::bit_ceil(T(9)) == T(16));
      CHECK(rsl::bit_ceil(T(60)) == T(64));
      CHECK(rsl::bit_ceil(T(61)) == T(64));
      CHECK(rsl::bit_ceil(T(62)) == T(64));
      CHECK(rsl::bit_ceil(T(63)) == T(64));
      CHECK(rsl::bit_ceil(T(64)) == T(64));
      CHECK(rsl::bit_ceil(T(65)) == T(128));
      CHECK(rsl::bit_ceil(T(66)) == T(128));
      CHECK(rsl::bit_ceil(T(67)) == T(128));
      CHECK(rsl::bit_ceil(T(68)) == T(128));
      CHECK(rsl::bit_ceil(T(69)) == T(128));

      return true;
		}

    template <typename T>
    bool test_bit_floor()
    {
      CHECK(rsl::is_same_v<decltype(rsl::bit_floor(T())), T>);
      T max = rsl::numeric_limits<T>::max();

      CHECK(rsl::bit_floor(T(0)) == T(0));
      CHECK(rsl::bit_floor(T(1)) == T(1));
      CHECK(rsl::bit_floor(T(2)) == T(2));
      CHECK(rsl::bit_floor(T(3)) == T(2));
      CHECK(rsl::bit_floor(T(4)) == T(4));
      CHECK(rsl::bit_floor(T(5)) == T(4));
      CHECK(rsl::bit_floor(T(6)) == T(4));
      CHECK(rsl::bit_floor(T(7)) == T(4));
      CHECK(rsl::bit_floor(T(8)) == T(8));
      CHECK(rsl::bit_floor(T(9)) == T(8));
      CHECK(rsl::bit_floor(T(125)) == T(64));
      CHECK(rsl::bit_floor(T(126)) == T(64));
      CHECK(rsl::bit_floor(T(127)) == T(64));
      CHECK(rsl::bit_floor(T(128)) == T(128));
      CHECK(rsl::bit_floor(T(129)) == T(128));
      CHECK(rsl::bit_floor(max) == T(max - (max >> 1)));

      return true;
    }

    template <typename T>
    bool test_bit_width()
    {
      CHECK(rsl::is_same_v<decltype(rsl::bit_width(T())), int32>);
      T max = rsl::numeric_limits<T>::max();

      CHECK(rsl::bit_width(T(0)) == 0);
      CHECK(rsl::bit_width(T(1)) == 1);
      CHECK(rsl::bit_width(T(2)) == 2);
      CHECK(rsl::bit_width(T(3)) == 2);
      CHECK(rsl::bit_width(T(4)) == 3);
      CHECK(rsl::bit_width(T(5)) == 3);
      CHECK(rsl::bit_width(T(6)) == 3);
      CHECK(rsl::bit_width(T(7)) == 3);
      CHECK(rsl::bit_width(T(8)) == 4);
      CHECK(rsl::bit_width(T(9)) == 4);
      CHECK(rsl::bit_width(T(125)) == 7);
      CHECK(rsl::bit_width(T(126)) == 7);
      CHECK(rsl::bit_width(T(127)) == 7);
      CHECK(rsl::bit_width(T(128)) == 8);
      CHECK(rsl::bit_width(T(129)) == 8);
      CHECK(rsl::bit_width(T(130)) == 8);
      CHECK(rsl::bit_width(T(max - 1)) == rsl::numeric_limits<T>::digits);
      CHECK(rsl::bit_width(max) == rsl::numeric_limits<T>::digits);
      
      return true;
    }

    template <typename T>
    bool test_has_single_bit()
    {
      CHECK(rsl::is_same_v<decltype(rsl::has_single_bit(T())), bool>);
      T max = rsl::numeric_limits<T>::max();

      CHECK(!rsl::has_single_bit(T(0)));
      CHECK( rsl::has_single_bit(T(1)));
      CHECK( rsl::has_single_bit(T(2)));
      CHECK(!rsl::has_single_bit(T(3)));
      CHECK( rsl::has_single_bit(T(4)));
      CHECK(!rsl::has_single_bit(T(5)));
      CHECK(!rsl::has_single_bit(T(6)));
      CHECK(!rsl::has_single_bit(T(7)));
      CHECK( rsl::has_single_bit(T(8)));
      CHECK(!rsl::has_single_bit(T(9)));
      CHECK(!rsl::has_single_bit(T(127)));
      CHECK( rsl::has_single_bit(T(128)));
      CHECK(!rsl::has_single_bit(T(129)));
      CHECK(!rsl::has_single_bit(max));
     
      return true;
    }

    template <typename T>
    bool test_countl_zero()
    {
      CHECK(rsl::is_same_v<decltype(rsl::countl_zero(T())), int>);
      
      T max = rsl::numeric_limits<T>::max();
      int dig = rsl::numeric_limits<T>::digits;

      CHECK(rsl::countl_zero(T(0)) == dig);
      CHECK(rsl::countl_zero(T(1)) == dig - 1);
      CHECK(rsl::countl_zero(T(2)) == dig - 2);
      CHECK(rsl::countl_zero(T(3)) == dig - 2);
      CHECK(rsl::countl_zero(T(4)) == dig - 3);
      CHECK(rsl::countl_zero(T(5)) == dig - 3);
      CHECK(rsl::countl_zero(T(6)) == dig - 3);
      CHECK(rsl::countl_zero(T(7)) == dig - 3);
      CHECK(rsl::countl_zero(T(8)) == dig - 4);
      CHECK(rsl::countl_zero(T(9)) == dig - 4);
      CHECK(rsl::countl_zero(T(127)) == dig - 7);
      CHECK(rsl::countl_zero(T(128)) == dig - 8);
      CHECK(rsl::countl_zero(max) == 0);
     
      return true;
    }

    template <typename T>
    bool test_countl_one()
    {
      CHECK(rsl::is_same_v<decltype(rsl::countl_one(T())), int>);
      
      T max = rsl::numeric_limits<T>::max();

      CHECK(rsl::countl_one(T(0)) == 0);
      CHECK(rsl::countl_one(T(1)) == 0);
      CHECK(rsl::countl_one(T(10)) == 0);
      CHECK(rsl::countl_one(T(100)) == 0);
      CHECK(rsl::countl_one(max) == rsl::numeric_limits<T>::digits);
      CHECK(rsl::countl_one(T(max - 1)) == rsl::numeric_limits<T>::digits - 1);
      CHECK(rsl::countl_one(T(max - 2)) == rsl::numeric_limits<T>::digits - 2);
      CHECK(rsl::countl_one(T(max - 3)) == rsl::numeric_limits<T>::digits - 2);
      CHECK(rsl::countl_one(T(max - 4)) == rsl::numeric_limits<T>::digits - 3);
      CHECK(rsl::countl_one(T(max - 5)) == rsl::numeric_limits<T>::digits - 3);
      CHECK(rsl::countl_one(T(max - 6)) == rsl::numeric_limits<T>::digits - 3);
      CHECK(rsl::countl_one(T(max - 7)) == rsl::numeric_limits<T>::digits - 3);
      CHECK(rsl::countl_one(T(max - 8)) == rsl::numeric_limits<T>::digits - 4);
      CHECK(rsl::countl_one(T(max - 9)) == rsl::numeric_limits<T>::digits - 4);
      CHECK(rsl::countl_one(T(max - 126)) == rsl::numeric_limits<T>::digits - 7);
      CHECK(rsl::countl_one(T(max - 127)) == rsl::numeric_limits<T>::digits - 7);
      CHECK(rsl::countl_one(T(max - 128)) == rsl::numeric_limits<T>::digits - 8);

      return true;
    }

    template <typename T>
    bool test_countr_zero()
    {
      CHECK(rsl::is_same_v<decltype(rsl::countr_zero(T())), int>);
      
      T max = rsl::numeric_limits<T>::max();

      CHECK(rsl::countr_zero(T(0)) == rsl::numeric_limits<T>::digits);
      CHECK(rsl::countr_zero(T(1)) == 0);
      CHECK(rsl::countr_zero(T(2)) == 1);
      CHECK(rsl::countr_zero(T(3)) == 0);
      CHECK(rsl::countr_zero(T(4)) == 2);
      CHECK(rsl::countr_zero(T(5)) == 0);
      CHECK(rsl::countr_zero(T(6)) == 1);
      CHECK(rsl::countr_zero(T(7)) == 0);
      CHECK(rsl::countr_zero(T(8)) == 3);
      CHECK(rsl::countr_zero(T(9)) == 0);
      CHECK(rsl::countr_zero(T(126)) == 1);
      CHECK(rsl::countr_zero(T(127)) == 0);
      CHECK(rsl::countr_zero(T(128)) == 7);
      CHECK(rsl::countr_zero(T(129)) == 0);
      CHECK(rsl::countr_zero(T(130)) == 1);
      CHECK(rsl::countr_zero(max) == 0);

      return true;
    }

    template <typename T>
    bool test_countr_one()
    {
      CHECK(rsl::is_same_v<decltype(rsl::countr_one(T())), int>);
      
      T max = rsl::numeric_limits<T>::max();

      CHECK(rsl::countr_one(T(0)) == 0);
      CHECK(rsl::countr_one(T(1)) == 1);
      CHECK(rsl::countr_one(T(2)) == 0);
      CHECK(rsl::countr_one(T(3)) == 2);
      CHECK(rsl::countr_one(T(4)) == 0);
      CHECK(rsl::countr_one(T(5)) == 1);
      CHECK(rsl::countr_one(T(6)) == 0);
      CHECK(rsl::countr_one(T(7)) == 3);
      CHECK(rsl::countr_one(T(8)) == 0);
      CHECK(rsl::countr_one(T(9)) == 1);
      CHECK(rsl::countr_one(T(126)) == 0);
      CHECK(rsl::countr_one(T(127)) == 7);
      CHECK(rsl::countr_one(T(128)) == 0);
      CHECK(rsl::countr_one(T(max - 1)) == 0);
      CHECK(rsl::countr_one(max) == rsl::numeric_limits<T>::digits);

      return true;
    }

    template <typename T>
    bool test_popcount()
    {
      CHECK(rsl::is_same_v<decltype(rsl::popcount(T())), int>);
      
      T max = rsl::numeric_limits<T>::max();

      CHECK(rsl::popcount(T(0)) == 0);
      CHECK(rsl::popcount(T(1)) == 1);
      CHECK(rsl::popcount(T(2)) == 1);
      CHECK(rsl::popcount(T(3)) == 2);
      CHECK(rsl::popcount(T(4)) == 1);
      CHECK(rsl::popcount(T(5)) == 2);
      CHECK(rsl::popcount(T(6)) == 2);
      CHECK(rsl::popcount(T(7)) == 3);
      CHECK(rsl::popcount(T(8)) == 1);
      CHECK(rsl::popcount(T(9)) == 2);
      CHECK(rsl::popcount(T(121)) == 5);
      CHECK(rsl::popcount(T(127)) == 7);
      CHECK(rsl::popcount(T(128)) == 1);
      CHECK(rsl::popcount(T(130)) == 2);
      CHECK(rsl::popcount(T(max >> 1)) == rsl::numeric_limits<T>::digits - 1);
      CHECK(rsl::popcount(T(max - 1)) == rsl::numeric_limits<T>::digits - 1);
      CHECK(rsl::popcount(max) == rsl::numeric_limits<T>::digits);

      return true;
    }

    template <typename T>
    bool test_rotl()
    {
      CHECK(rsl::is_same_v<decltype(rsl::rotl(T(), 0)), T>);
      
      T max = rsl::numeric_limits<T>::max();

      CHECK(rsl::rotl(T(max - 1), 0) == T(max - 1));
      CHECK(rsl::rotl(T(max - 1), 1) == T(max - 2));
      CHECK(rsl::rotl(T(max - 1), 2) == T(max - 4));
      CHECK(rsl::rotl(T(max - 1), 3) == T(max - 8));
      CHECK(rsl::rotl(T(max - 1), 4) == T(max - 16));
      CHECK(rsl::rotl(T(max - 1), 5) == T(max - 32));
      CHECK(rsl::rotl(T(max - 1), 6) == T(max - 64));
      CHECK(rsl::rotl(T(max - 1), 7) == T(max - 128));

      CHECK(rsl::rotl(T(1), 0) == T(1));
      CHECK(rsl::rotl(T(1), 1) == T(2));
      CHECK(rsl::rotl(T(1), 2) == T(4));
      CHECK(rsl::rotl(T(1), 3) == T(8));
      CHECK(rsl::rotl(T(1), 4) == T(16));
      CHECK(rsl::rotl(T(1), 5) == T(32));
      CHECK(rsl::rotl(T(1), 6) == T(64));
      CHECK(rsl::rotl(T(1), 7) == T(128));

      return true;
    }

    template <typename T>
    bool test_rotr()
    {
      CHECK(rsl::is_same_v<decltype(rsl::rotr(T(), 0)), T>);
      
      T max = rsl::numeric_limits<T>::max();
      T highbit = rsl::rotr(T(1), 1);

      CHECK(rsl::rotr(T(max - 1), 0) == T(max - 1));
      CHECK(rsl::rotr(T(max - 1), 1) == T(max - highbit));
      CHECK(rsl::rotr(T(max - 1), 2) == T(max - (highbit >> 1)));
      CHECK(rsl::rotr(T(max - 1), 3) == T(max - (highbit >> 2)));
      CHECK(rsl::rotr(T(max - 1), 4) == T(max - (highbit >> 3)));
      CHECK(rsl::rotr(T(max - 1), 5) == T(max - (highbit >> 4)));
      CHECK(rsl::rotr(T(max - 1), 6) == T(max - (highbit >> 5)));
      CHECK(rsl::rotr(T(max - 1), 7) == T(max - (highbit >> 6)));

      CHECK(rsl::rotr(T(128), 0) == T(128));
      CHECK(rsl::rotr(T(128), 1) == T(64));
      CHECK(rsl::rotr(T(128), 2) == T(32));
      CHECK(rsl::rotr(T(128), 3) == T(16));
      CHECK(rsl::rotr(T(128), 4) == T(8));
      CHECK(rsl::rotr(T(128), 5) == T(4));
      CHECK(rsl::rotr(T(128), 6) == T(2));
      CHECK(rsl::rotr(T(128), 7) == T(1));

      return true;
    }
	}
}

TEST_CASE("Basic Bit Cast")
{
  uint32_t int32Value = 0x12345678;
  float floatValue = rsl::bit_cast<float>(int32Value);
  CHECK(memcmp(&int32Value, &floatValue, sizeof(float)) == 0);
}
TEST_CASE("User Type Bit Cast")
{
	struct IntFloatStruct
	{
		uint32_t i = 0x87654321;
		float f = 10.f;
	};
	struct CharIntStruct
	{
		char c1;
		char c2;
		char c3;
		char c4;
		uint32_t i;
	};

	IntFloatStruct ifStruct;
	CharIntStruct ciStruct = rsl::bit_cast<CharIntStruct>(ifStruct);
	CHECK(memcmp(&ifStruct, &ciStruct, sizeof(IntFloatStruct)) == 0);
}
TEST_CASE("Bit Ceil")
{
  auto lambda = [](auto x) -> decltype(rsl::bit_ceil(x)) {};
  using L = decltype(lambda);

  rsl::test::test_bit_ceil<unsigned char>();
  rsl::test::test_bit_ceil<unsigned short>();
  rsl::test::test_bit_ceil<unsigned int>();
  rsl::test::test_bit_ceil<unsigned long>();
  rsl::test::test_bit_ceil<unsigned long long>();
  rsl::test::test_bit_ceil<uint8_t>();
  rsl::test::test_bit_ceil<uint16_t>();
  rsl::test::test_bit_ceil<uint32_t>();
  rsl::test::test_bit_ceil<uint64_t>();
  rsl::test::test_bit_ceil<uintmax_t>();
  rsl::test::test_bit_ceil<uintptr_t>();
  rsl::test::test_bit_ceil<size_t>();
}
TEST_CASE("Bit Floor")
{
  rsl::test::test_bit_floor<unsigned char>();
  rsl::test::test_bit_floor<unsigned short>();
  rsl::test::test_bit_floor<unsigned int>();
  rsl::test::test_bit_floor<unsigned long>();
  rsl::test::test_bit_floor<unsigned long long>();

  rsl::test::test_bit_floor<uint8_t>();
  rsl::test::test_bit_floor<uint16_t>();
  rsl::test::test_bit_floor<uint32_t>();
  rsl::test::test_bit_floor<uint64_t>();
  rsl::test::test_bit_floor<uintmax_t>();
  rsl::test::test_bit_floor<uintptr_t>();
  rsl::test::test_bit_floor<size_t>();
}
TEST_CASE("Bit Width")
{
  rsl::test::test_bit_width<unsigned char>();
  rsl::test::test_bit_width<unsigned short>();
  rsl::test::test_bit_width<unsigned int>();
  rsl::test::test_bit_width<unsigned long>();
  rsl::test::test_bit_width<unsigned long long>();

  rsl::test::test_bit_width<uint8_t>();
  rsl::test::test_bit_width<uint16_t>();
  rsl::test::test_bit_width<uint32_t>();
  rsl::test::test_bit_width<uint64_t>();
  rsl::test::test_bit_width<uintmax_t>();
  rsl::test::test_bit_width<uintptr_t>();
  rsl::test::test_bit_width<size_t>();
}
TEST_CASE("Has Single Bit")
{
  rsl::test::test_has_single_bit<unsigned char>();
  rsl::test::test_has_single_bit<unsigned short>();
  rsl::test::test_has_single_bit<unsigned int>();
  rsl::test::test_has_single_bit<unsigned long>();
  rsl::test::test_has_single_bit<unsigned long long>();
  
  rsl::test::test_has_single_bit<uint8_t>();
  rsl::test::test_has_single_bit<uint16_t>();
  rsl::test::test_has_single_bit<uint32_t>();
  rsl::test::test_has_single_bit<uint64_t>();
  rsl::test::test_has_single_bit<uintmax_t>();
  rsl::test::test_has_single_bit<uintptr_t>();
  rsl::test::test_has_single_bit<size_t>();
}
TEST_CASE("Countl Zero")
{
  rsl::test::test_countl_zero<unsigned char>();
  rsl::test::test_countl_zero<unsigned short>();
  rsl::test::test_countl_zero<unsigned int>();
  rsl::test::test_countl_zero<unsigned long>();
  rsl::test::test_countl_zero<unsigned long long>();

  rsl::test::test_countl_zero<uint8_t>();
  rsl::test::test_countl_zero<uint16_t>();
  rsl::test::test_countl_zero<uint32_t>();
  rsl::test::test_countl_zero<uint64_t>();
  rsl::test::test_countl_zero<uintmax_t>();
  rsl::test::test_countl_zero<uintptr_t>();
  rsl::test::test_countl_zero<size_t>();
}
TEST_CASE("Countl One")
{
  rsl::test::test_countl_one<unsigned char>();
  rsl::test::test_countl_one<unsigned short>();
  rsl::test::test_countl_one<unsigned int>();
  rsl::test::test_countl_one<unsigned long>();
  rsl::test::test_countl_one<unsigned long long>();

  rsl::test::test_countl_one<uint8_t>();
  rsl::test::test_countl_one<uint16_t>();
  rsl::test::test_countl_one<uint32_t>();
  rsl::test::test_countl_one<uint64_t>();
  rsl::test::test_countl_one<uintmax_t>();
  rsl::test::test_countl_one<uintptr_t>();
  rsl::test::test_countl_one<size_t>();
}
TEST_CASE("Countr Zero")
{
  rsl::test::test_countr_zero<unsigned char>();
  rsl::test::test_countr_zero<unsigned short>();
  rsl::test::test_countr_zero<unsigned int>();
  rsl::test::test_countr_zero<unsigned long>();
  rsl::test::test_countr_zero<unsigned long long>();

  rsl::test::test_countr_zero<uint8_t>();
  rsl::test::test_countr_zero<uint16_t>();
  rsl::test::test_countr_zero<uint32_t>();
  rsl::test::test_countr_zero<uint64_t>();
  rsl::test::test_countr_zero<uintmax_t>();
  rsl::test::test_countr_zero<uintptr_t>();
  rsl::test::test_countr_zero<size_t>();
}
TEST_CASE("Countr One")
{
  rsl::test::test_countr_one<unsigned char>();
  rsl::test::test_countr_one<unsigned short>();
  rsl::test::test_countr_one<unsigned int>();
  rsl::test::test_countr_one<unsigned long>();
  rsl::test::test_countr_one<unsigned long long>();

  rsl::test::test_countr_one<uint8_t>();
  rsl::test::test_countr_one<uint16_t>();
  rsl::test::test_countr_one<uint32_t>();
  rsl::test::test_countr_one<uint64_t>();
  rsl::test::test_countr_one<uintmax_t>();
  rsl::test::test_countr_one<uintptr_t>();
  rsl::test::test_countr_one<size_t>();
}
TEST_CASE("Popcount")
{
  rsl::test::test_popcount<unsigned char>();
  rsl::test::test_popcount<unsigned short>();
  rsl::test::test_popcount<unsigned int>();
  rsl::test::test_popcount<unsigned long>();
  rsl::test::test_popcount<unsigned long long>();

  rsl::test::test_popcount<uint8_t>();
  rsl::test::test_popcount<uint16_t>();
  rsl::test::test_popcount<uint32_t>();
  rsl::test::test_popcount<uint64_t>();
  rsl::test::test_popcount<uintmax_t>();
  rsl::test::test_popcount<uintptr_t>();
  rsl::test::test_popcount<size_t>();
}
TEST_CASE("rotl")
{
  rsl::test::test_rotl<unsigned char>();
  rsl::test::test_rotl<unsigned short>();
  rsl::test::test_rotl<unsigned int>();
  rsl::test::test_rotl<unsigned long>();
  rsl::test::test_rotl<unsigned long long>();

  rsl::test::test_rotl<uint8_t>();
  rsl::test::test_rotl<uint16_t>();
  rsl::test::test_rotl<uint32_t>();
  rsl::test::test_rotl<uint64_t>();
  rsl::test::test_rotl<uintmax_t>();
  rsl::test::test_rotl<uintptr_t>();
  rsl::test::test_rotl<size_t>();
}
TEST_CASE("rotr")
{
  rsl::test::test_rotr<unsigned char>();
  rsl::test::test_rotr<unsigned short>();
  rsl::test::test_rotr<unsigned int>();
  rsl::test::test_rotr<unsigned long>();
  rsl::test::test_rotr<unsigned long long>();

  rsl::test::test_rotr<uint8_t>();
  rsl::test::test_rotr<uint16_t>();
  rsl::test::test_rotr<uint32_t>();
  rsl::test::test_rotr<uint64_t>();
  rsl::test::test_rotr<uintmax_t>();
  rsl::test::test_rotr<uintptr_t>();
  rsl::test::test_rotr<size_t>();
}