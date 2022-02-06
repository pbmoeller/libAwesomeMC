#ifndef AWESOMEMC_NBT_TAGS_LONG_TAG_HPP
#define AWESOMEMC_NBT_TAGS_LONG_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/value_tag.hpp>

// STL
#include <cstdint>

namespace amc
{

using LongTag = ValueTag<int64_t, TagType::Long>;

} // namespace amc

#endif // AWESOMEMC_NBT_TAGS_LONG_TAG_HPP