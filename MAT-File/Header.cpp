#include "Header.h"

#include "Utils.hpp"

namespace mat {

inline Bytes< 2 > constexpr endian_indicator{ 'M', 'I' };

auto Header::magic_number( ) -> std::string_view
{

    return make_string_view( endian_indicator );
}

} /* mat */
