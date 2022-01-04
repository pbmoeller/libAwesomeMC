#include "util/conversion.hpp"
#include "anvil/constants.hpp"

namespace util
{

void convertCoordinates_Block2Region(const int blockX, const int blockY, const int blockZ,
                                     int &regionX, int &regionZ)
{
    regionX = blockX / (anvil::BlockWidth * anvil::ChunkWidth);
    regionZ = blockZ / (anvil::BlockWidth * anvil::ChunkWidth);
}

void convertCoordinates_Block2Chunk(const int blockX, const int blockY, const int blockZ,
                                    int &chunkX, int &chunkY, int &chunkZ)
{
    chunkX = blockX / anvil::BlockWidth;
    chunkY = blockY / anvil::BlockWidth;
    chunkZ = blockZ / anvil::BlockWidth;
}

} // namespace util