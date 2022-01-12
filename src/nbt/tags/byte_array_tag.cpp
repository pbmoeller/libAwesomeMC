#include <AwesomeMC/nbt/tags/byte_array_tag.hpp>

// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>

namespace nbt
{

ByteArrayTag::ByteArrayTag()
    : AbstractTag()
    , m_value{}
{

}

ByteArrayTag::ByteArrayTag(const ByteArrayTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{

}

ByteArrayTag::ByteArrayTag(ByteArrayTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{std::move(other.m_value)}
{

}

ByteArrayTag::ByteArrayTag(const std::string &name)
    : AbstractTag(name)
    , m_value{}
{

}

ByteArrayTag::ByteArrayTag(const std::vector<char> &value)
    : AbstractTag()
    , m_value{value}
{

}

ByteArrayTag::ByteArrayTag(const std::string &name, const std::vector<char> &value)
    : AbstractTag(name)
    , m_value{value}
{

}

ByteArrayTag::~ByteArrayTag()
{

}

ByteArrayTag& ByteArrayTag::operator=(const ByteArrayTag &other)
{
    if(this != &other) {
        m_name  = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

ByteArrayTag& ByteArrayTag::operator=(ByteArrayTag &&other) noexcept
{
    if(this != &other) {
        m_name  = std::move(other.m_name);
        m_value = std::move(other.m_value);
    }
    return *this;
}

AbstractTag* ByteArrayTag::clone()
{
    return new ByteArrayTag(*this);
}

std::vector<unsigned char> ByteArrayTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << (char)getType();
        stream << (int16_t)m_name.size();
        stream << m_name;
    }

    stream << (int32_t)m_value.size();
    for(size_t i = 0; i< m_value.size(); ++i) {
        stream << m_value[i];
    }

    return stream.vbuf();
}

bool ByteArrayTag::isEmpty() const
{
    return m_value.empty();
}

void ByteArrayTag::clear()
{
    m_value.clear();
}

bool ByteArrayTag::erase(size_t index)
{
    if(index >= m_value.size()) {
        return false;
    } else {
        m_value.erase(m_value.begin() + index);
        return true;
    }
}

bool ByteArrayTag::insert(size_t index, char value)
{
    if(index > m_value.size()) {
        return false;
    } else {
        m_value.insert(m_value.begin() + index, value);
        return true;
    }
}

void ByteArrayTag::pushBack(char value)
{
    m_value.push_back(value);
}

size_t ByteArrayTag::size() const
{
    return m_value.size();
}

char& ByteArrayTag::at(size_t index)
{
    return m_value.at(index);
}

const char& ByteArrayTag::at(size_t index) const
{
    return m_value.at(index);
}

std::vector<char>& ByteArrayTag::getValue()
{
    return m_value;
}

void ByteArrayTag::setValue(const std::vector<char> &value)
{
    m_value = value;
}

bool ByteArrayTag::isEqual(const AbstractTag &other) const
{
    const ByteArrayTag &oTag = static_cast<const ByteArrayTag&>(other);

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