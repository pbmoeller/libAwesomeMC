#ifndef AWESOMEMC_ANVIL_REGION_HPP
#define AWESOMEMC_ANVIL_REGION_HPP

// AwesomeMC
#include <AwesomeMC/constants.hpp>
#include <AwesomeMC/anvil/region_header.hpp>
#include <AwesomeMC/anvil/chunk.hpp>
#include <AwesomeMC/anvil/heightmap.hpp>

// STL
#include <array>
#include <vector>
#include <string>
#include <fstream>

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

    Block getBlockAt(const int blockX,
                     const int blockY,
                     const int blockZ) const;
    
    HeightMap getHeightMap(const int chunkX,
                           const int chunkZ,
                           HeightMap::MapType mapType = HeightMap::MapType::WorldSurface) const;

    void loadFromFile(const std::string &filename);
    void loadPartiallyFromFile(const std::string &filename);
    void loadChunkAt(unsigned int index);
    void loadAllChunks();

private:
    void readChunkData(std::ifstream &filestream, ChunkInfo &chunkInfo, unsigned int index);
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

    RegionHeader m_regionHeader;
    std::array<Chunk, ChunkCount> *m_chunks;
    std::vector<bool> m_loadedChunks;
};

} // namespace amc

#endif // AWESOMEMC_ANVIL_REGION_HPP