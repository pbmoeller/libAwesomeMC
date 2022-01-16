#ifndef AESOMEMC_ANVIL_HEIGHTMAP_HPP
#define AESOMEMC_ANVIL_HEIGHTMAP_HPP

// AwesomeMC
#include <AwesomeMC/constants.hpp>

// STL
#include <array>

namespace anvil
{

class HeightMap
{
public:
    enum class HeightMapType
    {
        MotionBlocking,
        MotionBlockingNoLeaves,
        OceanFloor,
        WorldSurface,
        Unknown,
    };

    HeightMap();
    HeightMap(const HeightMap &other);
    HeightMap(HeightMap &&other) noexcept;
    HeightMap(const int chunkX, const int chunkZ);
    ~HeightMap();

    HeightMap& operator=(const HeightMap &other);
    HeightMap& operator=(HeightMap &&other) noexcept;

    bool operator==(const HeightMap &other);
    bool operator!=(const HeightMap &other);

    void setChunkX(const int chunkX);
    int getChunkX() const;
    void setChunkZ(const int chunkZ);
    int getChunkZ() const;

    void setAt(const int index, const int value);
    void setAt(const int x, const int z, const int value);
    int getAt(const int index) const;
    int getAt(const int x, const int z) const;

    const std::array<int, BlockCount>& getData() const;
    std::array<int, BlockCount>& getData();

private:
    int m_chunkX;
    int m_chunkZ;
    std::array<int, BlockCount> m_data;
    HeightMapType m_mapType;
};

}

#endif // AESOMEMC_ANVIL_HEIGHTMAP_HPP