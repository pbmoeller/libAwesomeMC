#include <AwesomeMC/nbt/tags/tag_type.hpp>

// STL
#include <cassert>

namespace amc
{

const std::string tagTypeNames[14] = {
    "End",
    "Byte",
    "Short",
    "Int",
    "Long",
    "Float",
    "Double",
    "ByteArray",
    "String",
    "List",
    "Compound",
    "IntArray",
    "LongArray",
    "Unknown"
};

const std::string tagNames[14] = {
    "EndTag",
    "ByteTag",
    "ShortTag",
    "IntTag",
    "LongTag",
    "FloatTag",
    "DoubleTag",
    "ByteArrayTag",
    "StringTag",
    "ListTag",
    "CompoundTag",
    "IntArrayTag",
    "LongArrayTag",
    "UnknownTag"
};

std::string getTagTypeName(TagType type)
{
    assert(static_cast<unsigned char>(type) <= static_cast<unsigned char>(TagType::LongArray));
    if(static_cast<unsigned char>(type) <= static_cast<unsigned char>(TagType::LongArray)) {
        return tagTypeNames[static_cast<unsigned char>(type)];
    } else {
        return tagTypeNames[13];
    }
}

std::string getTagName(TagType type)
{
    assert(static_cast<unsigned char>(type) <= static_cast<unsigned char>(TagType::LongArray));
    if(static_cast<unsigned char>(type) <= static_cast<unsigned char>(TagType::LongArray)) {
        return tagNames[static_cast<unsigned char>(type)];
    } else {
        return tagNames[13];
    }
}

} // namespace amc