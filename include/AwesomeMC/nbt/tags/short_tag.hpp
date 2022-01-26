#ifndef AWESOMEMC_NBT_TAGS_SHORT_TAG_HPP
#define AWESOMEMC_NBT_TAGS_SHORT_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/value_tag.hpp>

// STL
#include <cstdint>

namespace nbt
{

using ShortTag = ValueTag<int16_t, TagType::Short>;

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_SHORT_TAG_HPP