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
    : AbstractVectorTag()
{

}

CompoundTag::CompoundTag(const CompoundTag &other)
    : AbstractVectorTag(other)
{

}

CompoundTag::CompoundTag(CompoundTag &&other) noexcept
    : AbstractVectorTag(std::move(other))
{

}

CompoundTag::CompoundTag(const std::string &name)
    : AbstractVectorTag(name)
{

}

CompoundTag::CompoundTag(std::initializer_list<AbstractTag*> items)
    : AbstractVectorTag()
{
    for(AbstractTag *item : items) {
        if(item) {
            m_value.push_back(item);
        }
    }
}

CompoundTag::CompoundTag(const std::string &name, std::initializer_list<AbstractTag*> items)
    : AbstractVectorTag(name)
{
    for(AbstractTag *item : items) {
        if(item) {
            m_value.push_back(item);
        }
    }
}

CompoundTag::~CompoundTag()
{

}

CompoundTag& CompoundTag::operator=(const CompoundTag &other)
{
    if(this != &other) {
        AbstractVectorTag::operator=(other);
    }
    return *this;
}

CompoundTag& CompoundTag::operator=(CompoundTag &&other) noexcept
{
    if(this != &other) {
        AbstractVectorTag::operator=(std::move(other));
    }
    return *this;
}

AbstractTag* CompoundTag::clone() const
{
    return new CompoundTag(*this);
}

std::vector<unsigned char> CompoundTag::getData(bool isListEntry)
{
    nbt::EndTag endTag;
    util::ByteStream stream(util::ByteStream::Swap::SwapEndian);

    if(!isListEntry) {
        stream << static_cast<int8_t>(getType());
        stream << static_cast<int16_t>(m_name.size());
        stream << m_name;
    }

    for(size_t i = 0; i < m_value.size(); ++i) {
        stream << m_value[i]->getData(false);
    }
    stream << endTag.getData(false);

    return stream.vbuf();
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

} // namespace nbt
