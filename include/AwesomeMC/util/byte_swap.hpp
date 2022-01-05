#ifndef LIBAWESOMEANVIL_UTIL_BYTE_SWAP_HPP
#define LIBAWESOMEANVIL_UTIL_BYTE_SWAP_HPP

// STL
#include <cstdint>
#include <bit>
#include <type_traits>
#include <concepts>

namespace util
{

namespace detail
{

#if defined(_MSC_VER)

inline auto bswap(std::uint64_t v) noexcept {
    return _byteswap_uint64(v);
}
inline auto bswap(std::uint32_t v) noexcept {
    return _byteswap_ulong(v);
}
inline auto bswap(std::uint16_t v) noexcept {
    return _byteswap_ushort(v);
}

#elif defined(__GNUC__)

inline auto bswap(std::uint64_t v) noexcept {
    return __builtin_bswap64(v);
}
inline auto bswap(std::uint32_t v) noexcept {
    return __builtin_bswap32(v);
}
inline auto bswap(std::uint16_t v) noexcept {
    return __builtin_bswap16(v);
}

#endif

} // namespace detail

inline auto bswap(std::integral auto value) noexcept {
    if constexpr(sizeof(value) == 1) {
        return static_cast<decltype(value)>(value);
    } else {
        return static_cast<decltype(value)>(detail::bswap(static_cast<std::make_unsigned_t<decltype(value)>>(value)));
    }
}

inline auto bswap(std::floating_point auto value) noexcept {
    std::conditional_t<sizeof(decltype(value)) <= sizeof(int32_t), int32_t, int64_t> out{
        std::bit_cast<decltype(out), decltype(value)>(value)};
    return std::bit_cast<decltype(value), decltype(out)>(detail::bswap(static_cast<std::make_unsigned_t<decltype(out)>>(out)));
}

} // namespace util

#endif // LIBAWESOMEANVIL_UTIL_BYTE_SWAP_HPP