#include "Header.h"

#include "Utils.hpp"

namespace mat {

auto Header::text_sv( ) const noexcept -> std::string_view
{
    return make_string_view( text );
}

auto Header::endian_sv( ) const noexcept -> std::string_view
{
    return make_string_view( endian );
}

auto Header::magic_number( ) noexcept -> std::string_view
{
    static Bytes< 2 > constexpr endian_indicator{ 'M', 'I' };
    return make_string_view( endian_indicator );
}

} /* mat */
