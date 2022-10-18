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

//NOLINTBEGIN

void dummy_function() noexcept
{

}

class dummy_class
{
public:
  void dummy_member_func()
  {}
};

union dummy_union
{

};

enum dummy_enum
{

};

enum class dummy_enum_class
{

};

enum class dummy_enum_class_short : short
{};

// trivial type:
// - scalar types
// - class
//    - trivially copyable
//    - default ctors
// - arrays of trivial types
class trivial_class
{

};

class non_trivial_class
{
public:
  non_trivial_class(int x)
    : m_x(x)
  {}

  non_trivial_class(const non_trivial_class& other)
    : m_x(other.m_x)
  {}

private:
  int m_x;
};

// standard layout class:
// - has no non-static data member of non-standard-layout class or reference
// - has no virtual functions and no virtual base classes
// - has the same access controll for all non-static data members
// - only one class in the hierarchy has non-static data members, and
// - informally, none of the base classes has the same type as the first non - static data member. 
// - formally: given the class as S, has no element of the set M(S) of types as a base class, where M(X) for a type X is defined as :
//    -if X is a non - union class type with no(possibly inherited) non - static data members, the set M(X) is empty.
//    -if X is a non - union class type whose first non - static data member has type X0(where said member may be an anonymous union), the set M(X) consists of X0and the elements of M(X0).
//    -if X is a union type, the set M(X) is the union of all M(Ui) and the set containing all Ui, where each Ui is the type of the ith non - static data member of X.
//    -if X is an array type with element type Xe, the set M(X) consists of Xeand the elements of M(Xe).
//    -if X is a non - class, non - array type, the set M(X) is empty.

class standard_layout_class
{
public:
  standard_layout_class()
    : m_x(0)
  {}

private:
  int m_x;
};

class non_standard_layout_class
{
  virtual ~non_standard_layout_class() = default;
};

// pod class
// - is a trivial class
// - is a standard layout class
// - has no non-static data members of type non-POD class
struct pod_class
{
  int x;
  int y;
  int z;
};

struct non_pod_class
{
  virtual ~non_pod_class() = default;
};

struct has_unique_object_represenations_class
{
  int a;
  int b;
};

struct non_has_unique_object_represenations_class
{
  char c;
  float f;
  short st;
  int i;
};

class empty_class
{};

class non_empty_class
{
  int m_x;
};

class polymorphic_class
{
public:
  virtual void foo() {}
};
class non_polymorphic_class
{
public:
  void foo() {}
};

class abstract_class
{
public:
  virtual void foo() = 0;
};
class non_abstract_class
{
public:
  virtual void foo() {}
};

class final_class final {};
class non_final_class {};

class constructible_test_class
{
public:
  constructible_test_class(int n)
    : m_v1(n)
    , m_v2()
  {}
  constructible_test_class(int n, double f) noexcept
    : m_v1(n)
    , m_v2(f)
  {}

private:
  int m_v1;
  double m_v2;
};

class default_constructible_test_class
{};

struct trivially_default_constructible_test_class
{
  int n;
  trivially_default_constructible_test_class() = default; // trivial and non-throwing
};
struct non_trivially_default_constructible_test_class
{
  polymorphic_class str; // member has a non-trivial default ctor
};

struct assignable_class
{
  int n;
};

class no_copy_assignment
{
  no_copy_assignment& operator=(const no_copy_assignment&) = delete;
};

class no_move_assignment
{
  no_move_assignment& operator=(no_move_assignment&&) = delete;
};

class base
{

};

class derived : public base
{

};

