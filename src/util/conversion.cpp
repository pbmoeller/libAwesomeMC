#include "util/conversion.hpp"
#include "anvil/constants.hpp"

// STL
#include <cmath>

namespace util
{

void convertCoordinates_Block2Region(const int blockX, const int blockY, const int blockZ,
                                     int &regionX, int &regionZ)
{
    regionX = static_cast<int>(std::floor(blockX / static_cast<float>(anvil::RegionWidth)));
    regionZ = static_cast<int>(std::floor(blockZ / static_cast<float>(anvil::RegionWidth)));
}

void convertCoordinates_Block2Chunk(const int blockX, const int blockY, const int blockZ,
                                    int &chunkX, int &chunkY, int &chunkZ)
{
    chunkX = blockX / anvil::BlockWidth;
    chunkY = blockY / anvil::BlockWidth;
    chunkZ = blockZ / anvil::BlockWidth;
}

} // namespace util