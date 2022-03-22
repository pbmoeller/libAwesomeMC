#include <AwesomeMC/anvil/region.hpp>
#include <AwesomeMC/nbt/nbt_read.hpp>
#include <AwesomeMC/util/conversion.hpp>
#include <AwesomeMC/util/byte_swap.hpp>
#include <AwesomeMC/util/compression.hpp>

// STL
#include <utility>
#include <stdexcept>
#include <regex>
#include <filesystem>

namespace amc
{

const std::regex RegionFilePattern = std::regex("r\\.([-]?[0-9]+)\\.([-]?[0-9]+)\\.mca");

Region::Region()
    : m_x{0}
    , m_z{0}
    , m_filename{""}
    , m_chunks{new std::array<Chunk, ChunkCount>()}
    , m_loadedChunks(ChunkCount, false)
{

}

Region::Region(int x, int z)
    : m_x{x}
    , m_z{z}
    , m_filename{""}
    , m_chunks{new std::array<Chunk, ChunkCount>()}
    , m_loadedChunks(ChunkCount, false)
{

}

Region::Region(const Region &other)
    : m_chunks{new std::array<Chunk, ChunkCount>()}
{
    *this = other;
}

Region::Region(Region &&other) noexcept
    : m_chunks(nullptr)
{
    *this = std::move(other);
}

Region::~Region()
{
    if(m_chunks) {
        delete m_chunks;
    }
}

Region& Region::operator=(const Region &other)
{
    if(this != &other) {
        m_x                 = other.m_x;
        m_z                 = other.m_z;
        m_regionHeader      = other.m_regionHeader;
        m_filename          = other.m_filename;
        m_loadedChunks      = other.m_loadedChunks;

        for(unsigned int i = 0; i < ChunkCount; ++i) {
            (*m_chunks)[i] = (*other.m_chunks)[i];
        }
    }
    return *this;
}

Region& Region::operator=(Region &&other) noexcept
{
    if(this != &other) {
        m_x                 = std::move(other.m_x);
        m_z                 = std::move(other.m_z);
        m_regionHeader      = std::move(other.m_regionHeader);
        m_filename          = std::move(other.m_filename);
        m_loadedChunks      = std::move(other.m_loadedChunks);
        std::swap(m_chunks, other.m_chunks);
    }
    return *this;
}

bool Region::operator==(const Region &other)
{
    if(this == &other) {
        return true;
    }

    // TODO: Check if partiallyLoaded and filename should be compared or only the "real" data, maybe second function.
    if(m_x != other.m_x
       || m_z != other.m_z
       || m_regionHeader != other.m_regionHeader
       || m_filename != other.m_filename
       || m_loadedChunks != other.m_loadedChunks) {
        return false;
    }

    for(unsigned int i = 0; i < ChunkCount; ++i) {
        if((*m_chunks)[i] != (*other.m_chunks)[i]) {
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
    return *m_chunks;
}

Chunk& Region::getChunkAt(unsigned int index)
{
    return (*m_chunks)[index];
}

const Chunk& Region::getChunkAt(unsigned int index) const
{
    return (*m_chunks)[index];
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
    convertBlockWorld2ChunkRegion(blockX, blockZ, xRegion, zRegion);
    unsigned chunkIdx = zRegion * ChunkWidth + xRegion;

    // Get data from chunk
    return getChunkAt(chunkIdx).getBlockAt(blockX, blockY, blockZ);
}

HeightMap Region::getHeightMap(const int chunkWorldX,
                               const int chunkWorldZ,
                               HeightMap::MapType mapType) const
{
    int chunkX = 0;
    int chunkZ = 0;
    convertChunkWorld2ChunkRegion(chunkWorldX, chunkWorldZ, chunkX, chunkZ);
    return getChunkAt(chunkZ * ChunkWidth + chunkX).getHeightMap(mapType);
}

void Region::loadFromFile(const std::string &filename)
{
    loadPartiallyFromFile(filename);

    loadAllChunks();
}

void Region::loadPartiallyFromFile(const std::string &filename)
{
    // Check if file name is valid.
    int x = 0;
    int z = 0;
    if(!validateAndParseRegionFilename(filename, x, z)) {
        throw std::runtime_error("Invalid region filename.");
    }

    // Open filestream
    std::ifstream stream(filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open region file.");
    }

    m_x = x;
    m_z = z;
    m_filename = filename;

    // Read region file header data
    if(!readRegionHeader(stream)) {
        throw std::runtime_error("Failed to read region header.");
    }
}

void Region::loadChunkAt(unsigned int index)
{
    ChunkInfo &info = m_regionHeader.getChunkInfoAt(index);

    // If the info is empty, we are done here
    if(info.isEmpty()) {
        return;
    }

    // Open filestream
    std::ifstream stream(m_filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open region file.");
    }

    readChunkData(stream, info, index);
}

void Region::loadAllChunks()
{
    // Open filestream
    std::ifstream stream(m_filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open region file.");
    }

    // Read Chunks from file and set it to region
    for(unsigned int index = 0; index < ChunkCount; ++index) {
        ChunkInfo &info = m_regionHeader.getChunkInfoAt(index);

        // If chunk is already loaded or the info is empty, skip this chunk
        if(m_loadedChunks[index] || info.isEmpty()) {
            continue;
        }

        readChunkData(stream, info, index);
    }
}

void Region::readChunkData(std::ifstream &filestream, ChunkInfo &chunkInfo, unsigned int index)
{
    // Seek to beginning of chunk data
    uint32_t offset = chunkInfo.getOffset() * SectorSize;
    filestream.seekg(offset, std::ios::beg);

    // Get size of binary data and compression type
    uint32_t dataSize = 0;
    CompressionType compressionType = CompressionType::Uncompressed;
    filestream.read((char*)&dataSize, sizeof(uint32_t));
    dataSize = bswap(dataSize);
    filestream.read((char*)&compressionType, sizeof(char));

    chunkInfo.setCompression(compressionType);

    // Read the chunk data
    std::vector<unsigned char> chunkData(dataSize, 0);
    filestream.read((char*)&chunkData[0], dataSize - 1);

    switch(compressionType) {
        case CompressionType::GZip:
            if(!inflate_gzip(chunkData)) {
                throw std::runtime_error("Failed to uncompress chunk data (gzip).");
            }
            break;
        case CompressionType::Zlib:
            if(!inflate_zlib(chunkData)) {
                throw std::runtime_error("Failed to uncompress chunk data (zlib).");
            }
            break;
        case CompressionType::Uncompressed:
            break;
        default:
            throw std::runtime_error("Unknown compression type.");
    }

    // Parse nbt data.
    getChunkAt(index).setRootTag(readNbtData(chunkData));
    m_loadedChunks[index] = true;
}

bool Region::readRegionHeader(std::ifstream &filestream)
{
        // Check if file is still open
    if(!filestream.is_open()) {
        throw std::runtime_error("Failed to read from region file.");
    }

    // Read first half of header data (Chunk Location Data) => Bytes 0 - 4095
    uint32_t value = 0;
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        filestream.read((char*)&value, sizeof(uint32_t));
        value = bswap(value);
        uint32_t size = value & 0x000000FF;
        uint32_t offset = (value & 0xFFFFFF00) >> 8;
        m_regionHeader.getChunkInfoAt(i).setOffset(offset);
        m_regionHeader.getChunkInfoAt(i).setLength(size);
    }

    // Read second half of header data (Chunk Timestamp Data) => Bytes 4096 - 8191
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        filestream.read((char*)&value, sizeof(uint32_t));
        value = bswap(value);
        m_regionHeader.getChunkInfoAt(i).setTimestamp(value);
    }

    return true;
}

bool Region::validateRegionFilename(const std::string &filename)
{
    std::filesystem::path filepath{filename};
    std::string convertedFilename = filepath.make_preferred().string();

    // Extract filename from filename with path
    std::string name = convertedFilename.substr(convertedFilename.find_last_of(std::filesystem::path::preferred_separator) + 1);

    // Search for region file pattern : 'r.X.Z.mca'
    std::cmatch ref;
    return std::regex_match(name.c_str(), ref, RegionFilePattern);
}

bool Region::validateAndParseRegionFilename(const std::string &filename, int &x, int &z)
{
    std::filesystem::path filepath{filename};
    std::string convertedFilename = filepath.make_preferred().string();

    // Extract filename from filename with path
    std::string name = convertedFilename.substr(convertedFilename.find_last_of(std::filesystem::path::preferred_separator) + 1);

    // Search for region file pattern : 'r.X.Z.mca'
    std::cmatch ref;
    if(!std::regex_match(name.c_str(), ref, RegionFilePattern)) {
        return false;
    }

    // If the pattern was found set X and Z values and return success
    x = std::atoi(ref[1].str().c_str());
    z = std::atoi(ref[2].str().c_str());
    return true;
}

} // namespace amc