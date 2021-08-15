#ifndef ARRAYDATAELEMENT_H
#define ARRAYDATAELEMENT_H

#include "Macros.h"
#include "TypeDefs.h"

#include <array>
#include <vector>

namespace mat {

#if 0
Subelement Data Type Number of Bytes
Array Flags miUINT32 2 * sizeOfDataType (8 bytes)
Dimensions Array
miINT32
numberOfDimensions * sizeOfDataType
(To learn how to determine the number of dimensions, see “Dimensions Array Subelement” on page 1-11.)
Array Name miINT8 numberOfCharacters * sizeOfDataType
Real part (pr) Any of the numeric data numberOfValues * sizeOfDataType types.
Imaginary part (pi) Any of the numeric data numberOfvalues * sizeOfDataType (Optional) types.
#endif

#define MAT_ARRAY_CLASS_TYPE( apply ) \
    apply(  1,  CellArray,      mxCELL_CLASS    ) \
    apply(  2,  Structure,      mxSTRUCT_CLASS  ) \
    apply(  3,  Object,         mxOBJECT_CLASS  ) \
    apply(  4,  Array< char >,  mxCHAR_CLASS    ) \
    apply(  5,  SparseArray,    mxSPARSE_CLASS  ) \
    apply(  6,  Array< f64 >,   mxDOUBLE_CLASS  ) \
    apply(  7,  Array< f32 >,   mxSINGLE_CLASS  ) \
    apply(  8,  Array< i8 >,    mxINT8_CLASS    ) \
    apply(  9,  Array< u8 >,    mxUINT8_CLASS   ) \
    apply( 10,  Array< i16 >,   mxINT16_CLASS   ) \
    apply( 11,  Array< u16 >,   mxUINT16_CLASS  ) \
    apply( 12,  Array< i32 >,   mxINT32_CLASS   ) \
    apply( 13,  Array< u32 >,   mxUINT32_CLASS  ) \
    apply( 14,  Array< i64 >,   mxINT64_CLASS   ) \
    apply( 15,  Array< u64 >,   mxUINT64_CLASS  )

#define MAT_ARRAY_CLASS_TYPE_ENUM( value, type, name ) \
    name = value,
enum class ArrayClassType
{
    MAT_ARRAY_CLASS_TYPE( MAT_ARRAY_CLASS_TYPE_ENUM )
};
#undef MAT_ARRAY_CLASS_TYPE_ENUM

struct NumericArrayDataElement
{
    std::array< u32, 2 > flags;
    std::vector< i32 > dimensions;
    std::vector< i8 > name;
    void * real;
    void * imaginary;

    [[ nodiscard ]]
    auto complex( ) const -> bool;

    [[ nodiscard ]]
    auto global( ) const -> bool;

    [[ nodiscard ]]
    auto logical( ) const -> bool;

    [[ nodiscard ]]
    auto class_type( ) const -> ArrayClassType;
};

using CharacterArrayDataElement = NumericArrayDataElement;

} /* mat */

#endif // ARRAYDATAELEMENT_H
