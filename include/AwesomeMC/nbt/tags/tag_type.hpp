#ifndef AWESOMEMC_NBT_TAGS_TAG_TYPE_HPP
#define AWESOMEMC_NBT_TAGS_TAG_TYPE_HPP

// STL
#include <string_view>

namespace amc
{

// Tag types to distinguish between types
enum class TagType : unsigned char
{
    End         = 0,
    Byte        = 1,
    Short       = 2,
    Int         = 3,
    Long        = 4,
    Float       = 5,
    Double      = 6,
    ByteArray   = 7,
    String      = 8,
    List        = 9,
    Compound    = 10,
    IntArray    = 11,
    LongArray   = 12,
    Unknown     = 255,
};

constexpr bool isValueTag(TagType type)
{
    return type == TagType::Byte
        || type == TagType::Short
        || type == TagType::Int
        || type == TagType::Long
        || type == TagType::Float
        || type == TagType::Double
        || type == TagType::String;
}

constexpr bool isArrayTag(TagType type)
{
    return type == TagType::ByteArray
        || type == TagType::IntArray
        || type == TagType::LongArray;
}

constexpr bool isContainerTag(TagType type)
{
    return type == TagType::List
        || type == TagType::Compound;
}

std::string_view getTagTypeName(TagType type);
std::string_view getTagName(TagType type);

}

#endif // AWESOMEMC_NBT_TAGS_TAG_TYPE_HPP