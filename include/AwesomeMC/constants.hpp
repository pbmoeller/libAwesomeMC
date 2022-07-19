#ifndef AWESOMEMC_CONSTANTS_HPP
#define AWESOMEMC_CONSTANTS_HPP

namespace amc
{
    constexpr unsigned int DataVersion  = 2865;

    constexpr int BlockCount            = 256;
    constexpr int BlockWidth            = 16;
    constexpr int BlockHeight           = 384;

    constexpr int MinimumBlockHeight    = -64;
    constexpr int MaximumBlockHeight    = 319;

    constexpr int ChunkCount            = 1024;
    constexpr int ChunkWidth            = 32;

    constexpr int RegionWidth           = 512;
    constexpr int WorldBorder           = 29999984;

    // Region File
    constexpr int HeaderOffset          = 0;
    constexpr int ChunkDataOffset       = 8192;
    constexpr int HeaderSize            = 8192;
    constexpr int HeaderSizeHalf        = 4096;
    constexpr int SectorSize            = 4096;

} // namespace amc

#endif // AWESOMEMC_CONSTANTS_HPP