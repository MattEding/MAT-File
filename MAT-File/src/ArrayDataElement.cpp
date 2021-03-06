#include "ArrayDataElement.h"
#include "Swab.hpp"

#include <bitset>

#include <cstring>

namespace mat {

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  ==========================                                   *
 *    Array Flags Subelement                                     *
 *  ==========================                                   *
 *                              Bytes                            *
 *                                                               *
 *      0      1      2       3       4      5      6     7      *
 *  +------+------+-------+-------+------+------+------+------+  *
 *  |  undefined  | flags | class |         undefined         |  *
 *  +------+------+-------+-------+------+------+------+------+  *
 *              /           \                                    *
 *           /                     \                             *
 *        /                               \                      *
 *     /                                         \               *
 *     0     1     2     3     4     5     6     7               *
 *  +-----+-----+-----+-----+-----+-----+-----+-----+            *
 *  |         undefined     | cmp | gbl | lgc | und |            *
 *  +-----+-----+-----+-----+-----+-----+-----+-----+            *
 *                                                               *
 *                         Bits                                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

static std::size_t constexpr flags_index{ 2 };
static std::size_t constexpr class_index{ 3 };

static std::size_t constexpr complex_index{ 4 };
static std::size_t constexpr global_index { 5 };
static std::size_t constexpr logical_index{ 6 };

template < std::size_t I >
auto byte( ArrayFlags const & flags ) noexcept -> unsigned char
{
    std::size_t constexpr N{ sizeof( flags ) };
    static_assert( I < N );
    auto const flags_swab = swab( flags[ 0 ] );
    Bytes< N > bytes;
    std::memcpy( &bytes, &flags_swab, sizeof( bytes ) );
    return bytes[ I ];
}

template < std::size_t I >
auto bit( ArrayFlags const & flags ) noexcept -> bool
{
    std::size_t constexpr N{ 8 };
    static_assert( I < N );
    std::bitset< N > const bits{ byte< flags_index >( flags ) };
    return bits[ I ];
}

auto ArrayCommon::complex( ) const noexcept -> bool
{
    return bit< complex_index >( flags );
}

auto ArrayCommon::global( ) const noexcept -> bool
{
    return bit< global_index >( flags );
}

auto ArrayCommon::logical( ) const noexcept -> bool
{
    return bit< logical_index >( flags );
}

auto ArrayCommon::array_class( ) const noexcept -> ArrayClass
{
    return static_cast< ArrayClass >( byte< class_index >( flags ) );
}

} /* mat */
