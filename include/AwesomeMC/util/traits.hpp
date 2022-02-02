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
inline constexpr bool is_specialization = false;
template<template<typename...> typename T, typename... Args>
inline constexpr bool is_specialization<T<Args...>, T> = true;

template<typename T>
concept is_std_vector = is_specialization<T, std::vector>;

template<typename T>
concept is_std_string = std::is_same_v<T, std::string>;

template<typename T>
concept is_std_string_or_std_vector = is_std_vector<T> || is_std_string<T>;

} // namespace util

#endif // AWESOMEMC_UTIL_TRAITS_HPP