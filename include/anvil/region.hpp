#ifndef LIBAWESOMEANVIL_REGION_HPP
#define LIBAWESOMEANVIL_REGION_HPP

#include "region_header.hpp"
#include "chunk_tag.hpp"
#include "constants.hpp"

namespace anvil
{

class Region
{
public:
    Region();
    Region(int x, int z);
    Region(const Region &other);
    Region(Region &&other) noexcept;
    Region(int x, int z, const RegionHeader &header, const ChunkTag (&tags)[ChunkCount]);
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
    void setRegionHeader(const RegionHeader &header);

    const ChunkTag (&getChunkTags() const)[ChunkCount];
    void setChunkTags(const ChunkTag (&tags)[ChunkCount]);

private:
    int m_x;
    int m_z;

    RegionHeader m_header;
    ChunkTag m_tags[ChunkCount];
};

} // namespace anvil

#endif // LIBAWESOMEANVIL_REGION_HPP