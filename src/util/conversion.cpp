#include <AwesomeMC/util/conversion.hpp>

// AwesomeMC
#include <AwesomeMC/anvil/constants.hpp>

// STL
#include <cmath>

namespace util
{

void convertBlockWorld2Region(const int blockX, const int blockY, const int blockZ,
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

void convertBlockWorld2BlockChunk(const int blockXW, const int blockYW, const int blockZW,
                                  int &blockXC, int &blockYC, int &blockZC,
                                  int &chunkX, int &chunkY, int &chunkZ)
{
    convertBlockWorld2BlockChunk(blockXW, blockYW, blockZW, blockXC, blockYC, blockZC);
    convertBlockWorld2Chunk(blockXW, blockYW, blockZW, chunkX, chunkY, chunkZ);
}

void convertBlockWorld2BlockChunk(const int blockXW, const int blockYW, const int blockZW,
                                  int &blockXC, int &blockYC, int &blockZC)
{
    blockXC = blockXW % anvil::BlockWidth;
    blockYC = blockYW % anvil::BlockWidth;
    blockZC = blockZW % anvil::BlockWidth;
}

void convertBlockWorld2Chunk(const int blockXW, const int blockYW, const int blockZW,
                             int &chunkX, int &chunkY, int &chunkZ)
{
    chunkX = static_cast<int>(std::floor(blockXW / static_cast<float>(anvil::BlockWidth)));
    chunkY = static_cast<int>(std::floor(blockYW / static_cast<float>(anvil::BlockWidth)));
    chunkZ = static_cast<int>(std::floor(blockZW / static_cast<float>(anvil::BlockWidth)));
}

} // namespace util