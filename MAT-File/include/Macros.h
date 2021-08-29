#pragma once

#define MAT_PRAGMA( x )  _Pragma( MAT_STR( x ) )

#define MAT_PACK( ... )  MAT_PRAGMA( pack( __VA_ARGS__ ) )

#define MAT_CAT_IMPL( x, y )  x ## y
#define MAT_CAT( x, y )  MAT_CAT_IMPL( x, y )

#define MAT_STR_IMPL( x )  #x
#define MAT_STR( x )  MAT_STR_IMPL( x )

#ifdef _WIN32
#  define MAT_OS_STR( x )  MAT_CAT( L, x )
#else
#  define MAT_OS_STR( x )  ( x )
#endif

#define MAT_ASSERT( x )  assert( x )

#define MAT_FWD( x )  std::forward< decltype( x ) >( x )

#define MAT_NOEXCEPT_AS( x )  noexcept( noexcept( x ) )

#define MAT_PRINT( x )  std::cout << __FILE__ << " | " << __func__ << " | " << __LINE__ << " | " << MAT_STR( x ) " = " << ( x ) << std::endl

#define MAT_UNUSED( ... )  static_cast< void >( sizeof( __VA_ARGS__ ) )

#ifdef _WIN32
#  define MAT_UNREACHABLE( )  __assume( 0 )
#else
#  define MAT_UNREACHABLE( )  __builtin_unreachable( )
#endif

#define MAT_D( cls )  auto d = static_cast< cls ## Private * >( d_ptr.get( ) )

#define MAT_Q( cls )  auto q = static_cast< cls * >( q_ptr )
