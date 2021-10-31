#include "nbt/double_tag.hpp"
#include "util/byte_stream.hpp"

// STL
#include <utility>

namespace nbt
{

DoubleTag::DoubleTag()
    : AbstractTag()
    , m_value{0}
{

}

DoubleTag::DoubleTag(const DoubleTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{

}

DoubleTag::DoubleTag(DoubleTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{other.m_value}
{

}

DoubleTag::DoubleTag(const std::string &name)
    : AbstractTag(name)
    , m_value{0}
{

}

DoubleTag::DoubleTag(double value)
    : AbstractTag()
    , m_value{value}
{

}

DoubleTag::DoubleTag(const std::string &name, double value)
    : AbstractTag(name)
    , m_value{value}
{

}

DoubleTag::~DoubleTag()
{

}

DoubleTag& DoubleTag::operator=(const DoubleTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

DoubleTag& DoubleTag::operator=(DoubleTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
        m_value = other.m_value;
    }
    return *this;
}

constexpr TagType DoubleTag::getType() const
{
    return TagType::Double;
}

std::vector<unsigned char> DoubleTag::getData(bool isListEntry)
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

double DoubleTag::getValue() const
{
    return m_value;
}

void DoubleTag::setValue(double value)
{
    m_value = value;
}

bool DoubleTag::isEqual(const AbstractTag &other) const
{
    const DoubleTag &oTag = static_cast<const DoubleTag&>(other);

    return m_name == oTag.m_name
        && getType() == oTag.getType()
        && m_value == oTag.m_value; // This comparison is wrong, however we test the object 
                                    // and not the number. So we expect the numbers to be equal
                                    // at the bits, if the objects are equal. TODO: better comparison.
}

} // namespace nbt