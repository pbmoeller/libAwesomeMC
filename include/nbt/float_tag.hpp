#ifndef NBT_FLOAT_TAG_HPP
#define NBT_FLOAT_TAG_HPP

// nbt
#include "nbt/abstract_tag.hpp"

// STL
#include <string>

namespace nbt
{

class FloatTag : public AbstractTag
{
public:
    FloatTag();
    FloatTag(const FloatTag &other);
    FloatTag(FloatTag &&other) noexcept;
    FloatTag(const std::string &name);
    FloatTag(float value);
    FloatTag(const std::string &name, float value);
    virtual ~FloatTag();

    FloatTag& operator=(const FloatTag &other);
    FloatTag& operator=(FloatTag &&other) noexcept;

    constexpr virtual TagType getType() const override;

    std::vector<unsigned char> getData(bool isListEntry) override;

    float getValue() const;
    void setValue(float value);

protected:
    virtual bool isEqual(const AbstractTag &other) const override;

private:
    float m_value;
};

} // namespace nbt

#endif // NBT_FLOAT_TAG_HPP