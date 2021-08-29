#include "Print.h"

#include <iomanip>
#include <iostream>

namespace mat {

struct [[ nodiscard ]] ScopedFmtFlags
{
    template < typename ... Args >
    ScopedFmtFlags( Args &&... args )
        : fmtflags_( std::cout.flags( ) )
    {
        ( std::cout << ... << args );
    }

    ~ScopedFmtFlags( )
    {
        std::cout.flags( fmtflags_ );
    }

    std::ios::fmtflags const fmtflags_;
};

[[ nodiscard ]]
inline
ScopedFmtFlags hex_fmt( )
{
    return { std::hex,
             std::showbase,
             std::left,
             std::setfill( '0' ) };
}

auto _print_header( Header const & header,
                    std::string_view const _ ) -> void
{
    MAT_PRINT( _ );
    MAT_PRINT( header.text_sv( ) );
    MAT_PRINT( header.subsystem_data_offset );

    {
        ScopedFmtFlags const fmt{ hex_fmt( ) };
        MAT_PRINT( header.version );
    }

    MAT_PRINT( header.endian_sv( ) );
    MAT_PRINT( Header::magic_number(  ) );
}

auto _print_data_element_tag( DataElement const & data_element,
                              std::string_view const _ ) -> void
{
    MAT_PRINT( _ );
    MAT_PRINT( data_element.is_large( ) );
    auto const data_type_sv = data_type_to_string( data_element.data_type( ) );
    MAT_PRINT( data_type_sv );
    MAT_PRINT( data_element.number_of_bytes( ) );
}

auto _print_array_common( ArrayCommon const & array_common,
                          std::string_view const _ ) -> void
{
    MAT_PRINT( _ );
    auto const is_complex = array_common.complex( );
    MAT_PRINT( is_complex );
    auto const is_global = array_common.global( );
    MAT_PRINT( is_global );
    auto const is_logical = array_common.logical( );
    MAT_PRINT( is_logical );
    auto const array_class = array_common.array_class( );
    auto const array_class_sv = array_class_to_string( array_class );
    MAT_PRINT( array_class_sv );
    auto const & dims = array_common.dimensions;
    for ( auto const dim : dims )
    {
        MAT_PRINT( dim );
    }
    auto const & name = array_common.name;
    MAT_PRINT( name );
}

auto _print_numeric_array_data_element( NumericArrayDataElement const & numeric_array_data_element,
                                        std::string_view const _ ) -> void
{
    MAT_PRINT( _ );
//    print_array_common( numeric_array_data_element.common );
    print_data_element_tag( numeric_array_data_element.real );
    print_data_element_tag( numeric_array_data_element.imaginary );
}

} /* mat */
