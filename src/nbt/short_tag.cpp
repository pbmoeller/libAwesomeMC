#include "nbt/short_tag.hpp"
#include "util/byte_stream.hpp"

// STL
#include <utility>

namespace nbt
{

ShortTag::ShortTag()
    : AbstractTag()
    , m_value{0}
{

}

ShortTag::ShortTag(const ShortTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{
    
}

ShortTag::ShortTag(ShortTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{other.m_value}
{

}

ShortTag::ShortTag(const std::string &name)
    : AbstractTag(name)
    , m_value{0}
{

}

ShortTag::ShortTag(int16_t value)
    : AbstractTag()
    , m_value{value}
{

}

ShortTag::ShortTag(const std::string &name, int16_t value)
    : AbstractTag(name)
    , m_value{value}
{

}

ShortTag::~ShortTag()
{

}

ShortTag& ShortTag::operator=(const ShortTag &other)
{
    if(this != &other) {
        m_name  = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

ShortTag& ShortTag::operator=(ShortTag &&other) noexcept
{
    if(this != &other) {
        m_name  = std::move(other.m_name);
        m_value = other.m_value;
    }
    return *this;
}

constexpr TagType ShortTag::getType() const
{
    return TagType::Short;
}

std::vector<unsigned char> ShortTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << (char)getType();
        stream << (int16_t)m_name.size();
        stream << m_name;
    }
    stream << m_value;

    return stream.vbuf();
}

int16_t ShortTag::getValue() const
{
    return m_value;
}

void ShortTag::setValue(int16_t value)
{
    m_value = value;
}


bool ShortTag::isEqual(const AbstractTag &other) const
{
    const ShortTag &oTag = static_cast<const ShortTag&>(other);

    return m_name == oTag.m_name
        && getType() == oTag.getType()
        && m_value == oTag.m_value;
}

} // namespace nbt