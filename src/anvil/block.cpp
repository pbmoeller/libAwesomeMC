#include <AwesomeMC/anvil/block.hpp>

namespace amc
{

Block::Block()
    : m_x(0)
    , m_y(0)
    , m_z(0)
    , m_name("")
    , m_properties()
{

}

Block::Block(const Block &other)
    : Block()
{
    *this = other;
}

Block::Block(Block &&other) noexcept
    : Block()
{
    *this = std::move(other);
}

Block::Block(int x, int y, int z, const std::string &name)
    : m_x(x)
    , m_y(y)
    , m_z(z)
    , m_name(name)
    , m_properties()
{

}

Block::Block(int x, int y, int z, const std::string &name, const CompoundTag &properties)
    : m_x(x)
    , m_y(y)
    , m_z(z)
    , m_name(name)
    , m_properties(properties)
{

}

Block::~Block()
{

}

Block& Block::operator=(const Block &other)
{
    if(this != &other) {
        m_x             = other.m_x;
        m_y             = other.m_y;
        m_z             = other.m_z;
        m_name          = other.m_name;
        m_properties    = other.m_properties;
    }
    return *this;
}

Block& Block::operator=(Block &&other) noexcept
{
    if(this != &other) {
        m_x             = std::move(other.m_x);
        m_y             = std::move(other.m_y);
        m_z             = std::move(other.m_z);
        m_name          = std::move(other.m_name);
        m_properties    = std::move(other.m_properties);
    }
    return *this;
}

bool Block::operator==(const Block &other)
{
    if(this == &other) {
        return true;
    }

    if(m_x != other.m_x
       || m_y != other.m_y
       || m_z != other.m_z
       || m_name != other.m_name
       || m_properties != other.m_properties) {
        return false;
    }

    return true;
}

bool Block::operator!=(const Block &other)
{
    return !(*this == other);
}

int Block::getX() const
{
    return m_x;
}

void Block::setX(int x)
{
    m_x = x;
}

int Block::getY() const
{
    return m_y;
}

void Block::setY(int y)
{
    m_y = y;
}

int Block::getZ() const
{
    return m_z;
}

void Block::setZ(int z)
{
    m_z = z;
}

void Block::setXYZ(int x, int y, int z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

std::string Block::getName() const
{
    return m_name;
}

void Block::setName(const std::string &name)
{
    m_name = name;
}

CompoundTag Block::getProperties() const
{
    return m_properties;
}

void Block::setProperties(const CompoundTag &properties)
{
    m_properties = properties;
}

} // namespace amc