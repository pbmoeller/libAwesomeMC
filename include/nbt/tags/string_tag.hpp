#ifndef NBT_TAGS_STRING_TAG_HPP
#define NBT_TAGS_STRING_TAG_HPP

// nbt
#include "abstract_tag.hpp"

// STL
#include <string>

namespace nbt
{

class StringTag : public AbstractTag
{
public:
    enum { Type = TagType::String };

    StringTag();
    StringTag(const StringTag &other);
    StringTag(StringTag &&other) noexcept;
    StringTag(const std::string &value);
    StringTag(const std::string &name, const std::string &value);
    virtual ~StringTag();

    StringTag& operator=(const StringTag &other);
    StringTag& operator=(StringTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    std::string getValue() const;
    void setValue(std::string value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    std::string m_value;
};

} // namespace nbt

#endif // NBT_TAGS_STRING_TAG_HPP