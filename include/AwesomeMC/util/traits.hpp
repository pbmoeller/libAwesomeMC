#ifndef AWESOMEMC_UTIL_TRAITS_HPP
#define AWESOMEMC_UTIL_TRAITS_HPP

// STL
#include <concepts>
#include <type_traits>
#include <string>
#include <vector>

namespace util
{

template<typename, template<typename...> typename>
inline constexpr bool isSpecialization = false;
template<template<typename...> typename T, typename... Args>
inline constexpr bool isSpecialization<T<Args...>, T> = true;

template<typename T>
concept StdVector = isSpecialization<T, std::vector>;

template<typename T>
concept StdString = std::is_same_v<T, std::string>;

template<typename T>
concept StdStringOrStdVector = StdVector<T> || StdString<T>;

template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;

} // namespace util

#endif // AWESOMEMC_UTIL_TRAITS_HPP