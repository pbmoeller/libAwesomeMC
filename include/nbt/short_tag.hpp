#ifndef NBT_SHORT_TAG_HPP
#define NBT_SHORT_TAG_HPP

// nbt
#include "nbt/abstract_tag.hpp"

// STL
#include <string>

namespace nbt
{

class ShortTag : public AbstractTag
{
public:
    ShortTag();
    ShortTag(const ShortTag &other);
    ShortTag(ShortTag &&other) noexcept;
    ShortTag(const std::string &name);
    ShortTag(int16_t value);
    ShortTag(const std::string &name, int16_t value);
    virtual ~ShortTag();

    ShortTag& operator=(const ShortTag &other);
    ShortTag& operator=(ShortTag &&other) noexcept;

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

#endif // NBT_SHORT_TAG_HPP