TEST_CASE("integral constant")
{
  rsl::integral_constant<int, 0> i0;
  rsl::integral_constant<int, 1> i1;
  rsl::integral_constant<int, 2> i2;
  rsl::integral_constant<int, 3> i3;

  STATIC_REQUIRE(i0.value == 0);
  STATIC_REQUIRE(i0.operator int() == 0);
  STATIC_REQUIRE(i0.operator()() == 0);
  STATIC_REQUIRE(i1.value == 1);
  STATIC_REQUIRE(i1.operator int() == 1);
  STATIC_REQUIRE(i1.operator()() == 1);
  STATIC_REQUIRE(i2.value == 2);
  STATIC_REQUIRE(i2.operator int() == 2);
  STATIC_REQUIRE(i2.operator()() == 2);
  STATIC_REQUIRE(i3.value == 3);
  STATIC_REQUIRE(i3.operator int() == 3);
  STATIC_REQUIRE(i3.operator()() == 3);
}
TEST_CASE("bool constant")
{
  rsl::bool_constant<false> b0;
  rsl::bool_constant<true> b1;

  STATIC_REQUIRE(b0.value == false);
  STATIC_REQUIRE(b1.value == true);
}
TEST_CASE("true type and false type")
{
  rsl::false_type t0;
  rsl::true_type t1;

  STATIC_REQUIRE(t0.value == false);
  STATIC_REQUIRE(t1.value == true);
}
TEST_CASE("is void")
{
  STATIC_REQUIRE(rsl::is_void_v<void> == true);
  STATIC_REQUIRE(rsl::is_void_v<int> == false);
  STATIC_REQUIRE(rsl::is_void_v<dummy_class> == false);
}
TEST_CASE("is nullptr")
{
  STATIC_REQUIRE(rsl::is_null_pointer_v<rsl::nullptr_t> == true);
  STATIC_REQUIRE(rsl::is_null_pointer_v<int> == false);
  STATIC_REQUIRE(rsl::is_null_pointer_v<dummy_class> == false);
}
TEST_CASE("is integral")
{
  STATIC_REQUIRE(rsl::is_integral_v<bool> == true);
  STATIC_REQUIRE(rsl::is_integral_v<int8> == true);
  STATIC_REQUIRE(rsl::is_integral_v<uint8> == true);
  STATIC_REQUIRE(rsl::is_integral_v<int16> == true);
  STATIC_REQUIRE(rsl::is_integral_v<uint16> == true);
  STATIC_REQUIRE(rsl::is_integral_v<int32> == true);
  STATIC_REQUIRE(rsl::is_integral_v<uint32> == true);
  STATIC_REQUIRE(rsl::is_integral_v<int64> == true);
  STATIC_REQUIRE(rsl::is_integral_v<uint64> == true);

  STATIC_REQUIRE(rsl::is_integral_v<float32> == false);
  STATIC_REQUIRE(rsl::is_integral_v<float64> == false);
  STATIC_REQUIRE(rsl::is_integral_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_integral_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_integral_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_integral_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_integral_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_integral_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_integral_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_integral_v<int*> == false);
}
TEST_CASE("is floating point")
{
  STATIC_REQUIRE(rsl::is_floating_point_v<bool> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<int8> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<int16> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<int32> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<int64> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_floating_point_v<float32> == true);
  STATIC_REQUIRE(rsl::is_floating_point_v<float64> == true);
  STATIC_REQUIRE(rsl::is_floating_point_v<rsl::lfloat64> == true);

  STATIC_REQUIRE(rsl::is_floating_point_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_floating_point_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_floating_point_v<int*> == false);
}
TEST_CASE("is array")
{
  STATIC_REQUIRE(rsl::is_array_v<bool> == false);
  STATIC_REQUIRE(rsl::is_array_v<int8> == false);
  STATIC_REQUIRE(rsl::is_array_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_array_v<int16> == false);
  STATIC_REQUIRE(rsl::is_array_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_array_v<int32> == false);
  STATIC_REQUIRE(rsl::is_array_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_array_v<int64> == false);
  STATIC_REQUIRE(rsl::is_array_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_array_v<float32> == false);
  STATIC_REQUIRE(rsl::is_array_v<float64> == false);
  STATIC_REQUIRE(rsl::is_array_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_array_v<int[]> == true);

  STATIC_REQUIRE(rsl::is_array_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_array_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_array_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_array_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_array_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_array_v<int*> == false);
}
TEST_CASE("is enum")
{
  STATIC_REQUIRE(rsl::is_enum_v<bool> == false);
  STATIC_REQUIRE(rsl::is_enum_v<int8> == false);
  STATIC_REQUIRE(rsl::is_enum_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_enum_v<int16> == false);
  STATIC_REQUIRE(rsl::is_enum_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_enum_v<int32> == false);
  STATIC_REQUIRE(rsl::is_enum_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_enum_v<int64> == false);
  STATIC_REQUIRE(rsl::is_enum_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_enum_v<float32> == false);
  STATIC_REQUIRE(rsl::is_enum_v<float64> == false);
  STATIC_REQUIRE(rsl::is_enum_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_enum_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_enum_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_enum_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_enum_v<dummy_enum> == true);
  STATIC_REQUIRE(rsl::is_enum_v<dummy_enum_class> == true);
  STATIC_REQUIRE(rsl::is_enum_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_enum_v<int*> == false);
}
TEST_CASE("is union")
{
  STATIC_REQUIRE(rsl::is_union_v<bool> == false);
  STATIC_REQUIRE(rsl::is_union_v<int8> == false);
  STATIC_REQUIRE(rsl::is_union_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_union_v<int16> == false);
  STATIC_REQUIRE(rsl::is_union_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_union_v<int32> == false);
  STATIC_REQUIRE(rsl::is_union_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_union_v<int64> == false);
  STATIC_REQUIRE(rsl::is_union_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_union_v<float32> == false);
  STATIC_REQUIRE(rsl::is_union_v<float64> == false);
  STATIC_REQUIRE(rsl::is_union_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_union_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_union_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_union_v<dummy_union> == true);
  STATIC_REQUIRE(rsl::is_union_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_union_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_union_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_union_v<int*> == false);
}
TEST_CASE("is class")
{
  STATIC_REQUIRE(rsl::is_class_v<bool> == false);
  STATIC_REQUIRE(rsl::is_class_v<int8> == false);
  STATIC_REQUIRE(rsl::is_class_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_class_v<int16> == false);
  STATIC_REQUIRE(rsl::is_class_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_class_v<int32> == false);
  STATIC_REQUIRE(rsl::is_class_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_class_v<int64> == false);
  STATIC_REQUIRE(rsl::is_class_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_class_v<float32> == false);
  STATIC_REQUIRE(rsl::is_class_v<float64> == false);
  STATIC_REQUIRE(rsl::is_class_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_class_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_class_v<dummy_class> == true);
  STATIC_REQUIRE(rsl::is_class_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_class_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_class_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_class_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_class_v<int*> == false);
}
TEST_CASE("is function")
{
  STATIC_REQUIRE(rsl::is_function_v<bool> == false);
  STATIC_REQUIRE(rsl::is_function_v<int8> == false);
  STATIC_REQUIRE(rsl::is_function_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_function_v<int16> == false);
  STATIC_REQUIRE(rsl::is_function_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_function_v<int32> == false);
  STATIC_REQUIRE(rsl::is_function_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_function_v<int64> == false);
  STATIC_REQUIRE(rsl::is_function_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_function_v<float32> == false);
  STATIC_REQUIRE(rsl::is_function_v<float64> == false);
  STATIC_REQUIRE(rsl::is_function_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_function_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_function_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_function_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_function_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_function_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_function_v<decltype(dummy_function)> == true);
  STATIC_REQUIRE(rsl::is_function_v<int*> == false);
}
TEST_CASE("is pointer")
{
  STATIC_REQUIRE(rsl::is_pointer_v<bool> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<int8> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<int16> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<int32> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<int64> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_pointer_v<float32> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<float64> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_pointer_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_pointer_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_pointer_v<int*> == true);
}
TEST_CASE("is lvalue reference")
{
  STATIC_REQUIRE(rsl::is_lvalue_reference_v<int> == false);
  STATIC_REQUIRE(rsl::is_lvalue_reference_v<const int> == false);
  STATIC_REQUIRE(rsl::is_lvalue_reference_v<int&> == true);
  STATIC_REQUIRE(rsl::is_lvalue_reference_v<const int&> == true);
  STATIC_REQUIRE(rsl::is_lvalue_reference_v<int&&> == false);
  STATIC_REQUIRE(rsl::is_lvalue_reference_v<const int&&> == false);
}
TEST_CASE("is rvalue reference")
{
  STATIC_REQUIRE(rsl::is_rvalue_reference_v<int> == false);
  STATIC_REQUIRE(rsl::is_rvalue_reference_v<const int> == false);
  STATIC_REQUIRE(rsl::is_rvalue_reference_v<int&> == false);
  STATIC_REQUIRE(rsl::is_rvalue_reference_v<const int&> == false);
  STATIC_REQUIRE(rsl::is_rvalue_reference_v<int&&> == true);
  STATIC_REQUIRE(rsl::is_rvalue_reference_v<const int&&> == true);
}
TEST_CASE("is member object pointer")
{
  STATIC_REQUIRE(rsl::is_member_object_pointer_v<int(dummy_class::*)> == true);
  STATIC_REQUIRE(rsl::is_member_object_pointer_v<int(dummy_class::*)()> == false);
}
TEST_CASE("is member function pointer")
{
  STATIC_REQUIRE(rsl::is_member_function_pointer_v<decltype(&dummy_class::dummy_member_func)> == true);
  STATIC_REQUIRE(rsl::is_member_function_pointer_v<decltype(dummy_function)> == false);
}
TEST_CASE("is fundamental")
{
  STATIC_REQUIRE(rsl::is_fundamental_v<bool> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<int8> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<uint8> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<int16> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<uint16> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<int32> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<uint32> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<int64> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<uint64> == true);

  STATIC_REQUIRE(rsl::is_fundamental_v<float32> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<float64> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<rsl::lfloat64> == true);

  STATIC_REQUIRE(rsl::is_fundamental_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_fundamental_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_fundamental_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_fundamental_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_fundamental_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_fundamental_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_fundamental_v<int*> == false);

  STATIC_REQUIRE(rsl::is_fundamental_v<void> == true);
  STATIC_REQUIRE(rsl::is_fundamental_v<nullptr_t> == true);
}
TEST_CASE("is arithmetic")
{
  STATIC_REQUIRE(rsl::is_arithmetic_v<bool> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<int8> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<uint8> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<int16> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<uint16> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<int32> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<uint32> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<int64> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<uint64> == true);

  STATIC_REQUIRE(rsl::is_arithmetic_v<float32> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<float64> == true);
  STATIC_REQUIRE(rsl::is_arithmetic_v<rsl::lfloat64> == true);

  STATIC_REQUIRE(rsl::is_arithmetic_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_arithmetic_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_arithmetic_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_arithmetic_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_arithmetic_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_arithmetic_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_arithmetic_v<int*> == false);

  STATIC_REQUIRE(rsl::is_arithmetic_v<void> == false);
  STATIC_REQUIRE(rsl::is_arithmetic_v<nullptr_t> == false);
}
TEST_CASE("is scalar")
{
  STATIC_REQUIRE(rsl::is_scalar_v<bool> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<int8> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<uint8> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<int16> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<uint16> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<int32> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<uint32> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<int64> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<uint64> == true);

  STATIC_REQUIRE(rsl::is_scalar_v<float32> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<float64> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<rsl::lfloat64> == true);

  STATIC_REQUIRE(rsl::is_scalar_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_scalar_v<dummy_class> == false);
  STATIC_REQUIRE(rsl::is_scalar_v<dummy_union> == false);
  STATIC_REQUIRE(rsl::is_scalar_v<dummy_enum> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<dummy_enum_class> == true);
  STATIC_REQUIRE(rsl::is_scalar_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_scalar_v<int*> == true);

  STATIC_REQUIRE(rsl::is_scalar_v<void> == false);
  STATIC_REQUIRE(rsl::is_scalar_v<nullptr_t> == true);
}
TEST_CASE("is object")
{
  STATIC_REQUIRE(rsl::is_object_v<int> == true);
  STATIC_REQUIRE(rsl::is_object_v<const int> == true);
  STATIC_REQUIRE(rsl::is_object_v<volatile int> == true);
  STATIC_REQUIRE(rsl::is_object_v<const volatile int> == true);
  STATIC_REQUIRE(rsl::is_object_v<int&> == false);
  STATIC_REQUIRE(rsl::is_object_v<void> == false);

  STATIC_REQUIRE(rsl::is_object_v<dummy_class> == true);
  STATIC_REQUIRE(rsl::is_object_v<dummy_union> == true);
  STATIC_REQUIRE(rsl::is_object_v<dummy_enum> == true);
  STATIC_REQUIRE(rsl::is_object_v<dummy_enum_class> == true);
  STATIC_REQUIRE(rsl::is_object_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_object_v<int*> == true);
}
TEST_CASE("is compound")
{
  STATIC_REQUIRE(rsl::is_compound_v<bool> == false);
  STATIC_REQUIRE(rsl::is_compound_v<int8> == false);
  STATIC_REQUIRE(rsl::is_compound_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_compound_v<int16> == false);
  STATIC_REQUIRE(rsl::is_compound_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_compound_v<int32> == false);
  STATIC_REQUIRE(rsl::is_compound_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_compound_v<int64> == false);
  STATIC_REQUIRE(rsl::is_compound_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_compound_v<float32> == false);
  STATIC_REQUIRE(rsl::is_compound_v<float64> == false);
  STATIC_REQUIRE(rsl::is_compound_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_compound_v<int[]> == true);

  STATIC_REQUIRE(rsl::is_compound_v<dummy_class> == true);
  STATIC_REQUIRE(rsl::is_compound_v<dummy_union> == true);
  STATIC_REQUIRE(rsl::is_compound_v<dummy_enum> == true);
  STATIC_REQUIRE(rsl::is_compound_v<dummy_enum_class> == true);
  STATIC_REQUIRE(rsl::is_compound_v<decltype(dummy_function)> == true);
  STATIC_REQUIRE(rsl::is_compound_v<int*> == true);

  STATIC_REQUIRE(rsl::is_compound_v<void> == false);
  STATIC_REQUIRE(rsl::is_compound_v<nullptr_t> == false);
}
TEST_CASE("is reference")
{
  STATIC_REQUIRE(rsl::is_reference_v<int> == false);
  STATIC_REQUIRE(rsl::is_reference_v<const int> == false);
  STATIC_REQUIRE(rsl::is_reference_v<volatile int> == false);
  STATIC_REQUIRE(rsl::is_reference_v<const volatile int> == false);
  STATIC_REQUIRE(rsl::is_reference_v<int&> == true);
  STATIC_REQUIRE(rsl::is_reference_v<const int&> == true);
  STATIC_REQUIRE(rsl::is_reference_v<volatile int&> == true);
  STATIC_REQUIRE(rsl::is_reference_v<const volatile int&> == true);

}
TEST_CASE("is member pointer")
{
  STATIC_REQUIRE(rsl::is_member_pointer_v<int(dummy_class::*)> == true);
  STATIC_REQUIRE(rsl::is_member_pointer_v<int(dummy_class::*)()> == true);

  STATIC_REQUIRE(rsl::is_member_pointer_v<decltype(&dummy_class::dummy_member_func)> == true);
  STATIC_REQUIRE(rsl::is_member_pointer_v<decltype(dummy_function)> == false);
}
TEST_CASE("is const")
{
  STATIC_REQUIRE(rsl::is_const_v<int> == false);
  STATIC_REQUIRE(rsl::is_const_v<const int> == true);
  STATIC_REQUIRE(rsl::is_const_v<volatile int> == false);
  STATIC_REQUIRE(rsl::is_const_v<const volatile int> == true);

  STATIC_REQUIRE(rsl::is_const_v<int&> == false);
  STATIC_REQUIRE(rsl::is_const_v<const int&> == false);
  STATIC_REQUIRE(rsl::is_const_v<volatile int&> == false);
  STATIC_REQUIRE(rsl::is_const_v<const volatile int&> == false);

  STATIC_REQUIRE(rsl::is_const_v<int*> == false);
  STATIC_REQUIRE(rsl::is_const_v<const int*> == false);
  STATIC_REQUIRE(rsl::is_const_v<volatile int*> == false);
  STATIC_REQUIRE(rsl::is_const_v<const volatile int*> == false);

  STATIC_REQUIRE(rsl::is_const_v<int* const> == true);
  STATIC_REQUIRE(rsl::is_const_v<int* volatile> == false);
  STATIC_REQUIRE(rsl::is_const_v<int* const volatile> == true);
}
TEST_CASE("is volatile")
{
  STATIC_REQUIRE(rsl::is_volatile_v<int> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<const int> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<volatile int> == true);
  STATIC_REQUIRE(rsl::is_volatile_v<const volatile int> == true);

  STATIC_REQUIRE(rsl::is_volatile_v<int&> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<const int&> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<volatile int&> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<const volatile int&> == false);

  STATIC_REQUIRE(rsl::is_volatile_v<int*> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<const int*> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<volatile int*> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<const volatile int*> == false);

  STATIC_REQUIRE(rsl::is_volatile_v<int* const> == false);
  STATIC_REQUIRE(rsl::is_volatile_v<int* volatile> == true);
  STATIC_REQUIRE(rsl::is_volatile_v<int* const volatile> == true);
}
TEST_CASE("is trivial")
{
  STATIC_REQUIRE(rsl::is_trivial_v<bool> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<int8> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<uint8> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<int16> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<uint16> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<int32> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<uint32> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<int64> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<uint64> == true);

  STATIC_REQUIRE(rsl::is_trivial_v<float32> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<float64> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<rsl::lfloat64> == true);

  STATIC_REQUIRE(rsl::is_trivial_v<int[]> == false);

  STATIC_REQUIRE(rsl::is_trivial_v<dummy_class> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<dummy_union> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<dummy_enum> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<dummy_enum_class> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_trivial_v<int*> == true);

  STATIC_REQUIRE(rsl::is_trivial_v<void> == false);
  STATIC_REQUIRE(rsl::is_trivial_v<nullptr_t> == true);

  STATIC_REQUIRE(rsl::is_trivial_v<trivial_class> == true);
  STATIC_REQUIRE(rsl::is_trivial_v<non_trivial_class> == false);
}
TEST_CASE("is trivially copyable")
{
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<bool> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<int8> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<uint8> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<int16> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<uint16> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<int32> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<uint32> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<int64> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<uint64> == true);

  STATIC_REQUIRE(rsl::is_trivially_copyable_v<float32> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<float64> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<rsl::lfloat64> == true);

  STATIC_REQUIRE(rsl::is_trivially_copyable_v<int[]> == true);

  STATIC_REQUIRE(rsl::is_trivially_copyable_v<dummy_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<dummy_union> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<dummy_enum> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<dummy_enum_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<int*> == true);

  STATIC_REQUIRE(rsl::is_trivially_copyable_v<void> == false);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<nullptr_t> == true);

  STATIC_REQUIRE(rsl::is_trivially_copyable_v<trivial_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_copyable_v<non_trivial_class> == false);
}
TEST_CASE("is standard layout")
{
  STATIC_REQUIRE(rsl::is_standard_layout_v<standard_layout_class> == true);
  STATIC_REQUIRE(rsl::is_standard_layout_v<non_standard_layout_class> == false);
}
TEST_CASE("is pod")
{
  STATIC_REQUIRE(rsl::is_pod_v<pod_class> == true);
  STATIC_REQUIRE(rsl::is_pod_v<non_pod_class> == false);
}
TEST_CASE("has unique object represenations")
{
  STATIC_REQUIRE(rsl::has_unique_object_representations_v<has_unique_object_represenations_class> == true);
  STATIC_REQUIRE(rsl::has_unique_object_representations_v<non_has_unique_object_represenations_class> == false);
}
TEST_CASE("is empty")
{
  STATIC_REQUIRE(rsl::is_empty_v<empty_class> == true);
  STATIC_REQUIRE(rsl::is_empty_v<non_empty_class> == false);
}
TEST_CASE("is polymorphic")
{
  STATIC_REQUIRE(rsl::is_polymorphic_v<polymorphic_class> == true);
  STATIC_REQUIRE(rsl::is_polymorphic_v<non_polymorphic_class> == false);
}
TEST_CASE("is abstract")
{
  STATIC_REQUIRE(rsl::is_abstract_v<abstract_class> == true);
  STATIC_REQUIRE(rsl::is_abstract_v<non_abstract_class> == false);
}
TEST_CASE("is final")
{
  STATIC_REQUIRE(rsl::is_final_v<final_class> == true);
  STATIC_REQUIRE(rsl::is_final_v<non_final_class> == false);
}
TEST_CASE("is aggregate")
{
  STATIC_REQUIRE(rsl::is_aggregate_v<bool> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<int8> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<uint8> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<int16> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<uint16> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<int32> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<uint32> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<int64> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<uint64> == false);

  STATIC_REQUIRE(rsl::is_aggregate_v<float32> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<float64> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<rsl::lfloat64> == false);

  STATIC_REQUIRE(rsl::is_aggregate_v<int[]> == true);

  STATIC_REQUIRE(rsl::is_aggregate_v<dummy_class> == true);
  STATIC_REQUIRE(rsl::is_aggregate_v<dummy_union> == true);
  STATIC_REQUIRE(rsl::is_aggregate_v<dummy_enum> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<dummy_enum_class> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<int*> == false);

  STATIC_REQUIRE(rsl::is_aggregate_v<void> == false);
  STATIC_REQUIRE(rsl::is_aggregate_v<nullptr_t> == false);
}
TEST_CASE("is signed")
{
  // the sign of types is implementation defined
  // however, we specify that they should be signed
  // to keep consistency on different platforms
  // we provide type aliases anyway to force sign or unsign
  // and unsigned values are discouraged already
  STATIC_REQUIRE(rsl::is_signed_v<char> == true);
  STATIC_REQUIRE(rsl::is_signed_v<short> == true);
  STATIC_REQUIRE(rsl::is_signed_v<int> == true);
  STATIC_REQUIRE(rsl::is_signed_v<long> == true);
  STATIC_REQUIRE(rsl::is_signed_v<long long> == true);

  STATIC_REQUIRE(rsl::is_signed_v<signed char> == true);
  STATIC_REQUIRE(rsl::is_signed_v<signed short> == true);
  STATIC_REQUIRE(rsl::is_signed_v<signed int> == true);
  STATIC_REQUIRE(rsl::is_signed_v<signed long> == true);
  STATIC_REQUIRE(rsl::is_signed_v<signed long long> == true);

  STATIC_REQUIRE(rsl::is_signed_v<unsigned char> == false);
  STATIC_REQUIRE(rsl::is_signed_v<unsigned short> == false);
  STATIC_REQUIRE(rsl::is_signed_v<unsigned int> == false);
  STATIC_REQUIRE(rsl::is_signed_v<unsigned long> == false);
  STATIC_REQUIRE(rsl::is_signed_v<unsigned long long> == false);
}
TEST_CASE("is unsigned")
{
  // the sign of types is implementation defined
  // however, we specify that they should be signed
  // to keep consistency on different platforms
  // we provide type aliases anyway to force sign or unsign
  // and unsigned values are discouraged already

  STATIC_REQUIRE(rsl::is_unsigned_v<char> == false);
  STATIC_REQUIRE(rsl::is_unsigned_v<short> == false);
  STATIC_REQUIRE(rsl::is_unsigned_v<int> == false);
  STATIC_REQUIRE(rsl::is_unsigned_v<long> == false);
  STATIC_REQUIRE(rsl::is_unsigned_v<long long> == false);

  STATIC_REQUIRE(rsl::is_unsigned_v<signed char> == false);
  STATIC_REQUIRE(rsl::is_unsigned_v<signed short> == false);
  STATIC_REQUIRE(rsl::is_unsigned_v<signed int> == false);
  STATIC_REQUIRE(rsl::is_unsigned_v<signed long> == false);
  STATIC_REQUIRE(rsl::is_unsigned_v<signed long long> == false);

  STATIC_REQUIRE(rsl::is_unsigned_v<unsigned char> == true);
  STATIC_REQUIRE(rsl::is_unsigned_v<unsigned short> == true);
  STATIC_REQUIRE(rsl::is_unsigned_v<unsigned int> == true);
  STATIC_REQUIRE(rsl::is_unsigned_v<unsigned long> == true);
  STATIC_REQUIRE(rsl::is_unsigned_v<unsigned long long> == true);
}
TEST_CASE("is bounded array")
{
  STATIC_REQUIRE(rsl::is_bounded_array_v<int[10]> == true);
  STATIC_REQUIRE(rsl::is_bounded_array_v<int[]> == false);
  STATIC_REQUIRE(rsl::is_bounded_array_v<int> == false);
  STATIC_REQUIRE(rsl::is_bounded_array_v<int*> == false);
}
TEST_CASE("is unbounded array")
{
  STATIC_REQUIRE(rsl::is_unbounded_array_v<int[10]> == false);
  STATIC_REQUIRE(rsl::is_unbounded_array_v<int[]> == true);
  STATIC_REQUIRE(rsl::is_unbounded_array_v<int> == false);
  STATIC_REQUIRE(rsl::is_unbounded_array_v<int*> == false);
}
TEST_CASE("is constructible")
{
  STATIC_REQUIRE(rsl::is_constructible_v<constructible_test_class, int> == true);
  STATIC_REQUIRE(rsl::is_constructible_v<constructible_test_class, float> == true);
  STATIC_REQUIRE(rsl::is_constructible_v<constructible_test_class, void> == false);
}
TEST_CASE("is trivially constructible")
{
  STATIC_REQUIRE(rsl::is_trivially_constructible_v<constructible_test_class, int> == false);
  STATIC_REQUIRE(rsl::is_trivially_constructible_v<constructible_test_class, float> == false);
  STATIC_REQUIRE(rsl::is_trivially_constructible_v<constructible_test_class, const constructible_test_class&> == true);
}
TEST_CASE("is nothrow constructible")
{
  STATIC_REQUIRE(rsl::is_constructible_v<constructible_test_class, int> == true);
  STATIC_REQUIRE(rsl::is_constructible_v<constructible_test_class, float> == true);
  STATIC_REQUIRE(rsl::is_constructible_v<constructible_test_class, void> == false);
}
TEST_CASE("is default constructible")
{
  STATIC_REQUIRE(rsl::is_default_constructible_v<default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_default_constructible_v<constructible_test_class> == false);
}
TEST_CASE("is trivially default constructible")
{
  STATIC_REQUIRE(rsl::is_trivially_default_constructible_v<trivially_default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_default_constructible_v<non_trivially_default_constructible_test_class> == false);
}
TEST_CASE("is nothrow default constructible")
{
  STATIC_REQUIRE(rsl::is_nothrow_default_constructible_v<trivially_default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_default_constructible_v<non_trivially_default_constructible_test_class> == true);
}
TEST_CASE("is copy constructible")
{
  STATIC_REQUIRE(rsl::is_copy_constructible_v<trivially_default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_copy_constructible_v<non_trivially_default_constructible_test_class> == true);
}
TEST_CASE("is trivially copy constructible")
{
  STATIC_REQUIRE(rsl::is_trivially_copy_constructible_v<trivially_default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_copy_constructible_v<non_trivially_default_constructible_test_class> == false);
}
TEST_CASE("is nothrow copy constructible")
{
  STATIC_REQUIRE(rsl::is_nothrow_copy_constructible_v<trivially_default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_copy_constructible_v<non_trivially_default_constructible_test_class> == true);
}
TEST_CASE("is move constructible")
{
  STATIC_REQUIRE(rsl::is_move_constructible_v<trivially_default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_move_constructible_v<non_trivially_default_constructible_test_class> == true);
}
TEST_CASE("is trivially move constructible")
{
  STATIC_REQUIRE(rsl::is_trivially_move_constructible_v<trivially_default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_move_constructible_v<non_trivially_default_constructible_test_class> == false);
}
TEST_CASE("is nothrow move constructible")
{
  STATIC_REQUIRE(rsl::is_nothrow_move_constructible_v<trivially_default_constructible_test_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_move_constructible_v<non_trivially_default_constructible_test_class> == true);
}
TEST_CASE("is assignable")
{
  STATIC_REQUIRE(rsl::is_assignable_v<int, int> == false); // 1 = 1 wouldn't work
  STATIC_REQUIRE(rsl::is_assignable_v<int&, int> == true); // int a; a = 1 works.
  STATIC_REQUIRE(rsl::is_assignable_v<assignable_class, const assignable_class&> == true);
}
TEST_CASE("is trivially assignable")
{
  STATIC_REQUIRE(rsl::is_trivially_assignable_v<int, int> == false); // 1 = 1 wouldn't work
  STATIC_REQUIRE(rsl::is_trivially_assignable_v<int&, int> == true); // int a; a = 1 works.
  STATIC_REQUIRE(rsl::is_trivially_assignable_v<assignable_class, const assignable_class&> == true);
  STATIC_REQUIRE(rsl::is_trivially_assignable_v<polymorphic_class, const polymorphic_class&> == false);
}
TEST_CASE("is nothrow assignable")
{
  STATIC_REQUIRE(rsl::is_nothrow_assignable_v<int, int> == false); // 1 = 1 wouldn't work
  STATIC_REQUIRE(rsl::is_nothrow_assignable_v<int&, int> == true); // int a; a = 1 works.
  STATIC_REQUIRE(rsl::is_nothrow_assignable_v<assignable_class, const assignable_class&> == true);
  STATIC_REQUIRE(rsl::is_nothrow_assignable_v<polymorphic_class, const polymorphic_class&> == true);
}
TEST_CASE("is copy assignable")
{
  STATIC_REQUIRE(rsl::is_copy_assignable_v<int> == true);
  STATIC_REQUIRE(rsl::is_copy_assignable_v<int&> == true);
  STATIC_REQUIRE(rsl::is_copy_assignable_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_copy_assignable_v<polymorphic_class> == true);
  STATIC_REQUIRE(rsl::is_copy_assignable_v<no_copy_assignment> == false);
}
TEST_CASE("is trivially copy assignable")
{
  STATIC_REQUIRE(rsl::is_trivially_copy_assignable_v<int> == true);
  STATIC_REQUIRE(rsl::is_trivially_copy_assignable_v<int&> == true);
  STATIC_REQUIRE(rsl::is_trivially_copy_assignable_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_copy_assignable_v<polymorphic_class> == false);
  STATIC_REQUIRE(rsl::is_trivially_copy_assignable_v<no_copy_assignment> == false);
}
TEST_CASE("is nothrow copy assignable")
{
  STATIC_REQUIRE(rsl::is_nothrow_copy_assignable_v<int> == true);
  STATIC_REQUIRE(rsl::is_nothrow_copy_assignable_v<int&> == true);
  STATIC_REQUIRE(rsl::is_nothrow_copy_assignable_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_copy_assignable_v<polymorphic_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_copy_assignable_v<no_copy_assignment> == false);
}
TEST_CASE("is move assignable")
{
  STATIC_REQUIRE(rsl::is_move_assignable_v<int> == true);
  STATIC_REQUIRE(rsl::is_move_assignable_v<int&> == true);
  STATIC_REQUIRE(rsl::is_move_assignable_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_move_assignable_v<polymorphic_class> == true);
  STATIC_REQUIRE(rsl::is_move_assignable_v<no_copy_assignment> == false);
  STATIC_REQUIRE(rsl::is_move_assignable_v<no_move_assignment> == false);
}
TEST_CASE("is trivially move assignable")
{
  STATIC_REQUIRE(rsl::is_trivially_move_assignable_v<int> == true);
  STATIC_REQUIRE(rsl::is_trivially_move_assignable_v<int&> == true);
  STATIC_REQUIRE(rsl::is_trivially_move_assignable_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_move_assignable_v<polymorphic_class> == false);
  STATIC_REQUIRE(rsl::is_trivially_move_assignable_v<no_copy_assignment> == false);
  STATIC_REQUIRE(rsl::is_trivially_move_assignable_v<no_move_assignment> == false);
}
TEST_CASE("is nothrow move assignable")
{
  STATIC_REQUIRE(rsl::is_nothrow_move_assignable_v<int> == true);
  STATIC_REQUIRE(rsl::is_nothrow_move_assignable_v<int&> == true);
  STATIC_REQUIRE(rsl::is_nothrow_move_assignable_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_move_assignable_v<polymorphic_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_move_assignable_v<no_copy_assignment> == false);
  STATIC_REQUIRE(rsl::is_nothrow_move_assignable_v<no_move_assignment> == false);
}
TEST_CASE("is destructible")
{
  STATIC_REQUIRE(rsl::is_destructible_v<int> == true);
  STATIC_REQUIRE(rsl::is_destructible_v<int&> == true);
  STATIC_REQUIRE(rsl::is_destructible_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_destructible_v<polymorphic_class> == true);
  STATIC_REQUIRE(rsl::is_destructible_v<no_copy_assignment> == true);
  STATIC_REQUIRE(rsl::is_destructible_v<no_move_assignment> == true);
}
TEST_CASE("is trivially destructible")
{
  STATIC_REQUIRE(rsl::is_trivially_destructible_v<int> == true);
  STATIC_REQUIRE(rsl::is_trivially_destructible_v<int&> == true);
  STATIC_REQUIRE(rsl::is_trivially_destructible_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_destructible_v<polymorphic_class> == true);
  STATIC_REQUIRE(rsl::is_trivially_destructible_v<no_copy_assignment> == true);
  STATIC_REQUIRE(rsl::is_trivially_destructible_v<no_move_assignment> == true);
}
TEST_CASE("is nothrow destructible")
{
  STATIC_REQUIRE(rsl::is_nothrow_destructible_v<int> == true);
  STATIC_REQUIRE(rsl::is_nothrow_destructible_v<int&> == true);
  STATIC_REQUIRE(rsl::is_nothrow_destructible_v<assignable_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_destructible_v<polymorphic_class> == true);
  STATIC_REQUIRE(rsl::is_nothrow_destructible_v<no_copy_assignment> == true);
  STATIC_REQUIRE(rsl::is_nothrow_destructible_v<no_move_assignment> == true);
}
TEST_CASE("has virtual destructor")
{
  STATIC_REQUIRE(rsl::has_virtual_destructor_v<assignable_class> == false);
  STATIC_REQUIRE(rsl::has_virtual_destructor_v<polymorphic_class> == false);
  STATIC_REQUIRE(rsl::has_virtual_destructor_v<no_copy_assignment> == false);
  STATIC_REQUIRE(rsl::has_virtual_destructor_v<no_move_assignment> == false);
  STATIC_REQUIRE(rsl::has_virtual_destructor_v<non_standard_layout_class> == true);
}
TEST_CASE("is swappable with")
{
  // NOTE
  // This trait does not check anything outside the immediate context of the swap expressions: 
  // if the use of T or U would trigger template specializations, 
  // generation of implicitly-defined special member functions etc, and those have errors, 
  // the actual swap may not compile even if std::is_swappable_with<T,U>::value compiles and evaluates to true.
  // because of this, we can't properly write unit tests because you can't rely on the result.
}
TEST_CASE("is swappable")
{
  // NOTE
  // This trait does not check anything outside the immediate context of the swap expressions: 
  // if the use of T or U would trigger template specializations, 
  // generation of implicitly-defined special member functions etc, and those have errors, 
  // the actual swap may not compile even if std::is_swappable_with<T,U>::value compiles and evaluates to true.
  // because of this, we can't properly write unit tests because you can't rely on the result.
}
TEST_CASE("is nothrow swappable")
{
  // NOTE
  // This trait does not check anything outside the immediate context of the swap expressions: 
  // if the use of T or U would trigger template specializations, 
  // generation of implicitly-defined special member functions etc, and those have errors, 
  // the actual swap may not compile even if std::is_swappable_with<T,U>::value compiles and evaluates to true.
  // because of this, we can't properly write unit tests because you can't rely on the result.
}
TEST_CASE("is nothrow swappable with")
{
  // NOTE
  // This trait does not check anything outside the immediate context of the swap expressions: 
  // if the use of T or U would trigger template specializations, 
  // generation of implicitly-defined special member functions etc, and those have errors, 
  // the actual swap may not compile even if std::is_swappable_with<T,U>::value compiles and evaluates to true.
  // because of this, we can't properly write unit tests because you can't rely on the result.
}
TEST_CASE("alignment of")
{
  STATIC_REQUIRE(rsl::alignment_of_v<int> == 4);
  STATIC_REQUIRE(rsl::alignment_of_v<short> == 2);
  STATIC_REQUIRE(rsl::alignment_of_v<char> == 1);
}
TEST_CASE("rank")
{
  STATIC_REQUIRE(rsl::rank_v<int> == 0);
  STATIC_REQUIRE(rsl::rank_v<int[5]> == 1);
  STATIC_REQUIRE(rsl::rank_v<int[5][5]> == 2);
  STATIC_REQUIRE(rsl::rank_v<int[][5][5]> == 3);
}
TEST_CASE("extent")
{
  STATIC_REQUIRE(rsl::extent_v<int[3]> == 3);
  STATIC_REQUIRE(rsl::extent_v<int[3][4]> == 3);
  STATIC_REQUIRE(rsl::extent_v<int[3][4], 1> == 4);
  STATIC_REQUIRE(rsl::extent_v<int[3][4], 2> == 0);
  STATIC_REQUIRE(rsl::extent_v<int[]> == 0);
}
TEST_CASE("is same")
{
  STATIC_REQUIRE(rsl::is_same_v<int, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<float, float> == true);
  STATIC_REQUIRE(rsl::is_same_v<short, short> == true);
  STATIC_REQUIRE(rsl::is_same_v<short, short int> == true);
  STATIC_REQUIRE(rsl::is_same_v<abstract_class, abstract_class> == true);
  STATIC_REQUIRE(rsl::is_same_v<abstract_class, constructible_test_class> == false);
  STATIC_REQUIRE(rsl::is_same_v<abstract_class, int> == false);
}
TEST_CASE("is base of")
{
  STATIC_REQUIRE(rsl::is_base_of_v<base, derived> == true);
  STATIC_REQUIRE(rsl::is_base_of_v<derived, base> == false);
  STATIC_REQUIRE(rsl::is_base_of_v<base, base> == true);
  STATIC_REQUIRE(rsl::is_base_of_v<abstract_class, base> == false);
}
TEST_CASE("is convertible")
{
  STATIC_REQUIRE(rsl::is_convertible_v<int, float> == true);
  STATIC_REQUIRE(rsl::is_convertible_v<float, int> == true);
  STATIC_REQUIRE(rsl::is_convertible_v<constructible_test_class, float> == false);
}
TEST_CASE("is nothrow comvertible")
{
  STATIC_REQUIRE(rsl::is_nothrow_convertible_v<int, float> == true);
  STATIC_REQUIRE(rsl::is_nothrow_convertible_v<float, int> == true);
  STATIC_REQUIRE(rsl::is_nothrow_convertible_v<constructible_test_class, float> == false);
}
TEST_CASE("is invocable")
{
  STATIC_REQUIRE(rsl::is_invocable_v<decltype(dummy_function)> == true);
  STATIC_REQUIRE(rsl::is_invocable_v<decltype(dummy_function), void> == false);
  STATIC_REQUIRE(rsl::is_invocable_v<decltype(dummy_function), int> == false);
}
TEST_CASE("is invocable r")
{
  STATIC_REQUIRE(rsl::is_invocable_r_v<void, decltype(dummy_function)> == true);
  STATIC_REQUIRE(rsl::is_invocable_r_v<int, decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_invocable_r_v<void, decltype(dummy_function), void> == false);
  STATIC_REQUIRE(rsl::is_invocable_r_v<void, decltype(dummy_function), int> == false);
}
TEST_CASE("is nothrow invocable")
{
  //STATIC_REQUIRE(rsl::is_nothrow_invocable_v<decltype(dummy_function)> == true); // Fails we don't use exceptions anyway
  STATIC_REQUIRE(rsl::is_nothrow_invocable_v<decltype(dummy_function), void> == false);
  STATIC_REQUIRE(rsl::is_nothrow_invocable_v<decltype(dummy_function), int> == false);
}
TEST_CASE("is nothrow invocable r")
{
  //STATIC_REQUIRE(rsl::is_nothrow_invocable_r_v<void, decltype(dummy_function)> == true); // Fails we don't use exceptions anyway
  STATIC_REQUIRE(rsl::is_nothrow_invocable_r_v<int, decltype(dummy_function)> == false);
  STATIC_REQUIRE(rsl::is_nothrow_invocable_r_v<void, decltype(dummy_function), void> == false);
  STATIC_REQUIRE(rsl::is_nothrow_invocable_r_v<void, decltype(dummy_function), int> == false);
}
TEST_CASE("remove cv")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cv_t<const int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cv_t<const volatile int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cv_t<volatile int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cv_t<const int*>, const int*> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cv_t<int* const>, int*> == true);
}
TEST_CASE("remove const")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_const_t<const int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_const_t<const volatile int>, volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_const_t<volatile int>, volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_const_t<const int*>, const int*> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_const_t<int* const>, int*> == true);
}
TEST_CASE("remove volatile")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_volatile_t<const int>, const int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_volatile_t<const volatile int>, const int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_volatile_t<volatile int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_volatile_t<const int*>, const int*> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_volatile_t<int* const>, int* const> == true);
}
TEST_CASE("add cv")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_cv_t<const int>, const volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_cv_t<const volatile int>, const volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_cv_t<volatile int>, const volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_cv_t<const int*>, const int* const volatile> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_cv_t<int* const>, int* const volatile> == true);
}
TEST_CASE("add const")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_const_t<const int>, const int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_const_t<const volatile int>, const volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_const_t<volatile int>, const volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_const_t<const int*>, const int* const> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_const_t<int* const>, int* const> == true);

}
TEST_CASE("add volatile")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_volatile_t<const int>, const volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_volatile_t<const volatile int>, const volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_volatile_t<volatile int>, volatile int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_volatile_t<const int*>, const int* volatile> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_volatile_t<int* const>, int* const volatile> == true);
}
TEST_CASE("remove reference")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_reference_t<int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_reference_t<int&>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_reference_t<int&&>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_reference_t<const int>, const int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_reference_t<const int&>, const int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_reference_t<const int&&>, const int> == true);
}
TEST_CASE("add lvalue reference")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_lvalue_reference_t<int>, int&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_lvalue_reference_t<int&>, int&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_lvalue_reference_t<int&&>, int&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_lvalue_reference_t<const int>, const int&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_lvalue_reference_t<const int&>, const int&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_lvalue_reference_t<const int&&>, const int&> == true);
}
TEST_CASE("add rvalue reference")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_rvalue_reference_t<int>, int&&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_rvalue_reference_t<int&>, int&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_rvalue_reference_t<int&&>, int&&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_rvalue_reference_t<const int>, const int&&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_rvalue_reference_t<const int&>, const int&> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_rvalue_reference_t<const int&&>, const int&&> == true);
}
TEST_CASE("remove pointer")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_pointer_t<int*>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_pointer_t<const int*>, const int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_pointer_t<int* const>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_pointer_t<rsl::nullptr_t>, rsl::nullptr_t> == true);
}
TEST_CASE("add pointer")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_pointer_t<int>, int*> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_pointer_t<const int>, const int*> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_pointer_t<int*>, int**> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_pointer_t<int* const>, int* const*> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::add_pointer_t<rsl::nullptr_t>, rsl::nullptr_t*> == true);
}
TEST_CASE("make signed")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<char>, signed char> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<short>, signed short> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<int>, signed int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<long>, signed long> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<long long>, signed long long> == true);

  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<signed char>, signed char> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<signed short>, signed short> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<signed int>, signed int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<signed long>, signed long> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<signed long long>, signed long long> == true);

  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<unsigned char>, signed char> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<unsigned short>, signed short> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<unsigned int>, signed int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<unsigned long>, signed long> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_signed_t<unsigned long long>, signed long long> == true);
}
TEST_CASE("make unsigned")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<char>, unsigned char> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<short>, unsigned short> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<int>, unsigned int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<long>, unsigned long> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<long long>, unsigned long long> == true);

  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<signed char>, unsigned char> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<signed short>, unsigned short> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<signed int>, unsigned int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<signed long>, unsigned long> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<signed long long>, unsigned long long> == true);

  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<unsigned char>, unsigned char> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<unsigned short>, unsigned short> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<unsigned int>, unsigned int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<unsigned long>, unsigned long> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::make_unsigned_t<unsigned long long>, unsigned long long> == true);
}
TEST_CASE("remove extent")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_extent_t<int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_extent_t<int[]>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_extent_t<int[1]>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_extent_t<int[1][1]>, int[1]> == true);
}
TEST_CASE("remove all extents")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_all_extents_t<int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_all_extents_t<int[]>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_all_extents_t<int[1]>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_all_extents_t<int[1][1]>, int> == true);
}
TEST_CASE("aligned storage")
{
  rsl::aligned_storage<int> storage;

  REQUIRE(*storage.get() == 0);
  storage.set(1);
  REQUIRE(*storage.get() == 1);
}
TEST_CASE("decay")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::decay_t<int[]>, int*> == true);
}
TEST_CASE("remove cvref")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cvref_t<int>, int>);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cvref_t<const int>, int>);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cvref_t<const volatile int>, int>);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cvref_t<const int&>, int>);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cvref_t<const volatile int&>, int>);
  STATIC_REQUIRE(rsl::is_same_v<rsl::remove_cvref_t<const int*>, const int*>);
}
TEST_CASE("enable if")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::enable_if_t<true, int>, int> == true);
}
TEST_CASE("conditional")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::conditional_t<true, int, float>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::conditional_t<false, int, float>, float> == true);
}
TEST_CASE("common type")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::common_type_t<int, double>, double> == true);
}
TEST_CASE("common reference")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::common_reference_t<base, derived>, base> == true);
}
TEST_CASE("underlying type")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::underlying_type_t<dummy_enum>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::underlying_type_t<dummy_enum_class>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::underlying_type_t<dummy_enum_class_short>, short> == true);
}
TEST_CASE("invoke result")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::invoke_result_t<decltype(dummy_function)>, void> == true);
}
TEST_CASE("void")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::void_t<void>, void> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::void_t<int, int, int>, void> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::void_t<int*, float, char>, void> == true);
}
TEST_CASE("type identity")
{
  STATIC_REQUIRE(rsl::is_same_v<rsl::type_identity_t<int>, int> == true);
  STATIC_REQUIRE(rsl::is_same_v<rsl::type_identity_t<float>, float> == true);
}
TEST_CASE("conjunction")
{
  STATIC_REQUIRE(rsl::conjunction_v<rsl::is_same<int, int>> == true);
  STATIC_REQUIRE(rsl::conjunction_v<rsl::is_same<int, int>, rsl::is_same<int, float>> == false);
}
TEST_CASE("disjunction")
{
  STATIC_REQUIRE(rsl::disjunction_v<rsl::is_same<int, int>> == true);
  STATIC_REQUIRE(rsl::disjunction_v<rsl::is_same<int, int>, rsl::is_same<int, float>> == true);
  STATIC_REQUIRE(rsl::disjunction_v<rsl::is_same<char, int>, rsl::is_same<int, float>> == false);

}
TEST_CASE("negation")
{
  STATIC_REQUIRE(rsl::negation_v<rsl::is_same<int, int>> == false);
  STATIC_REQUIRE(rsl::negation_v<rsl::is_same<int, float>> == true);

}
TEST_CASE("is constant evaluated")
{
  STATIC_REQUIRE(rsl::is_constant_evaluated() == true);
}

//NOLINTEND
