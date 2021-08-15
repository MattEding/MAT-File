#ifndef MALLOC_H
#define MALLOC_H

#include "Macros.h"
#include "TypeDefs.h"

#include <cerrno>

namespace mat {

[[ nodiscard ]] inline
auto aligned_alloc( std::size_t size ) -> void *
{
    #ifdef _WIN32
    #  error "TODO"
    #else
    void * ptr{ };

    if ( int const error = posix_memalign( &ptr, alignment, size );
         error )
    {
        switch ( error )
        {
            case ENOMEM: throw std::bad_alloc{ };
            case EINVAL: throw std::invalid_argument{ "alignment must be a power of 2 or multiple of sizeof(void *)" };
            default:     MAT_UNREACHABLE( );
        }
    }

    return ptr;
    #endif
}

inline
auto aligned_free( void * ptr ) -> void
{
    #ifdef _WIN32
    #  error "TODO"
    #else
    std::free( ptr );
    #endif
}

} /* mat */

#endif // MALLOC_H
