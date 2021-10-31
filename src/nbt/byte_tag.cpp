#include "nbt/byte_tag.hpp"
#include "util/byte_stream.hpp"

// STL
#include <utility>

namespace nbt
{

ByteTag::ByteTag()
    : AbstractTag()
    , m_byte{0}
{

}

ByteTag::ByteTag(const ByteTag &other)
    : AbstractTag(other.m_name)
    , m_byte{other.m_byte}
{
    
}

ByteTag::ByteTag(ByteTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_byte{other.m_byte}
{
    
}

ByteTag::ByteTag(const std::string &name)
    : AbstractTag(name)
    , m_byte{0}
{

}

ByteTag::ByteTag(char value)
    : AbstractTag()
    , m_byte{value}
{

}

ByteTag::ByteTag(const std::string &name, char value)
    : AbstractTag(name)
    , m_byte{value}
{

}

ByteTag::~ByteTag()
{

}

ByteTag& ByteTag::operator=(const ByteTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
        m_byte = other.m_byte;
    }
    return *this;
}

ByteTag& ByteTag::operator=(ByteTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
        m_byte = other.m_byte;
    }
    return *this;
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
    stream << m_byte;

    return stream.vbuf();
}

char ByteTag::getValue() const
{
    return m_byte;
}

void ByteTag::setValue(char value)
{
    m_byte = value;
}

bool ByteTag::isEqual(const AbstractTag &other) const
{
    const ByteTag &oTag = static_cast<const ByteTag&>(other);

    return m_name == oTag.m_name
        && getType() == oTag.getType()
        && m_byte == oTag.m_byte;
}

} // namespace nbt