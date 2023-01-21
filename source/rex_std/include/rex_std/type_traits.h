// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: type_traits.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/add_const.h"
#include "rex_std/internal/type_traits/add_cv.h"
#include "rex_std/internal/type_traits/add_lvalue_reference.h"
#include "rex_std/internal/type_traits/add_pointer.h"
#include "rex_std/internal/type_traits/add_rvalue_reference.h"
#include "rex_std/internal/type_traits/add_volatile.h"
#include "rex_std/internal/type_traits/aligned_storage.h"
#include "rex_std/internal/type_traits/alignment_of.h"
#include "rex_std/internal/type_traits/basic_common_reference.h"
#include "rex_std/internal/type_traits/common_reference.h"
#include "rex_std/internal/type_traits/common_type.h"
#include "rex_std/internal/type_traits/conditional.h"
#include "rex_std/internal/type_traits/conjunction.h"
#include "rex_std/internal/type_traits/decay.h"
#include "rex_std/internal/type_traits/disjunction.h"
#include "rex_std/internal/type_traits/enable_if.h"
#include "rex_std/internal/type_traits/extent.h"
#include "rex_std/internal/type_traits/has_unique_object_representations.h"
#include "rex_std/internal/type_traits/has_virtual_destructor.h"
#include "rex_std/internal/type_traits/invoke_result.h"
#include "rex_std/internal/type_traits/is_abstract.h"
#include "rex_std/internal/type_traits/is_aggregate.h"
#include "rex_std/internal/type_traits/is_arithmetic.h"
#include "rex_std/internal/type_traits/is_array.h"
#include "rex_std/internal/type_traits/is_assignable.h"
#include "rex_std/internal/type_traits/is_base_of.h"
#include "rex_std/internal/type_traits/is_bounded_array.h"
#include "rex_std/internal/type_traits/is_class.h"
#include "rex_std/internal/type_traits/is_compound.h"
#include "rex_std/internal/type_traits/is_const.h"
#include "rex_std/internal/type_traits/is_constant_evaluated.h"
#include "rex_std/internal/type_traits/is_constructible.h"
#include "rex_std/internal/type_traits/is_convertible.h"
#include "rex_std/internal/type_traits/is_copy_assignable.h"
#include "rex_std/internal/type_traits/is_copy_constructible.h"
#include "rex_std/internal/type_traits/is_corresponding_member.h"
#include "rex_std/internal/type_traits/is_default_constructible.h"
#include "rex_std/internal/type_traits/is_destructible.h"
#include "rex_std/internal/type_traits/is_empty.h"
#include "rex_std/internal/type_traits/is_enum.h"
#include "rex_std/internal/type_traits/is_final.h"
#include "rex_std/internal/type_traits/is_floating_point.h"
#include "rex_std/internal/type_traits/is_function.h"
#include "rex_std/internal/type_traits/is_fundamental.h"
#include "rex_std/internal/type_traits/is_integral.h"
#include "rex_std/internal/type_traits/is_invocable.h"
#include "rex_std/internal/type_traits/is_invocable_r.h"
#include "rex_std/internal/type_traits/is_layout_compatible.h"
#include "rex_std/internal/type_traits/is_lvalue_reference.h"
#include "rex_std/internal/type_traits/is_member_function_pointer.h"
#include "rex_std/internal/type_traits/is_member_object_pointer.h"
#include "rex_std/internal/type_traits/is_member_pointer.h"
#include "rex_std/internal/type_traits/is_move_assignable.h"
#include "rex_std/internal/type_traits/is_move_constructible.h"
#include "rex_std/internal/type_traits/is_nothrow_assignable.h"
#include "rex_std/internal/type_traits/is_nothrow_constructible.h"
#include "rex_std/internal/type_traits/is_nothrow_convertible.h"
#include "rex_std/internal/type_traits/is_nothrow_copy_assignable.h"
#include "rex_std/internal/type_traits/is_nothrow_copy_constructible.h"
#include "rex_std/internal/type_traits/is_nothrow_default_constructible.h"
#include "rex_std/internal/type_traits/is_nothrow_destructible.h"
#include "rex_std/internal/type_traits/is_nothrow_invocable.h"
#include "rex_std/internal/type_traits/is_nothrow_invocable_r.h"
#include "rex_std/internal/type_traits/is_nothrow_move_assignable.h"
#include "rex_std/internal/type_traits/is_nothrow_move_constructible.h"
#include "rex_std/internal/type_traits/is_nothrow_swappable.h"
#include "rex_std/internal/type_traits/is_nothrow_swappable_with.h"
#include "rex_std/internal/type_traits/is_object.h"
#include "rex_std/internal/type_traits/is_pod.h"
#include "rex_std/internal/type_traits/is_pointer.h"
#include "rex_std/internal/type_traits/is_pointer_interconvertible_base_of.h"
#include "rex_std/internal/type_traits/is_pointer_interconvertible_with_class.h"
#include "rex_std/internal/type_traits/is_polymorphic.h"
#include "rex_std/internal/type_traits/is_reference.h"
#include "rex_std/internal/type_traits/is_rvalue_reference.h"
#include "rex_std/internal/type_traits/is_same.h"
#include "rex_std/internal/type_traits/is_scalar.h"
#include "rex_std/internal/type_traits/is_scoped_enum.h"
#include "rex_std/internal/type_traits/is_signed.h"
#include "rex_std/internal/type_traits/is_standard_layout.h"
#include "rex_std/internal/type_traits/is_swappable.h"
#include "rex_std/internal/type_traits/is_swappable_with.h"
#include "rex_std/internal/type_traits/is_trivial.h"
#include "rex_std/internal/type_traits/is_trivially_assignable.h"
#include "rex_std/internal/type_traits/is_trivially_constructible.h"
#include "rex_std/internal/type_traits/is_trivially_copy_assignable.h"
#include "rex_std/internal/type_traits/is_trivially_copy_constructible.h"
#include "rex_std/internal/type_traits/is_trivially_copyable.h"
#include "rex_std/internal/type_traits/is_trivially_default_constructible.h"
#include "rex_std/internal/type_traits/is_trivially_destructible.h"
#include "rex_std/internal/type_traits/is_trivially_move_assignable.h"
#include "rex_std/internal/type_traits/is_trivially_move_constructible.h"
#include "rex_std/internal/type_traits/is_unbounded_array.h"
#include "rex_std/internal/type_traits/is_union.h"
#include "rex_std/internal/type_traits/is_unsigned.h"
#include "rex_std/internal/type_traits/is_void.h"
#include "rex_std/internal/type_traits/is_volatile.h"
#include "rex_std/internal/type_traits/make_signed.h"
#include "rex_std/internal/type_traits/make_unsigned.h"
#include "rex_std/internal/type_traits/negation.h"
#include "rex_std/internal/type_traits/rank.h"
#include "rex_std/internal/type_traits/remove_all_extents.h"
#include "rex_std/internal/type_traits/remove_const.h"
#include "rex_std/internal/type_traits/remove_cv.h"
#include "rex_std/internal/type_traits/remove_cvref.h"
#include "rex_std/internal/type_traits/remove_extent.h"
#include "rex_std/internal/type_traits/remove_pointer.h"
#include "rex_std/internal/type_traits/remove_reference.h"
#include "rex_std/internal/type_traits/remove_volatile.h"
#include "rex_std/internal/type_traits/type_identity.h"
#include "rex_std/internal/type_traits/underlying_type.h"
#include "rex_std/internal/type_traits/void.h"
