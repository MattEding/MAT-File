#pragma once

#include "Swab.hpp"
#include "Macros.h"
#include "TypeDefs.h"

#include <array>

#include <cstring>

namespace mat {

template < typename T >
[[ nodiscard ]] inline constexpr
auto swab( T const & field ) noexcept -> T
{
    std::array constexpr funcs{
        swab_impl< &swab16, T >,
        swab_impl< &swab32, T >,
        swab_impl< &swab64, T >,
        };

    std::size_t constexpr I = sizeof( T ) >> 2;
    auto constexpr func = funcs[ I ];
    return func( field );
}

template < auto func,
           typename T >
[[ nodiscard ]] inline constexpr
auto swab_impl( T const & field ) noexcept -> T
{
    using U = decltype( func( { } ) );
    if constexpr ( sizeof( T ) == sizeof( U ) )
    {
        U pre;
        std::memcpy( &pre, &field, sizeof( T ) );
        U post = func( pre );
        T result;
        std::memcpy( &result, &post, sizeof( T ) );
        return result;
    }
    MAT_UNREACHABLE( );
}

[[ nodiscard ]] inline constexpr
auto swab16( u16 const bytes ) noexcept -> u16
{
    #ifdef _WIN32
    return _byteswap_ushort( bytes );
    #else
    return __builtin_bswap16( bytes );
    #endif
}

[[ nodiscard ]] inline constexpr
auto swab32( u32 const bytes ) noexcept -> u32
{
    #ifdef _WIN32
    return _byteswap_ulong( bytes );
    #else
    return __builtin_bswap32( bytes );
    #endif
}

[[ nodiscard ]] inline constexpr
auto swab64( u64 const bytes ) noexcept -> u64
{
    #ifdef _WIN32
    return _byteswap_uint64( bytes );
    #else
    return __builtin_bswap64( bytes );
    #endif
}

} /* mat */
