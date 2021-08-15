#ifndef UTILS_HPP
#define UTILS_HPP

#include <string_view>

#if __has_include( <unistd.h> )
#  include <unistd.h>
#else
#  error "swab not found"
#endif

namespace mat {

template < typename Sequence,
           typename CharT = typename Sequence::value_type >
[[ nodiscard ]] inline constexpr
auto make_string_view( Sequence const & seq ) noexcept -> std::basic_string_view< CharT >
{
    return { data( seq ), size( seq ) };
}

template < typename T >
[[ nodiscard ]] inline
auto swab( T const & field ) -> T
{
    T flipped;
    ::swab( &field, &flipped, sizeof( T ) );
    return flipped;
}

} /* mat */

#endif // UTILS_HPP
