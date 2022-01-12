#include <AwesomeMC/nbt/tags/int_tag.hpp>

// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>

namespace nbt
{

IntTag::IntTag()
    : AbstractTag()
    , m_value{0}
{

}

IntTag::IntTag(const IntTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{

}

IntTag::IntTag(IntTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{other.m_value}
{

}

IntTag::IntTag(const std::string &name)
    : AbstractTag(name)
    , m_value{0}
{

}

IntTag::IntTag(int32_t value)
    : AbstractTag()
    , m_value{value}
{

}

IntTag::IntTag(const std::string &name, int32_t value)
    : AbstractTag(name)
    , m_value{value}
{

}

IntTag::~IntTag()
{

}

IntTag& IntTag::operator=(const IntTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

IntTag& IntTag::operator=(IntTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
        m_value = other.m_value;
    }
    return *this;
}

AbstractTag* IntTag::clone()
{
    return new IntTag(*this);
}

std::vector<unsigned char> IntTag::getData(bool isListEntry)
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

int32_t IntTag::getValue() const
{
    return m_value;
}

void IntTag::setValue(int32_t value)
{
    m_value = value;
}

bool IntTag::isEqual(const AbstractTag &other) const
{
    const IntTag &oTag = static_cast<const IntTag&>(other);

    return m_name == oTag.m_name
        && getType() == oTag.getType()
        && m_value == oTag.m_value;
}

} // namespace nbt