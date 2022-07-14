#ifndef AWESOMEMC_NBT_TAGS_LIST_TAG_HPP
#define AWESOMEMC_NBT_TAGS_LIST_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_vector_tag.hpp>

// STL
#include <vector>
#include <string>
#include <initializer_list>

namespace amc
{

class ListTag : public AbstractVectorTag
{
public:
    enum { Type = static_cast<int>(TagType::List) };

public:
    // Constructors, Destructor & Assignments
    ListTag();
    ListTag(const ListTag &other);
    ListTag(ListTag &&other) noexcept;
    ListTag(const std::string &name);
    ListTag(TagType listType);
    // !!! Takes ownership of items - do not delete the items after !!!
    ListTag(TagType listType, std::initializer_list<AbstractTag*> items);
    ListTag(const std::string &name, TagType listType);
    // !!! Takes ownership of items - do not delete the items after !!!
    ListTag(const std::string &name, TagType listType, std::initializer_list<AbstractTag*> items);
    virtual ~ListTag();

    ListTag& operator=(const ListTag &other);
    ListTag& operator=(ListTag &&other) noexcept;

    // Tag Stuff
    constexpr virtual TagType getType() const override {
        return TagType::List;
    }
    constexpr TagType getListType() const {
        return m_listType;
    }
    bool setListType(TagType newType);

    virtual AbstractTag* clone() const override;
    std::vector<unsigned char> getData(bool isListEntry) override;

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

public:
    // Vector Operations
    virtual bool insert(int64_t index, AbstractTag *value) override;
    virtual bool pushBack(AbstractTag* value) override;

private:
    TagType m_listType;
};

} // namespace amc

#endif // AWESOMEMC_NBT_TAGS_LIST_TAG_HPP