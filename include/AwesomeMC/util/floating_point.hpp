#ifndef AWESOMEMC_UTIL_FLOATING_POINT_HPP
#define AWESOMEMC_UTIL_FLOATING_POINT_HPP

// STL
#include <cstdint>
#include <concepts>
#include <cmath>

namespace util
{

namespace detail
{

template <typename T>
constexpr inline T abs(const T &value) 
{ 
    return value >= 0 ? value : -value;
}

template <typename T>
constexpr inline const T &min(const T &a, const T &b) 
{ 
    return (a < b) ? a : b;
}

template <typename T>
constexpr inline const T &max(const T &a, const T &b)
{ 
    return (a < b) ? b : a;
}

} // namespace detail

/*
 * https://embeddeduse.com/2019/08/26/qt-compare-two-floats/ 
 */
//bool floatCompare(float lhs, float rhs)
//{
//    static constexpr auto epsilon = 1.0e-05f;
//    if(detail::abs(lhs - rhs) <= epsilon) {
//        return true;
//    }
//    return detail::abs(lhs - rhs) <= epsilon * detail::max(detail::abs(lhs), detail::abs(rhs));
//}

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