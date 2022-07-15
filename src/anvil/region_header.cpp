#include <AwesomeMC/anvil/region_header.hpp>
#include <AwesomeMC/constants.hpp>
#include <AwesomeMC/util/byte_swap.hpp>

// STL
#include <stdexcept>
#include <utility>
#include <string>

namespace amc
{

//RegionHeader::RegionHeader()
//    : m_chunkInfo(new std::array<ChunkInfo, ChunkCount>())
//{
//    for(unsigned int i = 0; i < ChunkCount; ++i) {
//        (*m_chunkInfo)[i] = ChunkInfo();
//    }
//}
//
//RegionHeader::RegionHeader(const RegionHeader &other)
//    : m_chunkInfo(new std::array<ChunkInfo, ChunkCount>())
//{
//    *this = other;
//}
//
//RegionHeader::RegionHeader(RegionHeader &&other) noexcept
//    : m_chunkInfo(nullptr)
//{
//    *this = std::move(other);
//}
//
//RegionHeader::RegionHeader(const std::array<ChunkInfo, ChunkCount> &info)
//    : m_chunkInfo(new std::array<ChunkInfo, ChunkCount>())
//{
//    for(unsigned int i = 0; i < ChunkCount; ++i) {
//        (*m_chunkInfo)[i] = info[i];
//    }
//}
//
//RegionHeader::~RegionHeader()
//{
//    if(m_chunkInfo) {
//        delete m_chunkInfo;
//    }
//}
//
//RegionHeader& RegionHeader::operator=(const RegionHeader &other)
//{
//    if(this != &other) {
//        for(unsigned int i = 0; i < ChunkCount; ++i) {
//            (*m_chunkInfo)[i] = (*other.m_chunkInfo)[i];
//        }
//    }
//    return *this;
//}
//
//RegionHeader& RegionHeader::operator=(RegionHeader &&other) noexcept
//{
//    if(this != &other) {
//        std::swap(m_chunkInfo, other.m_chunkInfo);
//    }
//    return *this;
//}
//
//bool RegionHeader::operator==(const RegionHeader &other)
//{
//    if(this == &other) {
//        return true;
//    }
//
//    for(unsigned int i = 0; i < ChunkCount; ++i) {
//        if((*m_chunkInfo)[i] != (*other.m_chunkInfo)[i]) {
//            return false;
//        }
//    }
//    return true;
//}
//
//bool RegionHeader::operator!=(const RegionHeader &other)
//{
//    return !(*this == other);
//}
//
//unsigned int RegionHeader::getRegionCount() const
//{
//    unsigned int count{0};
//
//    for(unsigned int i = 0; i < ChunkCount; ++i) {
//        if(!(*m_chunkInfo)[i].isEmpty()) {
//            ++count;
//        }
//    }
//    return count;
//}
//
//std::vector<char> RegionHeader::getRegionData() const
//{
//    // TODO : Implement
//    return std::vector<char>();
//}
//
//const std::array<ChunkInfo, ChunkCount>& RegionHeader::getChunkInfo() const
//{
//    return *m_chunkInfo;
//}
//
//ChunkInfo& RegionHeader::getChunkInfoAt(unsigned int index)
//{
//    if(index >= ChunkCount) {
//        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
//    }
//    return (*m_chunkInfo)[index];
//}
//
//const ChunkInfo& RegionHeader::getChunkInfoAt(unsigned int index) const
//{
//    if(index >= ChunkCount) {
//        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
//    }
//    return (*m_chunkInfo)[index];
//}
//
//void RegionHeader::setChunkInfo(const std::array<ChunkInfo, ChunkCount> &info)
//{
//    for(unsigned int i = 0; i < ChunkCount; ++i) {
//        (*m_chunkInfo)[i] = info[i];
//    }
//}
//
//void RegionHeader::setChunkInfoAt(unsigned int index, const ChunkInfo &info)
//{
//    if(index >= ChunkCount) {
//        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
//    }
//    (*m_chunkInfo)[index] = info;
//}

// New implementation

RegionHeader::RegionHeader()
{
    m_data.resize(HeaderSize, 0);
}

RegionHeader::RegionHeader(const RegionHeader &other)
{
    *this = other;
}

RegionHeader::RegionHeader(RegionHeader &&other) noexcept
{
    *this = std::move(other);
}

RegionHeader::RegionHeader(const std::vector<unsigned char> &data)
{
    if(data.size() != HeaderSize) {
        throw std::runtime_error(std::string("Invalid data size for RegionHeader: ") 
                                 + std::to_string(data.size()));
    }
    m_data = data;
}

RegionHeader::RegionHeader(std::vector<unsigned char> &&data)
{
    if(data.size() != HeaderSize) {
        throw std::runtime_error(std::string("Invalid data size for RegionHeader: ")
                                 + std::to_string(data.size()));
    }
    m_data = std::move(data);
}

RegionHeader::~RegionHeader()
{

}

RegionHeader& RegionHeader::operator=(const RegionHeader &other)
{
    if(this != &other) {
        m_data = other.m_data;
    }
    return *this;
}

RegionHeader& RegionHeader::operator=(RegionHeader &&other) noexcept
{
    if(this != &other) {
        m_data = std::move(other.m_data);
    }
    return *this;
}


bool RegionHeader::operator==(const RegionHeader &other)
{
    if(this == &other) {
        return true;
    }
    return m_data == other.m_data;
}

bool RegionHeader::operator!=(const RegionHeader &other)
{
    return !(*this == other);
}

int RegionHeader::getChunkCount() const
{
    int count{0};
    const uint32_t *dataAsInt = reinterpret_cast<const uint32_t*>(m_data.data());
    for(int index = 0; index < ChunkCount; ++index) {
        if(((dataAsInt[index] & 0xFFFFFF00) >> 8) > 0) {
            ++count;
        }
    }
    return count;
}

std::vector<unsigned char> RegionHeader::getData() const
{
    return m_data;
}

bool RegionHeader::isEmpty(const int index) const
{
    return getOffset(index) == 0;
}

int RegionHeader::getOffset(const int index) const
{
    const uint32_t *dataAsInt = reinterpret_cast<const uint32_t *>(m_data.data());
    return ((bswap(dataAsInt[index]) & 0xFFFFFF00) >> 8);
}

int RegionHeader::getByteOffset(const int index) const
{
    return getOffset(index) * SectorSize;
}

int RegionHeader::getSize(const int index) const
{
    const uint32_t *dataAsInt = reinterpret_cast<const uint32_t *>(m_data.data());
    return (bswap(dataAsInt[index]) & 0x000000FF);
}

int RegionHeader::getByteSize(const int index) const
{
    return getSize(index) * SectorSize;
}

int RegionHeader::getTimestamp(const int index) const
{
    const uint32_t *dataAsInt = reinterpret_cast<const uint32_t *>(m_data.data());
    return bswap(dataAsInt[ChunkCount + index]);
}

void RegionHeader::setChunkData(const int index,
                                const int offset,
                                const int size,
                                const int timestamp)
{
    uint32_t *dataAsInt = reinterpret_cast<uint32_t *>(m_data.data());

    uint32_t value = ((static_cast<uint32_t>(offset) << 8) & 0xFFFFFF00)
        + (static_cast<uint32_t>(size) & 0x000000FF);

    dataAsInt[index] = bswap(value);
    dataAsInt[ChunkCount + index] = bswap(timestamp);
}

} // namespace amc