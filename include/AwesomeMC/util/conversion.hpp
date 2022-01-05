#ifndef AWESOMEMC_UTIL_CONVERSION_HPP
#define AWESOMEMC_UTIL_CONVERSION_HPP

// STL
#include <cstdint>

namespace util
{

void convertCoordinates_Block2Region(const int blockX, const int blockY, const int blockZ,
                                     int &chunkX, int &chunkZ);

void convertCoordinates_Block2Chunk(const int blockX, const int blockY, const int blockZ,
                                    int &chunkX, int &chunkY, int &chunkZ);

} // namespace util

#endif // AWESOMEMC_UTIL_CONVERSION_HPP