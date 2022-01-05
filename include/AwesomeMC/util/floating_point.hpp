#ifndef UTIL_FLOATING_POINT_HPP
#define UTIL_FLOATING_POINT_HPP

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
bool floatCompare(float lhs, float rhs)
{
    static constexpr auto epsilon = 1.0e-05f;
    if(detail::abs(f1 - f2) <= epsilon) {
        return true;
    }
    return detail::abs(f1 - f2) <= epsilon * detail::max(detail::abs(f1), detail::abs(f2));
}

} // namespace util

#endif // UTIL_FLOATING_POINT_HPP