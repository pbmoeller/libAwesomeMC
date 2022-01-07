#ifndef AWESOMEMC_ANVIL_CONSTANTS_HPP
#define AWESOMEMC_ANVIL_CONSTANTS_HPP

namespace anvil
{
    constexpr unsigned int DataVersion      = 2865;

    constexpr unsigned int BlockCount       = 256;
    constexpr unsigned int BlockWidth       = 16;
    constexpr unsigned int BlockHeight      = 384;

    constexpr int MinimumBlockHeight        = -64;
    constexpr int MaximumBlockHeight        = 319;

    constexpr unsigned int ChunkCount       = 1024;
    constexpr unsigned int ChunkWidth       = 32;

    constexpr unsigned int RegionWidth      = 512;

    // Region File
    constexpr unsigned int HeaderOffset     = 0;
    constexpr unsigned int ChunkDataOffset  = 8192;
    constexpr unsigned int HeaderSize       = 8192;
    constexpr unsigned int SectorSize       = 4096;
}

#endif // AWESOMEMC_ANVIL_CONSTANTS_HPP