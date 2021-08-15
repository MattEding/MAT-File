#ifndef MATFILE_H
#define MATFILE_H

#include "DataElement.h"
#include "Header.h"
#include "TypeDefs.h"

#include <fstream>
#include <memory>
#include <string_view>
#include <vector>

namespace mat {

class MatFile
{
public:
    MatFile( );

    ~MatFile( );

    [[ nodiscard ]]
    auto load( fs::path const & matfile ) -> bool;

    auto close( ) -> void;

    [[ nodiscard ]]
    auto header( ) const -> Header const &;

    [[ nodiscard ]]
    auto header_text( ) const -> std::string_view;

    [[ nodiscard ]]
    auto subsystem_data_offset( ) const -> u64;

    [[ nodiscard ]]
    auto version( ) const -> u16;

    [[ nodiscard ]]
    auto endian( ) const -> std::string_view;

    [[ nodiscard ]]
    auto data_elements( ) const -> std::vector< DataElement > const &;

    auto read( void * field,
               std::streamsize size ) -> void;

    template < typename T >
    auto read( T & field ) -> void
    {
        read( &field, sizeof( T ) );
    }

private:
    std::ifstream infile_;
    Header header_;
    std::vector< DataElement > data_elements_;

    auto read_header( ) -> void;
    auto read_data_element( ) -> void;
};

} /* mat */

#endif // MATFILE_H
