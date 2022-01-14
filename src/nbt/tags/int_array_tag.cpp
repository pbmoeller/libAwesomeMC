#include <AwesomeMC/nbt/tags/int_array_tag.hpp>

// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>

namespace nbt
{

IntArrayTag::IntArrayTag()
    : AbstractTag()
    , m_value{}
{

}

IntArrayTag::IntArrayTag(const IntArrayTag &other)
    : AbstractTag(other.m_name)
    , m_value{other.m_value}
{

}

IntArrayTag::IntArrayTag(IntArrayTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{std::move(other.m_value)}
{

}

IntArrayTag::IntArrayTag(const std::string &name)
    : AbstractTag(name)
    , m_value{}
{

}

IntArrayTag::IntArrayTag(const std::vector<int32_t> &value)
    : AbstractTag()
    , m_value{value}
{

}

IntArrayTag::IntArrayTag(const std::string &name, const std::vector<int32_t> &value)
    : AbstractTag(name)
    , m_value{value}
{

}

IntArrayTag::~IntArrayTag()
{

}

IntArrayTag& IntArrayTag::operator=(const IntArrayTag &other)
{
    if(this != &other) {
        m_name  = other.m_name;
        m_value = other.m_value;
    }
    return *this;
}

IntArrayTag& IntArrayTag::operator=(IntArrayTag &&other) noexcept
{
    if(this != &other) {
        m_name  = std::move(other.m_name);
        m_value = std::move(other.m_value);
    }
    return *this;
}

AbstractTag* IntArrayTag::clone()
{
    return new IntArrayTag(*this);
}

std::vector<unsigned char> IntArrayTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << static_cast<char>(getType());
        stream << static_cast<int16_t>(m_name.size());
        stream << m_name;
    }

    stream << static_cast<int32_t>(m_value.size());
    for(size_t i = 0; i < m_value.size(); ++i) {
        stream << m_value[i];
    }

    return stream.vbuf();
}

bool IntArrayTag::isEmpty() const
{
    return m_value.empty();
}

void IntArrayTag::clear()
{
    m_value.clear();
}

bool IntArrayTag::erase(size_t index)
{
    if(index >= m_value.size()) {
        return false;
    } else {
        m_value.erase(m_value.begin() + index);
        return true;
    }
}

bool IntArrayTag::insert(size_t index, int32_t value)
{
    if(index > m_value.size()) {
        return false;
    } else {
        m_value.insert(m_value.begin() + index, value);
        return true;
    }
}

void IntArrayTag::pushBack(int32_t value)
{
    m_value.push_back(value);
}

size_t IntArrayTag::size() const
{
    return m_value.size();
}

int32_t& IntArrayTag::at(size_t index)
{
    return m_value.at(index);
}

const int32_t& IntArrayTag::at(size_t index) const
{
    return m_value.at(index);
}

std::vector<int32_t>& IntArrayTag::getValue()
{
    return m_value;
}

void IntArrayTag::setValue(const std::vector<int32_t> &value)
{
    m_value = value;
}

bool IntArrayTag::isEqual(const AbstractTag &other) const
{
    const IntArrayTag &oTag = static_cast<const IntArrayTag&>(other);

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