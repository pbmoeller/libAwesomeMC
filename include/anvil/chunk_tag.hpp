#ifndef LIBAWESOMEANVIL_CHUNK_TAG_HPP
#define LIBAWESOMEANVIL_CHUNK_TAG_HPP

namespace anvil
{

class ChunkTag
{
public:
    ChunkTag();
    ChunkTag(const ChunkTag &other);
    ChunkTag(ChunkTag &&other);
    virtual ~ChunkTag();

    ChunkTag& operator=(const ChunkTag &other);
    ChunkTag& operator=(ChunkTag &&other);

    bool operator==(const ChunkTag &other);
    bool operator!=(const ChunkTag &other);

private:
};

} // namespace anvil

#endif // LIBAWESOMEANVIL_CHUNK_TAG_HPP