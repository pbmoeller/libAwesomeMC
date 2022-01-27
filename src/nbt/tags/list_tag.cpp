#include <AwesomeMC/nbt/tags/list_tag.hpp>

// AwesomeMC
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <utility>
#include <stdexcept>

namespace nbt
{

ListTag::ListTag()
    : AbstractVectorTag()
    , m_listType{TagType::Byte}
{

}

ListTag::ListTag(const ListTag &other)
    : AbstractVectorTag(other)
    , m_listType{other.m_listType}
{

}

ListTag::ListTag(ListTag &&other) noexcept
    : AbstractVectorTag(std::move(other))
    , m_listType{other.m_listType}
{

}

ListTag::ListTag(const std::string &name)
    : AbstractVectorTag(name)
    , m_listType{TagType::Byte}
{

}

ListTag::ListTag(TagType listType)
    : AbstractVectorTag()
    , m_listType{listType}
{

}

ListTag::ListTag(TagType listType, std::initializer_list<AbstractTag*> items)
    : AbstractVectorTag()
    , m_listType{listType}
{
    for(AbstractTag *item : items) {
        if(item && item->getType() == listType) {
            m_value.push_back(item);
        }
    }
}

ListTag::ListTag(const std::string &name, TagType listType)
    : AbstractVectorTag(name)
    , m_listType{listType}
{

}

ListTag::ListTag(const std::string &name, TagType listType, std::initializer_list<AbstractTag*> items)
    : AbstractVectorTag(name)
    , m_listType{listType}
{
    for(AbstractTag *item : items) {
        if(item && item->getType() == listType) {
            m_value.push_back(item);
        }
    }
}

ListTag::~ListTag()
{

}

ListTag& ListTag::operator=(const ListTag &other)
{
    if(this != &other) {
        m_listType = other.m_listType;
        AbstractVectorTag::operator=(other);
    }
    return *this;
}

ListTag& ListTag::operator=(ListTag &&other) noexcept
{
    if(this != &other) {
        m_listType = other.m_listType;
        AbstractVectorTag::operator=(std::move(other));
    }
    return *this;
}

AbstractTag* ListTag::clone() const
{
    return new ListTag(*this);
}

std::vector<unsigned char> ListTag::getData(bool isListEntry)
{
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << static_cast<int8_t>(getType());
        stream << static_cast<int16_t>(m_name.size());
        stream << m_name;
    }

    stream << static_cast<int8_t>(m_listType);
    stream << static_cast<int32_t>(m_value.size());
    for(size_t i = 0; i < m_value.size(); ++i) {
        stream << m_value[i]->getData(true);
    }

    return stream.vbuf();
}

bool ListTag::isEqual(const AbstractTag &other) const
{
    const ListTag &otherTag = static_cast<const ListTag&>(other);

    return m_listType == otherTag.m_listType
        && AbstractVectorTag::isEqual(other);
}

bool ListTag::insert(size_t index, AbstractTag *value)
{
    if(!value || value->getType() != m_listType) {
        return false;
    } else {
        return AbstractVectorTag::insert(index, value);
    }
}

bool ListTag::pushBack(AbstractTag* value)
{
    if(!value || value->getType() != m_listType) {
        return false;
    } else {
        return AbstractVectorTag::pushBack(value);
    }
}

} // namespace nbt