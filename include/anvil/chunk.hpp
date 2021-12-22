#ifndef ANVIL_CHUNK_HPP
#define ANVIL_CHUNK_HPP

#include "nbt/tags/compound_tag.hpp"

// STL
#include <vector>

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
    // !!! Do not delete or reuse the item - the chunk keeps the ownership !!!
    void setRootTag(nbt::CompoundTag *root);

    // !!! Do not delete or reuse the item - the chunk keeps the ownership !!!
    std::vector<nbt::AbstractTag*> getSubTagsByName(const std::string &name) const;

    std::vector<int32_t> getBiomes() const;
    int32_t getBiomeAt(unsigned int blockX, int blockY, unsigned int blockZ) const;

    // TODO: return value -> temporary : Change Leter to block class or sth else
    std::string getBlockAt(unsigned int blockX, int blockY, unsigned int blockZ) const;

protected:
    void getSubTagsByName(const std::string &name,
                          nbt::AbstractTag *currentSubTag,
                          std::vector<nbt::AbstractTag*> &subTags) const;

private:
    nbt::CompoundTag *m_data;
};

} // namespace anvil

#endif // ANVIL_CHUNK_HPP