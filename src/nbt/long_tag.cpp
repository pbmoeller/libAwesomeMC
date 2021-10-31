#include "nbt/long_tag.hpp"
#include "util/byte_stream.hpp"

// STL
#include <utility>

namespace nbt
{

LongTag::LongTag()
    : AbstractTag()
    , m_value{0}
{

}

LongTag::LongTag(const LongTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{

}

LongTag::LongTag(LongTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{other.m_value}
{

}

LongTag::LongTag(const std::string &name)
    : AbstractTag(name)
    , m_value{0}
{

}

LongTag::LongTag(int64_t value)
    : AbstractTag()
    , m_value{value}
{

}

LongTag::LongTag(const std::string &name, int64_t value)
    : AbstractTag(name)
    , m_value{value}
{

}

LongTag::~LongTag()
{

}

LongTag& LongTag::operator=(const LongTag &other)
{
    if(this != &other) {
        m_name  = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

LongTag& LongTag::operator=(LongTag &&other) noexcept
{
    if(this != &other) {
        m_name  = std::move(other.m_name);
        m_value = other.m_value;
    }
    return *this;
}

constexpr TagType LongTag::getType() const
{
    return TagType::Long;
}

std::vector<unsigned char> LongTag::getData(bool isListEntry)
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

int64_t LongTag::getValue() const
{
    return m_value;
}

void LongTag::setValue(int64_t value)
{
    m_value = value;
}

bool LongTag::isEqual(const AbstractTag &other) const
{
    const LongTag &oTag = static_cast<const LongTag&>(other);

    return m_name == oTag.m_name
        && getType() == oTag.getType()
        && m_value == oTag.m_value;
}

} // namespace nbt