#include <AwesomeMC/util/conversion.hpp>

// AwesomeMC
#include <AwesomeMC/constants.hpp>

// STL
#include <cmath>

namespace util
{

bool isValidWorldCoordinate(const int worldX, const int worldY, const int worldZ)
{
    // TODO: Validate the values
    return worldY >= anvil::MinimumBlockHeight
        && worldY <= anvil::MaximumBlockHeight
        && worldX < anvil::WorldBorder
        && worldX > -anvil::WorldBorder
        && worldZ < anvil::WorldBorder
        && worldZ > -anvil::WorldBorder;
}

bool isValidRegionCoordinate(const int regionX, const int regionY, const int regionZ)
{
        // TODO: Validate the values
    return regionY >= anvil::MinimumBlockHeight
        && regionY <= anvil::MaximumBlockHeight
        && regionX < anvil::RegionWidth
        && regionX >= 0
        && regionZ < anvil::RegionWidth
        && regionZ >= 0;
}

bool isValidChunkCoordinate(const int chunkX, const int chunkY, const int chunkZ)
{
    return chunkY >= anvil::MinimumBlockHeight
        && chunkY <= anvil::MaximumBlockHeight
        && chunkX < anvil::BlockWidth
        && chunkX >= 0
        && chunkZ < anvil::BlockWidth
        && chunkZ >= 0;
}

bool isValidSectionCoordinate(const int sectionX, const int sectionY, const int sectionZ)
{
    return sectionY < anvil::BlockWidth
        && sectionY >= 0
        && sectionX < anvil::BlockWidth
        && sectionX >= 0
        && sectionZ < anvil::BlockWidth
        && sectionZ >= 0;
}

int calculateSection(const int blockY)
{
    return (blockY / anvil::BlockWidth);
}

int calculateSectionIndex(const int blockY)
{
    return (blockY / (int)anvil::BlockWidth) + 5;
}

void convertBlockWorld2Region(const int blockWorldX, const int blockWorldZ,
                              int &regionX, int &regionZ)
{
    regionX = static_cast<int>(std::floor(blockWorldX / static_cast<float>(anvil::RegionWidth)));
    regionZ = static_cast<int>(std::floor(blockWorldZ / static_cast<float>(anvil::RegionWidth)));
}

void convertBlockWorld2ChunkWorld(const int blockWorldX, const int blockWorldZ,
                                  int &chunkWorldX, int &chunkWorldZ)
{
    chunkWorldX = static_cast<int>(std::floor(blockWorldX / static_cast<float>(anvil::BlockWidth)));
    chunkWorldZ = static_cast<int>(std::floor(blockWorldZ / static_cast<float>(anvil::BlockWidth)));
}

void convertBlockWorld2ChunkRegion(const int blockWorldX, const int blockWorldZ,
                                   int &chunkRegionX, int &chunkRegionZ)
{
    chunkRegionX = (anvil::ChunkWidth + (blockWorldX / static_cast<unsigned int>(anvil::BlockWidth))) & 0x0000001F;
    chunkRegionZ = (anvil::ChunkWidth + (blockWorldZ / static_cast<unsigned int>(anvil::BlockWidth))) & 0x0000001F;
}

void convertBlockWorld2BlockRegion(const int blockWorldX, const int blockWorldZ,
                                   int &blockRegionX, int &blockRegionZ)
{
    blockRegionX = (anvil::RegionWidth + (blockWorldX % anvil::RegionWidth)) & 0x000001FF;
    blockRegionZ = (anvil::RegionWidth + (blockWorldZ % anvil::RegionWidth)) & 0x000001FF;
}

void convertBlockWorld2BlockChunk(const int blockWorldX, const int blockWorldZ,
                                  int &blockChunkX, int &blockChunkZ)
{
    blockChunkX = (anvil::BlockWidth + (blockWorldX % anvil::BlockWidth)) & 0x0000000F;
    blockChunkZ = (anvil::BlockWidth + (blockWorldZ % anvil::BlockWidth)) & 0x0000000F;
}

void convertBlockWorld2BlockChunk(const int blockWorldX, const int blockWorldY, const int blockWorldZ,
                                  int &blockChunkX, int &blockChunkY, int &blockChunkZ)
{
    blockChunkX = (anvil::BlockWidth + (blockWorldX % anvil::BlockWidth)) & 0x0000000F; 
    blockChunkY = (anvil::BlockWidth + (blockWorldY % anvil::BlockWidth)) & 0x0000000F;
    blockChunkZ = (anvil::BlockWidth + (blockWorldZ % anvil::BlockWidth)) & 0x0000000F;
}

} // namespace util