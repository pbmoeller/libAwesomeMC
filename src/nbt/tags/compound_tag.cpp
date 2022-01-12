#include <AwesomeMC/nbt/tags/compound_tag.hpp>

// AwesomeMC
#include <AwesomeMC/nbt/tags/end_tag.hpp>
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>
#include <stdexcept>

namespace nbt
{

CompoundTag::CompoundTag()
    : AbstractTag()
    , m_value{}
{

}

CompoundTag::CompoundTag(const CompoundTag &other)
    : AbstractTag(other.m_name)
{
    copy(other.m_value);
}

CompoundTag::CompoundTag(CompoundTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{std::move(other.m_value)}
{

}

CompoundTag::CompoundTag(const std::string &name)
    : AbstractTag(name)
    , m_value{}
{

}

CompoundTag::CompoundTag(std::initializer_list<AbstractTag*> items)
    : AbstractTag()
    , m_value{}
{
    for(AbstractTag *item : items) {
        if(item) {
            m_value.push_back(item);
        }
    }
}

CompoundTag::CompoundTag(const std::string &name, std::initializer_list<AbstractTag*> items)
    : AbstractTag(name)
    , m_value{}
{
    for(AbstractTag *item : items) {
        if(item) {
            m_value.push_back(item);
        }
    }
}

CompoundTag::~CompoundTag()
{
    clear();
}

CompoundTag& CompoundTag::operator=(const CompoundTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
        copy(other.m_value);
    }
    return *this;
}

CompoundTag& CompoundTag::operator=(CompoundTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);

        // Delete old data
        clear();

        m_value = std::move(other.m_value);
    }
    return *this;
}

AbstractTag* CompoundTag::clone()
{
    return new CompoundTag(*this);
}

std::vector<unsigned char> CompoundTag::getData(bool isListEntry)
{
    nbt::EndTag endTag;
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << (char)getType();
        stream << (int16_t)m_name.size();
        stream << m_name;
    }

    for(size_t i = 0; i < m_value.size(); ++i) {
        stream << m_value[i]->getData(false);
    }
    stream << endTag.getData(false);

    return stream.vbuf();
}

bool CompoundTag::isEmpty() const
{
    return m_value.empty();
}

void CompoundTag::clear()
{
    // Delete all objects stored in the vector
    for(auto ptr : m_value) {
        // Check that ptr is not null
        if(ptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
    m_value.clear();
}

bool CompoundTag::erase(size_t index)
{
    if(index >= m_value.size()) {
        return false;
    } else {
        if(m_value[index] != nullptr) {
            delete m_value[index];
        }
        m_value.erase(m_value.begin() + index);
        return true;
    }
}

bool CompoundTag::insert(size_t index, AbstractTag *value)
{
    if(!value || index > m_value.size()) {
        return false;
    } else {
        m_value.insert(m_value.begin() + index, value);
        return true;
    }
}

bool CompoundTag::pushBack(AbstractTag* value)
{
    if(!value) {
        return false;
    } else {
        m_value.push_back(value);
        return true;
    }
}

size_t CompoundTag::size() const
{
    return m_value.size();
}

AbstractTag* CompoundTag::at(size_t index)
{
    if(index >= m_value.size()) {
        throw std::out_of_range("Index out of range!");
    }
    return m_value.at(index);
}

const AbstractTag* CompoundTag::at(size_t index) const
{
    if(index >= m_value.size()) {
        throw std::out_of_range("Index out of range!");
    }
    return m_value.at(index);
}

AbstractTag* CompoundTag::takeAt(size_t index)
{
    AbstractTag *tag = at(index);
    m_value.erase(m_value.begin() + index);
    return tag;
}

AbstractTag* CompoundTag::operator[](const size_t index)
{
    return m_value.at(index);
}

const AbstractTag* CompoundTag::operator[](const size_t index) const
{
    return m_value.at(index);
}

bool CompoundTag::hasChild(const std::string &name) const
{
    for(AbstractTag *tag : m_value) {
        if(tag->getName() == name) {
            return true;
        }
    }
    return false;
}

AbstractTag* CompoundTag::getChildByName(const std::string &name)
{
    for(AbstractTag *tag : m_value) {
        if(tag->getName() == name) {
            return tag;
        }
    }
    return nullptr;
}

const AbstractTag* CompoundTag::getChildByName(const std::string &name) const
{
    for(const AbstractTag *tag : m_value) {
        if(tag->getName() == name) {
            return tag;
        }
    }
    return nullptr;
}

std::vector<AbstractTag*> CompoundTag::getChildrenByName(const std::string &name) const
{
    std::vector<AbstractTag*> vec;
    for(AbstractTag *tag : m_value) {
        if(tag->getName() == name) {
            vec.push_back(tag);
        }
    }
    return vec;
}

std::vector<AbstractTag*>& CompoundTag::getValue()
{
    return m_value;
}

std::vector<AbstractTag*> CompoundTag::getValueCopy() const
{
    std::vector<AbstractTag*> valueCopy(m_value.size(), nullptr);
    for(size_t i = 0; i < m_value.size(); ++i) {
        valueCopy[i] = m_value[i]->clone();
    }

    return valueCopy;
}

void CompoundTag::setValue(std::vector<AbstractTag*> &value)
{
    copy(value);
}

bool CompoundTag::isEqual(const AbstractTag &other) const
{
    const CompoundTag &oTag = static_cast<const CompoundTag&>(other);

    if(m_name != oTag.m_name
       || getType() != oTag.getType()
       || m_value.size() != oTag.m_value.size()) {
        return false;
    }

    for(size_t i = 0; i < m_value.size(); ++i) {
        if(*m_value[i] != *oTag.m_value[i]) {
            return false;
        }
    }
    return true;
}

void CompoundTag::copy(const std::vector<AbstractTag*> &otherValue)
{
    clear();

    // Resize list to other size
    m_value.resize(otherValue.size());

    // Copy other data elements
    for(size_t i = 0; i < otherValue.size(); ++i) {
        m_value[i] = otherValue[i]->clone();
    }
}

} // namespace nbt