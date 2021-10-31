#include "anvil/region_header.hpp"

// STL
#include <stdexcept>
#include <utility>
#include <string>

namespace anvil
{

RegionHeader::RegionHeader()
{
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        m_info[i] = ChunkInfo();
    }
}

RegionHeader::RegionHeader(const RegionHeader &other)
{
    *this = other;
}

RegionHeader::RegionHeader(RegionHeader &&other) noexcept
{
    *this = std::move(other);
}

RegionHeader::RegionHeader(const ChunkInfo(&info)[ChunkCount])
{
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        m_info[i] = info[i];
    }
}

RegionHeader::~RegionHeader()
{

}

RegionHeader& RegionHeader::operator=(const RegionHeader &other)
{
    if(this != &other) {
        for(unsigned int i = 0; i < ChunkCount; ++i) {
            m_info[i] = other.m_info[i];
        }
    }
    return *this;
}

RegionHeader& RegionHeader::operator=(RegionHeader &&other) noexcept
{
    if(this != &other) {
        for(unsigned int i = 0; i < ChunkCount; ++i) {
            m_info[i] = other.m_info[i];
        }
    }
    return *this;
}

bool RegionHeader::operator==(const RegionHeader &other)
{
    if(this == &other) {
        return true;
    }

    for(unsigned int i = 0; i < ChunkCount; ++i) {
        if(m_info[i] != other.m_info[i]) {
            return false;
        }
    }
    return true;
}

bool RegionHeader::operator!=(const RegionHeader &other)
{
    return !(*this == other);
}

unsigned int RegionHeader::getRegionCount() const
{
    unsigned int count{0};

    for(unsigned int i = 0; i < ChunkCount; ++i) {
        if(!m_info[i].isEmpty()) {
            ++count;
        }
    }
    return count;
}

std::vector<char> RegionHeader::getRegionData() const
{
    // TODO
    return std::vector<char>();
}

const ChunkInfo(&RegionHeader::getChunkInfo() const)[ChunkCount]
{
    return m_info;
}

ChunkInfo& RegionHeader::getChunkInfoAt(unsigned int index)
{
    if(index >= ChunkCount) {
        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
    }
    return m_info[index];
}

const ChunkInfo& RegionHeader::getChunkInfoAt(unsigned int index) const
{
    if(index >= ChunkCount) {
        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
    }
    return m_info[index];
}

void RegionHeader::setChunkInfo(const ChunkInfo(&info)[ChunkCount])
{
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        m_info[i] = info[i];
    }
}

void RegionHeader::setChunkInfoAt(unsigned int index, const ChunkInfo &info)
{
    if(index >= ChunkCount) {
        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
    }
    m_info[index] = info;
}

} // namespace anvil