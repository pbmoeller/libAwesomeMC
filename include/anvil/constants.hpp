#ifndef LIBAWESOMEANVIL_CONSTANTS_HPP
#define LIBAWESOMEANVIL_CONSTANTS_HPP

namespace anvil
{
    constexpr unsigned int BlockCount   = 256;
    constexpr unsigned int BlockWidth   = 16;
    constexpr unsigned int BlockHeight  = 256;

    constexpr unsigned int ChunkCount   = 1024;
    constexpr unsigned int ChunkWidth   = 32;

    constexpr unsigned int HeaderOffset = 8192;
    constexpr unsigned int HeaderSize   = 8192;
    constexpr unsigned int SectorSize   = 4094;
}

#endif // LIBAWESOMEANVIL_CONSTANTS_HPP