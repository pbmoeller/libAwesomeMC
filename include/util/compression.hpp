#ifndef LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP
#define LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP

#include <vector>

namespace util
{
    constexpr unsigned int ZlibChunkSize = 16384;

    bool deflate(std::vector<char> &data);

    bool inflate(std::vector<char> &data);

} // namespace util

#endif // LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP