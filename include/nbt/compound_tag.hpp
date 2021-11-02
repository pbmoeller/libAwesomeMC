#ifndef NBT_COMPOUND_TAG_HPP
#define NBT_COMPOUND_TAG_HPP

// nbt
#include "nbt/abstract_tag.hpp"

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
    bool insert(size_t index, AbstractTag *value);
    bool pushBack(AbstractTag* value);
    size_t size() const;
    AbstractTag* at(size_t index);
    const AbstractTag* at(size_t index) const;

    std::vector<AbstractTag*>& getValue();
    std::vector<AbstractTag*> getValueCopy() const;
    void setValue(std::vector<AbstractTag*> &value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;
    void copy(const std::vector<AbstractTag*> &otherValue);

private:
    std::vector<AbstractTag*> m_value;
};

} // namespace nbt

#endif // NBT_COMPOUND_TAG_HPP