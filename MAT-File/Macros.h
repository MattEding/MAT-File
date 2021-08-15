#ifndef MACROS_H
#define MACROS_H

#include <iostream>
#include <utility>

#include <cassert>

#define MAT_PRAGMA( x )  _Pragma( MAT_STR( x ) )

#define MAT_PACK( ... )  MAT_PRAGMA( pack( __VA_ARGS__ ) )

#define MAT_CAT_IMPL( x, y )  x ## y
#define MAT_CAT( x, y )  MAT_CAT_IMPL( x, y )

#define MAT_STR_IMPL( x )  #x
#define MAT_STR( x )  MAT_STR_IMPL( x )

#define MAT_VA_ARGS( ... )  ( __VA_ARGS__ )

#define MAT_ASSERT( x )  assert( x )

#define MAT_FWD( x )  std::forward< decltype( x ) >( x )

#define MAT_PRINT( x )  std::cout << MAT_STR( x ) " = " << ( x ) << std::endl

#define MAT_UNUSED( ... )  static_cast< void >( sizeof( __VA_ARGS__ ) )

#define MAT_UNREACHABLE( )  __builtin_unreachable( )

#endif // MACROS_H