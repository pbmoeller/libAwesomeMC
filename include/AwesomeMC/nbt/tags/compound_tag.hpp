#ifndef AWESOMEMC_NBT_TAGS_COMPOUND_TAG_HPP
#define AWESOMEMC_NBT_TAGS_COMPOUND_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_vector_tag.hpp>

// STL
#include <vector>
#include <string>
#include <initializer_list>

namespace nbt
{

class CompoundTag : public AbstractVectorTag
{
public:
    enum { Type = static_cast<int>(TagType::Compound) };

public:
    // Constructors, Destructor & Assignments
    CompoundTag();
    CompoundTag(const CompoundTag &other);
    CompoundTag(CompoundTag &&other) noexcept;
    CompoundTag(const std::string &name);
    // !!! Takes ownership of items - do not delete the items after !!!
    CompoundTag(std::initializer_list<AbstractTag*> items);
    // !!! Takes ownership of items - do not delete the items after !!!
    CompoundTag(const std::string &name, std::initializer_list<AbstractTag*> items);
    virtual ~CompoundTag();

    CompoundTag& operator=(const CompoundTag &other);
    CompoundTag& operator=(CompoundTag &&other) noexcept;

    // Tag Stuff
    constexpr virtual TagType getType() const override {
        return TagType::Compound;
    }

    virtual AbstractTag* clone() const override;
    std::vector<unsigned char> getData(bool isListEntry) override;

    // CompoundTag
    bool hasChild(const std::string &name) const;
    AbstractTag* getChildByName(const std::string &name);
    const AbstractTag* getChildByName(const std::string &name) const;
    std::vector<AbstractTag*> getChildrenByName(const std::string &name) const;
};

} // namespace nbt

#endif // AWESOMEMC_NBT_TAGS_COMPOUND_TAG_HPP