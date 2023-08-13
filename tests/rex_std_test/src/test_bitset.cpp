// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: test_rsl::bitset.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"

#include "rex_std/bitset.h"

TEST_CASE("Test BitSet")
{
	int nErrorCount = 0;

	{
// rsl::bitset<8> tests
		rsl::bitset<8> b8(0x10101010);
		CHECK(b8.count() == 1);
		CHECK(b8.to_uint32() == 0x00000010);
		CHECK(b8.to_uint64() == 0x00000010);

		b8.flip();
		CHECK(b8.count() == 7);
		CHECK(b8.to_uint32() == 0x000000ef);
		CHECK(b8.to_uint64() == 0x000000ef);

		b8 <<= 1;
		CHECK(b8.count() == 6);
		CHECK(b8.to_uint32() == 0x000000de);
		CHECK(b8.to_uint64() == 0x000000de);

		b8.reset();
		b8.flip();
		b8 >>= 33;
		CHECK(b8.count() == 0);

		b8.reset();
		b8.flip();
		b8 >>= 65;
		CHECK(b8.count() == 0);



		// rsl::bitset<16> tests
		rsl::bitset<16> b16(0x10101010);
		CHECK(b16.count() == 2);
		CHECK(b16.to_uint32() == 0x00001010);
		CHECK(b16.to_uint64() == 0x00001010);

		b16.flip();
		CHECK(b16.count() == 14);
		CHECK(b16.to_uint32() == 0x0000efef);
		CHECK(b16.to_uint64() == 0x0000efef);

		b16 <<= 1;
		CHECK(b16.count() == 13);
		CHECK(b16.to_uint32() == 0x0000dfde);
		CHECK(b16.to_uint64() == 0x0000dfde);

		b16.reset();
		b16.flip();
		b16 >>= 33;
		CHECK(b16.count() == 0);

		b16.reset();
		b16.flip();
		b16 >>= 65;
		CHECK(b16.count() == 0);




		// rsl::bitset<32> tests
		rsl::bitset<32> b32(0x10101010);
		CHECK(b32.count() == 4);
		CHECK(b32.to_uint32() == 0x10101010);
		CHECK(b32.to_uint64() == 0x10101010);

		b32.flip();
		CHECK(b32.count() == 28);
		CHECK(b32.to_uint32() == 0xefefefef);
		CHECK(b32.to_uint64() == 0xefefefef);

		b32 <<= 1;
		CHECK(b32.count() == 27);
		CHECK(b32.to_uint32() == 0xdfdfdfde);
		CHECK(b32.to_uint64() == 0xdfdfdfde);

		b32.reset();
		b32.flip();
		b32 >>= 33;
		CHECK(b32.count() == 0);

		b32.reset();
		b32.flip();
		b32 >>= 65;
		CHECK(b32.count() == 0);




		// rsl::bitset<64> tests
		rsl::bitset<64> b64(0x10101010);                                 // b64 => 00000000 00000000 00000000 00000000 00010000 00010000 00010000 00010000
		CHECK(b64.count() == 4);
		CHECK(b64.to_uint32() == 0x10101010);
		CHECK(b64.to_uint64() == 0x10101010);

		b64.flip();                                                 // b64 => 11111111 11111111 11111111 11111111 11101111 11101111 11101111 11101111
		CHECK(b64.count() == 60);
		CHECK(b64.to_uint32() == 0xefefefef);


		b64 <<= 1;                                                  // b64 => 11111111 11111111 11111111 11111111 11011111 11011111 11011111 11011110
		CHECK(b64.count() == 59);
		if (sizeof(unsigned long) + nErrorCount - nErrorCount == 4)
		{
			CHECK(b64.to_uint32() == 0xdfdfdfde);
		}

		b64.reset();                                                // b64 => 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
		CHECK(b64.count() == 0);
		CHECK(b64.to_uint32() == 0);

		b64 <<= 1;                                                  // b64 => 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
		CHECK(b64.count() == 0);
		CHECK(b64.to_uint32() == 0);

		b64.flip();                                                 // b64 => 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111
		CHECK(b64.count() == 64);
    CHECK(b64.to_uint32() == 0xffffffff);

		b64 <<= 1;                                                  // b64 => 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111110
		CHECK(b64.count() == 63);
    CHECK(b64.to_uint32() == 0xfffffffe);

		b64.reset();
		b64.flip();
		b64 >>= 33;
		CHECK(b64.count() == 31);

		b64.reset();
		b64.flip();
		b64 >>= 65;
		CHECK(b64.count() == 0);

	}


	{
		rsl::bitset<1> b1;
		rsl::bitset<1> b1A(1);

		CHECK(b1.size() == 1);
		CHECK(b1.any() == false);
		CHECK(b1.all() == false);
		CHECK(b1.none() == true);
		CHECK(b1.to_uint32() == 0);
		CHECK(b1A.any() == true);
		CHECK(b1A.all() == true);
		CHECK(b1A.none() == false);
		CHECK(b1A.to_uint32() == 1);
		CHECK(b1A.to_uint64() == 1);


		rsl::bitset<33> b33;
		rsl::bitset<33> b33A(1);

		CHECK(b33.size() == 33);
		CHECK(b33.any() == false);
		CHECK(b33.all() == false);
		CHECK(b33.none() == true);
		CHECK(b33.to_uint32() == 0);
		CHECK(b33A.any() == true);
		CHECK(b33A.all() == false);
		CHECK(b33A.none() == false);
		CHECK(b33A.to_uint32() == 1);


		rsl::bitset<65> b65;
		rsl::bitset<65> b65A(1);

		CHECK(b65.size() == 65);
		CHECK(b65.any() == false);
		CHECK(b65.all() == false);
		CHECK(b65.none() == true);
		CHECK(b65.to_uint32() == 0);
		CHECK(b65A.any() == true);
		CHECK(b65A.all() == false);
		CHECK(b65A.none() == false);
		CHECK(b65A.to_uint32() == 1);


		rsl::bitset<129> b129;
		rsl::bitset<129> b129A(1);

		CHECK(b129.size() == 129);
		CHECK(b129.any() == false);
		CHECK(b129.all() == false);
		CHECK(b129.none() == true);
		CHECK(b129.to_uint32() == 0);
		CHECK(b129A.any() == true);
		CHECK(b129A.all() == false);
		CHECK(b129A.none() == false);
		CHECK(b129A.to_uint32() == 1);


		// operator[], data, test, to_uint32, count
		b1[0] = true;
		CHECK(b1.test(0) == true);
		CHECK(b1.count() == 1);

		b33[0] = true;
		b33[32] = true;
		CHECK(b33.test(0) == true);
		CHECK(b33.test(15) == false);
		CHECK(b33.test(32) == true);
		CHECK(b33.count() == 2);

		b65[0] = true;
		b65[32] = true;
		b65[64] = true;
		CHECK(b65.test(0) == true);
		CHECK(b65.test(15) == false);
		CHECK(b65.test(32) == true);
		CHECK(b65.test(47) == false);
		CHECK(b65.test(64) == true);
		CHECK(b65.count() == 3);

		b129[0] = true;
		b129[32] = true;
		b129[64] = true;
		b129[128] = true;
		CHECK(b129.test(0) == true);
		CHECK(b129.test(15) == false);
		CHECK(b129.test(32) == true);
		CHECK(b129.test(47) == false);
		CHECK(b129.test(64) == true);
		CHECK(b129.test(91) == false);
		CHECK(b129.test(128) == true);
		CHECK(b129.count() == 4);

		// rsl::bitset<1> set, reset, flip, ~
		b1.reset();
		CHECK(b1.count() == 0);

		b1.set();
		CHECK(b1.count() == b1.size());
		CHECK(b1.all());

		b1.flip();
		CHECK(b1.count() == 0);
		CHECK(!b1.all());
		CHECK(b1.none());

		b1.set(0, true);
		CHECK(b1[0] == true);

		b1.reset(0);
		CHECK(b1[0] == false);

		b1.flip(0);
		CHECK(b1[0] == true);

		rsl::bitset<1> b1Not = ~b1;
		CHECK(b1[0] == true);
		CHECK(b1Not[0] == false);


		// rsl::bitset<33> set, reset, flip, ~
		b33.reset();
		CHECK(b33.count() == 0);

		b33.set();
		CHECK(b33.count() == b33.size());
		CHECK(b33.all());


		b33.flip();
		CHECK(b33.count() == 0);
		CHECK(!b33.all());

		b33.set(0, true);
		b33.set(32, true);
		CHECK(b33[0] == true);
		CHECK(b33[15] == false);
		CHECK(b33[32] == true);

		b33.reset(0);
		b33.reset(32);
		CHECK(b33[0] == false);
		CHECK(b33[32] == false);

		b33.flip(0);
		b33.flip(32);
		CHECK(b33[0] == true);
		CHECK(b33[32] == true);

		rsl::bitset<33> b33Not(~b33);
		CHECK(b33[0] == true);
		CHECK(b33[32] == true);
		CHECK(b33Not[0] == false);
		CHECK(b33Not[32] == false);


		// rsl::bitset<65> set, reset, flip, ~
		b65.reset();
		CHECK(b65.count() == 0);
		CHECK(!b65.all());
		CHECK(b65.none());

		b65.set();
		CHECK(b65.count() == b65.size());
		CHECK(b65.all());
		CHECK(!b65.none());

		b65.flip();
		CHECK(b65.count() == 0);
		CHECK(!b65.all());
		CHECK(b65.none());


		b65.set(0, true);
		b65.set(32, true);
		b65.set(64, true);
		CHECK(b65[0] == true);
		CHECK(b65[15] == false);
		CHECK(b65[32] == true);
		CHECK(b65[50] == false);
		CHECK(b65[64] == true);

		b65.reset(0);
		b65.reset(32);
		b65.reset(64);
		CHECK(b65[0] == false);
		CHECK(b65[32] == false);
		CHECK(b65[64] == false);

		b65.flip(0);
		b65.flip(32);
		b65.flip(64);
		CHECK(b65[0] == true);
		CHECK(b65[32] == true);
		CHECK(b65[64] == true);

		rsl::bitset<65> b65Not(~b65);
		CHECK(b65[0] == true);
		CHECK(b65[32] == true);
		CHECK(b65[64] == true);
		CHECK(b65Not[0] == false);
		CHECK(b65Not[32] == false);
		CHECK(b65Not[64] == false);


		// rsl::bitset<65> set, reset, flip, ~
		b129.reset();
		CHECK(b129.count() == 0);

		b129.set();
		CHECK(b129.count() == b129.size());
		CHECK(b129.all());

		b129.flip();
		CHECK(b129.count() == 0);
		CHECK(!b129.all());
		CHECK(b129.none());

		b129.set(0, true);
		b129.set(32, true);
		b129.set(64, true);
		b129.set(128, true);
		CHECK(b129[0] == true);
		CHECK(b129[15] == false);
		CHECK(b129[32] == true);
		CHECK(b129[50] == false);
		CHECK(b129[64] == true);
		CHECK(b129[90] == false);
		CHECK(b129[128] == true);

		b129.reset(0);
		b129.reset(32);
		b129.reset(64);
		b129.reset(128);
		CHECK(b129[0] == false);
		CHECK(b129[32] == false);
		CHECK(b129[64] == false);
		CHECK(b129[128] == false);

		b129.flip(0);
		b129.flip(32);
		b129.flip(64);
		b129.flip(128);
		CHECK(b129[0] == true);
		CHECK(b129[32] == true);
		CHECK(b129[64] == true);
		CHECK(b129[128] == true);

		rsl::bitset<129> b129Not(~b129);
		CHECK(b129[0] == true);
		CHECK(b129[32] == true);
		CHECK(b129[64] == true);
		CHECK(b129[128] == true);
		CHECK(b129Not[0] == false);
		CHECK(b129Not[32] == false);
		CHECK(b129Not[64] == false);
		CHECK(b129Not[128] == false);


		// operator ==, !=
		rsl::bitset<1> b1Equal(b1);
		CHECK(b1Equal == b1);
		CHECK(b1Equal != b1Not);

		rsl::bitset<33> b33Equal(b33);
		CHECK(b33Equal == b33);
		CHECK(b33Equal != b33Not);

		rsl::bitset<65> b65Equal(b65);
		CHECK(b65Equal == b65);
		CHECK(b65Equal != b65Not);

		rsl::bitset<129> b129Equal(b129);
		CHECK(b129Equal == b129);
		CHECK(b129Equal != b129Not);


		// rsl::bitset<1> operator<<=, operator>>=, operator<<, operator>>
		b1.reset();

		b1[0] = true;
		b1 >>= 0;
		CHECK(b1[0] == true);
		b1 >>= 1;
		CHECK(b1[0] == false);

		b1[0] = true;
		b1 <<= 0;
		CHECK(b1[0] == true);
		b1 <<= 1;
		CHECK(b1[0] == false);

		b1[0] = true;
		b1Equal = b1 >> 0;
		CHECK(b1Equal == b1);
		b1Equal = b1 >> 1;
		CHECK(b1Equal[0] == false);

		b1[0] = true;
		b1Equal = b1 << 0;
		CHECK(b1Equal[0] == true);
		b1Equal = b1 << 1;
		CHECK(b1Equal[0] == false);

		b1.reset();
		b1.flip();
		b1 >>= 33;
		CHECK(b1.count() == 0);
		CHECK(!b1.all());
		CHECK(b1.none());

		b1.reset();
		b1.flip();
		b1 <<= 33;
		CHECK(b1.count() == 0);
		CHECK(!b1.all());
		CHECK(b1.none());

		b1.reset();
		b1.flip();
		b1 >>= 65;
		CHECK(b1.count() == 0);
		CHECK(!b1.all());
		CHECK(b1.none());

		b1.reset();
		b1.flip();
		b1 <<= 65;
		CHECK(b1.count() == 0);
		CHECK(!b1.all());
		CHECK(b1.none());


		// rsl::bitset<33> operator<<=, operator>>=, operator<<, operator>>
		b33.reset();

		b33[0] = true;
		b33[32] = true;
		b33 >>= 0;
		CHECK(b33[0] == true);
		CHECK(b33[32] == true);
		b33 >>= 10;
		CHECK(b33[22] == true);

		b33.reset();
		b33[0] = true;
		b33[32] = true;
		b33 <<= 0;
		CHECK(b33[0] == true);
		CHECK(b33[32] == true);
		b33 <<= 10;
		CHECK(b33[10] == true);

		b33.reset();
		b33[0] = true;
		b33[32] = true;
		b33Equal = b33 >> 0;
		CHECK(b33Equal == b33);
		b33Equal = b33 >> 10;
		CHECK(b33Equal[22] == true);

		b33.reset();
		b33[0] = true;
		b33[32] = true;
		b33Equal = b33 << 10;
		CHECK(b33Equal[10] == true);

		b33.reset();
		b33.flip();
		b33 >>= 33;
		CHECK(b33.count() == 0);
		CHECK(!b33.all());
		CHECK(b33.none());

		b33.reset();
		b33.flip();
		b33 <<= 33;
		CHECK(b33.count() == 0);
		CHECK(!b33.all());
		CHECK(b33.none());

		b33.reset();
		b33.flip();
		b33 >>= 65;
		CHECK(b33.count() == 0);
		CHECK(!b33.all());
		CHECK(b33.none());

		b33.reset();
		b33.flip();
		b33 <<= 65;
		CHECK(b33.count() == 0);
		CHECK(!b33.all());
		CHECK(b33.none());


		// rsl::bitset<65> operator<<=, operator>>=, operator<<, operator>>
		b65.reset();

		b65[0] = true;
		b65[32] = true;
		b65[64] = true;
		b65 >>= 0;
		CHECK(b65[0] == true);
		CHECK(b65[32] == true);
		CHECK(b65[64] == true);
		b65 >>= 10;
		CHECK(b65[22] == true);
		CHECK(b65[54] == true);

		b65.reset();
		b65[0] = true;
		b65[32] = true;
		b65[64] = true;
		b65 <<= 0;
		CHECK(b65[0] == true);
		CHECK(b65[32] == true);
		CHECK(b65[64] == true);
		b65 <<= 10;
		CHECK(b65[10] == true);
		CHECK(b65[42] == true);

		b65.reset();
		b65[0] = true;
		b65[32] = true;
		b65[64] = true;
		b65Equal = b65 >> 0;
		CHECK(b65Equal == b65);
		b65Equal = b65 >> 10;
		CHECK(b65Equal[22] == true);
		CHECK(b65Equal[54] == true);

		b65.reset();
		b65[0] = true;
		b65[32] = true;
		b65[64] = true;
		b65Equal = b65 << 10;
		CHECK(b65Equal[10] == true);
		CHECK(b65Equal[42] == true);

		b65.reset();
		b65.flip();
		b65 >>= 33;
		CHECK(b65.count() == 32);

		b65.reset();
		b65.flip();
		b65 <<= 33;
		CHECK(b65.count() == 32);

		b65.reset();
		b65.flip();
		b65 >>= 65;
		CHECK(b65.count() == 0);

		b65.reset();
		b65.flip();
		b65 <<= 65;
		CHECK(b65.count() == 0);


		// rsl::bitset<129> operator<<=, operator>>=, operator<<, operator>>
		b129.reset();

		b129[0] = true;
		b129[32] = true;
		b129[64] = true;
		b129[128] = true;
		b129 >>= 0;
		CHECK(b129[0] == true);
		CHECK(b129[32] == true);
		CHECK(b129[64] == true);
		CHECK(b129[128] == true);
		b129 >>= 10;
		CHECK(b129[22] == true);
		CHECK(b129[54] == true);
		CHECK(b129[118] == true);

		b129.reset();
		b129[0] = true;
		b129[32] = true;
		b129[64] = true;
		b129[128] = true;
		b129 <<= 0;
		CHECK(b129[0] == true);
		CHECK(b129[32] == true);
		CHECK(b129[64] == true);
		CHECK(b129[128] == true);
		b129 <<= 10;
		CHECK(b129[10] == true);
		CHECK(b129[42] == true);
		CHECK(b129[74] == true);

		b129.reset();
		b129[0] = true;
		b129[32] = true;
		b129[64] = true;
		b129[128] = true;
		b129Equal = b129 >> 0;
		CHECK(b129Equal == b129);
		b129Equal = b129 >> 10;
		CHECK(b129Equal[22] == true);
		CHECK(b129Equal[54] == true);
		CHECK(b129Equal[118] == true);

		b129.reset();
		b129[0] = true;
		b129[32] = true;
		b129[64] = true;
		b129[128] = true;
		b129Equal = b129 << 10;
		CHECK(b129Equal[10] == true);
		CHECK(b129Equal[42] == true);
		CHECK(b129Equal[74] == true);

		b129.reset();
		b129.flip();
		b129 >>= 33;
		CHECK(b129.count() == 96);

		b129.reset();
		b129.flip();
		b129 <<= 33;
		CHECK(b129.count() == 96);

		b129.reset();
		b129.flip();
		b129 >>= 65;
		CHECK(b129.count() == 64);

		b129.reset();
		b129.flip();
		b129 <<= 65;
		CHECK(b129.count() == 64);


		// operator&=(const this_type& x), operator|=(const this_type& x), operator^=(const this_type& x)
		b1.set();
		b1[0] = false;
		b1A[0] = true;
		b1 &= b1A;
		CHECK(b1[0] == false);
		b1 |= b1A;
		CHECK(b1[0] == true);
		b1 ^= b1A;
		CHECK(b1[0] == false);
		b1 |= b1A;
		CHECK(b1[0] == true);

		b33.set();
		b33[0] = false;
		b33[32] = false;
		b33A[0] = true;
		b33A[32] = true;
		b33 &= b33A;
		CHECK(((b33[0] == false) && (b33[32] == false)));
		b33 |= b33A;
		CHECK(((b33[0] == true) && (b33[32] == true)));
		b33 ^= b33A;
		CHECK(((b33[0] == false) && (b33[32] == false)));
		b33 |= b33A;
		CHECK(((b33[0] == true) && (b33[32] == true)));

		b65.set();
		b65[0] = false;
		b65[32] = false;
		b65[64] = false;
		b65A[0] = true;
		b65A[32] = true;
		b65A[64] = true;
		b65 &= b65A;
		CHECK(((b65[0] == false) && (b65[32] == false) && (b65[64] == false)));
		b65 |= b65A;
		CHECK(((b65[0] == true) && (b65[32] == true) && (b65[64] == true)));
		b65 ^= b65A;
		CHECK(((b65[0] == false) && (b65[32] == false) && (b65[64] == false)));
		b65 |= b65A;
		CHECK(((b65[0] == true) && (b65[32] == true) && (b65[64] == true)));

		b129.set();
		b129[0] = false;
		b129[32] = false;
		b129[64] = false;
		b129[128] = false;
		b129A[0] = true;
		b129A[32] = true;
		b129A[64] = true;
		b129A[128] = true;
		b129 &= b129A;
		CHECK(((b129[0] == false) && (b129[32] == false) && (b129[64] == false) && (b129[128] == false)));
		b129 |= b129A;
		CHECK(((b129[0] == true) && (b129[32] == true) && (b129[64] == true) && (b129[128] == true)));
		b129 ^= b129A;
		CHECK(((b129[0] == false) && (b129[32] == false) && (b129[64] == false) && (b129[128] == false)));
		b129 |= b129A;
		CHECK(((b129[0] == true) && (b129[32] == true) && (b129[64] == true) && (b129[128] == true)));
	}

	{ // Test rsl::bitset::reference
		rsl::bitset<65> b65;
		rsl::bitset<65>::reference r = b65[33];

		r = true;
		CHECK(r == true);
	}

}