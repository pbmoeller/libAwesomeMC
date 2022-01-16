#include <AwesomeMC/anvil/region.hpp>
#include <AwesomeMC/util/conversion.hpp>

// STL
#include <utility>
#include <stdexcept>

namespace anvil
{

Region::Region()
    : m_x{0}
    , m_z{0}
{

}

Region::Region(int x, int z)
    : m_x{x}
    , m_z{z}
{

}

Region::Region(const Region &other)
{
    *this = other;
}

Region::Region(Region &&other) noexcept
{
    *this = std::move(other);
}

Region::~Region()
{

}

Region& Region::operator=(const Region &other)
{
    if(this != &other) {
        m_x             = other.m_x;
        m_z             = other.m_z;
        m_regionHeader  = other.m_regionHeader;

        for(unsigned int i = 0; i < ChunkCount; ++i) {
            m_chunks[i] = other.m_chunks[i];
        }
    }
    return *this;
}

Region& Region::operator=(Region &&other) noexcept
{
    if(this != &other) {
        m_x             = std::move(other.m_x);
        m_z             = std::move(other.m_z);
        m_regionHeader  = std::move(other.m_regionHeader);

        for(unsigned int i = 0; i < ChunkCount; ++i) {
            m_chunks[i] = std::move(other.m_chunks[i]);
        }
    }
    return *this;
}

bool Region::operator==(const Region &other)
{
    if(this == &other) {
        return true;
    }

    if(m_x != other.m_x
       || m_z != other.m_z
       || m_regionHeader != other.m_regionHeader) {
        return false;
    }

    for(unsigned int i = 0; i < ChunkCount; ++i) {
        if(m_chunks[i] != other.m_chunks[i]) {
            return false;
        }
    }

    return true;
}

bool Region::operator!=(const Region &other)
{
    return !(*this == other);
}

int Region::getX() const
{
    return m_x;
}

void Region::setX(int x)
{
    m_x = x;
}

int Region::getZ() const
{
    return m_z;
}

void Region::setZ(int z)
{
    m_z = z;
}

RegionHeader& Region::getRegionHeader()
{
    return m_regionHeader;
}

const RegionHeader& Region::getRegionHeader() const
{
    return m_regionHeader;
}

void Region::setRegionHeader(const RegionHeader &header)
{
    m_regionHeader = header;
}

const std::array<Chunk, ChunkCount>& Region::getChunks() const
{
    return m_chunks;
}

Chunk& Region::getChunkAt(unsigned int index)
{
    return m_chunks[index];
}

const Chunk& Region::getChunkAt(unsigned int index) const
{
    return m_chunks[index];
}

std::vector<int32_t> Region::getBiomesAt(unsigned int x, unsigned int z) const
{
    // Check if chunk coodinates are valid
    if(x >= ChunkWidth || z >= ChunkWidth) {
        throw std::out_of_range("Coordinates out of range");
    }

    // Calculate the requested chunk
    unsigned chunkIdx = z * ChunkWidth + x;

    // Get data from chunk
    return getChunkAt(chunkIdx).getBiomes();
}

int32_t Region::getBiomeAt(unsigned int x,
                           unsigned int z, 
                           unsigned int blockX, 
                           int blockY, 
                           unsigned int blockZ) const
{
    // Check if chunk coodinates are valid
    if(x >= ChunkWidth || z >= ChunkWidth) {
        throw std::out_of_range("Coordinates out of range");
    }

    // Calculate the requested chunk
    unsigned chunkIdx = z * ChunkWidth + x;

    // Get data from chunk
    return getChunkAt(chunkIdx).getBiomeAt(blockX, blockY, blockZ);
}

Block Region::getBlockAt(const int blockX,
                         const int blockY,
                         const int blockZ) const
{
    // Check if chunk coodinates are valid
    //if(x >= ChunkWidth || z >= ChunkWidth) {
    //    throw std::out_of_range("Coordinates out of range");
    //}

    // Calculate the requested chunk
    int xRegion = 0;
    int zRegion = 0;
    util::convertBlockWorld2ChunkRegion(blockX, blockZ, xRegion, zRegion);
    unsigned chunkIdx = zRegion * ChunkWidth + xRegion;

    // Get data from chunk
    return getChunkAt(chunkIdx).getBlockAt(blockX, blockY, blockZ);
}

HeightMap Region::getHeightMap(const int chunkWorldX,
                               const int chunkWorldZ,
                               HeightMap::HeightMapType mapType) const
{
    int chunkX = 0;
    int chunkZ = 0;
    util::convertChunkWorld2ChunkRegion(chunkWorldX, chunkWorldZ, chunkX, chunkZ);
    return getChunkAt(chunkZ * ChunkWidth + chunkX).getHeightMap(mapType);
}

} // namespace anvil