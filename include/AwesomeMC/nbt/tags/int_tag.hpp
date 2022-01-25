#ifndef AWESOMEMC_NBT_TAGS_INT_TAG_HPP
#define AWESOMEMC_NBT_TAGS_INT_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_number_tag.hpp>

// STL
#include <cstdint>

namespace nbt
{

using IntTag = AbstractNumberTag<int32_t, TagType::Int>;

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_INT_TAG_HPP