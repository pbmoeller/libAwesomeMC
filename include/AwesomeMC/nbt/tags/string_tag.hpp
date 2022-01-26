#ifndef AWESOMEMC_NBT_TAGS_STRING_TAG_HPP
#define AWESOMEMC_NBT_TAGS_STRING_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/number_tag.hpp>

// STL
#include <string>

namespace nbt
{

template<>
inline std::vector<unsigned char> ValueTag<std::string, TagType::String>::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << static_cast<int8_t>(getType());
        stream << static_cast<int16_t>(m_name.size());
        stream << m_name;
    }
    stream << static_cast<int16_t>(m_value.size());
    stream << m_value;

    return stream.vbuf();
}

using StringTag = ValueTag<std::string, TagType::String>;

} // nbt

#endif // AWESOMEMC_NBT_TAGS_STRING_TAG_HPP