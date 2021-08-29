#include "DataElement.h"
#include "Malloc.h"

#include <cstring>

namespace mat {

DataElement::DataElement( ) = default;

DataElement::~DataElement( )
{
    if ( element_type( ) == DataElement::Large )
    {
        mat::aligned_free( large.data );
    }
}

auto DataElement::element_type( ) const noexcept -> DataElement::Type
{
    /* When reading a MAT-file, you can tell if you are processing a small data element
     * by comparing the value of the first 2 bytes of the tag with the value zero (0).
     * If these 2 bytes are not zero, the tag uses the small data element format.
     */
    Bytes< 2 > bytes;
    std::memcpy( &bytes, this, sizeof( bytes ) );
    bool const is_small = bytes[ 0 ] and bytes[ 1 ];
    return is_small ? Small : Large;
}

auto DataElement::is_large( ) const noexcept -> bool
{
    return element_type( ) == Large;
}

auto DataElement::is_small( ) const noexcept -> bool
{
    return element_type( ) == Small;
}

auto DataElement::data_type( ) const noexcept -> DataType
{
    switch ( element_type( ) )
    {
        case Small:
        {
            return static_cast< DataType >( small.data_type );
        }
        case Large:
        {
            return static_cast< DataType >( large.tag.data_type );
        }
    }
}

auto DataElement::number_of_bytes( ) const noexcept -> u32
{
    switch ( element_type( ) )
    {
        case Small:
        {
            return small.number_of_bytes;
        }
        case Large:
        {
            return large.tag.number_of_bytes;
        }
    }
}

auto DataElement::data( ) noexcept -> void *
{
    return const_cast< void * >( std::as_const( *this ).data( ) );
}

auto DataElement::data( ) const noexcept -> void const *
{
    switch ( element_type( ) )
    {
        case Small:
        {
            return &small.data;
        }
        case Large:
        {
            return large.data;
        }
    }
}

} /* mat */
