#ifndef ENUMS_H
#define ENUMS_H

#include "TypeDefs.h"

namespace mat {

struct CompressedData;
struct MatlabArray;

#define DATA_TYPE( apply ) \
    apply(  1,  miINT8,         i8              ) \
    apply(  2,  miUINT8,        u8              ) \
    apply(  3,  miINT16,        i16             ) \
    apply(  4,  miUINT16,       u16             ) \
    apply(  5,  miINT32,        i32             ) \
    apply(  6,  miUINT32,       u32             ) \
    apply(  7,  miSINGLE,       f32             ) \
    apply(  9,  miDOUBLE,       f64             ) \
    apply( 12,  miINT64,        i64             ) \
    apply( 13,  miUINT64,       u64             ) \
    apply( 14,  miMATRIX,       MatlabArray     ) \
    apply( 15,  miCOMPRESSED,   CompressedData  ) \
    apply( 16,  miUTF8,         unsigned char   ) \
    apply( 17,  miUTF16,        char16_t        ) \
    apply( 18,  miUTF32,        char32_t        )

#define DATA_TYPE_ENUM( value, name, type ) \
    name = value,
enum class DataType
{
    DATA_TYPE( DATA_TYPE_ENUM )
};
#undef DATA_TYPE_ENUM

struct CellArray;
struct Structure;
struct Object;
struct CharacterArray;
struct SparseArray;

template < typename T >
struct Array;

#define ARRAY_TYPE( apply ) \
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

#define ARRAY_TYPE_ENUM( value, type, name ) \
    name = value,
enum class ArrayType
{
    ARRAY_TYPE( ARRAY_TYPE_ENUM )
};
#undef ARRAY_TYPE_ENUM

} /* mat */

#endif // ENUMS_H
