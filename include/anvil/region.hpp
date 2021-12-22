#ifndef ANVIL_REGION_HPP
#define ANVIL_REGION_HPP

#include "constants.hpp"
#include "region_header.hpp"
#include "chunk.hpp"

// STL
#include <array>

namespace anvil
{

class Region
{
public:
    Region();
    Region(int x, int z);
    Region(const Region &other);
    Region(Region &&other) noexcept;
    virtual ~Region();

    Region& operator=(const Region &other);
    Region& operator=(Region &&other) noexcept;
 
    bool operator==(const Region &other);
    bool operator!=(const Region &other);

    int getX() const;
    void setX(int x);

    int getZ() const;
    void setZ(int z);

    RegionHeader& getRegionHeader();
    const RegionHeader& getRegionHeader() const;
    void setRegionHeader(const RegionHeader &header);

    const std::array<Chunk, ChunkCount>& getChunks() const;
    Chunk& getChunkAt(unsigned int index);
    const Chunk& getChunkAt(unsigned int index) const;

    std::vector<int32_t> getBiomesAt(unsigned int x, unsigned int z) const;
    int32_t getBiomeAt(unsigned int x,
                       unsigned int z,
                       unsigned int blockX, 
                       int blockY,
                       unsigned int blockZ) const;

    // TODO: return value -> temporary : Change Leter to block class or sth else
    std::string getBlockAt(unsigned int x,
                           unsigned int z,
                           unsigned int blockX,
                           int blockY,
                           unsigned int blockZ) const;

private:
    int m_x;
    int m_z;

    RegionHeader m_regionHeader;
    std::array<Chunk, ChunkCount> m_chunks;
};

} // namespace anvil

#endif // ANVIL_REGION_HPP