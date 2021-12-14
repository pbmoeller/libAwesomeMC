#ifndef ANVIL_CHUNK_INFO_HPP
#define ANVIL_CHUNK_INFO_HPP

namespace anvil
{

class ChunkInfo
{
public:
    enum class CompressionType : char
    {
        GZip            = 1,
        Zlib            = 2,
        Uncompressed    = 3,
    };

    ChunkInfo();
    ChunkInfo(const ChunkInfo &other);
    ChunkInfo(ChunkInfo &&other) noexcept;
    ChunkInfo(unsigned int offset,
              unsigned int length,
              unsigned int timestamp,
              CompressionType compression);
    virtual ~ChunkInfo();

    ChunkInfo& operator=(const ChunkInfo &other);
    ChunkInfo& operator=(ChunkInfo &&other) noexcept;

    bool operator==(const ChunkInfo &other);
    bool operator!=(const ChunkInfo &other);

    bool isEmpty() const;

    unsigned int getOffset() const;
    void setOffset(unsigned int offset);

    unsigned int getLength() const;
    void setLength(unsigned int length);

    unsigned int getTimestamp() const;
    void setTimestamp(unsigned int timestamp);

    CompressionType getCompression() const;
    void setCompression(CompressionType compression);

private:
    unsigned int m_offset;
    unsigned int m_length;
    unsigned int m_timestamp;
    CompressionType m_compression;
};

} // namespace anvil

#endif // ANVIL_CHUNK_INFO_HPP