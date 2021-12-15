#ifndef ANVIL_CHUNK_HPP
#define ANVIL_CHUNK_HPP

#include "nbt/tags/compound_tag.hpp"

namespace anvil
{

class Chunk
{
public:
    Chunk();
    Chunk(const Chunk &other);
    Chunk(Chunk &&other) noexcept;
    virtual ~Chunk();

    Chunk& operator=(const Chunk &other);
    Chunk& operator=(Chunk &&other) noexcept;

    bool operator==(const Chunk &other);
    bool operator!=(const Chunk &other);

    void clear();

    nbt::CompoundTag* getRootTag();
    void setRootTag(nbt::CompoundTag *root);

private:
    nbt::CompoundTag *m_data;
};

} // namespace anvil

#endif // ANVIL_CHUNK_HPP