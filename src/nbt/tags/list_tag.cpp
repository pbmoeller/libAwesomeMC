#include <AwesomeMC/nbt/tags/list_tag.hpp>

// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>
#include <stdexcept>

namespace nbt
{

ListTag::ListTag()
    : AbstractTag()
    , m_listType{TagType::Byte}
    , m_value{}
{

}

ListTag::ListTag(const ListTag &other)
    : AbstractTag(other.m_name)
    , m_listType{other.m_listType}
{
    copy(other.m_value);
}

ListTag::ListTag(ListTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_listType{std::move(other.m_listType)}
    , m_value{std::move(other.m_value)}
{
    
}

ListTag::ListTag(const std::string &name)
    : AbstractTag(name)
    , m_listType{TagType::Byte}
    , m_value{}
{

}

ListTag::ListTag(TagType listType)
    : AbstractTag()
    , m_listType{listType}
    , m_value{}
{

}

ListTag::ListTag(TagType listType, std::initializer_list<AbstractTag*> items)
    : AbstractTag()
    , m_listType{listType}
    , m_value{}
{
    for(AbstractTag *item : items) {
        if(item && item->getType() == listType) {
            m_value.push_back(item);
        }
    }
}

ListTag::ListTag(const std::string &name, TagType listType)
    : AbstractTag(name)
    , m_listType{listType}
    , m_value{}
{

}

ListTag::ListTag(const std::string &name, TagType listType, std::initializer_list<AbstractTag*> items)
    : AbstractTag(name)
    , m_listType{listType}
    , m_value{}
{
    for(AbstractTag *item : items) {
        if(item && item->getType() == listType) {
            m_value.push_back(item);
        }
    }
}

ListTag::~ListTag()
{
    clear();
}

ListTag& ListTag::operator=(const ListTag &other)
{
    if(this != &other) {
        m_name      = other.m_name;
        m_listType  = other.m_listType;
        copy(other.m_value);
    }
    return *this;
}

ListTag& ListTag::operator=(ListTag &&other) noexcept
{
    if(this != &other) {
        m_name      = std::move(other.m_name);
        m_listType  = other.m_listType;

        // Delete old data
        clear();

        m_value = std::move(other.m_value);
    }
    return *this;
}

AbstractTag* ListTag::clone()
{
    return new ListTag(*this);
}

constexpr TagType ListTag::getType() const
{
    return TagType::List;
}

TagType ListTag::getListType() const
{
    return m_listType;
}

std::vector<unsigned char> ListTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << (char)getType();
        stream << (int16_t)m_name.size();
        stream << m_name;
    }

    stream << (int8_t)m_listType;
    stream << (int32_t)m_value.size();
    for(size_t i = 0; i < m_value.size(); ++i) {
        stream << m_value[i]->getData(true);
    }

    return stream.vbuf();
}

bool ListTag::isEmpty() const
{
    return m_value.empty();
}

void ListTag::clear()
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

bool ListTag::erase(size_t index)
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

bool ListTag::insert(size_t index, AbstractTag *value)
{
    if(!value || value->getType() != m_listType
       || index > m_value.size()) {
        return false;
    } else {
        m_value.insert(m_value.begin() + index, value);
        return true;
    }
}

bool ListTag::pushBack(AbstractTag* value)
{
    if(!value || value->getType() != m_listType) {
        return false;
    } else {
        m_value.push_back(value);
        return true;
    }
}

size_t ListTag::size() const
{
    return m_value.size();
}

AbstractTag* ListTag::at(size_t index)
{
    if(index >= m_value.size()) {
        throw std::out_of_range("Index out of range!");
    }
    return m_value.at(index);
}

const AbstractTag* ListTag::at(size_t index) const
{
    if(index >= m_value.size()) {
        throw std::out_of_range("Index out of range!");
    }
    return m_value.at(index);
}

AbstractTag* ListTag::takeAt(size_t index)
{
    AbstractTag *tag = at(index);
    m_value.erase(m_value.begin() + index);
    return tag;
}

AbstractTag* ListTag::operator[](const size_t index)
{
    return m_value.at(index);
}

const AbstractTag* ListTag::operator[](const size_t index) const
{
    return m_value.at(index);
}

std::vector<AbstractTag*>& ListTag::getValue()
{
    return m_value;
}

const std::vector<AbstractTag*>& ListTag::getValue() const
{
    return m_value;
}

std::vector<AbstractTag*> ListTag::getValueCopy() const
{
    std::vector<AbstractTag*> valueCopy(m_value.size(), nullptr);
    for(size_t i = 0; i < m_value.size(); ++i) {
        valueCopy[i] = m_value[i]->clone();
    }

    return valueCopy;
}

void ListTag::setValue(std::vector<AbstractTag*> &value)
{
    copy(value);
}

bool ListTag::isEqual(const AbstractTag &other) const
{
    const ListTag &oTag = static_cast<const ListTag&>(other);

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

void ListTag::copy(const std::vector<AbstractTag*> &otherValue)
{
    //TODO: Check the type. One might pass a CompoundTag vector
    clear();

    // Resize list to other size
    m_value.resize(otherValue.size());

    // Copy other data elements
    for(size_t i = 0; i < otherValue.size(); ++i) {
        m_value[i] = otherValue[i]->clone();
    }
}

} // namespace nbt