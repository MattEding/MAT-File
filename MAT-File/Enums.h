#pragma once

#include "Macros.h"
#include "TypeDefs.h"

namespace mat {

struct MatlabArray;
struct CompressedData;

#define MAT_DATA_TYPE( apply ) \
    apply(  1,  Int8,           i8              ) \
    apply(  2,  UInt8,          u8              ) \
    apply(  3,  Int16,          i16             ) \
    apply(  4,  UInt16,         u16             ) \
    apply(  5,  Int32,          i32             ) \
    apply(  6,  UInt32,         u32             ) \
    apply(  7,  Single,         f32             ) \
    apply(  9,  Double,         f64             ) \
    apply( 12,  Int64,          i64             ) \
    apply( 13,  UInt64,         u64             ) \
    apply( 14,  Matrix,         MatlabArray     ) \
    apply( 15,  Compressed,     CompressedData  ) \
    apply( 16,  Utf8,           std::byte       ) \
    apply( 17,  Utf16,          char16_t        ) \
    apply( 18,  Utf32,          char32_t        )

//apply(  8,  _reserved8,     struct _dummy8  ) \
//apply( 10,  _reserved10,    struct _dummy10 ) \
//apply( 11,  _reserved11,    struct _dummy11 ) \
//

#define MAT_DATA_TYPE_ENUM( value, name, type ) \
    name = value,
enum struct DataType : u16
{
    MAT_DATA_TYPE( MAT_DATA_TYPE_ENUM )
};
#undef MAT_DATA_TYPE_ENUM

[[ nodiscard ]]
auto data_type_to_string( DataType data_type ) noexcept -> std::string_view;

template < typename T >
[[ nodiscard ]]
inline constexpr
auto to_data_type( ) noexcept -> DataType;

#define MAT_DATA_TYPE_TO( value, name, type ) \
    template < > \
    [[ nodiscard ]] \
    inline constexpr \
    auto to_data_type< type >( ) noexcept -> DataType \
    { \
        return static_cast< DataType >( value ); \
    }
MAT_DATA_TYPE( MAT_DATA_TYPE_TO )
#undef MAT_DATA_TYPE_TO

#define MAT_ARRAY_CLASS( apply ) \
    apply(  1,  Cell    ) \
    apply(  2,  Struct  ) \
    apply(  3,  Object  ) \
    apply(  4,  Char    ) \
    apply(  5,  Sparse  ) \
    apply(  6,  Double  ) \
    apply(  7,  Single  ) \
    apply(  8,  Int8    ) \
    apply(  9,  UInt8   ) \
    apply( 10,  Int16   ) \
    apply( 11,  UInt16  ) \
    apply( 12,  Int32   ) \
    apply( 13,  UInt32  ) \
    apply( 14,  Int64   ) \
    apply( 15,  UInt64  )

#define MAT_ARRAY_CLASS_ENUM( value, name ) \
    name = value,
enum struct ArrayClass
{
    MAT_ARRAY_CLASS( MAT_ARRAY_CLASS_ENUM )
};
#undef MAT_ARRAY_CLASS_ENUM

[[ nodiscard ]]
auto array_class_to_string( ArrayClass array_class ) noexcept -> std::string_view;

[[ nodiscard ]]
auto is_numeric_array( ArrayClass array_class ) noexcept -> bool;

[[ nodiscard ]]
auto is_character_array( ArrayClass array_class ) noexcept -> bool;

#define MAT_ENDIAN( apply ) \
    apply( 0, Little ) \
    apply( 1, Big ) \
    apply( 2, Native )

#define MAT_ENDIAN_ENUM( value, name ) \
    name = value,
enum struct Endian
{
    MAT_ENDIAN( MAT_ENDIAN_ENUM )
};
#undef MAT_ENDIAN_ENUM

[[ nodiscard ]]
auto endian_to_string( Endian endian ) noexcept -> std::string_view;

} /* mat */
