#include <AwesomeMC/nbt/tags/long_array_tag.hpp>

// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>

namespace nbt
{

LongArrayTag::LongArrayTag()
    : AbstractTag()
    , m_value{}
{

}

LongArrayTag::LongArrayTag(const LongArrayTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{

}

LongArrayTag::LongArrayTag(LongArrayTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{std::move(other.m_value)}
{

}

LongArrayTag::LongArrayTag(const std::string &name)
    : AbstractTag(name)
    , m_value{}
{

}

LongArrayTag::LongArrayTag(const std::vector<int64_t> &value)
    : AbstractTag()
    , m_value{value}
{

}

LongArrayTag::LongArrayTag(const std::string &name, const std::vector<int64_t> &value)
    : AbstractTag(name)
    , m_value{value}
{

}

LongArrayTag::~LongArrayTag()
{

}

LongArrayTag& LongArrayTag::operator=(const LongArrayTag &other)
{
    if(this != &other) {
        m_name  = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

LongArrayTag& LongArrayTag::operator=(LongArrayTag &&other) noexcept
{
    if(this != &other) {
        m_name  = std::move(other.m_name);
        m_value = std::move(other.m_value);
    }
    return *this;
}

AbstractTag* LongArrayTag::clone()
{
    return new LongArrayTag(*this);
}

std::vector<unsigned char> LongArrayTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << (char)getType();
        stream << (int16_t)m_name.size();
        stream << m_name;
    }

    stream << (int32_t)m_value.size();
    for(size_t i = 0; i < m_value.size(); ++i) {
        stream << m_value[i];
    }

    return stream.vbuf();
}

bool LongArrayTag::isEmpty() const
{
    return m_value.empty();
}

void LongArrayTag::clear()
{
    m_value.clear();
}

bool LongArrayTag::erase(size_t index)
{
    if(index >= m_value.size()) {
        return false;
    } else {
        m_value.erase(m_value.begin() + index);
        return true;
    }
}

bool LongArrayTag::insert(size_t index, int64_t value)
{
    if(index > m_value.size()) {
        return false;
    } else {
        m_value.insert(m_value.begin() + index, value);
        return true;
    }
}

void LongArrayTag::pushBack(int64_t value)
{
    m_value.push_back(value);
}

size_t LongArrayTag::size() const
{
    return m_value.size();
}

int64_t& LongArrayTag::at(size_t index)
{
    return m_value.at(index);
}

const int64_t& LongArrayTag::at(size_t index) const
{
    return m_value.at(index);
}

std::vector<int64_t>& LongArrayTag::getValue()
{
    return m_value;
}

void LongArrayTag::setValue(const std::vector<int64_t> &value)
{
    m_value = value;
}

bool LongArrayTag::isEqual(const AbstractTag &other) const
{
    const LongArrayTag &oTag = static_cast<const LongArrayTag&>(other);

    if(m_name != oTag.m_name
       || getType() != oTag.getType()
       || m_value.size() != oTag.m_value.size()) {
        return false;
    }

    for(size_t i = 0; i < m_value.size(); ++i) {
        if(m_value[i] != oTag.m_value[i]) {
            return false;
        }
    }
    return true;
}

} // namespace nbt