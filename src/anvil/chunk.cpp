#include "anvil/chunk.hpp"
#include "nbt/tags/list_tag.hpp"
#include "nbt/tags/compound_tag.hpp"

// STL
#include <utility>

namespace anvil
{

Chunk::Chunk()
    : m_data{nullptr}
{

}

Chunk::Chunk(const Chunk &other)
    : m_data{nullptr}
{
    *this = other;
}

Chunk::Chunk(Chunk &&other) noexcept
    : m_data{nullptr}
{
    *this = std::move(other);
}

Chunk::~Chunk()
{
    clear();
}

Chunk& Chunk::operator=(const Chunk &other)
{
    if(this != &other) {
        clear();
        m_data = static_cast<nbt::CompoundTag*>(other.m_data->clone());
    }
    return *this;
}

Chunk& Chunk::operator=(Chunk &&other) noexcept
{
    if(this != &other) {
        clear();
        m_data = other.m_data;
        other.m_data = nullptr;
    }
    return *this;
}

bool Chunk::operator==(const Chunk &other)
{
    if(this == &other) {
        return true;
    }
    if(!m_data || !other.m_data) {
        return false;
    }

    return (*m_data == *other.m_data);
}

bool Chunk::operator!=(const Chunk &other)
{
    return !(*this == other);
}

void Chunk::clear()
{
    if(m_data) {
        delete m_data;
        m_data = nullptr;
    }
}

nbt::CompoundTag* Chunk::getRootTag()
{
    return m_data;
}

void Chunk::setRootTag(nbt::CompoundTag *root)
{
    m_data = root;
}

std::vector<nbt::AbstractTag*> Chunk::getSubTagsByName(const std::string &name)
{
    std::vector<nbt::AbstractTag*> subTags;
    getSubTagsByName(name, m_data, subTags);
    return subTags;
}

std::vector<nbt::AbstractTag*> Chunk::getSubTagsByName(const std::string &name,
                                                       nbt::AbstractTag *currentSubTag,
                                                       std::vector<nbt::AbstractTag*> &subTags)
{
    // check if this sub tag matches the search name
    if(currentSubTag->getName() == name) {
        subTags.push_back(currentSubTag);
    }

    // iterate through child tags, if this tag is list or compound
    switch(currentSubTag->getType()) {
        case nbt::TagType::List:
            nbt::ListTag *listTag = static_cast<nbt::ListTag*>(currentSubTag);
            for(unsigned int i = 0; i < listTag->size(); ++i) {
                getSubTagsByName(name, listTag->at(i), subTags);
            }
            break;
        case nbt::TagType::Compound:
            nbt::CompoundTag *compoundTag = static_cast<nbt::CompoundTag*>(currentSubTag);
            for(unsigned int i = 0; i < compoundTag->size(); ++i) {
                getSubTagsByName(name, compoundTag->at(i), subTags);
            }
            break;
        default:
            break;
    }
}

} // namespace anvil