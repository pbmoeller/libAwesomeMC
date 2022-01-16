#include <AwesomeMC/anvil/chunk.hpp>

// AwesomeMC
#include <AwesomeMC/constants.hpp>
#include <AwesomeMC/nbt/tags/list_tag.hpp>
#include <AwesomeMC/nbt/tags/compound_tag.hpp>
#include <AwesomeMC/nbt/tags/int_tag.hpp>
#include <AwesomeMC/nbt/tags/int_array_tag.hpp>
#include <AwesomeMC/nbt/tags/long_array_tag.hpp>
#include <AwesomeMC/nbt/tags/string_tag.hpp>
#include <AwesomeMC/util/bit.hpp>
#include <AwesomeMC/util/byte_swap.hpp>
#include <AwesomeMC/util/conversion.hpp>

// STL
#include <bit>
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

Block Chunk::getBlockAt(const int blockX, const int blockY, const int blockZ) const
{
    // Check ranges of block coordinates
    //if(blockX >= BlockWidth || blockZ >= BlockWidth
    //   || blockY < MinimumBlockHeight || blockY > MaximumBlockHeight) {
    //    throw std::out_of_range("Block Coordinates out of range");
    //}

    // Calculate Section

    int sectionIndex = util::calculateSectionIndex(blockY);

    // Get BlockStates
    auto vecTmp = getSubTagsByName("sections");
    if(vecTmp.size() == 0) {
        throw std::runtime_error("\"sections\" not found!");
    }
    nbt::ListTag *sections = tag_cast<nbt::ListTag*>(vecTmp.at(0));
    if(!sections) {
        throw std::runtime_error("\"sections\" is not a list!");
    }
    nbt::CompoundTag *section = tag_cast<nbt::CompoundTag*>(sections->at(sectionIndex));
    if(!section) {
        throw std::runtime_error(std::string("\"section\" at index \"") + std::to_string(sectionIndex) + std::string("\" not found!"));
    }
    nbt::CompoundTag *blockStates = tag_cast<nbt::CompoundTag*>(section->getChildByName("block_states"));
    if(!blockStates) {
        throw std::runtime_error("\"block_states\" not found!");
    }
    nbt::ListTag *palette = tag_cast<nbt::ListTag*>(blockStates->getChildByName("palette"));
    if(!palette) {
        throw std::runtime_error("\"palette\" not found!");
    }

    // Get Block data
    size_t paletteIndex = 0;
    nbt::LongArrayTag *blockData = tag_cast<nbt::LongArrayTag*>(blockStates->getChildByName("data"));
    if(blockData) {
        int localX = 0;
        int localY = 0;
        int localZ = 0;
        util::convertBlockWorld2BlockChunk(blockX, blockY, blockZ, localX, localY, localZ);
        char bitWidth = static_cast<char>(std::bit_width(palette->size() - 1));
        int blocksPerLong = static_cast<int>(64 / bitWidth);

        int blockIndex = localY * anvil::BlockCount + localZ * anvil::BlockWidth + localX;
        unsigned int longIndex = blockIndex / blocksPerLong;
        int blockInLong = blockIndex % blocksPerLong;
        if(longIndex >= blockData->size()) {
            throw std::runtime_error("Long index out of range!");
        }
        int64_t longValue = blockData->at(longIndex);
        int64_t mask = util::setNLeastSignificantBits64(bitWidth);

        longValue = longValue >> (blockInLong * bitWidth);
        paletteIndex = longValue & mask;
    } else {
        // Valid case => this section must be full of air (or on other block, see palette entry TODO: (check!!))
        paletteIndex = 0;
    }

    nbt::CompoundTag *paletteEntry = tag_cast<nbt::CompoundTag*>(palette->at(paletteIndex));
    if(!paletteEntry) {
        throw std::runtime_error("\"palette\" is empty!");
    }
    nbt::StringTag *entryName = tag_cast<nbt::StringTag*>(paletteEntry->getChildByName("Name"));
    if(!entryName) {
        throw std::runtime_error("\"Name\" of palette entry not found!");
    }

    // If the palette entyr has a Properties field add it to the Block data
    nbt::CompoundTag *properties = tag_cast<nbt::CompoundTag*>(paletteEntry->getChildByName("Properties"));
    if(properties) {
        nbt::CompoundTag props(*properties);
        return Block(blockX, blockY, blockZ, entryName->getValue(), props);
    } else {
        return Block(blockX, blockY, blockZ, entryName->getValue());
    }
}

HeightMap Chunk::getHeightMap(HeightMap::HeightMapType mapType) const
{
    // Get Heightmaps CompoundTag
    auto vecTmp = getSubTagsByName("Heightmaps");
    if(vecTmp.size() == 0) {
        throw std::runtime_error("\"Heightmaps\" not found!");
    } else if(vecTmp.size() != 1) {
        throw std::runtime_error("Invalid count of Heightmaps!");
    }
    nbt::CompoundTag *heightmaps = tag_cast<nbt::CompoundTag*>(vecTmp.at(0));
    if(!heightmaps) {
        throw std::runtime_error("Invalid tag type of Heightmaps!");
    }

    // Get LongArrayTag depending on type.
    nbt::AbstractTag *tmp = nullptr;
    switch(mapType)
    {
        case HeightMap::HeightMapType::MotionBlocking:
            tmp = heightmaps->getChildByName("MOTION_BLOCKING");
            break;
        case HeightMap::HeightMapType::MotionBlockingNoLeaves:
            tmp = heightmaps->getChildByName("MOTION_BLOCKING_NO_LEAVES");
            break;
        case HeightMap::HeightMapType::OceanFloor:
            tmp = heightmaps->getChildByName("OCEAN_FLOOR");
            break;
        case HeightMap::HeightMapType::WorldSurface:
            tmp = heightmaps->getChildByName("WORLD_SURFACE");
            break;
        case HeightMap::HeightMapType::Unknown:
        default:
            break;
    }

    nbt::LongArrayTag *heightmapData = tag_cast<nbt::LongArrayTag*>(tmp);
    if(!heightmapData) {
        throw std::runtime_error("Empty Heightmap data!");
    }
    if(heightmapData->size() != 37) {
        throw std::runtime_error("Invalid size of Heightmap!");
    }

    // Get height values.
    HeightMap heightmap;
    int currenBlockIndex = 0;
    const int64_t mask = util::setNLeastSignificantBits64(9);
    for(int i = 0; i < 37 && currenBlockIndex < BlockCount; ++i) {
        int64_t longValue = heightmapData->at(i);
        for(int j = 0; j < 7 && currenBlockIndex < BlockCount; ++j) {
            int heightValue = (longValue & mask);
            heightValue += MinimumBlockHeight - 1;
            heightmap.setAt(currenBlockIndex++, heightValue);
            longValue >>= 9;
        }
    }

    // Set X and Z coordinate of chunk if available
    auto vecTmpX = getSubTagsByName("xPos");
    auto vecTmpZ = getSubTagsByName("zPos");
    if(vecTmpX.size() > 0 && vecTmpZ.size() > 0) {
        nbt::IntTag *intTagX = tag_cast<nbt::IntTag*>(vecTmpX[0]);
        nbt::IntTag *intTagZ = tag_cast<nbt::IntTag*>(vecTmpZ[0]);
        if(intTagX && intTagZ) {
            heightmap.setChunkX(intTagX->getValue());
            heightmap.setChunkZ(intTagZ->getValue());
        }
    }

    return heightmap;
}

} // namespace anvil