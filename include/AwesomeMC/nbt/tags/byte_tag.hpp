#ifndef AWESOMEMC_NBT_TAGS_BYTE_TAG_HPP
#define AWESOMEMC_NBT_TAGS_BYTE_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/number_tag.hpp>

// STL
#include <cstdint>

namespace nbt
{

using ByteTag = ValueTag<int8_t, TagType::Byte>;

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_BYTE_TAG_HPP