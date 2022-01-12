#include <AwesomeMC/nbt/tags/float_tag.hpp>

// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>

namespace nbt
{

FloatTag::FloatTag()
    : AbstractTag()
    , m_value{0}
{

}

FloatTag::FloatTag(const FloatTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{

}

FloatTag::FloatTag(FloatTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{other.m_value}
{

}

FloatTag::FloatTag(const std::string &name)
    : AbstractTag(name)
    , m_value{0}
{

}

FloatTag::FloatTag(float value)
    : AbstractTag()
    , m_value{value}
{

}

FloatTag::FloatTag(const std::string &name, float value)
    : AbstractTag(name)
    , m_value{value}
{

}

FloatTag::~FloatTag()
{

}

FloatTag& FloatTag::operator=(const FloatTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

FloatTag& FloatTag::operator=(FloatTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
        m_value = other.m_value;
    }
    return *this;
}

AbstractTag* FloatTag::clone()
{
    return new FloatTag(*this);
}

std::vector<unsigned char> FloatTag::getData(bool isListEntry)
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

float FloatTag::getValue() const
{
    return m_value;
}

void FloatTag::setValue(float value)
{
    m_value = value;
}

bool FloatTag::isEqual(const AbstractTag &other) const
{
    const FloatTag &oTag = static_cast<const FloatTag&>(other);

    return m_name == oTag.m_name
        && getType() == oTag.getType()
        && m_value == oTag.m_value; // This comparison is wrong, however we test the object 
                                    // and not the number. So we expect the numbers to be equal
                                    // at the bits, if the objects are equal. TODO: better comparison.
}


} // namespace nbt