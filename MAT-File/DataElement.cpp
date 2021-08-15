#include "DataElement.h"

namespace mat {

auto DataElement::is_small( ) const -> bool
{
    /* When reading a MAT-file, you can tell if you are processing a small data element
     * by comparing the value of the first 2 bytes of the tag with the value zero (0).
     * If these 2 bytes are not zero, the tag uses the small data element format.
     */
    auto const & bytes = reinterpret_cast< Bytes< sizeof( *this ) > const & >( *this );
    return bytes[ 0 ] and bytes[ 1 ];
}

DataElement::DataElement( ) = default;

DataElement::~DataElement( )
{
    if ( not is_small( ) )
    {
        aligned_free( data );
    }
}

} /* mat */
