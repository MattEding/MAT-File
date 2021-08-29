#pragma once

#include <string_view>

namespace mat {

template < typename Sequence >
[[ nodiscard ]] inline constexpr
auto make_string_view( Sequence const & seq ) noexcept -> std::string_view
{
    return { reinterpret_cast<char const * >( data( seq ) ), size( seq ) };
}

} /* mat */
