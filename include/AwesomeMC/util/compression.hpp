#ifndef AWESOMEMC_UTIL_COMPRESSION_HPP
#define AWESOMEMC_UTIL_COMPRESSION_HPP

// STL
#include <vector>

namespace amc
{
    constexpr unsigned int ZlibChunkSize = 16384;

    bool deflate_zlib(std::vector<unsigned char> &data);

    bool inflate_zlib(std::vector<unsigned char> &data);

    bool inflate_gzip(std::vector<unsigned char> &data);

    bool inflate_gzip2(std::vector<unsigned char> &data);

} // namespace amc

#endif // AWESOMEMC_UTIL_COMPRESSION_HPP