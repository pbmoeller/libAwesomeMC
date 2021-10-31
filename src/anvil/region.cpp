#include "anvil/region.hpp"

// STL
#include <utility>

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

Region::Region(int x, int z, const RegionHeader &header, const ChunkTag(&tags)[ChunkCount])
    : m_x{x}
    , m_z{z}
    , m_header{header}
{
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        m_tags[i] = tags[i];
    }
}

Region::~Region()
{

}

Region& Region::operator=(const Region &other)
{
    if(this != &other) {
        m_x = other.m_x;
        m_z = other.m_z;
        m_header = other.m_header;
        for(unsigned int i = 0; i < ChunkCount; ++i) {
            m_tags[i] = other.m_tags[i];
        }
    }
    return *this;
}

Region& Region::operator=(Region &&other) noexcept
{
    if(this != &other) {
        m_x = other.m_x;
        m_z = other.m_z;
        m_header = other.m_header;
        for(unsigned int i = 0; i < ChunkCount; ++i) {
            m_tags[i] = other.m_tags[i];
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
       || m_header != other.m_header) {
        return false;
    }
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        if(m_tags[i] != other.m_tags[i]) {
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
    return m_header;
}

void Region::setRegionHeader(const RegionHeader &header)
{
    m_header = header;
}

const ChunkTag (&Region::getChunkTags() const)[ChunkCount]
{
    return m_tags;
}

void Region::setChunkTags(const ChunkTag(&tags)[ChunkCount])
{
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        m_tags[i] = tags[i];
    }
}

} // namespace anvil