#include <AwesomeMC/anvil/anvil_read.hpp>

// AwesomeMC
#include <AwesomeMC/anvil/constants.hpp>
#include <AwesomeMC/nbt/nbt_read.hpp>
#include <AwesomeMC/util/byte_swap.hpp>
#include <AwesomeMC/util/compression.hpp>

// STL
#include <fstream>
#include <regex>
#include <stdexcept>
#include <iostream>

namespace anvil
{

// Constants
#ifdef _MSC_VER
const char DirectorySeparator = '\\';
#elif defined(__linux__)
const char DirectorySeparator = '/';
#endif

const std::regex RegionFilePattern = std::regex("r\\.([-]?[0-9]+)\\.([-]?[0-9]+)\\.mca");



bool checkRegionFilename(const std::string &filename, int &x, int &z)
{
    // Extract filename from filename with path
    std::string name = filename.substr(filename.find_last_of(DirectorySeparator) + 1);

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

Region loadRegion(const std::string &filename)
{
    // Check if file name is valid.
    int x = 0;
    int z = 0;
    if(!checkRegionFilename(filename, x, z)) {
        throw std::runtime_error("Invalid region filename.");
    }

    // Open filestream
    std::ifstream stream(filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error("Failed to open region file.");
    }

    // Create Region.
    Region region(x, z);

    // Read region file data
    if(!readRegionHeader(stream, region)) {
        throw std::runtime_error("Failed to read region header.");
    }

    // Read region file data
    if(!readRegionChunks(stream, region)) {
        throw std::runtime_error("Failed to read chunk data.");
    }

    return region;
}

bool readRegionHeader(std::ifstream &filestream, Region &region)
{
    // Check if file is still open
    if(!filestream.is_open()) {
        throw std::runtime_error("Failed to read from region file.");
    }

    // Read first half of header data (Chunk Location Data) => Bytes 0 - 4095
    uint32_t value = 0;
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        filestream.read((char*)&value, sizeof(uint32_t));
        value = util::bswap(value);
        uint32_t size   = value & 0x000000FF;
        uint32_t offset = (value & 0xFFFFFF00) >> 8;
        region.getRegionHeader().getChunkInfoAt(i).setOffset(offset);
        region.getRegionHeader().getChunkInfoAt(i).setLength(size);
    }

    // Read second half of header data (Chunk Timestamp Data) => Bytes 4096 - 8191
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        filestream.read((char*)&value, sizeof(uint32_t));
        value = util::bswap(value);
        region.getRegionHeader().getChunkInfoAt(i).setTimestamp(value);
    }

    return true;
}

bool readRegionChunks(std::ifstream &filestream, Region &region)
{
    // Check if file is still open
    if(!filestream.is_open()) {
        throw std::runtime_error("Failed to read from region file.");
    }

    // Read Chunks from file and set it to region
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        ChunkInfo &info = region.getRegionHeader().getChunkInfoAt(i);

        // If the info is empty, skip this chunk
        if(info.isEmpty()) {
            continue;
        }

        // Seek to beginning of chunk data
        uint32_t offset = info.getOffset() * SectorSize;
        filestream.seekg(offset, std::ios::beg);

        // Get size of binary data and compression type
        uint32_t dataSize = 0;
        ChunkInfo::CompressionType compressionType = ChunkInfo::CompressionType::Uncompressed;
        filestream.read((char*)&dataSize, sizeof(uint32_t));
        dataSize = util::bswap(dataSize);
        filestream.read((char*)&compressionType, sizeof(char));

        info.setCompression(compressionType);

        // Read the chunk data
        std::vector<unsigned char> chunkData(dataSize, 0);
        filestream.read((char*)&chunkData[0], dataSize - 1);

        switch(compressionType) {
            case ChunkInfo::CompressionType::GZip:
                if(!util::inflate_gzip(chunkData)) {
                    throw std::runtime_error("Failed to uncompress chunk data (gzip).");
                }
                break;
            case ChunkInfo::CompressionType::Zlib:
                if(!util::inflate_zlib(chunkData)) {
                    throw std::runtime_error("Failed to uncompress chunk data (zlib).");
                }
                break;
            case ChunkInfo::CompressionType::Uncompressed:
                break;
            default:
                throw std::runtime_error("Unknown compression type.");
        }

        // Parse nbt data.
        region.getChunkAt(i).setRootTag(nbt::readNbtData(chunkData));
    }

    return true;
}

} // namespace anvil