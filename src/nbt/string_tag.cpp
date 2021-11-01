#include "nbt/string_tag.hpp"
#include "util/byte_stream.hpp"

// STL
#include <utility>

namespace nbt
{

StringTag::StringTag()
    : AbstractTag()
    , m_value{}
{

}

StringTag::StringTag(const StringTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{

}

StringTag::StringTag(StringTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{std::move(other.m_value)}
{

}

StringTag::StringTag(const std::string &value)
    : AbstractTag()
    , m_value{value}
{

}

StringTag::StringTag(const std::string &name, const std::string &value)
    : AbstractTag(name)
    , m_value{value}
{

}

StringTag::~StringTag()
{

}

StringTag& StringTag::operator=(const StringTag &other)
{
    if(this != &other) {
        m_name  = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

StringTag& StringTag::operator=(StringTag &&other) noexcept
{
    if(this != &other) {
        m_name  = std::move(other.m_name);
        m_value = other.m_value;
    }
    return *this;
}

constexpr TagType StringTag::getType() const
{
    return TagType::String;
}

std::vector<unsigned char> StringTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << (char)getType();
        stream << (int16_t)m_name.size();
        stream << m_name;
    }
    stream << (int16_t)m_value.size();
    stream << m_value;

    return stream.vbuf();
}

std::string StringTag::getValue() const
{
    return m_value;
}

void StringTag::setValue(std::string value)
{
    m_value = value;
}

bool StringTag::isEqual(const AbstractTag &other) const
{
    const StringTag &oTag = static_cast<const StringTag&>(other);

    return m_name == oTag.m_name
        && getType() == oTag.getType()
        && m_value == oTag.m_value;
}

} // namespace nbt