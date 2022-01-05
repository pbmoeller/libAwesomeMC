#include <AwesomeMC/anvil/chunk.hpp>

// AwesomeMC
#include <AwesomeMC/anvil/constants.hpp>
#include <AwesomeMC/nbt/tags/list_tag.hpp>
#include <AwesomeMC/nbt/tags/compound_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>
#include <AwesomeMC/nbt/tags/int_array_tag.hpp>

// STL
#include <utility>
#include <stdexcept>

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
        m_data = tag_cast<nbt::CompoundTag*>(other.m_data->clone());
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
    // Delete old data
    clear();

    // Set new data
    m_data = root;
}

std::vector<nbt::AbstractTag*> Chunk::getSubTagsByName(const std::string &name) const
{
    std::vector<nbt::AbstractTag*> subTags;
    getSubTagsByName(name, m_data, subTags);
    return subTags;
}

void Chunk::getSubTagsByName(const std::string &name,
                             nbt::AbstractTag *currentSubTag,
                             std::vector<nbt::AbstractTag*> &subTags) const
{
    // Check if this sub tag matches the search name
    if(currentSubTag->getName() == name) {
        subTags.push_back(currentSubTag);
    }

    // Iterate through child tags, if this tag is list or compound
    switch(currentSubTag->getType()) {
        case nbt::TagType::List:
        {
            nbt::ListTag *listTag = tag_cast<nbt::ListTag*>(currentSubTag);
            for(unsigned int i = 0; i < listTag->size(); ++i) {
                getSubTagsByName(name, listTag->at(i), subTags);
            }
            break;
        }
        case nbt::TagType::Compound:
        {
            nbt::CompoundTag *compoundTag = tag_cast<nbt::CompoundTag*>(currentSubTag);
            for(unsigned int i = 0; i < compoundTag->size(); ++i) {
                getSubTagsByName(name, compoundTag->at(i), subTags);
            }
            break;
        }
        default:
            break;
    }
}

std::vector<int32_t> Chunk::getBiomes() const
{
    // Get Biomes array
    std::vector<nbt::AbstractTag*> biomesArray = getSubTagsByName("Biomes");

    // If Biomes array is empty return empty list.
    if(biomesArray.empty()) {
        return std::vector<int32_t>();
    }

    // Take first item (in errornous case where there are more than 1 "Biomes" sub tag in root tag)
    return tag_cast<nbt::IntArrayTag*>(biomesArray[0])->getValue();
}

int32_t Chunk::getBiomeAt(unsigned int blockX, int blockY, unsigned int blockZ) const
{
    // Check ranges of block coordinates
    if(blockX >= BlockWidth || blockZ >= BlockWidth
       || blockY < MinimumBlockHeight || blockY > MaximumBlockHeight) {
        throw std::out_of_range("Block Coordinates out of range");
    }

    // Get Biome Array
    std::vector<nbt::AbstractTag*> biomesArray = getSubTagsByName("Biomes");

    // If Biomes array is empty return 0.
    if(biomesArray.empty()) {
        return 0;
    }

    // Calculate biome index (https://minecraft.fandom.com/wiki/Java_Edition_19w36a#Additions)
    // Values are arranged by Z, then X, then Y
    int biomeIndex = (blockY % 4) * 4 + (blockX % 4) * 2 + (blockZ % 4);

    return tag_cast<nbt::IntArrayTag*>(biomesArray[0])->at(biomeIndex);
}

Block Chunk::getBlockAt(unsigned int blockX, int blockY, unsigned int blockZ) const
{
    // Check ranges of block coordinates
    if(blockX >= BlockWidth || blockZ >= BlockWidth
       || blockY < MinimumBlockHeight || blockY > MaximumBlockHeight) {
        throw std::out_of_range("Block Coordinates out of range");
    }

    // Calculate Section
    int sectionIndex = blockY / BlockWidth + 5;

    // Get BlockStates
    nbt::CompoundTag *section = tag_cast<nbt::CompoundTag*>(getSubTagsByName("sections").at(sectionIndex));

    return Block();
}

std::vector<nbt::AbstractTag*> Chunk::getPaletteAt(unsigned int blockX, int blockY, unsigned int blockZ) const
{
    // Check ranges of block coordinates
    if(blockX >= BlockWidth || blockZ >= BlockWidth
       || blockY < MinimumBlockHeight || blockY > MaximumBlockHeight) {
        throw std::out_of_range("Block Coordinates out of range");
    }

    // Calculate Section
    int sectionIndex = blockY / BlockWidth + 5;

    return std::vector<nbt::AbstractTag*>();
}

} // namespace anvil