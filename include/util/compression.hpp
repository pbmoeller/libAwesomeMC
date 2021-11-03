#ifndef LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP
#define LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP

#include <vector>

namespace util
{
    constexpr unsigned int ZlibChunkSize = 16384;

    bool deflate_zlib(std::vector<char> &data);

    bool inflate_zlib(std::vector<char> &data);

    bool inflate_gzip(std::vector<char> &data);

    bool inflate_gzip2(std::vector<char> &data);

} // namespace util

#endif // LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP