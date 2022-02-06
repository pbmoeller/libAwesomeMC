#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <utility>
#include <typeinfo>

namespace amc
{

AbstractTag::AbstractTag()
    : m_name("")
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

AbstractTag::AbstractTag(const std::string &name)
    : m_name(name)
{

}

AbstractTag::AbstractTag(std::string &&name)
    : m_name(std::move(name))
{

}

AbstractTag::~AbstractTag()
{

}

AbstractTag& AbstractTag::operator=(const AbstractTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
    }
    return *this;
}

AbstractTag& AbstractTag::operator=(AbstractTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);
    }
    return *this;
}

std::string AbstractTag::getName() const
{
    return m_name;
}

void AbstractTag::setName(const std::string &name)
{
    m_name = name;
}

bool AbstractTag::isEqual(const AbstractTag &other) const
{
    if(this == &other) {
        return true;
    }

    return m_name == other.m_name
        && getType() == other.getType();
}

bool operator==(const AbstractTag &lhs,
                const AbstractTag &rhs)
{
    return &lhs == &rhs
        || (typeid(lhs) == typeid(rhs)
            && lhs.isEqual(rhs));
}

bool operator!=(const AbstractTag &lhs,
                const AbstractTag &rhs)
{
    return !(lhs == rhs);
}

} // namespace amc