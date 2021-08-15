#ifndef HEADER_H
#define HEADER_H

#include "Macros.h"
#include "TypeDefs.h"

namespace mat {

MAT_PACK( push, 4 )
struct alignas( alignment ) Header
{
    Bytes< 116 > text;
    u64 subsystem_data_offset;
    u16 version;
    Bytes< 2 > endian;

    [[ nodiscard ]]
    static
    auto magic_number( ) -> std::string_view;
};
static_assert( sizeof( Header ) == 128 );
static_assert( std::is_standard_layout_v< Header > );
MAT_PACK( pop )

} /* mat */

#endif // HEADER_H
