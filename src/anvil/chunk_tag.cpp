#include "anvil/chunk_tag.hpp"

// STL
#include <utility>

namespace anvil
{

ChunkTag::ChunkTag()
{

}

ChunkTag::ChunkTag(const ChunkTag &other)
{
    *this = other;
}

ChunkTag::ChunkTag(ChunkTag &&other)
{
    *this = std::move(other);
}

ChunkTag::~ChunkTag()
{

}

ChunkTag& ChunkTag::operator=(const ChunkTag &other)
{
    if(this != &other) {

    }
    return *this;
}

ChunkTag& ChunkTag::operator=(ChunkTag &&other)
{
    if(this != &other) {

    }
    return *this;
}

bool ChunkTag::operator==(const ChunkTag &other)
{
    if(this == &other) {
        return true;
    }
}

bool ChunkTag::operator!=(const ChunkTag &other)
{
    return !(*this == other);
}

} // namespace anvil