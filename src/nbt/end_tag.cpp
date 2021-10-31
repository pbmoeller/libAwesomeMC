#include "nbt/end_tag.hpp"

namespace nbt
{

EndTag::EndTag()
    : AbstractTag(TagType::End)
{

}

EndTag::EndTag(const EndTag &other)
    : AbstractTag(other.m_name, TagType::End)
{

}

EndTag::EndTag(EndTag &&other) noexcept
    : AbstractTag(std::move(other.m_name), TagType::End)
{

}

EndTag::~EndTag()
{

}

EndTag& EndTag::operator=(const EndTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
        m_type = other.m_type;
    }
    return *this;
}

EndTag& EndTag::operator=(EndTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
        m_type = other.m_type;
    }
    return *this;
}

bool EndTag::operator==(const AbstractTag &other)
{
    if(this == &other) {
        return true;
    }

    const EndTag *oTag = dynamic_cast<const EndTag*>(&other);
    if(!oTag) {
        return false;
    }

    // TODO: use oTag and make members private again?
    return m_name == other.m_name
        && m_type == other.m_type;
}

bool EndTag::operator!=(const AbstractTag &other)
{
    return !(*this == other);
}

std::vector<unsigned char> EndTag::getData(bool value)
{
    // TODO: Constructor init data(1, 0) instead of insert
    std::vector<unsigned char> data;
    data.insert(data.end(), 0);
    return data;
}

} // namespace nbt