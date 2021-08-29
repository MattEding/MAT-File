#pragma once

#include <cstddef>

namespace mat {

[[ nodiscard ]]
auto aligned_alloc( std::size_t alignment,
                    std::size_t size ) -> void *;

auto aligned_free( void * ptr ) -> void;

} /* mat */
