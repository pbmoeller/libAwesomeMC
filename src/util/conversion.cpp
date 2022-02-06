#include <AwesomeMC/util/conversion.hpp>

// AwesomeMC
#include <AwesomeMC/constants.hpp>

// STL
#include <cmath>

namespace amc
{

bool isValidWorldCoordinate(const int worldX, const int worldY, const int worldZ)
{
    // TODO: Validate the values
    return worldY >= amc::MinimumBlockHeight
        && worldY <= amc::MaximumBlockHeight
        && worldX < amc::WorldBorder
        && worldX > -amc::WorldBorder
        && worldZ < amc::WorldBorder
        && worldZ > -amc::WorldBorder;
}

bool isValidRegionCoordinate(const int regionX, const int regionY, const int regionZ)
{
        // TODO: Validate the values
    return regionY >= amc::MinimumBlockHeight
        && regionY <= amc::MaximumBlockHeight
        && regionX < amc::RegionWidth
        && regionX >= 0
        && regionZ < amc::RegionWidth
        && regionZ >= 0;
}

bool isValidChunkCoordinate(const int chunkX, const int chunkY, const int chunkZ)
{
    return chunkY >= amc::MinimumBlockHeight
        && chunkY <= amc::MaximumBlockHeight
        && chunkX < amc::BlockWidth
        && chunkX >= 0
        && chunkZ < amc::BlockWidth
        && chunkZ >= 0;
}

bool isValidSectionCoordinate(const int sectionX, const int sectionY, const int sectionZ)
{
    return sectionY < amc::BlockWidth
        && sectionY >= 0
        && sectionX < amc::BlockWidth
        && sectionX >= 0
        && sectionZ < amc::BlockWidth
        && sectionZ >= 0;
}

int calculateSection(const int blockY)
{
    return (blockY / amc::BlockWidth);
}

int calculateSectionIndex(const int blockY)
{
    return (blockY / static_cast<int>(amc::BlockWidth)) + 5;
}

void convertBlockWorld2Region(const int blockWorldX, const int blockWorldZ,
                              int &regionX, int &regionZ)
{
    regionX = static_cast<int>(std::floor(blockWorldX / static_cast<float>(amc::RegionWidth)));
    regionZ = static_cast<int>(std::floor(blockWorldZ / static_cast<float>(amc::RegionWidth)));
}

void convertBlockWorld2ChunkWorld(const int blockWorldX, const int blockWorldZ,
                                  int &chunkWorldX, int &chunkWorldZ)
{
    chunkWorldX = static_cast<int>(std::floor(blockWorldX / static_cast<float>(amc::BlockWidth)));
    chunkWorldZ = static_cast<int>(std::floor(blockWorldZ / static_cast<float>(amc::BlockWidth)));
}

void convertBlockWorld2ChunkRegion(const int blockWorldX, const int blockWorldZ,
                                   int &chunkRegionX, int &chunkRegionZ)
{
    chunkRegionX = (amc::ChunkWidth + (blockWorldX / static_cast<unsigned int>(amc::BlockWidth))) & 0x0000001F;
    chunkRegionZ = (amc::ChunkWidth + (blockWorldZ / static_cast<unsigned int>(amc::BlockWidth))) & 0x0000001F;
}

void convertBlockWorld2BlockRegion(const int blockWorldX, const int blockWorldZ,
                                   int &blockRegionX, int &blockRegionZ)
{
    blockRegionX = (amc::RegionWidth + (blockWorldX % amc::RegionWidth)) & 0x000001FF;
    blockRegionZ = (amc::RegionWidth + (blockWorldZ % amc::RegionWidth)) & 0x000001FF;
}

void convertBlockWorld2BlockChunk(const int blockWorldX, const int blockWorldZ,
                                  int &blockChunkX, int &blockChunkZ)
{
    blockChunkX = (amc::BlockWidth + (blockWorldX % amc::BlockWidth)) & 0x0000000F;
    blockChunkZ = (amc::BlockWidth + (blockWorldZ % amc::BlockWidth)) & 0x0000000F;
}

void convertBlockWorld2BlockChunk(const int blockWorldX, const int blockWorldY, const int blockWorldZ,
                                  int &blockChunkX, int &blockChunkY, int &blockChunkZ)
{
    blockChunkX = (amc::BlockWidth + (blockWorldX % amc::BlockWidth)) & 0x0000000F;
    blockChunkY = (amc::BlockWidth + (blockWorldY % amc::BlockWidth)) & 0x0000000F;
    blockChunkZ = (amc::BlockWidth + (blockWorldZ % amc::BlockWidth)) & 0x0000000F;
}

void convertChunkWorld2ChunkRegion(const int chunkWorldX, const int chunkWorldZ,
                                   int &chunkRegionX, int &chunkRegionZ)
{
    chunkRegionX = (amc::ChunkWidth + (chunkWorldX % amc::ChunkWidth)) & 0x0000001F;
    chunkRegionZ = (amc::ChunkWidth + (chunkWorldZ % amc::ChunkWidth)) & 0x0000001F;
}

} // namespace amc