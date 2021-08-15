#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <array>
#include <filesystem>

#include <cstdint>

namespace mat {

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;

namespace fs = std::filesystem;

template < std::size_t N >
using Bytes = std::array< char, N >;

inline std::size_t constexpr alignment{ 8 };

} /* mat */

#endif // TYPEDEFS_H
