#include <AwesomeMC/nbt/tags/end_tag.hpp>

namespace nbt
{

EndTag::EndTag()
    : AbstractTag()
{

}

EndTag::EndTag(const EndTag &other)
    : AbstractTag(other.m_name)
{

}

EndTag::EndTag(EndTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
{

}

EndTag::~EndTag()
{

}

EndTag& EndTag::operator=(const EndTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
    }
    return *this;
}

EndTag& EndTag::operator=(EndTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
    }
    return *this;
}

AbstractTag* EndTag::clone() const
{
    return new EndTag(*this);
}

std::vector<unsigned char> EndTag::getData(bool isListEntry)
{
    (void)(isListEntry);
    return std::vector<unsigned char>(1, 0);
}

bool EndTag::isEqual(const AbstractTag &other) const
{
    const EndTag &oTag = static_cast<const EndTag&>(other);
    
    return m_name == oTag.m_name
        && getType() == oTag.getType();
}

} // namespace nbt