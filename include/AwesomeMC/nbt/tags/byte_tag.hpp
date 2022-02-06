#ifndef AWESOMEMC_NBT_TAGS_BYTE_TAG_HPP
#define AWESOMEMC_NBT_TAGS_BYTE_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/value_tag.hpp>

// STL
#include <cstdint>

namespace amc
{

using ByteTag = ValueTag<int8_t, TagType::Byte>;

} // namespace amc

#endif // AWESOMEMC_NBT_TAGS_BYTE_TAG_HPP