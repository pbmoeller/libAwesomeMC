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
#include <fstream>
#include <iomanip>

namespace amc
{

const std::regex RegionFilePattern = std::regex("r\\.([-]?[0-9]+)\\.([-]?[0-9]+)\\.mca");

Region::Region()
    : m_x{0}
    , m_z{0}
    , m_filename{""}
    , m_loadedChunks(ChunkCount, false)
    , m_chunks()
    , m_chunkCompression(ChunkCount, CompressionType::Zlib)
    , m_regionHeader(nullptr)
{
    m_chunks.resize(ChunkCount);
}

Region::Region(int x, int z)
    : m_x{x}
    , m_z{z}
    , m_filename{""}
    , m_loadedChunks(ChunkCount, false)
    , m_chunks()
    , m_chunkCompression(ChunkCount, CompressionType::Zlib)
    , m_regionHeader(nullptr)
{
    m_chunks.resize(ChunkCount);
}

Region::Region(const Region &other)
    : m_chunks()
{
    m_chunks.resize(ChunkCount);
    *this = other;
}

Region::Region(Region &&other) noexcept
    : m_chunks()
{
    m_chunks.resize(ChunkCount);
    *this = std::move(other);
}

Region::~Region()
{
    
}

Region& Region::operator=(const Region &other)
{
    if(this != &other) {
        m_x                 = other.m_x;
        m_z                 = other.m_z;
        m_filename          = other.m_filename;
        m_loadedChunks      = other.m_loadedChunks;
        m_chunks            = other.m_chunks;
        m_chunkCompression  = other.m_chunkCompression;
        *m_regionHeader     = *other.m_regionHeader;    // TODO: Check !!!

        /*for(unsigned int i = 0; i < ChunkCount; ++i) {
            (m_chunks)[i] = (other.m_chunks)[i];
        }*/
    }
    return *this;
}

Region& Region::operator=(Region &&other) noexcept
{
    if(this != &other) {
        m_x                 = std::move(other.m_x);
        m_z                 = std::move(other.m_z);
        m_filename          = std::move(other.m_filename);
        m_loadedChunks      = std::move(other.m_loadedChunks);
        m_chunks            = std::move(other.m_chunks);
        m_chunkCompression  = std::move(other.m_chunkCompression);
        m_regionHeader      = std::move(other.m_regionHeader);
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
       // || m_regionHeader != other.m_regionHeader
       // || m_filename != other.m_filename
       // || m_loadedChunks != other.m_loadedChunks
       // || m_chunkCompression != other.m_chunkCompression
       ) {
        return false;
    }

    for(unsigned int i = 0; i < ChunkCount; ++i) {
        if(m_chunks[i].isEmpty() && other.m_chunks[i].isEmpty()) {
            continue;
        }

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

Chunk& Region::getChunkAt(unsigned int index)
{
    return m_chunks[index];
}

const Chunk& Region::getChunkAt(unsigned int index) const
{
    return m_chunks[index];
}

std::vector<int32_t> Region::getBiomesAt(unsigned int chunkX,
                                         unsigned int chunkZ) const
{
    // Check if chunk coodinates are valid
    if(chunkX >= ChunkWidth || chunkZ >= ChunkWidth) {
        throw std::out_of_range("Coordinates out of range");
    }

    // Calculate the requested chunk
    unsigned int chunkIdx = chunkIndexFromXZ(chunkX, chunkZ);

    // Get data from chunk
    return getChunkAt(chunkIdx).getBiomes();
}

int32_t Region::getBiomeAt(unsigned int chunkX,
                           unsigned int chunkZ,
                           unsigned int blockX, 
                           int blockY, 
                           unsigned int blockZ) const
{
    // Check if chunk coodinates are valid
    if(chunkX >= ChunkWidth || chunkZ >= ChunkWidth) {
        throw std::out_of_range("Coordinates out of range");
    }

    // Calculate the requested chunk
    unsigned int chunkIdx = chunkIndexFromXZ(chunkX, chunkZ);

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
    int chunkX = 0;
    int chunkZ = 0;
    convertBlockWorld2ChunkRegion(blockX, blockZ, chunkX, chunkZ);
    unsigned int chunkIdx = chunkIndexFromXZ(chunkX, chunkZ);

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
    unsigned int chunkIdx = chunkIndexFromXZ(chunkX, chunkZ);
    return getChunkAt(chunkIdx).getHeightMap(mapType);
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
    // If the chunk is marked as empty, we are done here
    if(m_regionHeader->isEmpty(index)) {
        return;
    }

    // Open filestream
    std::ifstream stream(m_filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open region file.");
    }

    readChunkData(stream, index);
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
        // If chunk is already loaded or the info is empty, skip this chunk
        if(m_loadedChunks[index] || m_regionHeader->isEmpty(index)) {
            continue;
        }

        readChunkData(stream, index);
    }

    // Not needed anymore
    m_regionHeader.reset();
}

void Region::readChunkData(std::ifstream &filestream, unsigned int index)
{
    // Seek to beginning of chunk data
    uint32_t offset = m_regionHeader->getByteOffset(index);
    filestream.seekg(offset, std::ios::beg);

    // Get size of binary data and compression type
    uint32_t dataSize = 0;
    CompressionType compressionType = CompressionType::Uncompressed;
    filestream.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
    dataSize = bswap(dataSize);
    filestream.read(reinterpret_cast<char*>(&compressionType), sizeof(char));

    // Read the chunk data
    std::vector<unsigned char> chunkData(dataSize - 1, 0);
    filestream.read(reinterpret_cast<char*>(&chunkData[0]), dataSize - 1);

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
    m_chunkCompression[index] = compressionType;
    m_loadedChunks[index] = true;
}

bool Region::readRegionHeader(std::ifstream &filestream)
{
    // Check if file is still open
    if(!filestream.is_open()) {
        throw std::runtime_error("Failed to read from region file.");
    }

    std::vector<unsigned char> data(HeaderSize, 0);
    filestream.read(reinterpret_cast<char *>(data.data()), HeaderSize);

    // Delete old header before setting the new.
    if(m_regionHeader) {
        m_regionHeader.reset();
    }
    m_regionHeader = std::make_unique<RegionHeader>(std::move(data));
    
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

bool Region::saveToFile(const std::string &filename)
{
    // Init data vector for region data
    std::vector<unsigned char> regionData(HeaderSize, 0);
    int storageDataIndex = ChunkDataOffset;

    // Init RegionHeader
    RegionHeader regionHeader;

    // Iterate over all Chunks in region and write them to the data vector
    for(int index = 0; index < ChunkCount; ++index) {
        // get chunks compression information
        CompressionType compression = m_chunkCompression[index];
        CompoundTag *rootTag = m_chunks[index].getRootTag();

        if(!rootTag) {
            regionHeader.setChunkData(index, 0, 0, 0);
        } else {
            // Get data and compress
            std::vector<unsigned char> chunkData = rootTag->getData(false);
            if(compression == CompressionType::Zlib) {
                if(!deflate_zlib(chunkData)) {
                    throw std::runtime_error("Failed to compress chunk data (zlib).");
                }
            } else if(compression == CompressionType::GZip) {
                // this is super rarly used for region data,
                // but just in case someone asks for it.
                if(!deflate_gzip(chunkData)) {
                    throw std::runtime_error("Failed to compress chunk data (gzip).");
                }
            } else if(compression == CompressionType::Uncompressed) {
                // this is even more rarly used for region data,
                // but luckily we have to do nothing.
            }

            // Calculate chunk storage space
            int length          = 1 + static_cast<int>(chunkData.size());
            int payload         = 4 + length;
            int paddingSector   = (((payload % SectorSize) > 0) ? 1 : 0);
            int sectors         = payload / SectorSize + paddingSector;
            int storageSize     = sectors * SectorSize;

            // Set header data
            regionHeader.setChunkData(index, storageDataIndex / SectorSize, sectors, 0);

            // Append chunk data to region data
            regionData.resize(regionData.size() + storageSize, 0);
            length = bswap(length);
            std::memcpy(&regionData[storageDataIndex], reinterpret_cast<char *>(&length), 4);
            std::memcpy(&regionData[storageDataIndex + 4], reinterpret_cast<char *>(&compression), 1);
            std::memcpy(&regionData[storageDataIndex + 5], chunkData.data(), chunkData.size());

            // Increase the data index
            storageDataIndex += storageSize;
        }
    }

    // Write region header data
    std::memcpy(&regionData[0], regionHeader.getData().data(), HeaderSize);

    // Write data to file
    std::ofstream stream(filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open new file.");
    }
    stream.write(reinterpret_cast<char *>(regionData.data()), regionData.size());
    stream.close();

    return true;
}

} // namespace amc