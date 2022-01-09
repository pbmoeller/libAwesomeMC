#ifndef AWESOMEMC_NBT_TAGS_COMPOUND_TAG_HPP
#define AWESOMEMC_NBT_TAGS_COMPOUND_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <vector>
#include <string>
#include <initializer_list>

namespace nbt
{

class CompoundTag : public AbstractTag
{
public:
    enum { Type = TagType::Compound };

    CompoundTag();
    CompoundTag(const CompoundTag &other);
    CompoundTag(CompoundTag &&other) noexcept;
    CompoundTag(const std::string &name);
    CompoundTag(std::initializer_list<AbstractTag*> items);
    CompoundTag(const std::string &name, std::initializer_list<AbstractTag*> items);
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
    // !!! Do not delete these items - the CompoundTag keeps the ownership !!!
    // Does range checking -> throws
    AbstractTag* at(size_t index);
    // !!! Do not delete these items - the CompoundTag keeps the ownership !!!
    // Does range checking -> throws
    const AbstractTag* at(size_t index) const;
    // !!! This functions removes the item from CompoundTag - transfers ownership !!!
    AbstractTag* takeAt(size_t index);

    // !!! Do not delete these items - the CompoundTag keeps the ownership !!!
    // Does not do range checking
    AbstractTag* operator[](const size_t index);
    // !!! Do not delete these items - the CompoundTag keeps the ownership !!!
    // Does not do range checking
    const AbstractTag* operator[](const size_t index) const;

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

#endif // AWESOMEMC_NBT_TAGS_COMPOUND_TAG_HPP