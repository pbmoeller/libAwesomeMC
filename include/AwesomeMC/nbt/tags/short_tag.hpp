#ifndef NBT_TAGS_SHORT_TAG_HPP
#define NBT_TAGS_SHORT_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <string>

namespace nbt
{

class ShortTag : public AbstractTag
{
public:
    enum { Type = TagType::Short };

    ShortTag();
    ShortTag(const ShortTag &other);
    ShortTag(ShortTag &&other) noexcept;
    ShortTag(const std::string &name);
    ShortTag(int16_t value);
    ShortTag(const std::string &name, int16_t value);
    virtual ~ShortTag();

    ShortTag& operator=(const ShortTag &other);
    ShortTag& operator=(ShortTag &&other) noexcept;

    virtual AbstractTag* clone();

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    int16_t getValue() const;
    void setValue(int16_t value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    int16_t m_value;
};

} // namespace nbt

#endif // NBT_TAGS_SHORT_TAG_HPP