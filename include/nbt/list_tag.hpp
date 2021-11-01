#ifndef NBT_LIST_TAG_HPP
#define NBT_LIST_TAG_HPP

// nbt
#include "nbt/abstract_tag.hpp"

// STL
#include <vector>
#include <string>

namespace nbt
{

class ListTag : public AbstractTag
{
public:
    ListTag();
    ListTag(const ListTag &other);
    ListTag(ListTag &&other) noexcept;
    ListTag(const std::string &name);
    ListTag(TagType listType);
    ListTag(const std::string &name, TagType listType);
    virtual ~ListTag();

    ListTag& operator=(const ListTag &other);
    ListTag& operator=(ListTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;
    TagType getListType() const;

    std::vector<unsigned char> getData(bool isListEntry) override;

    bool isEmpty() const;
    void clear();
    bool erase(size_t index);
    // !!! Takes ownership of value - do not delete the object after !!!
    bool insert(size_t index, AbstractTag *value);
    // !!! Takes ownership of value - do not delete the object after !!!
    bool pushBack(AbstractTag* value);
    size_t size() const;
    // !!! Do not delete these items - the list keeps the ownership !!!
    AbstractTag* at(size_t index);
    // !!! Do not delete these items - the list keeps the ownership !!!
    const AbstractTag* at(size_t index) const;

    // !!! Do not delete these items - the list keeps the ownership 
    //     -> use getValueCopy, if you want to modify the data !!!
    std::vector<AbstractTag*>& getValue();
    std::vector<AbstractTag*> getValueCopy() const;
    // !!! Takes ownership of value - do not delete the object after !!!
    void setValue(std::vector<AbstractTag*> &value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;
    void copy(const std::vector<AbstractTag*> &otherValue);

private:
    TagType m_listType;
    std::vector<AbstractTag*> m_value;
};

} // namespace nbt

#endif // NBT_LIST_TAG_HPP