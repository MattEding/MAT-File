#pragma once

#include "DataElement.h"
#include "Enums.h"
#include "TypeDefs.h"

#include <array>
#include <string>
#include <type_traits>
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
};
static_assert( std::is_standard_layout_v< ArrayCommon > );

struct Array { };
static_assert( std::is_empty_v< Array > );

struct NumericArrayDataElement : Array
{
    ArrayCommon common;
    DataElement real;
    DataElement imaginary;
};
static_assert( std::is_standard_layout_v< NumericArrayDataElement > );

using CharacterArrayDataElement = NumericArrayDataElement;

struct SparseArrayDataElement : Array
{
    ArrayCommon common;
    // TODO
};
static_assert( std::is_standard_layout_v< SparseArrayDataElement > );

struct CellArrayDataElement : Array
{
    ArrayCommon common;
    // TODO
};
static_assert( std::is_standard_layout_v< CellArrayDataElement > );

struct StructureArrayDataElement : Array
{
    ArrayCommon common;
    // TODO
};
static_assert( std::is_standard_layout_v< StructureArrayDataElement > );

struct ObjectArrayDataElement : Array
{
    ArrayCommon common;
    // TODO
};
static_assert( std::is_standard_layout_v< ObjectArrayDataElement > );

} /* mat */
