#include "anvil/chunk.hpp"

// STL
#include <utility>

namespace anvil
{

Chunk::Chunk()
    : m_data{nullptr}
{

}

Chunk::Chunk(const Chunk &other)
    : m_data{nullptr}
{
    *this = other;
}

Chunk::Chunk(Chunk &&other) noexcept
    : m_data{nullptr}
{
    *this = std::move(other);
}

Chunk::~Chunk()
{
    clear();
}

Chunk& Chunk::operator=(const Chunk &other)
{
    if(this != &other) {
        clear();
        m_data = static_cast<nbt::CompoundTag*>(other.m_data->clone());
    }
    return *this;
}

Chunk& Chunk::operator=(Chunk &&other) noexcept
{
    if(this != &other) {
        clear();
        m_data = other.m_data;
        other.m_data = nullptr;
    }
    return *this;
}

bool Chunk::operator==(const Chunk &other)
{
    if(this == &other) {
        return true;
    }
    if(!m_data || !other.m_data) {
        return false;
    }

    return (*m_data == *other.m_data);
}

bool Chunk::operator!=(const Chunk &other)
{
    return !(*this == other);
}

void Chunk::clear()
{
    if(m_data) {
        delete m_data;
        m_data = nullptr;
    }
}

nbt::CompoundTag* Chunk::getRootTag()
{
    return m_data;
}

void Chunk::setRootTag(nbt::CompoundTag *root)
{
    m_data = root;
}

} // namespace anvil