#pragma once

#include "DataElement.h"
#include "Enums.h"
#include "TypeDefs.h"

#include <array>
#include <string>
#include <vector>

namespace mat {

using ArrayFlags = std::array< u32, 2 >;

using DimensionsArray = std::vector< i32 >;

using ArrayName = std::string;
static_assert( sizeof( ArrayName::value_type ) == sizeof( i8 ) );;

struct ArrayCommon
{
    ArrayFlags flags;
    DimensionsArray dimensions;
    ArrayName name;

    [[ nodiscard ]]
    auto complex( ) const noexcept -> bool;

    [[ nodiscard ]]
    auto global( ) const noexcept -> bool;

    [[ nodiscard ]]
    auto logical( ) const noexcept -> bool;

    [[ nodiscard ]]
    auto array_class( ) const noexcept -> ArrayClass;

private:
    template < std::size_t I >
    [[ nodiscard ]]
    auto bit( ) const noexcept -> bool;

    template < std::size_t I >
    [[ nodiscard ]]
    auto byte( ) const noexcept -> unsigned char;
};

struct NumericArrayDataElement
{
    ArrayCommon common;
    DataElement real;
    DataElement imaginary;
};

using CharacterArrayDataElement = NumericArrayDataElement;

} /* mat */
