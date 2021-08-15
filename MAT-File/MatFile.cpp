#include "MatFile.h"
#include "Macros.h"
#include "Malloc.h"
#include "Utils.hpp"

#include <cstdlib>

namespace mat {

MatFile::MatFile( ) = default;

MatFile::~MatFile( ) = default;

auto MatFile::load( fs::path const & matfile ) -> bool
{
    std::error_code ec;
    if ( not ( fs::exists( matfile, ec )
           and fs::is_regular_file( matfile, ec ) ) )
    {
        return false;
    }

    infile_.open( matfile );

    if ( infile_.is_open( ) )
    {
        read_header( );
        // TODO:
        read_data_element( );
    }

    return infile_.is_open( );
}

auto MatFile::close( ) -> void
{
    infile_.close( );
}

auto MatFile::header( ) const -> Header const &
{
    return header_;
}

auto MatFile::header_text( ) const ->std::string_view
{
    return make_string_view( header_.text );
}

auto MatFile::subsystem_data_offset( ) const -> u64
{
    return header_.subsystem_data_offset;
}

auto MatFile::version( ) const -> u16
{
    return header_.version;
}

auto MatFile::endian( ) const -> std::string_view
{
    return make_string_view( header_.endian );
}

auto MatFile::data_elements( ) const -> std::vector< DataElement > const &
{
    return data_elements_;
}

auto MatFile::read( void * field,
                    std::streamsize size ) -> void
{
    infile_.read( reinterpret_cast< char * >( field ),
                  size );
}

auto MatFile::read_header( ) -> void
{
    read(header_);
}

auto MatFile::read_data_element( ) -> void
{
    DataElement & data_element = data_elements_.emplace_back( );
    read( data_element );

    if ( data_element.is_small( ) )
    {
        data_element.small = reinterpret_cast< SmallDataElement & >( data_element );
        data_element.data = &data_element.small.data;
    }
    else
    {
        data_element.tag = reinterpret_cast< DataElementTag & >( data_element );
        /* All data that is uncompressed must be aligned on 64-bit boundaries. */
        data_element.data = aligned_alloc( data_element.tag.number_of_bytes );
    }
}

} /* mat */

#undef READ
