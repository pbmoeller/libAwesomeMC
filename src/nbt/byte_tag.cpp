#include "nbt/byte_tag.hpp"
#include "util/byte_stream.hpp"

// STL
#include <utility>

namespace nbt
{

ByteTag::ByteTag()
    : AbstractTag(TagType::Byte)
    , m_byte{0}
{

}

ByteTag::ByteTag(const ByteTag &other)
{
    *this = other;
}

ByteTag::ByteTag(ByteTag &&other) noexcept
    : AbstractTag(std::move(other.m_name), TagType::Byte)
    , m_byte{other.m_byte}
{
    
}

ByteTag::ByteTag(const std::string &name)
    : AbstractTag(name, TagType::Byte)
    , m_byte{0}
{

}

ByteTag::ByteTag(char value)
    : AbstractTag(TagType::Byte)
    , m_byte{value}
{

}

ByteTag::ByteTag(const std::string &name, char value)
    : AbstractTag(name, TagType::Byte)
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
        m_type = other.m_type;
        m_byte = other.m_byte;
    }
    return *this;
}

ByteTag& ByteTag::operator=(ByteTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
        m_type = other.m_type;
        m_byte = other.m_byte;
    }
    return *this;
}

bool ByteTag::operator==(const AbstractTag &other)
{
    if(this == &other) {
        return true;
    }

    const ByteTag *oTag = dynamic_cast<const ByteTag*>(&other);
    if(!oTag) {
        return false;
    }

    return m_name == other.m_name
        && m_type == other.m_type
        && m_byte == oTag->m_byte;
}

bool ByteTag::operator!=(const AbstractTag &other)
{
    return !(*this == other);
}

std::vector<unsigned char> ByteTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << (char) m_type;
    }


    return std::vector<unsigned char>();
}

char ByteTag::getValue() const
{
    return m_byte;
}

void ByteTag::setValue(char value)
{
    m_byte = value;
}

} // namespace nbt