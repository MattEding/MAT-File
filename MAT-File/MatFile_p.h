#pragma once

#include "MatFile.h"
#include "TypeTraits.hpp"

namespace mat {

class MatFilePrivate
{
public:
    MatFilePrivate( ) = default;

    ~MatFilePrivate( ) = default;

    std::ifstream infile_;

    auto validate_data_type( DataElementTag const & tag,
                             DataType data_type ) -> void;

    auto read( void * field,
               std::streamsize size ) -> void;

    template < typename T >
    auto read( T & field ) -> T &;

    auto read_header( Header & header ) -> void;

    auto read_data_element( DataElement & data_element ) -> DataElement &;

    auto read_array( LargeDataElement & large_data_element ) -> LargeDataElement &;

    auto read_array_common( ArrayCommon & array_common ) -> ArrayCommon &;

    template < auto read_func,
               typename ArrayDataElement = std::decay_t< return_type_t< decltype( read_func ) > > >
    auto read_array_data_element( LargeDataElement & large_data_element,
                                  ArrayCommon & array_common ) -> ArrayDataElement &;

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
