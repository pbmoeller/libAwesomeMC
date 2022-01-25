#ifndef AWESOMEMC_NBT_TAGS_SHORT_TAG_HPP
#define AWESOMEMC_NBT_TAGS_SHORT_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_number_tag.hpp>

// STL
#include <cstdint>

namespace nbt
{

using ShortTag = AbstractNumberTag<int16_t, TagType::Short>;

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_SHORT_TAG_HPP