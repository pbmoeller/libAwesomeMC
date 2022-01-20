#ifndef AWESOMEMC_UTIL_FLOATING_POINT_HPP
#define AWESOMEMC_UTIL_FLOATING_POINT_HPP

// STL
#include <cstdint>
#include <concepts>
#include <cmath>

namespace util
{

inline bool almostEqualUlps(float a, float b, int32_t maxUlps)
{
    if(std::isinf(a) || std::isinf(b)) {
        return a == b;
    }
    if(std::isnan(a) || std::isnan(b)) {
        return false;
    }
    if(std::signbit(a) != std::signbit(b)) {
        return a == b;
    }

    int32_t aInt = *(int32_t *)&a;
    if(aInt < 0) {
        aInt = 0x80000000 - aInt;
    }
    int32_t bInt = *(int32_t *)&b;
    if(bInt < 0) {
        bInt = 0x80000000 - bInt;
    }

    int32_t diff = std::abs(aInt - bInt);
    if(diff < maxUlps) {
        return true;
    }
    return false;
}

inline bool almostEqualUlps(double a, double b, int64_t maxUlps)
{
    if(std::isinf(a) || std::isinf(b)) {
        return a == b;
    }
    if(std::isnan(a) || std::isnan(b)) {
        return false;
    }
    if(std::signbit(a) != std::signbit(b)) {
        return a == b;
    }

    int64_t aInt = *(int64_t *)&a;
    if(aInt < 0) {
        aInt = 0x8000000000000000 - aInt;
    }
    int64_t bInt = *(int64_t *)&b;
    if(bInt < 0) {
        bInt = 0x8000000000000000 - bInt;
    }

    int64_t diff = std::abs(aInt - bInt);
    if(diff < maxUlps) {
        return true;
    }
    return false;
}

} // namespace util

#endif // AWESOMEMC_UTIL_FLOATING_POINT_HPP