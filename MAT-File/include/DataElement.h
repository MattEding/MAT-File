#pragma once

#include "Enums.h"
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

struct LargeDataElement
{
    DataElementTag tag;
    void * data;
};

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
    enum Type { Small, Large };

    union
    {
        SmallDataElement small;
        LargeDataElement large;
    };

    DataElement( );

    ~DataElement( );

    [[ nodiscard ]]
    auto element_type( ) const noexcept -> Type;

    [[ nodiscard ]]
    auto is_large( ) const noexcept -> bool;

    [[ nodiscard ]]
    auto is_small( ) const noexcept -> bool;

    [[ nodiscard ]]
    auto data_type( ) const noexcept -> DataType;

    [[ nodiscard ]]
    auto number_of_bytes( ) const noexcept -> u32;

    [[ nodiscard ]]
    auto data( ) noexcept -> void *;

    [[ nodiscard ]]
    auto data( ) const noexcept -> void const *;
};
static_assert( std::is_standard_layout_v< DataElement > );

} /* mat */
