#ifndef AWESOMEMC_NBT_TAGS_TAG_TYPE_HPP
#define AWESOMEMC_NBT_TAGS_TAG_TYPE_HPP

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

}

#endif // AWESOMEMC_NBT_TAGS_TAG_TYPE_HPP