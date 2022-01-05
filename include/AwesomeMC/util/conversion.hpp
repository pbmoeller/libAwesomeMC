#ifndef AWESOMEMC_UTIL_CONVERSION_HPP
#define AWESOMEMC_UTIL_CONVERSION_HPP

// STL
#include <cstdint>

namespace util
{

void convertBlockWorld2Region(const int blockX, const int blockY, const int blockZ,
                              int &chunkX, int &chunkZ);

void convertBlockWorld2BlockChunk(const int blockXW, const int blockYW, const int blockZW,
                                  int &blockXC, int &blockYC, int &blockZC,
                                  int &chunkX, int &chunkY, int &chunkZ);
void convertBlockWorld2BlockChunk(const int blockXW, const int blockYW, const int blockZW,
                                  int &blockXC, int &blockYC, int &blockZC);
void convertBlockWorld2Chunk(const int blockXW, const int blockYW, const int blockZW,
                             int &chunkX, int &chunkY, int &chunkZ);

} // namespace util

#endif // AWESOMEMC_UTIL_CONVERSION_HPP