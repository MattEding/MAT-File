#pragma once

#include <type_traits>

namespace mat {

template < typename T >
struct return_type;

template < typename T >
using return_type_t = typename return_type< T >::value_type;

template < typename Return, typename... Args >
struct return_type< Return(*)(Args...) >
{
    using value_type = Return;
};

template < typename Return, typename Class, typename... Args >
struct return_type< Return(Class::*)(Args...) >
{
    using value_type = Return;
};

template < typename Return, typename Class, typename... Args >
struct return_type< Return(Class::*)(Args...) const >
{
    using value_type = Return;
};

} /* mat */
