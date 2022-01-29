#ifndef AWESOMEMC_NBT_TAGS_FLOAT_TAG_HPP
#define AWESOMEMC_NBT_TAGS_FLOAT_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/value_tag.hpp>
#include <AwesomeMC/util/floating_point.hpp>

namespace nbt
{

template<>
inline bool ValueTag<float, TagType::Float>::isEqual(const AbstractTag &other) const
{
    const ValueTag<float, TagType::Float> &otherTag = static_cast<const ValueTag<float, TagType::Float>&>(other);

    return m_name == otherTag.m_name
        && getType() == otherTag.getType()
        && util::almostEqualUlps(m_value, otherTag.m_value, static_cast<int32_t>(10));
}

using FloatTag = ValueTag<float, TagType::Float>;

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_FLOAT_TAG_HPP