#pragma once

#include "Macros.h"
#include "TypeDefs.h"

#include <string_view>

namespace mat {

MAT_PACK( push, 4 )
struct alignas( 8 ) Header
{
    Bytes< 116 > text;
    u64 subsystem_data_offset;
    u16 version;
    Bytes< 2 > endian;

    [[ nodiscard ]]
    auto text_sv( ) const noexcept -> std::string_view;

    [[ nodiscard ]]
    auto endian_sv( ) const noexcept -> std::string_view;

    [[ nodiscard ]]
    static
    auto magic_number( ) noexcept -> std::string_view;
};
static_assert( sizeof( Header ) == 128 );
static_assert( std::is_standard_layout_v< Header > );
MAT_PACK( pop )

} /* mat */
