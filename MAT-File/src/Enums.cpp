#include "Enums.h"
#include "Macros.h"

#include <string_view>

namespace mat {

#define MAT_INVALID_PREFIX  "Invalid"

auto data_type_to_string( DataType const data_type ) noexcept -> std::string_view
{
    #define MAT_DATA_TYPE_SUFFIX  "DataType"
    #define MAT_DATA_TYPE_CASE( value, name, type ) \
        case static_cast< DataType >( value ): \
        { \
            static std::string_view constexpr name ## _sv{ MAT_STR( name ) MAT_DATA_TYPE_SUFFIX }; \
            return name ## _sv; \
        }

    switch ( data_type )
    {
        MAT_DATA_TYPE( MAT_DATA_TYPE_CASE )
    }

    static std::string_view constexpr invalid_sv{ MAT_INVALID_PREFIX MAT_DATA_TYPE_SUFFIX };
    return invalid_sv;

    #undef MAT_DATA_TYPE_CASE
    #undef MAT_DATA_TYPE_SUFFIX
}

auto array_class_to_string( ArrayClass const array_class ) noexcept -> std::string_view
{
    #define MAT_ARRAY_CLASS_SUFFIX  "ArrayClass"
    #define MAT_ARRAY_CLASS_CASE( value, name ) \
        case ArrayClass::name: \
        { \
            static std::string_view constexpr name ## _sv{ MAT_STR( name ) MAT_ARRAY_CLASS_SUFFIX }; \
            return name ## _sv; \
        }

    switch ( array_class )
    {
        MAT_ARRAY_CLASS( MAT_ARRAY_CLASS_CASE )
    }

    static std::string_view constexpr invalid_sv{ MAT_INVALID_PREFIX MAT_ARRAY_CLASS_SUFFIX };
    return invalid_sv;

    #undef MAT_ARRAY_CLASS_CASE
    #undef MAT_ARRAY_CLASS_SUFFIX
}

auto is_numeric_array( ArrayClass const array_class ) noexcept -> bool
{
    switch ( array_class )
    {
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
            return true;
        }
        default:
        {
            return false;
        }
    }
}

auto is_character_array( ArrayClass const array_class ) noexcept -> bool
{
    switch ( array_class )
    {
        case ArrayClass::Char:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

auto endian_to_string( Endian const endian ) noexcept -> std::string_view
{
    #define MAT_ENDIAN_SUFFIX  "Endian"
    #define MAT_ENDIAN_CASE( value, name ) \
        case Endian::name: \
        { \
            static std::string_view constexpr name ## _sv{ MAT_STR( name ) MAT_ENDIAN_SUFFIX }; \
            return name ## _sv; \
        }

    switch ( endian )
    {
        MAT_ENDIAN( MAT_ENDIAN_CASE )
    }

    static std::string_view constexpr invalid_sv{ MAT_INVALID_PREFIX MAT_ENDIAN_SUFFIX };
    return invalid_sv;

    #undef MAT_ARRAY_CLASS_CASE
    #undef MAT_ENDIAN_SUFFIX
}

#undef MAT_INVALID_PREFIX

} /* mat */
