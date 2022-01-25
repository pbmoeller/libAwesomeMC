#ifndef AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP
#define AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/number_tag.hpp>
#include <AwesomeMC/util/floating_point.hpp>

namespace nbt
{

template<>
inline bool NumberTag<double, TagType::Double>::isEqual(const AbstractTag &other) const
{
    const NumberTag<double, TagType::Double> &otherTag = static_cast<const NumberTag<double, TagType::Double>&>(other);

    return m_name == otherTag.m_name
        && getType() == otherTag.getType()
        && util::almostEqualUlps(m_value, otherTag.m_value, static_cast<int64_t>(10));
}

using DoubleTag = NumberTag<double, TagType::Double>;

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP