#ifndef AWESOMEMC_UTIL_CONVERSION_HPP
#define AWESOMEMC_UTIL_CONVERSION_HPP

// STL
#include <cstdint>
#include <tuple>

namespace amc
{

bool isValidWorldCoordinate(const int worldXx, const int worldY, const int worldZ);
bool isValidRegionCoordinate(const int regionX, const int regionY, const int regionZ);
bool isValidChunkCoordinate(const int chunkX, const int chunkY, const int chunkZ);
bool isValidSectionCoordinate(const int sectionX, const int sectionY, const int sectionZ);

int calculateSection(const int blockY);
int calculateSectionIndex(const int blockY);

void convertBlockWorld2Region(const int blockWorldX, const int blockWorldZ,
                              int &regionX, int &regionZ);
void convertBlockWorld2ChunkWorld(const int blockWorldX, const int blockWorldZ,
                                  int &chunkWorldX, int &chunkWorldZ);
void convertBlockWorld2ChunkRegion(const int blockWorldX, const int blockWorldZ,
                                   int &chunkRegionX, int &chunkRegionZ);
void convertBlockWorld2BlockRegion(const int blockWorldX, const int blockWorldZ,
                                   int &blockRegionX, int &blockRegionZ);
void convertBlockWorld2BlockChunk(const int blockWorldX, const int blockWorldZ,
                                  int &blockChunkX, int &blockChunkZ);
void convertBlockWorld2BlockChunk(const int blockWorldX, const int blockWorldY, const int blockWorldZ,
                                  int &blockChunkX, int &blockChunkY, int &blockChunkZ);
void convertChunkWorld2ChunkRegion(const int chunkWorldX, const int chunkWorldZ,
                                   int &cunkRegionX, int &chunkRegionZ);
void convertChunkRegion2ChunkWorld(const int chunkRegionX, const int chunkRegionZ,
                                   const int regionX, const int regionZ,
                                   int &chunkWorldX, int &chunkWorldZ);

unsigned int chunkIndexFromXZ(const int regionChunkX, const int regionChunkZ);
void xzFromChunkIndex(const int index, int &x, int &z);
std::tuple<int, int> xzFromChunkIndex(const int index);

} // namespace amc

#endif // AWESOMEMC_UTIL_CONVERSION_HPP