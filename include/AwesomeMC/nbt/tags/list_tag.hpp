#ifndef AWESOMEMC_NBT_TAGS_LIST_TAG_HPP
#define AWESOMEMC_NBT_TAGS_LIST_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <vector>
#include <string>
#include <initializer_list>

namespace nbt
{

class ListTag : public AbstractTag
{
public:
    using iterator = typename std::vector<AbstractTag*>::iterator;
    using const_iterator = typename std::vector<AbstractTag*>::const_iterator;

    enum { Type = static_cast<int>(TagType::List) };

public:
    ListTag();
    ListTag(const ListTag &other);
    ListTag(ListTag &&other) noexcept;
    ListTag(const std::string &name);
    ListTag(TagType listType);
    // !!! Takes ownership of value - do not delete the object after !!!
    ListTag(TagType listType, std::initializer_list<AbstractTag*> items);
    ListTag(const std::string &name, TagType listType);
    // !!! Takes ownership of value - do not delete the object after !!!
    ListTag(const std::string &name, TagType listType, std::initializer_list<AbstractTag*> items);
    virtual ~ListTag();

    ListTag& operator=(const ListTag &other);
    ListTag& operator=(ListTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override {
        return TagType::List;
    }

    TagType getListType() const;

    std::vector<unsigned char> getData(bool isListEntry) override;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    bool isEmpty() const;
    void clear();
    bool erase(size_t index);
    // !!! Takes ownership of value - do not delete the object after !!!
    bool insert(size_t index, AbstractTag *value);
    // !!! Takes ownership of value - do not delete the object after !!!
    bool pushBack(AbstractTag* value);
    size_t size() const;
    // !!! Do not delete these items - the ListTag keeps the ownership !!!
    // Does range checking -> throws
    AbstractTag* at(size_t index);
    // !!! Do not delete these items - the ListTag keeps the ownership !!!
    // Does range checking -> throws
    const AbstractTag* at(size_t index) const;
    // !!! This functions removes the item from ListTag - transfers ownership !!!
    AbstractTag* takeAt(size_t index);

    // !!! Do not delete these items - the ListTag keeps the ownership !!!
    // Does not do range checking
    AbstractTag* operator[](const size_t index);
    // !!! Do not delete these items - the ListTag keeps the ownership !!!
    // Does not do range checking
    const AbstractTag* operator[](const size_t index) const;

    // !!! Do not delete these items - the ListTag keeps the ownership 
    //     -> use getValueCopy, if you want to modify the data !!!
    std::vector<AbstractTag*>& getValue();
    const std::vector<AbstractTag*>& getValue() const;
    std::vector<AbstractTag*> getValueCopy() const;

    void setValue(std::vector<AbstractTag*> &value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;
    void copy(const std::vector<AbstractTag*> &otherValue);

private:
    TagType m_listType;
    std::vector<AbstractTag*> m_value;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_LIST_TAG_HPP