#ifndef AWESOMEMC_ANVIL_REGION_HPP
#define AWESOMEMC_ANVIL_REGION_HPP

// AwesomeMC
#include <AwesomeMC/constants.hpp>
#include <AwesomeMC/anvil/region_header.hpp>
#include <AwesomeMC/anvil/chunk.hpp>
#include <AwesomeMC/anvil/heightmap.hpp>
#include <AwesomeMC/util/compression.hpp>

// STL
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

namespace amc
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

    Chunk& getChunkAt(int index);
    const Chunk& getChunkAt(int index) const;

    std::vector<int32_t> getBiomesAt(int chunkX,
                                     int chunkZ) const;
    int32_t getBiomeAt(int chunkX,
                       int chunkZ,
                       int blockX,
                       int blockY,
                       int blockZ) const;

    Block getBlockAt(const int blockX,
                     const int blockY,
                     const int blockZ) const;
    
    HeightMap getHeightMap(const int chunkX,
                           const int chunkZ,
                           HeightMap::MapType mapType = HeightMap::MapType::WorldSurface) const;

    void loadFromFile(const std::string &filename);
    void loadPartiallyFromFile(const std::string &filename);
    void loadChunkAt(int index);
    void loadAllChunks();

    bool saveToFile(const std::string &filename);

private:
    void readChunkData(std::ifstream &filestream, int index);
    bool readRegionHeader(std::ifstream &filestream);

    // Static functions
public:
    static bool validateRegionFilename(const std::string &filename);
    static bool validateAndParseRegionFilename(const std::string &filename, int &x, int &z);

    // Private variables
private:
    int m_x;
    int m_z;
    std::string m_filename;

    std::vector<bool> m_loadedChunks;
    std::vector<Chunk> m_chunks;
    std::vector<CompressionType> m_chunkCompression;

    // Only used during loading
    std::unique_ptr<RegionHeader> m_regionHeader;
};

} // namespace amc

#endif // AWESOMEMC_ANVIL_REGION_HPP