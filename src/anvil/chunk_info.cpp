#include "anvil/chunk_info.hpp"

// STL
#include <utility>

namespace anvil
{

ChunkInfo::ChunkInfo()
    : m_offset{0}
    , m_length{0}
    , m_timestamp{0}
    , m_compression{CompressionType::GZip}
{

}

ChunkInfo::ChunkInfo(const ChunkInfo &other)
{
    *this = other;
}

ChunkInfo::ChunkInfo(ChunkInfo &&other) noexcept
{
    *this = std::move(other);
}

ChunkInfo::ChunkInfo(unsigned int offset,
                     unsigned int length,
                     unsigned int timestamp,
                     CompressionType compression)
    : m_offset{offset}
    , m_length{length}
    , m_timestamp{timestamp}
    , m_compression{compression}
{

}

ChunkInfo::~ChunkInfo()
{

}

ChunkInfo& ChunkInfo::operator=(const ChunkInfo &other)
{
    if(this != &other) {
        m_offset        = other.m_offset;
        m_length        = other.m_length;
        m_timestamp     = other.m_timestamp;
        m_compression   = other.m_compression;
    }

    return *this;
}

ChunkInfo& ChunkInfo::operator=(ChunkInfo &&other) noexcept
{
    if(this != &other) {
        m_offset        = other.m_offset;
        m_length        = other.m_length;
        m_timestamp     = other.m_timestamp;
        m_compression   = other.m_compression;
    }

    return *this;
}

bool ChunkInfo::operator==(const ChunkInfo &other)
{
    return m_offset == other.m_offset
        && m_length == other.m_length
        && m_timestamp == other.m_timestamp
        && m_compression == other.m_compression;
}

bool ChunkInfo::operator!=(const ChunkInfo &other)
{
    return !(*this == other);
}

bool ChunkInfo::isEmpty() const
{
    return (m_offset == 0);
}

unsigned int ChunkInfo::getOffset() const
{
    return m_offset;
}

void ChunkInfo::setOffset(unsigned int offset)
{
    m_offset = offset;
}

unsigned int ChunkInfo::getLength() const
{
    return m_length;
}

void ChunkInfo::setLength(unsigned int length)
{
    m_length = length;
}

unsigned int ChunkInfo::getTimestamp() const
{
    return m_timestamp;
}

void ChunkInfo::setTimestamp(unsigned int timestamp)
{
    m_timestamp = timestamp;
}

ChunkInfo::CompressionType ChunkInfo::getCompression() const
{
    return m_compression;
}

void ChunkInfo::setCompression(ChunkInfo::CompressionType compression)
{
    m_compression = compression;
}

} // namespace anvil