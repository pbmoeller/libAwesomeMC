#ifndef AWESOMEMC_NBT_TAGS_FLOAT_TAG_HPP
#define AWESOMEMC_NBT_TAGS_FLOAT_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>

// STL
#include <string>

namespace nbt
{

class FloatTag : public AbstractTag
{
public:
    enum { Type = TagType::Float };

    FloatTag();
    FloatTag(const FloatTag &other);
    FloatTag(FloatTag &&other) noexcept;
    FloatTag(const std::string &name);
    FloatTag(float value);
    FloatTag(const std::string &name, float value);
    virtual ~FloatTag();

    FloatTag& operator=(const FloatTag &other);
    FloatTag& operator=(FloatTag &&other) noexcept;

    virtual AbstractTag* clone();

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

#endif // AWESOMEMC_NBT_TAGS_FLOAT_TAG_HPP