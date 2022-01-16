#include <AwesomeMC/anvil/heightmap.hpp>

// STL
#include <string>
#include <stdexcept>
#include <climits>
#include <utility>

namespace anvil
{

HeightMap::HeightMap()
    : m_chunkX{std::numeric_limits<int>::max()}
    , m_chunkZ{std::numeric_limits<int>::max()}
    , m_data{0}
    , m_mapType{HeightMapType::Unknown}
{

}

HeightMap::HeightMap(const HeightMap &other)
    : m_chunkX{other.m_chunkX}
    , m_chunkZ{other.m_chunkZ}
    , m_data{other.m_data}
    , m_mapType{other.m_mapType}
{

}

HeightMap::HeightMap(HeightMap &&other) noexcept
    : m_chunkX{std::move(other.m_chunkX)}
    , m_chunkZ{std::move(other.m_chunkZ)}
    , m_data{std::move(other.m_data)}
    , m_mapType{std::move(other.m_mapType)}
{

}

HeightMap::HeightMap(const int chunkX, const int chunkZ)
    : m_chunkX{chunkX}
    , m_chunkZ{chunkZ}
    , m_data{0}
    , m_mapType{HeightMapType::Unknown}
{

}

HeightMap::~HeightMap()
{

}

HeightMap& HeightMap::operator=(const HeightMap &other)
{
    if(this != &other) {
        m_chunkX    = other.m_chunkX;
        m_chunkZ    = other.m_chunkZ;
        m_data      = other.m_data;
        m_mapType   = other.m_mapType;
    }
    return *this;
}

HeightMap& HeightMap::operator=(HeightMap &&other) noexcept
{
    if(this != &other) {
        m_chunkX    = std::move(other.m_chunkX);
        m_chunkZ    = std::move(other.m_chunkZ);
        m_data      = std::move(other.m_data);
        m_mapType   = std::move(other.m_mapType);
    }
    return *this;
}

bool HeightMap::operator==(const HeightMap &other)
{
    if(this == &other) {
        return true;
    }

    if(m_chunkX != other.m_chunkZ
       || m_chunkZ != other.m_chunkZ
       || m_data != other.m_data
       || m_mapType != other.m_mapType) {
        return false;
    }

    return true;
}

bool HeightMap::operator!=(const HeightMap &other)
{
    return !(*this == other);
}

void HeightMap::setChunkX(const int chunkX)
{
    m_chunkX = chunkX;
}

int HeightMap::getChunkX() const
{
    return m_chunkX;
}

void HeightMap::setChunkZ(const int chunkZ)
{
    m_chunkZ = chunkZ;
}

int HeightMap::getChunkZ() const
{
    return m_chunkZ;
}

void HeightMap::setAt(const int index, const int value)
{
    if(index < 0 || index >= BlockCount) {
        throw std::out_of_range("Block index out of range: " + std::to_string(index));
    }
    m_data[index] = value;
}

void HeightMap::setAt(const int x, const int z, const int value)
{
    if(x < 0 || x >= BlockWidth || z < 0 || z >= BlockWidth) {
        throw std::out_of_range("Block coordinates out of range.");
    }
    m_data[z * BlockWidth + x] = value;
}

int HeightMap::getAt(const int index) const
{
    if(index < 0 || index >= BlockCount) {
        throw std::out_of_range("Block index out of range." + std::to_string(index));
    }
    return m_data[index];
}

int HeightMap::getAt(const int x, const int z) const
{
    if(x < 0 || x >= BlockWidth || z < 0 || z >= BlockWidth) {
        throw std::out_of_range("Block coordinates out of range.");
    }
    return m_data[z * BlockWidth + x];
}

const std::array<int, BlockCount>& HeightMap::getData() const
{
    return m_data;
}

std::array<int, BlockCount>& HeightMap::getData()
{
    return m_data;
}

} // namespace anvil
