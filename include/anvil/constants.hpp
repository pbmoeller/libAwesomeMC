#ifndef ANVIL_CONSTANTS_HPP
#define ANVIL_CONSTANTS_HPP

namespace anvil
{
    constexpr unsigned int BlockCount       = 256;
    constexpr unsigned int BlockWidth       = 16;
    constexpr unsigned int BlockHeight      = 256;      // TODO: check value for version >= 1.18

    constexpr unsigned int ChunkCount       = 1024;
    constexpr unsigned int ChunkWidth       = 32;

    // Region File
    constexpr unsigned int HeaderOffset     = 0;
    constexpr unsigned int ChunkDataOffset  = 8192;
    constexpr unsigned int HeaderSize       = 8192;
    constexpr unsigned int SectorSize       = 4096;
}

#endif // ANVIL_CONSTANTS_HPP