// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: invoke.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std/internal/type_traits/remove_reference.h"
#include "rex_std/internal/type_traits/is_member_object_pointer.h"
#include "rex_std/internal/type_traits/conditional.h"
#include "rex_std/internal/type_traits/is_base_of.h"

#include "rex_std/internal/functional/reference_wrapper.h"

REX_RSL_BEGIN_NAMESPACE

    namespace internal
    {
        enum class InvokerStrategy
        {
            Functor,
            PmfObject,  // pointer member function object
            PmfRewrap,  // pointer member function rewrap
            PmfPointer, // pointer member function pointer
            PmdObject,  // pointer data member
            PmdRefwrap, // pointer data member
            PmdPointer  // pointer data member
        };

        struct InvokerFunctor
        {
            static constexpr InvokerStrategy Strategy = InvokerStrategy::Functor;

            template <typename Callable, typename... Types>
            static constexpr auto call(Callable &&obj, Types &&...args) -> decltype(static_cast<Callable &&>(obj)(static_cast<Types &&>(args)...))
            {
                return static_cast<Callable &&>(obj)(static_cast<Types &&>(args)...);
            }
        };

        struct InvokerPmfObject
        {
            static constexpr InvokerStrategy Strategy = InvokerStrategy::PmfObject;

            template <typename Decayed, typename T1, typename... Types2>
            static constexpr auto call(Decayed pmf, T1 &&args1, Types2 &&...args2) -> decltype((static_cast<T1 &&>(args1).*pmf)(static_cast<Types2 &&>(args2)...))
            {
                return (static_cast<T1 &&>(args1).*pmf)(static_cast<Types2 &&>(args2)...);
            }
        };

        struct InvokerPmfRewrap
        {
            static constexpr InvokerStrategy Strategy = InvokerStrategy::PmfRewrap;

            template <typename Decayed, typename Refwrap, typename... Types2>
            static constexpr auto call(Decayed pmf, Refwrap rw, Types2 &&...args2) -> decltype((rw.get().*pmf)(static_cast<Types2 &&>(args2)...))
            {
                return (rw.get().*pmf)(static_cast<Types2 &&>(args2)...);
            }
        };

        struct InvokerPmfPointer
        {
            static constexpr InvokerStrategy Strategy = InvokerStrategy::PmfPointer;

            template <typename Decayed, typename T1, typename... Types2>
            static constexpr auto call(Decayed pmf, T1 &&args1, Types2 &&...args2) -> decltype(((*static_cast<T1 &&>(args1)).*pmf)(static_cast<Types2 &&>(args2)...))
            {
                return ((*static_cast<T1 &&>(args1)).*pmf)(static_cast<Types2 &&>(args2)...);
            }
        };

        struct InvokerPmdObject
        {
            static constexpr InvokerStrategy Strategy = InvokerStrategy::PmdObject;

            template <typename Decayed, typename T1>
            static constexpr auto call(Decayed _Pmd, T1 &&args1) noexcept -> decltype(static_cast<T1 &&>(args1).*_Pmd)
            {
                return static_cast<T1 &&>(args1).*_Pmd;
            }
        };

        struct InvokerPmdRefwrap
        {
            static constexpr InvokerStrategy Strategy = InvokerStrategy::PmdRefwrap;

            template <typename Decayed, typename Refwrap>
            static constexpr auto call(Decayed _Pmd, Refwrap rw) noexcept -> decltype(rw.get().*_Pmd)
            {
                return rw.get().*_Pmd;
            }
        };

        struct InvokerPmdPointer
        {
            static constexpr InvokerStrategy Strategy = InvokerStrategy::PmdPointer;

            template <typename Decayed, typename T1>
            static constexpr auto call(Decayed _Pmd, T1 &&args1) -> decltype((*static_cast<T1 &&>(args1)).*_Pmd)
            {
                return (*static_cast<T1 &&>(args1)).*_Pmd;
            }
        };

        template <typename T>
        using RemoveCVRef = remove_cv_t<remove_reference<T>>;

        template <typename Callable, typename T1, typename RemovedCVRef = RemoveCVRef<Callable>,
                  bool IsPmf = is_member_function_pointer_v<RemovedCVRef>,
                  bool IsPmd = is_member_object_pointer_v<RemovedCVRef>>
        struct Invoker1;

        template <typename T, template <typename...> typename Template>
        inline constexpr bool is_specialization_v = false;

        template <template <typename ...> typename Template, typename ... Types>
        inline constexpr bool is_specialization_v<Template<Types...>, Template> = true;

        template <typename Type, template <typename ...> typename Template>
        struct is_specialization : bool_constant<is_specialization_v<Type, Template>>
        {};

        template <typename Callable, typename T1, typename RemovedCVRef>
        struct Invoker1<Callable, T1, RemovedCVRef, true, false>
            : conditional_t<is_base_of_v<typename is_member_function_pointer<RemovedCVRef>::class_type, remove_reference_t<T1>>,
                          InvokerPmfObject,
                          conditional_t<is_specialization_v<RemoveCVRef<T1>, reference_wrapper>, InvokerPmfRewrap,
                                      InvokerPmfPointer>>
        {
        }; // pointer to member function

        template <typename Callable, typename T1, typename RemovedCVRef>
        struct Invoker1<Callable, T1, RemovedCVRef, false, true>
            : conditional_t<
                  is_base_of_v<typename is_member_object_pointer<RemovedCVRef>::class_type, remove_reference<T1>>,
                  InvokerPmdObject,
                  conditional_t<is_specialization_v<RemoveCVRef<T1>, reference_wrapper>, InvokerPmdRefwrap,
                              InvokerPmdPointer>>
        {
        }; // pointer to member data

        template <typename Callable, typename T1, typename RemovedCVRef>
        struct Invoker1<Callable, T1, RemovedCVRef, false, false> : InvokerFunctor
        {
        };
    }

    template <typename Callable>
    constexpr auto invoke(Callable &&obj) -> decltype(static_cast<Callable &&>(obj)())
    {
        return static_cast<Callable &&>(obj)();
    }

    template <typename Callable, typename T1, typename... Types2>
    constexpr auto invoke(Callable &&obj, T1 &&args1, Types2 &&...args2) -> decltype(internal::Invoker1<Callable, T1>::call(static_cast<Callable &&>(obj), static_cast<T1 &&>(args1), static_cast<Types2 &&>(args2)...))
    {
        if constexpr (internal::Invoker1<Callable, T1>::Strategy == internal::InvokerStrategy::Functor)
        {
            return static_cast<Callable &&>(obj)(static_cast<T1 &&>(args1), static_cast<Types2 &&>(args2)...);
        }
        else if constexpr (internal::Invoker1<Callable, T1>::Strategy == internal::InvokerStrategy::PmfObject)
        {
            return (static_cast<T1 &&>(args1).*obj)(static_cast<Types2 &&>(args2)...);
        }
        else if constexpr (internal::Invoker1<Callable, T1>::Strategy == internal::InvokerStrategy::PmfRewrap)
        {
            return (args1.get().*obj)(static_cast<Types2 &&>(args2)...);
        }
        else if constexpr (internal::Invoker1<Callable, T1>::Strategy == internal::InvokerStrategy::PmfPointer)
        {
            return ((*static_cast<T1 &&>(args1)).*obj)(static_cast<Types2 &&>(args2)...);
        }
        else if constexpr (internal::Invoker1<Callable, T1>::Strategy == internal::InvokerStrategy::PmdObject)
        {
            return static_cast<T1 &&>(args1).*obj;
        }
        else if constexpr (internal::Invoker1<Callable, T1>::Strategy == internal::InvokerStrategy::PmdRefwrap)
        {
            return args1.get().*obj;
        }
        else
        {
            static_assert(internal::Invoker1<Callable, T1>::Strategy == internal::InvokerStrategy::PmdPointer, "bug in invoke");
            return (*static_cast<T1 &&>(args1)).*obj;
        }
    }

REX_RSL_END_NAMESPACE
