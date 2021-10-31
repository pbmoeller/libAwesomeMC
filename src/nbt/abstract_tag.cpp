#include "nbt/abstract_tag.hpp"

// STL
#include <utility>

namespace nbt
{

AbstractTag::AbstractTag()
    : m_name("")
    , m_type(TagType::End)
{

}

AbstractTag::AbstractTag(const AbstractTag &other)
{
    *this = other;
}

AbstractTag::AbstractTag(AbstractTag &&other) noexcept
{
    *this = std::move(other);
}

AbstractTag::AbstractTag(TagType type)
    : m_name("")
    , m_type (type)
{

}

AbstractTag::AbstractTag(const std::string &name, TagType type)
    : m_name(name)
    , m_type(type)
{

}

AbstractTag::~AbstractTag()
{

}

AbstractTag& AbstractTag::operator=(const AbstractTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
        m_type = other.m_type;
    }
    return *this;
}

AbstractTag& AbstractTag::operator=(AbstractTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
        m_type = other.m_type;
    }
    return *this;
}

bool AbstractTag::operator==(const AbstractTag &other)
{
    if(this == &other) {
        return true;
    }

    return m_name == other.m_name
        && m_type == other.m_type;
}

bool AbstractTag::operator!=(const AbstractTag &other)
{
    return !(*this == other);
}

std::string AbstractTag::getName() const
{
    return m_name;
}

void AbstractTag::setName(const std::string &name)
{
    m_name = name;
}

TagType AbstractTag::getType() const
{
    return m_type;
}

void AbstractTag::setType(TagType type)
{
    m_type = type;
}

} // namespace nbt