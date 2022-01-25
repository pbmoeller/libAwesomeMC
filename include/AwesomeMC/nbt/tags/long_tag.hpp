#ifndef AWESOMEMC_NBT_TAGS_LONG_TAG_HPP
#define AWESOMEMC_NBT_TAGS_LONG_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/number_tag.hpp>

// STL
#include <cstdint>

namespace nbt
{

using LongTag = NumberTag<int64_t, TagType::Long>;

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_LONG_TAG_HPP