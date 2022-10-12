// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: type_traits_test.cpp
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#include "catch2/catch.hpp"

#include "rex_std/type_traits.h"

void dummy_function()
{

}

class dummy_class 
{
public:
  void dummy_member_func()
  {}
};

TEST_CASE("integral constant")
{
  rsl::integral_constant<int, 0> i0;
  rsl::integral_constant<int, 1> i1;
  rsl::integral_constant<int, 2> i2;
  rsl::integral_constant<int, 3> i3;

  REQUIRE(i0.value == 0);
  REQUIRE(i0.operator int() == 0);
  REQUIRE(i0.operator()() == 0);
  REQUIRE(i1.value == 1);
  REQUIRE(i1.operator int() == 1);
  REQUIRE(i1.operator()() == 1);
  REQUIRE(i2.value == 2);
  REQUIRE(i2.operator int() == 2);
  REQUIRE(i2.operator()() == 2);
  REQUIRE(i3.value == 3);
  REQUIRE(i3.operator int() == 3);
  REQUIRE(i3.operator()() == 3);
}
TEST_CASE("bool constant")
{
  rsl::bool_constant<false> b0;
  rsl::bool_constant<true> b1;

  REQUIRE(b0.value == false);
  REQUIRE(b1.value == true);
}
TEST_CASE("true type and false type")
{
  rsl::false_type t0;
  rsl::true_type t1;

  REQUIRE(t0.value == false);
  REQUIRE(t1.value == true);
}
TEST_CASE("is void")
{
  REQUIRE(rsl::is_void_v<void> == true);
  REQUIRE(rsl::is_void_v<int> == false);
  REQUIRE(rsl::is_void_v<class unused> == false);
}
TEST_CASE("is nullptr")
{
  REQUIRE(rsl::is_null_pointer_v<rsl::nullptr_t> == true);
  REQUIRE(rsl::is_null_pointer_v<int> == false);
  REQUIRE(rsl::is_null_pointer_v<class unused> == false);
}
TEST_CASE("is integral")
{
  REQUIRE(rsl::is_integral_v<bool> == true);
  REQUIRE(rsl::is_integral_v<int8> == true);
  REQUIRE(rsl::is_integral_v<uint8> == true);
  REQUIRE(rsl::is_integral_v<int16> == true);
  REQUIRE(rsl::is_integral_v<uint16> == true);
  REQUIRE(rsl::is_integral_v<int32> == true);
  REQUIRE(rsl::is_integral_v<uint32> == true);
  REQUIRE(rsl::is_integral_v<int64> == true);
  REQUIRE(rsl::is_integral_v<uint64> == true);

  REQUIRE(rsl::is_integral_v<float32> == false);
  REQUIRE(rsl::is_integral_v<float64> == false);
  REQUIRE(rsl::is_integral_v<rsl::lfloat64> == false);

  REQUIRE(rsl::is_integral_v<int[]> == false);

  REQUIRE(rsl::is_integral_v<class unused> == false);
  REQUIRE(rsl::is_integral_v<union unused_u> == false);
  REQUIRE(rsl::is_integral_v<enum unused_e> == false);
  REQUIRE(rsl::is_integral_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_integral_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_integral_v<int*> == false);
}
TEST_CASE("is floating point")
{
  REQUIRE(rsl::is_floating_point_v<bool> == false);
  REQUIRE(rsl::is_floating_point_v<int8> == false);
  REQUIRE(rsl::is_floating_point_v<uint8> == false);
  REQUIRE(rsl::is_floating_point_v<int16> == false);
  REQUIRE(rsl::is_floating_point_v<uint16> == false);
  REQUIRE(rsl::is_floating_point_v<int32> == false);
  REQUIRE(rsl::is_floating_point_v<uint32> == false);
  REQUIRE(rsl::is_floating_point_v<int64> == false);
  REQUIRE(rsl::is_floating_point_v<uint64> == false);

  REQUIRE(rsl::is_floating_point_v<float32> == true);
  REQUIRE(rsl::is_floating_point_v<float64> == true);
  REQUIRE(rsl::is_floating_point_v<rsl::lfloat64> == true);

  REQUIRE(rsl::is_floating_point_v<int[]> == false);

  REQUIRE(rsl::is_floating_point_v<class unused> == false);
  REQUIRE(rsl::is_floating_point_v<union unused_u> == false);
  REQUIRE(rsl::is_floating_point_v<enum unused_e> == false);
  REQUIRE(rsl::is_floating_point_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_floating_point_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_floating_point_v<int*> == false);
}
TEST_CASE("is array")
{
  REQUIRE(rsl::is_array_v<bool> == false);
  REQUIRE(rsl::is_array_v<int8> == false);
  REQUIRE(rsl::is_array_v<uint8> == false);
  REQUIRE(rsl::is_array_v<int16> == false);
  REQUIRE(rsl::is_array_v<uint16> == false);
  REQUIRE(rsl::is_array_v<int32> == false);
  REQUIRE(rsl::is_array_v<uint32> == false);
  REQUIRE(rsl::is_array_v<int64> == false);
  REQUIRE(rsl::is_array_v<uint64> == false);

  REQUIRE(rsl::is_array_v<float32> == false);
  REQUIRE(rsl::is_array_v<float64> == false);
  REQUIRE(rsl::is_array_v<rsl::lfloat64> == false);

  REQUIRE(rsl::is_array_v<int[]> == true);

  REQUIRE(rsl::is_array_v<class unused> == false);
  REQUIRE(rsl::is_array_v<union unused_u> == false);
  REQUIRE(rsl::is_array_v<enum unused_e> == false);
  REQUIRE(rsl::is_array_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_array_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_array_v<int*> == false);
}
TEST_CASE("is enum")
{
  REQUIRE(rsl::is_enum_v<bool> == false);
  REQUIRE(rsl::is_enum_v<int8> == false);
  REQUIRE(rsl::is_enum_v<uint8> == false);
  REQUIRE(rsl::is_enum_v<int16> == false);
  REQUIRE(rsl::is_enum_v<uint16> == false);
  REQUIRE(rsl::is_enum_v<int32> == false);
  REQUIRE(rsl::is_enum_v<uint32> == false);
  REQUIRE(rsl::is_enum_v<int64> == false);
  REQUIRE(rsl::is_enum_v<uint64> == false);

  REQUIRE(rsl::is_enum_v<float32> == false);
  REQUIRE(rsl::is_enum_v<float64> == false);
  REQUIRE(rsl::is_enum_v<rsl::lfloat64> == false);

  REQUIRE(rsl::is_enum_v<int[]> == false);

  REQUIRE(rsl::is_enum_v<class unused> == false);
  REQUIRE(rsl::is_enum_v<union unused_u> == false);
  REQUIRE(rsl::is_enum_v<enum unused_e> == true);
  REQUIRE(rsl::is_enum_v<enum class unused_ec> == true);
  REQUIRE(rsl::is_enum_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_enum_v<int*> == false);
}
TEST_CASE("is union")
{
  REQUIRE(rsl::is_union_v<bool> == false);
  REQUIRE(rsl::is_union_v<int8> == false);
  REQUIRE(rsl::is_union_v<uint8> == false);
  REQUIRE(rsl::is_union_v<int16> == false);
  REQUIRE(rsl::is_union_v<uint16> == false);
  REQUIRE(rsl::is_union_v<int32> == false);
  REQUIRE(rsl::is_union_v<uint32> == false);
  REQUIRE(rsl::is_union_v<int64> == false);
  REQUIRE(rsl::is_union_v<uint64> == false);
               
  REQUIRE(rsl::is_union_v<float32> == false);
  REQUIRE(rsl::is_union_v<float64> == false);
  REQUIRE(rsl::is_union_v<rsl::lfloat64> == false);
               
  REQUIRE(rsl::is_union_v<int[]> == false);
               
  REQUIRE(rsl::is_union_v<class unused> == false);
  REQUIRE(rsl::is_union_v<union unused_u> == true);
  REQUIRE(rsl::is_union_v<enum unused_e> == false);
  REQUIRE(rsl::is_union_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_union_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_union_v<int*> == false);
}
TEST_CASE("is class")
{
  REQUIRE(rsl::is_class_v<bool> == false);
  REQUIRE(rsl::is_class_v<int8> == false);
  REQUIRE(rsl::is_class_v<uint8> == false);
  REQUIRE(rsl::is_class_v<int16> == false);
  REQUIRE(rsl::is_class_v<uint16> == false);
  REQUIRE(rsl::is_class_v<int32> == false);
  REQUIRE(rsl::is_class_v<uint32> == false);
  REQUIRE(rsl::is_class_v<int64> == false);
  REQUIRE(rsl::is_class_v<uint64> == false);
               
  REQUIRE(rsl::is_class_v<float32> == false);
  REQUIRE(rsl::is_class_v<float64> == false);
  REQUIRE(rsl::is_class_v<rsl::lfloat64> == false);
               
  REQUIRE(rsl::is_class_v<int[]> == false);
               
  REQUIRE(rsl::is_class_v<class unused> == true);
  REQUIRE(rsl::is_class_v<union unused_u> == false);
  REQUIRE(rsl::is_class_v<enum unused_e> == false);
  REQUIRE(rsl::is_class_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_class_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_class_v<int*> == false);
}
TEST_CASE("is function")
{
  REQUIRE(rsl::is_function_v<bool> == false);
  REQUIRE(rsl::is_function_v<int8> == false);
  REQUIRE(rsl::is_function_v<uint8> == false);
  REQUIRE(rsl::is_function_v<int16> == false);
  REQUIRE(rsl::is_function_v<uint16> == false);
  REQUIRE(rsl::is_function_v<int32> == false);
  REQUIRE(rsl::is_function_v<uint32> == false);
  REQUIRE(rsl::is_function_v<int64> == false);
  REQUIRE(rsl::is_function_v<uint64> == false);

  REQUIRE(rsl::is_function_v<float32> == false);
  REQUIRE(rsl::is_function_v<float64> == false);
  REQUIRE(rsl::is_function_v<rsl::lfloat64> == false);

  REQUIRE(rsl::is_function_v<int[]> == false);

  REQUIRE(rsl::is_function_v<class unused> == false);
  REQUIRE(rsl::is_function_v<union unused_u> == false);
  REQUIRE(rsl::is_function_v<enum unused_e> == false);
  REQUIRE(rsl::is_function_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_function_v<decltype(dummy_function)> == true);
  REQUIRE(rsl::is_function_v<int*> == false);
}
TEST_CASE("is pointer")
{
  REQUIRE(rsl::is_pointer_v<bool> == false);
  REQUIRE(rsl::is_pointer_v<int8> == false);
  REQUIRE(rsl::is_pointer_v<uint8> == false);
  REQUIRE(rsl::is_pointer_v<int16> == false);
  REQUIRE(rsl::is_pointer_v<uint16> == false);
  REQUIRE(rsl::is_pointer_v<int32> == false);
  REQUIRE(rsl::is_pointer_v<uint32> == false);
  REQUIRE(rsl::is_pointer_v<int64> == false);
  REQUIRE(rsl::is_pointer_v<uint64> == false);

  REQUIRE(rsl::is_pointer_v<float32> == false);
  REQUIRE(rsl::is_pointer_v<float64> == false);
  REQUIRE(rsl::is_pointer_v<rsl::lfloat64> == false);

  REQUIRE(rsl::is_pointer_v<int[]> == false);

  REQUIRE(rsl::is_pointer_v<class unused> == false);
  REQUIRE(rsl::is_pointer_v<union unused_u> == false);
  REQUIRE(rsl::is_pointer_v<enum unused_e> == false);
  REQUIRE(rsl::is_pointer_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_pointer_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_pointer_v<int*> == true);
}
TEST_CASE("is lvalue reference")
{
  REQUIRE(rsl::is_lvalue_reference_v<int> == false);
  REQUIRE(rsl::is_lvalue_reference_v<const int> == false);
  REQUIRE(rsl::is_lvalue_reference_v<int&> == true);
  REQUIRE(rsl::is_lvalue_reference_v<const int&> == true);
  REQUIRE(rsl::is_lvalue_reference_v<int&&> == false);
  REQUIRE(rsl::is_lvalue_reference_v<const int&&> == false);
}
TEST_CASE("is rvalue reference")
{
  REQUIRE(rsl::is_rvalue_reference_v<int> == false);
  REQUIRE(rsl::is_rvalue_reference_v<const int> == false);
  REQUIRE(rsl::is_rvalue_reference_v<int&> == false);
  REQUIRE(rsl::is_rvalue_reference_v<const int&> == false);
  REQUIRE(rsl::is_rvalue_reference_v<int&&> == true);
  REQUIRE(rsl::is_rvalue_reference_v<const int&&> == true);
}
TEST_CASE("is member object pointer")
{
  REQUIRE(rsl::is_member_object_pointer_v<int(dummy_class::*)> == true);
  REQUIRE(rsl::is_member_object_pointer_v<int(dummy_class::*)()> == false);
}
TEST_CASE("is member function pointer")
{
  REQUIRE(rsl::is_member_function_pointer_v<decltype(&dummy_class::dummy_member_func)> == true);
  REQUIRE(rsl::is_member_function_pointer_v<decltype(dummy_function)> == false);
}
TEST_CASE("is fundamental")
{
  REQUIRE(rsl::is_fundamental_v<bool> == true);
  REQUIRE(rsl::is_fundamental_v<int8> == true);
  REQUIRE(rsl::is_fundamental_v<uint8> == true);
  REQUIRE(rsl::is_fundamental_v<int16> == true);
  REQUIRE(rsl::is_fundamental_v<uint16> == true);
  REQUIRE(rsl::is_fundamental_v<int32> == true);
  REQUIRE(rsl::is_fundamental_v<uint32> == true);
  REQUIRE(rsl::is_fundamental_v<int64> == true);
  REQUIRE(rsl::is_fundamental_v<uint64> == true);

  REQUIRE(rsl::is_fundamental_v<float32> == true);
  REQUIRE(rsl::is_fundamental_v<float64> == true);
  REQUIRE(rsl::is_fundamental_v<rsl::lfloat64> == true);

  REQUIRE(rsl::is_fundamental_v<int[]> == false);

  REQUIRE(rsl::is_fundamental_v<class unused> == false);
  REQUIRE(rsl::is_fundamental_v<union unused_u> == false);
  REQUIRE(rsl::is_fundamental_v<enum unused_e> == false);
  REQUIRE(rsl::is_fundamental_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_fundamental_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_fundamental_v<int*> == false);

  REQUIRE(rsl::is_fundamental_v<void> == true);
  REQUIRE(rsl::is_fundamental_v<nullptr_t> == true);
}
TEST_CASE("is arithmetic")
{
  REQUIRE(rsl::is_arithmetic_v<bool> == true);
  REQUIRE(rsl::is_arithmetic_v<int8> == true);
  REQUIRE(rsl::is_arithmetic_v<uint8> == true);
  REQUIRE(rsl::is_arithmetic_v<int16> == true);
  REQUIRE(rsl::is_arithmetic_v<uint16> == true);
  REQUIRE(rsl::is_arithmetic_v<int32> == true);
  REQUIRE(rsl::is_arithmetic_v<uint32> == true);
  REQUIRE(rsl::is_arithmetic_v<int64> == true);
  REQUIRE(rsl::is_arithmetic_v<uint64> == true);

  REQUIRE(rsl::is_arithmetic_v<float32> == true);
  REQUIRE(rsl::is_arithmetic_v<float64> == true);
  REQUIRE(rsl::is_arithmetic_v<rsl::lfloat64> == true);

  REQUIRE(rsl::is_arithmetic_v<int[]> == false);

  REQUIRE(rsl::is_arithmetic_v<class unused> == false);
  REQUIRE(rsl::is_arithmetic_v<union unused_u> == false);
  REQUIRE(rsl::is_arithmetic_v<enum unused_e> == false);
  REQUIRE(rsl::is_arithmetic_v<enum class unused_ec> == false);
  REQUIRE(rsl::is_arithmetic_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_arithmetic_v<int*> == false);

  REQUIRE(rsl::is_arithmetic_v<void> == false);
  REQUIRE(rsl::is_arithmetic_v<nullptr_t> == false);
}
TEST_CASE("is scalar")
{
  REQUIRE(rsl::is_scalar_v<bool> == true);
  REQUIRE(rsl::is_scalar_v<int8> == true);
  REQUIRE(rsl::is_scalar_v<uint8> == true);
  REQUIRE(rsl::is_scalar_v<int16> == true);
  REQUIRE(rsl::is_scalar_v<uint16> == true);
  REQUIRE(rsl::is_scalar_v<int32> == true);
  REQUIRE(rsl::is_scalar_v<uint32> == true);
  REQUIRE(rsl::is_scalar_v<int64> == true);
  REQUIRE(rsl::is_scalar_v<uint64> == true);

  REQUIRE(rsl::is_scalar_v<float32> == true);
  REQUIRE(rsl::is_scalar_v<float64> == true);
  REQUIRE(rsl::is_scalar_v<rsl::lfloat64> == true);

  REQUIRE(rsl::is_scalar_v<int[]> == false);

  REQUIRE(rsl::is_scalar_v<class unused> == false);
  REQUIRE(rsl::is_scalar_v<union unused_u> == false);
  REQUIRE(rsl::is_scalar_v<enum unused_e> == true);
  REQUIRE(rsl::is_scalar_v<enum class unused_ec> == true);
  REQUIRE(rsl::is_scalar_v<decltype(dummy_function)> == false);
  REQUIRE(rsl::is_scalar_v<int*> == true);

  REQUIRE(rsl::is_scalar_v<void> == false);
  REQUIRE(rsl::is_scalar_v<nullptr_t> == true);
}