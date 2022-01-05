#ifndef LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP
#define LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP

// STL
#include <vector>

namespace util
{
    constexpr unsigned int ZlibChunkSize = 16384;

    bool deflate_zlib(std::vector<unsigned char> &data);

    bool inflate_zlib(std::vector<unsigned char> &data);

    bool inflate_gzip(std::vector<unsigned char> &data);

    bool inflate_gzip2(std::vector<unsigned char> &data);

} // namespace util

#endif // LIBAWESOMEANVIL_UTIL_COMPRESSION_HPP