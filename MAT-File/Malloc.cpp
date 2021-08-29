#include "Malloc.h"
#include "Macros.h"

#include <system_error>

#ifdef _WIN32
#  error "TODO"
#else
#  include <stdlib.h>
#endif

namespace mat {

inline char constexpr error_message[ ]{ "alignment must be a power of 2 or multiple of sizeof(void *)" };

auto aligned_alloc( std::size_t const alignment,
                    std::size_t const size ) -> void *
{
    #ifdef _WIN32
    #  error "TODO"
    #else
    void * ptr{ };

    if ( int const error = posix_memalign( &ptr, alignment, size );
         error )
    {
        switch ( std::errc{ error } )
        {
            case std::errc::not_enough_memory: throw std::bad_alloc{ };
            case std::errc::invalid_argument:  throw std::invalid_argument{ error_message };
            default:                           MAT_UNREACHABLE( );
        }
    }

    return ptr;
    #endif
}

auto aligned_free( void * const ptr ) -> void
{
    #ifdef _WIN32
    #  error "TODO"
    #else
    std::free( ptr );
    #endif
}

} /* mat */
