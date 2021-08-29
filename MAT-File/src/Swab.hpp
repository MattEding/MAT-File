#pragma once

#include "TypeDefs.h"

namespace mat {

template < typename T >
[[ nodiscard ]] inline constexpr
auto swab( T const & field ) noexcept -> T;

template < auto func,
           typename T >
[[ nodiscard ]] inline constexpr
auto swab_impl( T const & field ) noexcept -> T;

[[ nodiscard ]] inline constexpr
auto swab16( u16 const bytes ) noexcept -> u16;

[[ nodiscard ]] inline constexpr
auto swab32( u32 const bytes ) noexcept -> u32;

[[ nodiscard ]] inline constexpr
auto swab64( u64 const bytes ) noexcept -> u64;

} /* mat */

#include <Swab.inl>
