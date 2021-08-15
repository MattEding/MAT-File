#ifndef DATAELEMENT_H
#define DATAELEMENT_H

#include "Malloc.h"
#include "TypeDefs.h"

#include <type_traits>

namespace mat {

struct DataElementTag
{
    u32 data_type;
    u32 number_of_bytes;
};
static_assert( sizeof( DataElementTag ) == 8 );
static_assert( std::is_standard_layout_v< DataElementTag > );
static_assert( std::is_trivial_v< DataElementTag > );

struct SmallDataElement
{
    u16 data_type;
    u16 number_of_bytes;
    u32 data;
};
static_assert( sizeof( SmallDataElement ) == sizeof( DataElementTag ) );
static_assert( std::is_standard_layout_v< SmallDataElement > );
static_assert( std::is_trivial_v< SmallDataElement > );

struct DataElement
{
    union
    {
        DataElementTag tag;
        SmallDataElement small;
    };

    void * data;

    DataElement( );

    ~DataElement( );

    [[ nodiscard ]]
    auto is_small( ) const -> bool;
};
static_assert( std::is_standard_layout_v< DataElement > );

} /* mat */

#endif // DATAELEMENT_H
