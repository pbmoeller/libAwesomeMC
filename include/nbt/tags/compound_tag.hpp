#ifndef NBT_TAGS_COMPOUND_TAG_HPP
#define NBT_TAGS_COMPOUND_TAG_HPP

// nbt
#include "abstract_tag.hpp"

// STL
#include <vector>
#include <string>

namespace nbt
{

class CompoundTag : public AbstractTag
{
public:
    CompoundTag();
    CompoundTag(const CompoundTag &other);
    CompoundTag(CompoundTag &&other) noexcept;
    CompoundTag(const std::string &name);
    virtual ~CompoundTag();

    CompoundTag& operator=(const CompoundTag &other);
    CompoundTag& operator=(CompoundTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

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
    // !!! This functions removes the item from CompoundTag - transfers ownership !!!
    AbstractTag* takeAt(size_t index);

    AbstractTag* getChildByName(const std::string &name);
    const AbstractTag* getChildByName(const std::string &name) const;
    std::vector<AbstractTag*> getChildrenByName(const std::string &name) const;

    // !!! Do not delete these items - the CompoundTag keeps the ownership 
    //     -> use getValueCopy, if you want to modify the data !!!
    std::vector<AbstractTag*>& getValue();
    std::vector<AbstractTag*> getValueCopy() const;
    // !!! Takes ownership of value - do not delete the object after !!!
    void setValue(std::vector<AbstractTag*> &value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;
    void copy(const std::vector<AbstractTag*> &otherValue);

private:
    std::vector<AbstractTag*> m_value;
};

} // namespace nbt

#endif // NBT_TAGS_COMPOUND_TAG_HPP