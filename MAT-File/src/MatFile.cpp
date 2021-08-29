#include "MatFile_p.h"
#include "Macros.h"
#include "Malloc.h"
#include "Utils.hpp"

#include <functional>
#include <type_traits>

#include <cassert>
#include <cstdlib>

#include <iostream>

namespace mat {

MatFile::MatFile( )
    : d_ptr( std::make_unique< MatFilePrivate >( ) )
{
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

    MAT_ASSERT( matfile.extension( ) == MAT_OS_STR( ".mat" ) );

    MAT_D( MatFile );

    d->infile_.open( matfile );
    bool const ok = d->infile_.is_open( );

    if ( ok )
    {
        d->read_header( header );
        d->read_data_element( data_element );
    }

    return ok;
}

auto MatFile::close( ) -> void
{
    MAT_D( MatFile );

    if ( d->infile_.is_open( ) )
    {
        d->infile_.close( );
    }
}

auto MatFilePrivate::validate_data_type( DataElementTag const & tag,
                                         DataType const data_type ) -> void
{
    bool const is_valid = static_cast< DataType >( tag.data_type ) == data_type;
    MAT_ASSERT( is_valid );
}

auto MatFilePrivate::read( void * const field,
                           std::streamsize const size ) -> void
{
    infile_.read( reinterpret_cast< char * const >( field ), size );
}

template < typename T >
auto MatFilePrivate::read( T & field ) -> T &
{
    read( &field, sizeof( T ) );
    return field;
}

auto MatFilePrivate::read_header( Header & header ) -> void
{
    read( header );
}

auto MatFilePrivate::read_data_element( DataElement & data_element ) -> DataElement &
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
                    read_array( data_element.large );
                    break;
                }
            }
            break;
        }
    }

    return data_element;
}

auto MatFilePrivate::read_array( LargeDataElement & large_data_element ) -> LargeDataElement &
{
    DataElementTag const flag_tag = read_tag( DataType::UInt32 );
    MAT_ASSERT( flag_tag.number_of_bytes == sizeof( ArrayFlags ) );

    ArrayCommon array_common;
    read_array_common( array_common );

    switch ( array_common.array_class( ) )
    {
        case ArrayClass::Char:
        case ArrayClass::Int8:
        case ArrayClass::Int16:
        case ArrayClass::Int32:
        case ArrayClass::Int64:
        case ArrayClass::UInt8:
        case ArrayClass::UInt16:
        case ArrayClass::UInt32:
        case ArrayClass::UInt64:
        case ArrayClass::Single:
        case ArrayClass::Double:
        {
            read_array_data_element< &MatFilePrivate::read_numeric_array_data_element >( large_data_element, array_common );
            break;
        }
        case ArrayClass::Cell:
        {
            // TODO
            break;
        }
        case ArrayClass::Sparse:
        {
            // TODO
            break;
        }
        case ArrayClass::Structure:
        {
            // TODO
            break;
        }
        case ArrayClass::Object:
        {
            // TODO
            break;
        }
    }

    return large_data_element;
}

auto MatFilePrivate::read_array_common( ArrayCommon & array_common ) -> ArrayCommon &
{
    read( array_common.flags );
    read_vector_data( array_common.dimensions );
    read_vector_data( array_common.name, DataType::Int8 );
    return array_common;
}

template < auto read_func,
           typename ArrayDataElement >
auto MatFilePrivate::read_array_data_element( LargeDataElement & large_data_element,
                                              ArrayCommon & array_common ) -> ArrayDataElement &
{
    static_assert( std::is_base_of_v< Array, ArrayDataElement > );
    auto * array_data_element = new ArrayDataElement{ };
    array_data_element->common = std::move( array_common );
    large_data_element.data = &std::invoke( read_func, this, *array_data_element );
    return *array_data_element;
}

auto MatFilePrivate::read_numeric_array_data_element( NumericArrayDataElement & numeric_array_data_element ) -> NumericArrayDataElement &
{
    read_data_element( numeric_array_data_element.real );

    if ( DataElement & imaginary = numeric_array_data_element.imaginary;
         numeric_array_data_element.common.complex( ) )
    {
        read_data_element( imaginary );
    }
    else
    {
        std::memset( &imaginary, 0, sizeof( imaginary ) );
    }

    return numeric_array_data_element;
}

auto MatFilePrivate::read_tag( DataType const data_type ) -> DataElementTag
{
    DataElementTag const tag = read_tag( );
    validate_data_type( tag, data_type );
    return tag;
}

auto MatFilePrivate::read_tag( ) -> DataElementTag
{
    DataElementTag tag{ };
    return read( tag );
}

auto MatFilePrivate::read_large_data( LargeDataElement & large_data_element ) -> LargeDataElement &
{
    u32 const number_of_bytes = large_data_element.tag.number_of_bytes;
    void * & data = large_data_element.data;
    data = mat::aligned_alloc( 8, number_of_bytes );
    read( data, number_of_bytes );
    return large_data_element;
}

template < typename Vector >
auto MatFilePrivate::read_vector_data( Vector & vector,
                                       DataElementTag const & tag ) -> void
{
    using T = typename Vector::value_type;
    vector.resize( tag.number_of_bytes / sizeof( T ) );
    read( data( vector ), tag.number_of_bytes );
    /* All data that is uncompressed must be aligned on 64-bit boundaries. */
    seek_bit_boundary< 64 >( );
}

template < typename Vector >
auto MatFilePrivate::read_vector_data( Vector & vector,
                                       DataType const data_type ) -> void
{
    DataElementTag const tag = read_tag( data_type );
    read_vector_data( vector, tag );
}

template < typename Vector >
auto MatFilePrivate::read_vector_data( Vector & vector ) -> void
{
    using T = typename Vector::value_type;
    read_vector_data( vector, to_data_type< T >( ) );
}

template < i64 bits >
auto MatFilePrivate::seek_bit_boundary( ) -> void
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
