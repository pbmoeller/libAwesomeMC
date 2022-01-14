#ifndef AWESOMEMC_UTIL_BIT_HPP
#define AWESOMEMC_UTIL_BIT_HPP

// STL
#include <cstdint>
#include <cassert>
#include <limits>

namespace util
{

//template<typename T>
//inline T setNLeastSignificantBits(char n)
//{
//    assert(n <= std::numeric_limits<T>::digits());
//    return n == std::numeric_limits<T>::digits() ? std::numeric_limits<T>::max() : (1 << n) - 1;
//}

inline uint16_t setNLeastSignificantBits16(char n)
{
    assert(n <= 16);
    return n == 16 ? std::numeric_limits<uint16_t>::max() : (static_cast<int16_t>(1) << n) - 1;
}

inline uint32_t setNLeastSignificantBits32(char n)
{
    assert(n <= 32);
    return n == 32 ? std::numeric_limits<uint32_t>::max() : (static_cast<int32_t>(1) << n) - 1;
}

inline uint64_t setNLeastSignificantBits64(char n)
{
    assert(n <= 64);
    return n == 64 ? std::numeric_limits<uint64_t>::max() : (static_cast<int64_t>(1) << n) - 1;
}

} // namespace util

#endif // AWESOMEMC_UTIL_BIT_HPP