#pragma once

#include "ArrayDataElement.h"
#include "DataElement.h"
#include "Enums.h"
#include "Header.h"
#include "TypeDefs.h"

#include <fstream>
#include <vector>

namespace mat {

class MatFile
{
public:
    Header header;
    DataElement data_element;

    MatFile( );

    MatFile( Endian endian );

    ~MatFile( );

    [[ nodiscard ]]
    auto load( fs::path const & matfile ) -> bool;

    auto close( ) -> void;

private:
    std::ifstream infile_;

    auto validate_data_type( DataElementTag const & tag,
                             DataType data_type ) -> void;

    auto read( void * field,
               std::streamsize size ) -> void;

    template < typename T >
    auto read( T & field ) -> T &;

    auto read_header( ) -> void;

    auto read_data_element( DataElement & data_element ) -> DataElement &;

    auto read_numeric_array_data_element( NumericArrayDataElement & numeric_array_data_element ) -> NumericArrayDataElement &;

    [[ nodiscard ]]
    auto read_tag( DataType data_type ) -> DataElementTag;

    [[ nodiscard ]]
    auto read_tag( ) -> DataElementTag;

    auto read_large_data( LargeDataElement & large_data_element ) -> LargeDataElement &;

    template < typename Vector >
    auto read_vector_data( Vector & vector,
                           DataElementTag const & tag ) -> void;

    template < typename Vector >
    auto read_vector_data( Vector & vector,
                           DataType data_type ) -> void;

    template < typename Vector >
    auto read_vector_data( Vector & vector ) -> void;

    template < i64 bits >
    auto seek_bit_boundary( ) -> void;
};

} /* mat */
