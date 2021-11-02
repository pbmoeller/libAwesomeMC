#ifndef NBT_TAGS_INT_TAG_HPP
#define NBT_TAGS_INT_TAG_HPP

// nbt
#include "abstract_tag.hpp"

// STL
#include <string>

namespace nbt
{

class IntTag : public AbstractTag
{
public:
    IntTag();
    IntTag(const IntTag &other);
    IntTag(IntTag &&other) noexcept;
    IntTag(const std::string &name);
    IntTag(int32_t value);
    IntTag(const std::string &name, int32_t value);
    virtual ~IntTag();

    IntTag& operator=(const IntTag &other);
    IntTag& operator=(IntTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    int32_t getValue() const;
    void setValue(int32_t value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    int32_t m_value;
};

} // namespace nbt

#endif // NBT_TAGS_INT_TAG_HPP