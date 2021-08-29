#include "MatFile.h"
#include "Macros.h"
#include "Malloc.h"
#include "Utils.hpp"

#include <cassert>
#include <cstdlib>

namespace mat {

MatFile::MatFile( ) = default;

MatFile::MatFile( Endian const endian )
{
    // TODO
}

MatFile::~MatFile( )
{
    close( );
}

auto MatFile::load( fs::path const & matfile ) -> bool
{
    std::error_code ec{ };
    if ( not ( fs::exists( matfile, ec )
           and fs::is_regular_file( matfile, ec ) ) )
    {
        return false;
    }

    infile_.open( matfile );
    bool const ok = infile_.is_open( );

    if ( ok )
    {
        read_header( );
//        read_data_element( data_elements_.emplace_back( ) );
        read_data_element( data_element );
    }

    return ok;
}

auto MatFile::close( ) -> void
{
    if ( infile_.is_open( ) )
    {
        infile_.close( );
    }
}

auto MatFile::validate_data_type( DataElementTag const & tag,
                                  DataType const data_type ) -> void
{
    bool const is_valid = static_cast< DataType >( tag.data_type ) == data_type;
    MAT_ASSERT( is_valid );
}

auto MatFile::read( void * const field,
                    std::streamsize const size ) -> void
{
    infile_.read( reinterpret_cast< char * const >( field ), size );
}

template < typename T >
auto MatFile::read( T & field ) -> T &
{
    read( &field, sizeof( T ) );
    return field;
}

auto MatFile::read_header( ) -> void
{
    read( header );
}

auto MatFile::read_data_element( DataElement & data_element ) -> DataElement &
{
    std::size_t constexpr N = sizeof( DataElementTag );
    read( &data_element, N );

    switch ( data_element.element_type( ) )
    {
        case DataElement::Type::Small:
        {
            std::memcpy( &data_element.small, &data_element, N );
            break;
        }
        case DataElement::Type::Large:
        {
            std::memcpy( &data_element.large, &data_element, N );

            switch ( data_element.data_type( ) )
            {
                case DataType::Int8:
                case DataType::Int16:
                case DataType::Int32:
                case DataType::Int64:
                case DataType::UInt8:
                case DataType::UInt16:
                case DataType::UInt32:
                case DataType::UInt64:
                case DataType::Single:
                case DataType::Double:
                case DataType::Utf8:
                case DataType::Utf16:
                case DataType::Utf32:
                {
                    read_large_data( data_element.large );
                    break;
                }
                case DataType::Compressed:
                {
                    // TODO
                    break;
                }
                case DataType::Matrix:
                {
                    data_element.large.data = &read_numeric_array_data_element( *new NumericArrayDataElement{ } );
                    break;
                }
            }
            break;
        }
    }

    return data_element;
}

auto MatFile::read_numeric_array_data_element( NumericArrayDataElement & numeric_array_data_element ) -> NumericArrayDataElement &
{
    DataElementTag const flag_tag = read_tag( DataType::UInt32 );
    MAT_ASSERT( flag_tag.number_of_bytes == sizeof( ArrayFlags ) );

    read( numeric_array_data_element.common.flags );

    read_vector_data( numeric_array_data_element.common.dimensions );
    read_vector_data( numeric_array_data_element.common.name, DataType::Int8 );

    read_data_element( numeric_array_data_element.real );

    if ( numeric_array_data_element.common.complex( ) )
    {
        read_data_element( numeric_array_data_element.imaginary );
    }

    return numeric_array_data_element;
}

auto MatFile::read_tag( DataType const data_type ) -> DataElementTag
{
    DataElementTag const tag = read_tag( );
    validate_data_type( tag, data_type );
    return tag;
}

auto MatFile::read_tag( ) -> DataElementTag
{
    DataElementTag tag{ };
    return read( tag );
}

auto MatFile::read_large_data( LargeDataElement & large_data_element ) -> LargeDataElement &
{
    u32 const number_of_bytes = large_data_element.tag.number_of_bytes;
    void * & data = large_data_element.data;
    data = mat::aligned_alloc( 8, number_of_bytes );
    read( data, number_of_bytes );
    return large_data_element;
}

template < typename Vector >
auto MatFile::read_vector_data( Vector & vector,
                                DataElementTag const & tag ) -> void
{
    using T = typename Vector::value_type;
    vector.resize( tag.number_of_bytes / sizeof( T ) );
    read( data( vector ), tag.number_of_bytes );
    /* All data that is uncompressed must be aligned on 64-bit boundaries. */
    seek_bit_boundary< 64 >( );
}

template < typename Vector >
auto MatFile::read_vector_data( Vector & vector,
                                DataType const data_type ) -> void
{
    DataElementTag const tag = read_tag( data_type );
    read_vector_data( vector, tag );
}

template < typename Vector >
auto MatFile::read_vector_data( Vector & vector ) -> void
{
    using T = typename Vector::value_type;
    read_vector_data( vector, to_data_type< T >( ) );
}

template < i64 bits >
auto MatFile::seek_bit_boundary( ) -> void
{
    i64 constexpr alignment = bits / 8;

    if ( auto delta = static_cast< i64 >( infile_.tellg( ) );
         delta %= alignment )
    {
        delta = alignment - delta;
        infile_.seekg( delta, std::ios::seekdir::cur );
    }

    MAT_ASSERT( infile_.tellg( ) % alignment == 0 );
}

} /* mat */

#undef READ
