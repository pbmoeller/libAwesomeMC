#include "nbt/tags/byte_tag.hpp"
#include "util/byte_stream.hpp"

// STL
#include <utility>

namespace nbt
{

ByteTag::ByteTag()
    : AbstractTag()
    , m_value{0}
{

}

ByteTag::ByteTag(const ByteTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{
    
}

ByteTag::ByteTag(ByteTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{other.m_value}
{
    
}

ByteTag::ByteTag(const std::string &name)
    : AbstractTag(name)
    , m_value{0}
{

}

ByteTag::ByteTag(char value)
    : AbstractTag()
    , m_value{value}
{

}

ByteTag::ByteTag(const std::string &name, char value)
    : AbstractTag(name)
    , m_value{value}
{

}

ByteTag::~ByteTag()
{

}

ByteTag& ByteTag::operator=(const ByteTag &other)
{
    if(this != &other) {
        m_name  = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

ByteTag& ByteTag::operator=(ByteTag &&other) noexcept
{
    if(this != &other) {
        m_name  = std::move(other.m_name);
        m_value = other.m_value;
    }
    return *this;
}

AbstractTag* ByteTag::clone()
{
    return new ByteTag(*this);
}

constexpr TagType ByteTag::getType() const
{
    return TagType::Byte;
}

std::vector<unsigned char> ByteTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << (char) getType();
        stream << (int16_t) m_name.size();
        stream << m_name;
    }
    stream << m_value;

    return stream.vbuf();
}

char ByteTag::getValue() const
{
    return m_value;
}

void ByteTag::setValue(char value)
{
    m_value = value;
}

bool ByteTag::isEqual(const AbstractTag &other) const
{
    const ByteTag &oTag = static_cast<const ByteTag&>(other);

    return m_name == oTag.m_name
        && getType() == oTag.getType()
        && m_value == oTag.m_value;
}

} // namespace nbt